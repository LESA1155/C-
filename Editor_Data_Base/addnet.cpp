#include "addnet.h"

AddNet::AddNet(int id, QWidget *parent) : QGroupBox(parent)

{

    int netIndex;
    QString NameLog;

    int x0;
    int x1;
    int x2;
    int x3;
    int x4;
    int y0;
    int y1;
    int y2;
    int y3;
    int y4;

    if (id<0)
    {
        QSqlQuery selectQuery;
        selectQuery.exec("SELECT Devices.id, AllocationDevices.id FROM Devices INNER JOIN AllocationDevices ON AllocationDevices.device_id = Devices.id");
        selectQuery.next();
        deviceId =  selectQuery.value(0).toInt();
        defectiveDeviceId = selectQuery.value(1).toInt();

        selectQuery.exec("SELECT Units.id, AllocationUnits.id FROM Units INNER JOIN AllocationUnits ON AllocationUnits.unit_id = Units.id");
        selectQuery.next();
        unitId = selectQuery.value(0).toInt();
        defectiveUnitId =  selectQuery.value(1).toInt();

        netIndex  = 0;
        NameLog = "Без имени";
        x0 = 0;
        x1 = 0;
        x2 = 0;
        x3 = 0;
        x4 = 0;
        y0 = 0;
        y1 = 0;
        y2 = 0;
        y3 = 0;
        y4 = 0;

        QSqlQuery query;
        query.exec("INSERT INTO AddNets(net_index,test,defective_device_allocation_id,defective_unit_allocation_id,x_0,y_0,x_1,y_1,x_2,y_2,x_3,y_3,x_4,y_4)"
                   "VALUES ('" +  QString::number(netIndex) + "','" + NameLog + "','" + QString::number(defectiveDeviceId) + "','" + QString::number(defectiveUnitId) + "','" + QString::number(x0) + "','" + QString::number(y0) + "','" + QString::number(x1) + "','" + QString::number(y1) + "','" + QString::number(x2) +
                   QString::number(y2) + "','" + QString::number(x3) + "','" + QString::number(y3) + "','" + QString::number(x4) + "','" + QString::number(y4) + "')");

        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());

        this->id = query.lastInsertId().toInt();
    }

    else {
        this->id = id;

        QSqlQuery query;
        query.exec("SELECT net_index, AddNets.test, defective_device_allocation_id, defective_unit_allocation_id, x_0, y_0, x_1, y_1, x_2, y_2, x_3, y_3, x_4, y_4, d1.id, u1.id "
                   "FROM AddNets "
                   "JOIN AllocationDevices AS ad1 ON ad1.id =  AddNets.defective_device_allocation_id "
                   "JOIN AllocationUnits AS au1 ON au1.id =  AddNets.defective_unit_allocation_id "
                   "JOIN Devices AS d1  ON d1.id = ad1.device_id "
                   "JOIN Units AS u1  ON u1.id = au1.unit_id "
                   "WHERE AddNets.id = " + QString::number(id));

        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        if (!query.next()) {
            QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }

        netIndex = query.value(0).toInt();
        NameLog = query.value(1).toString();
        deviceId = query.value(14).toInt();
        unitId = query.value(15).toInt();
        defectiveDeviceId = query.value(2).toInt();
        defectiveUnitId = query.value(3).toInt();
        x0 = query.value(4).toInt();
        y0 = query.value(5).toInt();
        x1 = query.value(6).toInt();
        y1 = query.value(7).toInt();
        x2 = query.value(8).toInt();
        y2 = query.value(9).toInt();
        x3 = query.value(10).toInt();
        y3 = query.value(11).toInt();
        x4 = query.value(12).toInt();
        y4 = query.value(13).toInt();

//        query.exec("SELECT  Units.name, Units.id "
//                   "FROM AddNets JOIN AllocationUnits  ON AllocationUnits.id =  AddNets.defective_unit_allocation_id "
//                   "JOIN Units  ON Units.id =  AllocationUnits.unit_id "
//                   "WHERE id = " + QString::number(id));

//       unitId = query.value(1).toInt();


    }
    QSqlQuery query;

    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    QGridLayout *gridLayout = new QGridLayout();
    mainLayout->addLayout(gridLayout);


    QLabel *labelLog = new  QLabel("Расположение лога");
    QLabel *labelDefectiveDevice =  new QLabel("Неисправный прибор");
    QLabel *labelDefectiveUnit =  new QLabel("Неисправная плата/Модуль");
    QLabel *labelNetIndex = new QLabel("Индекс сети");

    editLog = new QLineEdit();
    editLog->setText(NameLog);
    editNetIndex = new QLineEdit();
    QRegExp regExp("[0-9]{3}");
    QRegExpValidator *netIndexValidator = new QRegExpValidator(regExp);
    editNetIndex->setValidator(netIndexValidator);
    editNetIndex->setText(QString::number(netIndex));

    comboDevice = new QComboBox();
    comboDevice->installEventFilter(this);
    comboDevice->setFocusPolicy(Qt::StrongFocus);
    query.exec("SELECT  Devices.id, Devices.name, AllocationDevices.device_postfix, AllocationDevices.id "
                               "FROM Devices "
                               "JOIN AllocationDevices  ON AllocationDevices.device_id = Devices.id  ");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    for (int i = this->comboDevice->count(); query.next(); i++) {
        this->comboDevice->addItem(query.value(1).toString() +" " + query.value(2).toString() , query.value(3).toInt());
        if (query.value(3).toInt() == this->defectiveDeviceId) { //???
            this->comboDevice->setCurrentIndex(i);
        }
    }


    comboDefectiveUnits = new QComboBox();
    comboDefectiveUnits->installEventFilter(this);
    comboDefectiveUnits->setFocusPolicy(Qt::StrongFocus);
    this->fillDefectiveUnits();


