/*=========================================================================

  Library:   CTK

  Copyright (c) Isomics, Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

// std includes
#include <iostream>

// Qt includes
#include <QBuffer>
#include <QByteArray>
#include <QDebug>

// ctkWidgets includes
// ctkCommandLineModulesCore includes
#include "ctkCmdLineModuleDescription.h"
#include "ctkCmdLineModuleFrontend.h"
#include "ctkCmdLineModuleFrontendQtGui.h"
#include "ctkCmdLineModuleReference.h"
#include "ctkCmdLineModuleQtUiLoader.h"
#include "ctkCmdLineModuleXmlParser_p.h"
#include "ctkCmdLineModuleXslTransform.h"

// ctkCommandLineModulesWidgets includes
#include "ctkCmdLineModuleWidget.h"

//logger
#include <ctkLogger.h>
static ctkLogger logger("org.commontk.CommandLineModules.Widgets.ctkCmdLineModuleWidget");

class ctkCmdLineModuleWidgetFrontendQtGui;

//----------------------------------------------------------------------------
class ctkCmdLineModuleWidgetPrivate
{
public:
  ctkCmdLineModuleWidget* const q_ptr;
  Q_DECLARE_PUBLIC(ctkCmdLineModuleWidget);

  ctkCmdLineModuleWidgetPrivate(ctkCmdLineModuleWidget* );
  ~ctkCmdLineModuleWidgetPrivate();

  QString xml;
  ctkCmdLineModuleDescription moduleDescription;
  ctkCmdLineModuleReference *moduleReference;
  QWidget *moduleWidget;

  ctkCmdLineModuleWidgetFrontendQtGui *qtGui;
};

//----------------------------------------------------------------------------
class ctkCmdLineModuleWidgetFrontendQtGui : public ctkCmdLineModuleFrontendQtGui
{
public:
  ctkCmdLineModuleWidgetFrontendQtGui(const ctkCmdLineModuleReference& moduleRef)
    : ctkCmdLineModuleFrontendQtGui(moduleRef)
    {
    this->widgetPrivates = 0;
    };
  virtual ~ctkCmdLineModuleWidgetFrontendQtGui() {};

  void setPrivates(ctkCmdLineModuleWidgetPrivate* privates) {
    this->widgetPrivates = privates;
  };

  virtual QObject *guiHandle() const;

  ctkCmdLineModuleWidgetPrivate *widgetPrivates;
};

//----------------------------------------------------------------------------
// ctkCmdLineModuleWidgetFrontendQtGui methods

QObject *ctkCmdLineModuleWidgetFrontendQtGui::guiHandle() const
{
  // Reimplemented from superclass
  // TODO: some of this can be factored out

  if (!widgetPrivates)
    {
    return 0;
    }

  QBuffer input;
  QByteArray xmlByteArray(this->widgetPrivates->xml.toStdString().c_str());
  input.setData(xmlByteArray);

  QBuffer uiForm;
  uiForm.open(QIODevice::ReadWrite);

  ctkCmdLineModuleXslTransform* xslTransform = this->xslTransform();
  xslTransform->setInput(&input);
  xslTransform->setOutput(&uiForm);

  if (!xslTransform->transform())
  {
    // maybe throw an exception
    qCritical() << xslTransform->errorString();
    return 0;
  }

  QUiLoader* uiLoader = this->uiLoader();
#ifdef CMAKE_INTDIR
  QString appPath = QCoreApplication::applicationDirPath();
  if (appPath.endsWith(CMAKE_INTDIR))
  {
    uiLoader->addPluginPath(appPath + "/../designer");
  }
#endif
  this->widgetPrivates->moduleWidget = uiLoader->load(&uiForm);
  return this->widgetPrivates->moduleWidget;
}

//----------------------------------------------------------------------------
// ctkCmdLineModuleWidgetPrivate methods

ctkCmdLineModuleWidgetPrivate::ctkCmdLineModuleWidgetPrivate(ctkCmdLineModuleWidget* parent): q_ptr(parent)
{
  this->moduleReference = 0;
}

ctkCmdLineModuleWidgetPrivate::~ctkCmdLineModuleWidgetPrivate()
{
  if (moduleReference)
    {
    delete this->moduleReference;
    }
}


//----------------------------------------------------------------------------
// ctkCmdLineModuleWidget methods

//----------------------------------------------------------------------------
ctkCmdLineModuleWidget::ctkCmdLineModuleWidget(QWidget* _parent):Superclass(_parent),
    d_ptr(new ctkCmdLineModuleWidgetPrivate(this))
{
  Q_D(ctkCmdLineModuleWidget);

  //d->setupUi(this);
}

//----------------------------------------------------------------------------
ctkCmdLineModuleWidget::~ctkCmdLineModuleWidget()
{
  Q_D(ctkCmdLineModuleWidget);
}

//----------------------------------------------------------------------------
void ctkCmdLineModuleWidget::setXml(const QString& xml)
{
  Q_D(ctkCmdLineModuleWidget);
  d->xml = xml;

  if (d->moduleReference)
    {
    delete d->moduleReference;
    }

  // create a QBuffer as the QIODevice for the xml parser
  QByteArray xmlByteArray(xml.toStdString().c_str());
  QBuffer xmlBuffer;
  xmlBuffer.setData(xmlByteArray);

  // parse the xml to get a module description
  ctkCmdLineModuleXmlParser xmlParser(&xmlBuffer, &d->moduleDescription);
  xmlParser.doParse();

  // make a qt gui matching the module description
  d->moduleReference = new ctkCmdLineModuleReference();
  d->qtGui = new ctkCmdLineModuleWidgetFrontendQtGui(*d->moduleReference);
  d->qtGui->setPrivates(d);
  d->moduleWidget = qobject_cast<QWidget *>(d->qtGui->guiHandle());
  if (d->moduleWidget)
    {
    qDebug() << "Widget Exists";
    d->moduleWidget->setParent(this);
    }
  else
    {
    qDebug() << "Widget missing";
    }

  // TODO: check for exceptions
}
//----------------------------------------------------------------------------
const QString ctkCmdLineModuleWidget::xml()
{
  Q_D(ctkCmdLineModuleWidget);

  return d->xml;
}

//----------------------------------------------------------------------------
QStringList ctkCmdLineModuleWidget::names()
{
  Q_D(ctkCmdLineModuleWidget);

  QStringList result;
  result << "Test Result";
  return result;
}

//----------------------------------------------------------------------------
QWidget *ctkCmdLineModuleWidget::widget(const QString name)
{
  Q_D(ctkCmdLineModuleWidget);

  // TODO - get widget for named parameter
  return 0;
}

//----------------------------------------------------------------------------
QVariant ctkCmdLineModuleWidget::value(const QString name)
{

  Q_D(ctkCmdLineModuleWidget);

  return "Test Result";
}
