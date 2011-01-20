/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.commontk.org/LICENSE

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

// Qt includes
#include <QApplication>
#include <QTreeView>
#include <QSettings>
#include <QDir>
#include <QPushButton>

// CTK widget includes
#include <ctkDICOMQueryRetrieveWidget.h>

// ctkDICOMCore includes
#include "ctkDICOM.h"
#include "ctkDICOMModel.h"
#include "ctkDICOMIndexer.h"

// Logger
#include "ctkLogger.h"

// STD includes
#include <iostream>

int main(int argc, char** argv)
{
  ctkLogger::configure();
  QApplication app(argc, argv);

  // for settings
  app.setOrganizationName("commontk");
  app.setOrganizationDomain("commontk.org");
  app.setApplicationName("ctkDICOM");

  QSettings settings;
  QString databaseDirectory;

  // set up the database 
  // - use command line argument if one is given, otherwise use default
  if (argc > 1)
    {
    QString directory(argv[1]);
    settings.setValue("DatabaseDirectory", directory);
    settings.sync();
    }

  if ( settings.value("DatabaseDirectory", "") == "" )
  {
    databaseDirectory = QString("./ctkDICOM-Database");
    std::cerr << "No DatabaseDirectory on command line or in settings.  Using \"" << databaseDirectory.toLatin1().data() << "\".\n";
  } else
  {
    databaseDirectory = settings.value("DatabaseDirectory", "").toString();
  }

  // create the database directory
  QDir qdir(databaseDirectory);
  if ( !qdir.exists(databaseDirectory) ) 
  {
    if ( !qdir.mkpath(databaseDirectory) )
    {
      std::cerr << "Could not create database directory \"" << databaseDirectory.toLatin1().data() << "\".\n";
      return EXIT_FAILURE;
    }
  }


  // load the database
  QString databaseFileName = databaseDirectory + QString("/ctkDICOM.sql");

  ctkDICOM myCTK;
  try { myCTK.openDatabase( databaseFileName ); }
  catch (std::exception e)
  {
    std::cerr << "Database error: " << qPrintable(myCTK.GetLastError()) << "\n";
    myCTK.closeDatabase();
    return EXIT_FAILURE;
  }

  // set up the data model for the database
  // - this is a map from sql database to qt callable representation
  ctkDICOMModel model;
  model.setDatabase(myCTK.database());
  
  // create the query/retrieve widget
  // - associate the tree view with the database model
  ctkDICOMQueryRetrieveWidget queryRetrieve;
  QTreeView *treeView = queryRetrieve.findChild<QTreeView *>("treeView");
  if (!treeView)
    {
    std::cerr << "Could not access tree view from QueryRetrieve widget\n";
    return EXIT_FAILURE;
    }
  treeView->setModel(&model);

  // connect the Add button for the local database
  QPushButton *addButton = queryRetrieve.findChild<QPushButton *>("addToDatabase");
  //TODO: this should be moved into the ctkLibrary widget: connect(addButton, SIGNAL("clicked()"), this

  queryRetrieve.show();
  queryRetrieve.raise();
  return app.exec();
}