/*
         query.exec("SELECT Devices.id "
                    "FROM Devices");
         if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
             QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
         }
         if (!query.next()) {
             QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
         }
         this->deviceId = query.value(0).toInt();
     QSqlQuery query("SELECT id, name "
                     "FROM Devices");
     if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
         QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
     }
     int i = 0;
     while (query.next()) {
         this->comboDevice->addItem(query.value(1).toString(), query.value(0).toInt());
         if (query.value(0).toInt() == this->deviceId) {
             this->comboDevice->setCurrentIndex(i);
         }
         i++;
     }
*/


    gridLayout->addWidget(labelLog,0,0);
    gridLayout->addWidget(editLog,0,1);
    gridLayout->addWidget(labelNetIndex,0,2);
    gridLayout->addWidget(editNetIndex,0,3);
    gridLayout->addWidget(labelDefectiveDevice,1,0);
    gridLayout->addWidget(comboDevice,1,1);
    gridLayout->addWidget(labelDefectiveUnit,1,2);
    gridLayout->addWidget(comboDefectiveUnits,1,3);


    QGroupBox *gpXY = new QGroupBox("Координаты");
    gpXY->setTitle(" Координаты ");
    QGridLayout *xyLayout = new QGridLayout();
    gpXY->setLayout(xyLayout);

    QLabel *labelX0 = new QLabel("x_0");
    QLabel *labelY0 = new QLabel("y_0");
    QLabel *labelX1 = new QLabel("x_1");
    QLabel *labelY1 = new QLabel("y_1");
    QLabel *labelX2 = new QLabel("x_2");
    QLabel *labelY2 = new QLabel("y_2");
    QLabel *labelX3 = new QLabel("x_3");
    QLabel *labelY3 = new QLabel("y_3");
    QLabel *labelX4 = new QLabel("x_4");
    QLabel *labelY4 = new QLabel("y_4");

    editX0 = new QLineEdit();
    editX0->setText(QString::number(x0));
    editY0 = new QLineEdit();
    editY0->setText(QString::number(y0));

    editX1 = new QLineEdit();
    editX1->setText(QString::number(x1));
    editY1 = new QLineEdit();
    editY1->setText(QString::number(y1));

    editX2 = new QLineEdit();
    editX2->setText(QString::number(x2));
    editY2 = new QLineEdit();
    editY2->setText(QString::number(y2));

    editX3 = new QLineEdit();
    editX3->setText(QString::number(x3));
    editY3 = new QLineEdit();
    editY3->setText(QString::number(y3));

    editX4 = new QLineEdit();
    editX4->setText(QString::number(x4));
    editY4 = new QLineEdit();
    editY4->setText(QString::number(y4));

    xyLayout->addWidget(labelX0,0,0);
    xyLayout->addWidget(editX0,1,0);
    xyLayout->addWidget(labelY0,0,1);
    xyLayout->addWidget(editY0,1,1);

    xyLayout->addWidget(labelX1,0,2);
    xyLayout->addWidget(editX1,1,2);
    xyLayout->addWidget(labelY1,0,3);
    xyLayout->addWidget(editY1,1,3);

    xyLayout->addWidget(labelX2,0,4);
    xyLayout->addWidget(editX2,1,4);
    xyLayout->addWidget(labelY2,0,5);
    xyLayout->addWidget(editY2,1,5);
    //Подправить
    xyLayout->addWidget(labelX3,0,6);
    xyLayout->addWidget(editX3,1,6);
    xyLayout->addWidget(labelY3,0,7);
    xyLayout->addWidget(editY3,1,7);

    xyLayout->addWidget(labelX4,0,8);
    xyLayout->addWidget(editX4,1,8);
    xyLayout->addWidget(labelY4,0,9);
    xyLayout->addWidget(editY4,1,9);

    mainLayout->addWidget(gpXY);

    buttonDelete = new QPushButton("Удалить");
    buttonDelete->setStyleSheet("background-color: Cornsilk;");
    mainLayout->addWidget(buttonDelete);



