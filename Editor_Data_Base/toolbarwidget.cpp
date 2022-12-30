
#include "toolbarwidget.h"

ToolBarWidget::ToolBarWidget(QWidget *parent)
    : QWidget(parent)
{

    mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    toolBar = new QToolBar ();
    toolBar->setMovable(true);
    toolBar->setStyleSheet("QToolBar{background:silver;}");
    toolBar->addAction(QIcon(":/logo/createTab.png"),"Создать вкладку",this, SLOT(slotAddTab()));
    toolBar->addSeparator();
    QAction *doQueryAction = new QAction(QIcon(":/logo/do1.png"),"Выполнить");
    //toolBar->addAction(QIcon(":/logo/do1.png"),"Выполнить",this,SLOT(slotDoQuery(CodeEditor*)));
    toolBar->addAction(doQueryAction);

    tabWidget = new QTabWidget();
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    tabWidget->setTabShape(QTabWidget::Rounded);

    mainLayout->addWidget(toolBar);
    mainLayout->addWidget(tabWidget);

    connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(slotCloseTab()));
    connect(doQueryAction, SIGNAL(triggered()), this, SLOT(slotDoQuery()));
    //connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(slotDoQuery(CodeEditor*)));

}

QString ToolBarWidget::tabName()
{

    //static int tabId = 1;
    //return "SQl " + QString::number(tabId++);
    return "SQL " + QString::number(tabWidget->count()+1);
}

void ToolBarWidget::slotAddTab()
{
    codeEditor = new CodeEditor();
    //this->tabs.push_back(codeEditor);
    tabWidget->addTab(codeEditor,tabName());

}

void ToolBarWidget::slotDoQuery()
{
    CodeEditor *currentWidget =  qobject_cast<CodeEditor*>(tabWidget->currentWidget());
    queryText = currentWidget->toPlainText().replace(QString("\n"),QString(" "));



    QSqlQuery query;
    query.exec(queryText);

    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    if (!query.next()) {
        QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
   // qDebug()<< "query.exec(" << queryText << ")" << endl;
}



void ToolBarWidget::slotCloseTab()
{
    delete tabWidget->currentWidget();
}


