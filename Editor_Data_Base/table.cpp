#include "table.h"

Table::Table(QSqlDatabase *db,QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    tvAD = new QTableView();
    modelAD = new QSqlRelationalTableModel(this,*db);
    modelAD->setTable("AllocationDevices");
    modelAD->setRelation(1, QSqlRelation("Groups","id","name"));
    modelAD->setRelation(2, QSqlRelation("Devices","id","name"));
    modelAD->setHeaderData(1, Qt::Horizontal, QObject::tr("group_name"));
    modelAD->setHeaderData(2, Qt::Horizontal, QObject::tr("device_name"));
    modelAD->select();
    tvAD->setModel(modelAD);
    tvAD->setItemDelegate(new QSqlRelationalDelegate(tvAD));
    mainLayout->addWidget(tvAD);
    this->setLayout(mainLayout);
    mainLayout->addWidget(tvAD);

    btnRefresh = new QPushButton("Записать данные");
    btnRefresh->setStyleSheet("background-color: #56887D; color: white");
    mainLayout->addWidget(btnRefresh);
    connect(btnRefresh,SIGNAL(clicked()),SLOT(slotRefreshTable()));

}

void Table::slotRefreshTable()
{
    modelAD->submitAll();
}





