/*=========================================================================

  Library:   CTK

  Copyright (c) Isomics Inc.

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

#ifndef __ctkCmdLineModuleWidget_h
#define __ctkCmdLineModuleWidget_h

// Qt includes 
#include <QWidget>

#include "ctkCommandLineModulesWidgetsExport.h"

class ctkCmdLineModuleWidgetPrivate;
class ctkThumbnailLabel;
class QModelIndex;

/// \ingroup CommandLineModules_Widgets
class CTK_COMMANDlINEMODULES_WIDGETS_EXPORT ctkCmdLineModuleWidget : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(QString xml READ xml WRITE setXml)

public:
  typedef QWidget Superclass;
  explicit ctkCmdLineModuleWidget(QWidget* parent=0);
  virtual ~ctkCmdLineModuleWidget();

  /// The XML description that defines the information
  /// about the widget contents
  /// @see ctkCmdLineModuleReference
  void setXml(const QString xml);
  const QString xml();

  /// The names of all the widgets
  QStringList names();

  /// The QWidget associated with the name
  QWidget widget(QString name);

  /// The current value of the widget with a given name
  QVariant value(QString name);

public Q_SLOTS:

Q_SIGNALS:
  /// Emited when ...

protected:
    QScopedPointer<ctkCmdLineModuleWidgetPrivate> d_ptr;
protected Q_SLOTS:

private Q_SLOTS:

private:
  Q_DECLARE_PRIVATE(ctkCmdLineModuleWidget);
  Q_DISABLE_COPY(ctkCmdLineModuleWidget);
};

#endif
