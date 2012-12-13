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

static QString xml = "<?xml version=\"1.0\" encoding=\"utf-8\"?> \
<executable> \
  <category>Filtering.Arithmetic</category> \
  <title>Add Scalar Volumes</title> \
  <description><![CDATA[Adds two images. Although all image types are supported on input, only signed types are produced. The two images do not have to have the same dimensions.]]></description> \
  <version>0.1.0.$Revision$(alpha)</version> \
  <documentation-url>http://slicer.org/slicerWiki/index.php/Documentation/4.2/Modules/Add</documentation-url> \
  <license/> \
  <contributor>Bill Lorensen (GE)</contributor> \
  <acknowledgements><![CDATA[This work is part of the National Alliance for Medical Image Computing (NAMIC), funded by the National Institutes of Health through the NIH Roadmap for Medical Research, Grant U54 EB005149.]]></acknowledgements> \
  <parameters> \
    <label>IO</label> \
    <description><![CDATA[Input/output parameters]]></description> \
    <image> \
      <name>inputVolume1</name> \
      <label>Input Volume 1</label> \
      <channel>input</channel> \
      <index>0</index> \
      <description><![CDATA[Input volume 1]]></description> \
    </image> \
    <image> \
      <name>inputVolume2</name> \
      <label>Input Volume 2</label> \
      <channel>input</channel> \
      <index>1</index> \
      <description><![CDATA[Input volume 2]]></description> \
    </image> \
    <image> \
      <name>outputVolume</name> \
      <label>Output Volume</label> \
      <channel>output</channel> \
      <index>2</index> \
      <description><![CDATA[Volume1 + Volume2]]></description> \
    </image> \
  </parameters> \
  <parameters> \
    <label>Controls</label> \
    <description><![CDATA[Control how the module operates]]></description> \
    <integer-enumeration> \
      <name>order</name> \
      <label>Interpolation order</label> \
      <default>1</default> \
      <element>0</element> \
      <element>1</element> \
      <element>2</element> \
      <element>3</element> \
      <longflag>order</longflag> \
      <description><![CDATA[Interpolation order if two images are in different coordinate frames or have different sampling.]]></description> \
    </integer-enumeration> \
  </parameters> \
</executable>\
";

int ctkCmdLineModuleWidgetTest1( int argc, char * argv [] )
{
  QApplication app(argc, argv);
  
  ctkCmdLineModuleWidget cliWidget;

  cliWidget.setXml(xml);

  cliWidget.show();
  cliWidget.raise();

  if (argc <= 1 || QString(argv[1]) != "-I")
    {
    QTimer::singleShot(500, &app, SLOT(quit()));
    }
  return app.exec();
}