//    connect(this->editLog,SIGNAL(editingFinished()), this, SLOT(slotUpdateEditLog()));
//    connect(this->editNetIndex,SIGNAL(editingFinished()), this, SLOT(slotUpdatededitNetIndex()));

//    connect(this->editX0, SIGNAL(editingFinished()), this, SLOT(slotUpdateX0()));
//    connect(this->editX1, SIGNAL(editingFinished()), this, SLOT(slotUpdateX1()));
//    connect(this->editX2, SIGNAL(editingFinished()), this, SLOT(slotUpdateX2()));
//    connect(this->editX3, SIGNAL(editingFinished()), this, SLOT(slotUpdateX3()));
//    connect(this->editX4, SIGNAL(editingFinished()), this, SLOT(slotUpdateX4()));

//    connect(this->editY0, SIGNAL(editingFinished()), this, SLOT(slotUpdateY0()));
//    connect(this->editY1, SIGNAL(editingFinished()), this, SLOT(slotUpdateY1()));
//    connect(this->editY2, SIGNAL(editingFinished()), this, SLOT(slotUpdateY2()));
//    connect(this->editY3, SIGNAL(editingFinished()), this, SLOT(slotUpdateY3()));
//    connect(this->editY4, SIGNAL(editingFinished()), this, SLOT(slotUpdateY4()));
    connect(this->buttonDelete, SIGNAL(clicked()), this, SLOT(deleteFromDB()));
}

AddNet::~AddNet()
{

}


void AddNet::fillDefectiveUnits()
{
//    disconnect(this->comboDefectiveUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDefectiveUnit(int)));

    this->comboDefectiveUnits->clear();

//    this->comboDefectiveUnits->addItem("Отсутствует", -1);
//    this->comboDefectiveUnits->setCurrentIndex(0);

    QSqlQuery query("SELECT AllocationUnits.id, Units.name, AllocationUnits.is_main, AllocationUnits.slot "
                    "FROM Units INNER JOIN AllocationUnits on ALlocationUnits.unit_id = Units.id "
                    "WHERE ALlocationUnits.device_id = " % QString::number(this->deviceId));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

    for (int i = this->comboDefectiveUnits->count(); query.next(); i++) {
        QString text = query.value(3).toString();
        if (!text.isEmpty()) {
            text += ": ";
        }
        text += query.value(1).toString() % (query.value(2).toBool() ? " (основной)" : " (резервный)");
        this->comboDefectiveUnits->addItem(text, query.value(0).toInt());

        if (query.value(0).toInt() == this->defectiveUnitId) {
            this->comboDefectiveUnits->setCurrentIndex(i);
        }
    }

//    connect(this->comboDefectiveUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDefectiveUnit(int)));
}




