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
#include "ctkCmdLineModuleReference.h"
#include "ctkCmdLineModuleXmlParser_p.h"
#include "ctkCmdLineModuleFrontendQtGui.h"

// ctkCommandLineModulesWidgets includes
#include "ctkCmdLineModuleWidget.h"

//logger
#include <ctkLogger.h>
static ctkLogger logger("org.commontk.CommandLineModules.Widgets.ctkCmdLineModuleWidget");

class ctkCmdLineModuleProxyReference;

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
  ctkCmdLineModuleProxyReference *moduleReference;
  QObject *moduleWidget;

  ctkCmdLineModuleFrontendQtGui *qtGui;
};

//----------------------------------------------------------------------------
class ctkCmdLineModuleProxyReference : public ctkCmdLineModuleReference
{
public:
  ctkCmdLineModuleProxyReference(ctkCmdLineModuleWidgetPrivate* privates) {
    this->widgetPrivates = privates;
  }
  ~ctkCmdLineModuleProxyReference() {};

  operator bool() const {
    return !this->widgetPrivates->xml.isNull();
  };

  ctkCmdLineModuleDescription description() const {
    return this->widgetPrivates->moduleDescription;
  };

  QByteArray rawXmlDescription() const {
    return QByteArray(this->widgetPrivates->xml.toStdString().c_str());
  };

  QString xmlValidationErrorString() const {
    // TODO
    return "";
  };

  ctkCmdLineModuleBackend* backend() const {
    return 0;
  };


  ctkCmdLineModuleWidgetPrivate *widgetPrivates;
};


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
  d->moduleReference = new ctkCmdLineModuleProxyReference(d);
  d->qtGui = new ctkCmdLineModuleFrontendQtGui(*d->moduleReference);

  d->moduleWidget = d->qtGui->guiHandle();
  if (d->moduleWidget)
    {
    d->moduleWidget->setParent(this);
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

  // TOOD - get widget for named parameter
}

//----------------------------------------------------------------------------
QVariant ctkCmdLineModuleWidget::value(const QString name)
{

  Q_D(ctkCmdLineModuleWidget);

  return "Test Result";
}
