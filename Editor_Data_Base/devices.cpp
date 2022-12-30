#include "devices.h"




Devices::Devices(QWidget *parent)
    :QWidget(parent)
{
        mainLayout = new QVBoxLayout();
        setLayout(this->mainLayout);

        scrollArea = new QScrollArea();
        mainLayout->addWidget(this->scrollArea);
        scrollArea->setWidgetResizable(true);

        scrollWidget = new QWidget();
        scrollArea->setWidget(this->scrollWidget);

        scrollLayout = new QVBoxLayout();
        scrollWidget->setLayout(this->scrollLayout);
        scrollLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

        setWindowTitle("Перечень устройств");
        setMinimumWidth(800);


        btnSave = new QPushButton("Сохранить");
        mainLayout->addWidget(this->btnSave);
        btnSave->setStyleSheet("background-color: #56887D; color: white");

        buttonAdd = new QPushButton("Добавить устройство");
        buttonAdd->setStyleSheet("background-color: Cornsilk;");
        mainLayout->addWidget(this->buttonAdd);
        buttonAdd->setFocusPolicy(Qt::NoFocus);



        QSqlQuery query("SELECT id "
                        "FROM Devices");
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        while (query.next()) {
            Device *deviceEdit = new Device(query.value(0).toInt());
            deviceEdits.push_back(deviceEdit);
            scrollLayout->addWidget(deviceEdit);
            connect(deviceEdit, SIGNAL(wasDeleted(Device *)), this, SLOT(remove(Device *))); // Придумать как удалять несколько полей, а не по одному
            connect(deviceEdit, SIGNAL(deviceNameChanged(int, const QString &)), this, SLOT(setNewDeviceName(int, const QString &)));
            connect(this->btnSave, SIGNAL(clicked()), deviceEdit , SLOT(slotSave()));

        }
        connect(this->buttonAdd, SIGNAL(clicked()), this, SLOT(addDeviceEdit()));
}
void Devices::setNewUnitName(int id, const QString &name)
{
    emit unitNameChanged(id, name);
}

void Devices::updateUnits()
{
    emit unitsChanged();
}

void Devices::remove(Device *deviceEdit)
{
    QVector <Device *>::iterator it = std::find(
            this->deviceEdits.begin(),
            this->deviceEdits.end(), deviceEdit);
    if (it != this->deviceEdits.end()) {
        this->deviceEdits.erase(it);
        this->scrollLayout->removeWidget(deviceEdit);
        delete deviceEdit;

        emit updated();
    }
    else {
        throw DeleteException();
    }
}

void Devices::addDeviceEdit()
{
    Device *deviceEdit = new Device();
    this->deviceEdits.push_back(deviceEdit);
    this->scrollLayout->addWidget(deviceEdit);
    connect(deviceEdit, SIGNAL(wasDeleted(Device *)), this, SLOT(remove(Device *)));
    connect(deviceEdit, SIGNAL(deviceNameChanged(int, const QString &)), this, SLOT(setNewDeviceName(int, const QString &)));
    connect(this->btnSave, SIGNAL(clicked()), deviceEdit , SLOT(slotSave()));

    emit updated();
}

void Devices::setNewDeviceName(int id, const QString &name)
{
    emit deviceNameChanged(id, name);
}
