#include "allocationdevices.h"

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>



AllocationDevices::AllocationDevices(QWidget*parent)
                                    :QWidget(parent)
{

    this->mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

//    scrollArea = new QScrollArea();
//    mainLayout->addWidget(this->scrollArea);
//    scrollArea->setWidgetResizable(true);

//    scrollWidget = new QWidget();
//    scrollArea->setWidget(this->scrollWidget);

//    scrollLayout = new QVBoxLayout();
//    scrollWidget->setLayout(this->scrollLayout);
//    scrollLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    this->gpWindowSettings = new QGroupBox("Настройки Поля");
    mainLayout->addWidget(gpWindowSettings);
    gpWindowSettings->setCheckable(true);
    settingsWindowLayout = new QGridLayout();
    gpWindowSettings->setLayout(settingsWindowLayout);
     QSqlQuery query("SELECT "
                    "nw_width, "
                    "nw_height, "
                    "nw_step_x "
                    "FROM TestLauncherSettings "
                    "WHERE id = 1");

    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    if (!query.next()) {
        QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

    int width_bd = query.value(0).toInt();
    int height_bd = query.value(1).toInt();
    int gridStep_bd = query.value(2).toInt();

    QLabel *labelWidthWindow = new QLabel("Ширина");
    settingsWindowLayout->addWidget(labelWidthWindow,0,0);
    
    this->editWidthWindow = new QLineEdit();
    settingsWindowLayout->addWidget(editWidthWindow,0,1);
    editWidthWindow->setText(QString::number(width_bd));


    
    QLabel *labelHeightWindow = new QLabel("Высота");
    settingsWindowLayout->addWidget(labelHeightWindow,1,0);
    
    this->editHeightWindow = new QLineEdit();
    settingsWindowLayout->addWidget(editHeightWindow,1,1);
    editHeightWindow->setText(QString::number(height_bd));

    
    
    QLabel *labelGridStep = new QLabel("Шаг Сетки");
    settingsWindowLayout->addWidget(labelGridStep);

    editGridStep = new QLineEdit();
    settingsWindowLayout->addWidget(editGridStep);
    editGridStep->setText(QString::number(gridStep_bd));
;
    

  //  paintWidget = new PaintWidget(width_bd,height_bd,gridStep_bd);
   // mainLayout->addWidget(paintWidget);
// Если будешь возвращаться к этому классу, то не забудь разблокировать и подключить сигналы ниже


    //Сигнал для связи с исправлением ширины, высоты и шага сетки
    connect(editWidthWindow,SIGNAL(editingFinished()),this, SLOT(updateWidthWindow()));
    connect(editHeightWindow,SIGNAL(editingFinished()),this, SLOT(updateHeightWindow()));
    connect(editGridStep,SIGNAL(editingFinished()),this, SLOT(updateGridStep()));
    //connect(this,SIGNAL(widthChanged(int)),paintWidget,SLOT(setWidth(int)));
    //connect(this,SIGNAL(heightChanged(int)),paintWidget,SLOT(setHeight(int)));
   // connect(this,SIGNAL(gridChanged(int)),paintWidget,SLOT(setGridStep(int)));



}


void AllocationDevices::updateWidthWindow()
{
    int width = editWidthWindow->text().toInt();
    QSqlQuery query;
    query.exec("UPDATE TestLauncherSettings "
               "SET nw_width = '" + QString::number(width) +"'"
               "WHERE id = 1");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    emit widthChanged(width);


} 

void AllocationDevices::updateHeightWindow()
{
    int height = editHeightWindow->text().toInt();
    QSqlQuery query;
    query.exec("UPDATE TestLauncherSettings "
               "SET nw_height = '" + QString::number(height) +"'"
               "WHERE id = 1");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    emit heightChanged(height);


}

void AllocationDevices::updateGridStep()
{
    int gridStep = editGridStep->text().toInt();
    QSqlQuery query;
    query.exec("UPDATE TestLauncherSettings "
               "SET nw_step_x = '" + QString::number(gridStep) +" '"
               "WHERE id = 1");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    emit gridChanged(gridStep);

}









