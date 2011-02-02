#include <QDebug>
#include <QTreeView>
#include <QTabBar>
#include <QSettings>

// ctkDICOMWidgets includes
#include "ctkDICOMLibraryWidget.h"
#include "ui_ctkDICOMLibraryWidget.h"

#include <ctkLogger.h>
static ctkLogger logger("org.commontk.DICOM.Widgets.ctkDICOMLibraryWidget");

//----------------------------------------------------------------------------
class ctkDICOMLibraryWidgetPrivate: public Ui_ctkDICOMLibraryWidget
{
public:
  ctkDICOMLibraryWidgetPrivate(){}
};

//----------------------------------------------------------------------------
// ctkDICOMLibraryWidgetPrivate methods


//----------------------------------------------------------------------------
// ctkDICOMLibraryWidget methods

//----------------------------------------------------------------------------
ctkDICOMLibraryWidget::ctkDICOMLibraryWidget(QWidget* _parent):Superclass(_parent), 
  d_ptr(new ctkDICOMLibraryWidgetPrivate)
{
  Q_D(ctkDICOMLibraryWidget);
  
  d->setupUi(this);

  d->results->disableCloseOnTab(0);
  connect(d->sqlDirectory, SIGNAL(directoryChanged(const QString&)), this, SLOT(onDatabaseDirectoryChanged(const QString&)));
  connect(d->addToDatabase, SIGNAL(clicked()), this, SLOT(onAddToDatabase()));

  QSettings settings;
  if ( settings.value("DatabaseDirectory", "") != "" )
  {
    d->sqlDirectory->setDirectory(settings.value("DatabaseDirectory").toString());
  }

}

//----------------------------------------------------------------------------
ctkDICOMLibraryWidget::~ctkDICOMLibraryWidget()
{
}

//----------------------------------------------------------------------------
void ctkDICOMLibraryWidget::onDatabaseDirectoryChanged(const QString& directory)
{
  QSettings settings;
  settings.setValue("DatabaseDirectory", directory);
  settings.sync();
}

//----------------------------------------------------------------------------
void ctkDICOMLibraryWidget::onAddToDatabase()
{
  Q_D(ctkDICOMLibraryWidget);

  //d->
}

//----------------------------------------------------------------------------
void ctkDICOMLibraryWidget::processQuery()
{
  Q_D(ctkDICOMLibraryWidget);

  d->serverNodeWidget->populateQuery();
  d->queryWidget->populateQuery();

  QTreeView *queryResults = new QTreeView;
  int tabIndex = d->results->addTab(queryResults, tr("Query Results"));
  d->results->setCurrentIndex(tabIndex);
}

