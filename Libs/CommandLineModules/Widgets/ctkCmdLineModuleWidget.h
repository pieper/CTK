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
  /// Emited when n
  void databaseDirectoryChanged(const QString&);
  /// Emited when query/retrieve operation has happened
  void queryRetrieveFinished();
  /// Emited when the directory import operation has completed
  void directoryImported();

protected:
    QScopedPointer<ctkCmdLineModuleWidgetPrivate> d_ptr;
protected Q_SLOTS:
    void onImportDirectory(QString directory);
    void onModelSelected(const QModelIndex& index);

    /// To be called when a thumbnail in thumbnail list widget is selected
    void onThumbnailSelected(const ctkThumbnailLabel& widget);

    /// To be called when a thumbnail in thumbnail list widget is double-clicked
    void onThumbnailDoubleClicked(const ctkThumbnailLabel& widget);

    /// To be called when previous and next buttons are clicked
    void onNextImage();
    void onPreviousImage();
    void onNextSeries();
    void onPreviousSeries();
    void onNextStudy();
    void onPreviousStudy();

    /// To be called when dialog finishes
    void onQueryRetrieveFinished();

    /// To be called when an entry of the tree list is collapsed
    void onTreeCollapsed(const QModelIndex& index);

    /// To be called when an entry of the tree list is expanded
    void onTreeExpanded(const QModelIndex& index);

    /// To be called when auto-play checkbox state changed
    void onAutoPlayCheckboxStateChanged(int state);

    /// Called by timer for auto-play functionality
    void onAutoPlayTimer();

    /// To be called when the value of thumbnail size slider bar is changed
    void onThumbnailWidthSliderValueChanged(int val);

    /// To be called when search parameters in query widget changed
    void onSearchParameterChanged();

    /// To be called after image preview displayed an image
    void onImagePreviewDisplayed(int imageID, int count);

private Q_SLOTS:

    void onSearchPopUpButtonClicked();

    void onSearchWidgetTopLevelChanged(bool topLevel);

private:
  Q_DECLARE_PRIVATE(ctkCmdLineModuleWidget);
  Q_DISABLE_COPY(ctkCmdLineModuleWidget);
};

#endif
