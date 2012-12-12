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
#include <QAction>
#include <QCheckBox>
#include <QDebug>
#include <QMetaType>
#include <QModelIndex>
#include <QPersistentModelIndex>
#include <QProgressDialog>
#include <QSettings>
#include <QSlider>
#include <QTabBar>
#include <QTimer>
#include <QTreeView>

// ctkWidgets includes
#include "ctkDirectoryButton.h"
#include "ctkFileDialog.h"

// ctkCommandLineModulesCore includes
#include "ctkCmdLineModuleReference.h"

// ctkCommandLineModulesWidgets includes
#include "ctkCmdLineModuleWidget.h"

//logger
#include <ctkLogger.h>
static ctkLogger logger("org.commontk.CommandLineModules.Widgets.ctkCmdLineModuleWidget");

Q_DECLARE_METATYPE(QPersistentModelIndex);

//----------------------------------------------------------------------------
class ctkCmdLineModuleWidgetPrivate
{
public:
  ctkCmdLineModuleWidget* const q_ptr;
  Q_DECLARE_PUBLIC(ctkCmdLineModuleWidget);

  ctkCmdLineModuleWidgetPrivate(ctkCmdLineModuleWidget* );
  ~ctkCmdLineModuleWidgetPrivate();

  ctkCmdLineModuleReference moduleReference;
  QString xml;
};

//----------------------------------------------------------------------------
// ctkCmdLineModuleWidgetPrivate methods

ctkCmdLineModuleWidgetPrivate::ctkCmdLineModuleWidgetPrivate(ctkCmdLineModuleWidget* parent): q_ptr(parent){
}

ctkCmdLineModuleWidgetPrivate::~ctkCmdLineModuleWidgetPrivate()
{
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
QVariant ctkCmdLineModuleWidget::value(QString name)
{

  Q_D(ctkCmdLineModuleWidget);

  return "Test Result";
}
