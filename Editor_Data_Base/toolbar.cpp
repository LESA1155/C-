#include "toolbar.h"

ToolBar::ToolBar(QWidget *parent)
    : QMainWindow(parent)
{

    addToolBar((Qt::TopToolBarArea,createToolBar()));
}

QToolBar *ToolBar::createToolBar()
{
    QToolBar *pToolBar = new QToolBar("Панель инструментов");
    pToolBar->addAction(QPixmap(":/createTab.png"),"Создать вкладку",this,SLOT(print()));
            return  pToolBar;

}
