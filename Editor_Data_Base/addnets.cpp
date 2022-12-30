#include "addnets.h"

AddNets::AddNets( QWidget *parent)
    :QWidget(parent)
{
    pMainLayout = new QVBoxLayout();
    this->setLayout(pMainLayout);

    scrollArea = new QScrollArea();
    pMainLayout->addWidget(scrollArea);
    scrollArea->setWidgetResizable(true);

    scrollWidget = new QWidget();
    scrollArea->setWidget(scrollWidget);

    scrollLayout = new QVBoxLayout();
    scrollWidget->setLayout(scrollLayout);

    btnSave = new QPushButton("Сохранить");
    pMainLayout->addWidget(btnSave);
    btnSave->setStyleSheet("background-color: #56887D; color: white");

    buttonAdd   = new QPushButton("Добавить сеть");
    pMainLayout->addWidget(buttonAdd);
    buttonAdd->setStyleSheet("background-color: Cornsilk;");

    setWindowTitle("Сети");


    QSqlQuery query("SELECT AddNets.id, defective_device_allocation_id FROM AddNets");

    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty()))
    {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    while(query.next())
    {
        AddNet *net = new AddNet(query.value(0).toInt());
        nets.push_back(net);
        scrollLayout->addWidget(net);
        connect(net,SIGNAL(wasDeleted(AddNet*)),this,SLOT(slotRemove(AddNet*)));
        connect(this->btnSave, SIGNAL(clicked()), net , SLOT(slotSave()));
    }

        connect(buttonAdd,SIGNAL(clicked()),this,SLOT(slotAddNet()));
}

AddNets::~AddNets()
{
//    delete pMainLayout;
//    delete scrollArea;
//    delete scrollWidget;
//    delete buttonAdd;
}

void AddNets::slotSetNewName(int id, QString &name)
{
    emit roomNameChanged(id,name);
}

void AddNets::slotAddNet()
{
    // Создать запрос и добавить еще один параметр с id AllocationDevices. Который буду передавать и считывать в другом классе.
    AddNet *net = new AddNet();
    nets.push_back(net);
    scrollLayout->addWidget(net);
    connect(net, SIGNAL(wasDeleted(AddNet *)), this, SLOT(slotRemove(AddNet *)));
     connect(this->btnSave, SIGNAL(clicked()), net , SLOT(slotSave()));
    this->scrollArea->verticalScrollBar()->setSliderDown(true);

    //connect(net,SIGNAL(roomNameChangeed(int,QString)),this,SLOT(slotSetNewName(int, QString))); [Возможно ненужно вообще]
    //emit sigUpdate();
}

void AddNets::slotRemove(AddNet *net)
{
    QVector <AddNet*>::iterator it =std::find(nets.begin(),nets.end(),net);
    if(it!=nets.end())
    {
        nets.erase(it);
        scrollLayout->removeWidget(net);
        delete net;
       //emit sigUpdate();
    }
    else
    {
        throw DeleteException();
    }
}