void AddNet::updateDefectiveUnit()
{
    if (comboDefectiveUnits->currentIndex() == 0) {
        this->defectiveUnitId = -1;
    }
    else {
        this->defectiveUnitId = this->comboDefectiveUnits->itemData(comboDefectiveUnits->currentIndex()).toInt();
    }

    QSqlQuery query;
    query.exec("UPDATE AddNet SET defective_unit_allocation_id = " % (this->defectiveUnitId < 0 ? "NULL" : QString::number(this->defectiveUnitId)) %
               " WHERE id = " % QString::number(this->id));

    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void AddNet::updateComboBoxDevices()
{
    QSqlQuery query;
    this->deviceId = this->comboDevice->itemData(comboDevice->currentIndex()).toInt();
    defectiveDeviceId = deviceId;
    query.exec("UPDATE AddNets "
               "SET defective_unit_device_id = " % QString::number(this->defectiveDeviceId) % " "
               " WHERE id = " % QString::number(this->id));
    //this->fillDefectiveUnits();

}

void AddNet::slotSave()
{
    slotUpdateEditLog();
    slotUpdatededitNetIndex();
    slotUpdateX0();
    slotUpdateX1();
    slotUpdateX2();
    slotUpdateX3();
    slotUpdateX4();
    slotUpdateY0();
    slotUpdateY1();
    slotUpdateY2();
    slotUpdateY3();
    slotUpdateY4();
    updateDefectiveUnit();
    updateComboBoxDevices();

}

bool AddNet::eventFilter(QObject *target, QEvent *event)
{
    if(event->type() == QEvent::Wheel)
    {
        const char *className = target->metaObject()->className();
        if(QString(className) == QString("QComboBox"))
        {
             QCoreApplication::sendEvent(this, event);
                         return true;
        }

    }
    return QWidget::eventFilter(target, event);
}

void AddNet::slotUpdateEditLog()
{


    QString log = this->editLog->text();


    QSqlQuery query;
    query.exec("UPDATE AddNets "
              "SET test = '" + log + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void AddNet::slotUpdatededitNetIndex()
{

    QString netIndex = this->editNetIndex->text();


    QSqlQuery query;
    query.exec("UPDATE AddNets "
              "SET net_index = '" + netIndex +  "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}




void AddNet::slotUpdateX0()
{
    QString X0 = this->editX0->text();

    QSqlQuery query;
    query.exec("UPDATE AddNets "
              "SET x_0 = '" + X0 + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void AddNet::slotUpdateX1()
{
    QString X1 = this->editX1->text();

    QSqlQuery query;
    query.exec("UPDATE AddNets "
              "SET x_1 = '" + X1 + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void AddNet::slotUpdateX2()
{
    QString X2 = this->editX2->text();

    QSqlQuery query;
    query.exec("UPDATE AddNets "
              "SET x_2 = '" + X2 + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void AddNet::slotUpdateX3()
{
    QString X3 = this->editX3->text();

    QSqlQuery query;
    query.exec("UPDATE AddNets "
              "SET x_3 = '" + X3 + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void AddNet::slotUpdateX4()
{
    QString X4 = this->editX4->text();

    QSqlQuery query;
    query.exec("UPDATE AddNets "
              "SET x_4 = '" + X4 + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void AddNet::slotUpdateY0()
{
    QString Y0 = this->editY0->text();

    QSqlQuery query;
    query.exec("UPDATE AddNets "
              "SET y_0 = '" + Y0 + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void AddNet::slotUpdateY1()
{
    QString Y1 = this->editY1->text();

    QSqlQuery query;
    query.exec("UPDATE AddNets "
              "SET y_1 = '" + Y1 + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void AddNet::slotUpdateY2()
{
    QString Y2 = this->editY2->text();

    QSqlQuery query;
    query.exec("UPDATE AddNets "
              "SET y_2 = '" + Y2 + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void AddNet::slotUpdateY3()
{
    QString Y3 = this->editY3->text();

    QSqlQuery query;
    query.exec("UPDATE AddNets "
              "SET y_3 = '" + Y3 + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void AddNet::slotUpdateY4()
{
    QString Y4 = this->editY4->text();

    QSqlQuery query;
    query.exec("UPDATE AddNets "
              "SET y_4 = '" + Y4 + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}



void AddNet::deleteFromDB()
{
    if (QMessageBox::question(this, "Подтвердите действие", "Вы точно хотите удалить?", QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
        QSqlQuery query;
        query.exec("DELETE FROM AddNets "
                  "WHERE id = " + QString::number(this->id));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }

        emit wasDeleted(this);
    }
}


