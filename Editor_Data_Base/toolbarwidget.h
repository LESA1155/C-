#ifndef SQL_H
#define SQL_H

#include <QObject>
#include <QtWidgets>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QToolBar>
#include <QPixmap>
#include <QMenu>
#include <QAction>
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include <codeeditor.h>



class ToolBarWidget : public QWidget
{

    Q_OBJECT
public:
    ToolBarWidget(QWidget *parent = 0);

private:
    QVBoxLayout *mainLayout;
    QToolBar * toolBar;
    QTabWidget *tabWidget;
    CodeEditor *codeEditor;
    QString queryText;
    std::vector <CodeEditor *> tabs;

    QString tabName();







private slots:
    void  slotAddTab();
    void  slotCloseTab();
    void slotDoQuery();
    //CodeEditor queryCodeEditor(CodeEditor *currenCodeEditor);




};

#endif // SQL_H
