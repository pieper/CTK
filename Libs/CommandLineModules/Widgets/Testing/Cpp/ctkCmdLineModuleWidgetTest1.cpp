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

// Qt includes
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QTimer>

// ctkCommandLineModulesWidgets includes
#include "ctkCmdLineModuleWidget.h"

// STD includes
#include <iostream>

int ctkCmdLineModuleWidgetTest1( int argc, char * argv [] )
{
  QApplication app(argc, argv);
  
  ctkCmdLineModuleWidget cliWidget;
  
  cliWidget.show();

  if (argc <= 1 || QString(argv[1]) != "-I")
    {
    QTimer::singleShot(200, &app, SLOT(quit()));
    }
  return app.exec();
}
