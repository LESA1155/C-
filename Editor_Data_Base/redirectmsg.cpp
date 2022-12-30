#include "redirectmsg.h"

RedirectMsg::RedirectMsg(int id, QWidget *parent) : QGroupBox(parent)
{

    QString redirectMessageText; // Перменная для хранения текста при запросе из БД

    if (id < 0) {
        QSqlQuery selectQuery;
        selectQuery.exec("SELECT Devices.id, AllocationDevices.id FROM Devices INNER JOIN AllocationDevices ON AllocationDevices.device_id = Devices.id");
        selectQuery.next();
        beforeDeviceId = selectQuery.value(0).toInt();
        beforeDeviceAllId = selectQuery.value(1).toInt();
        afterDeviceId = selectQuery.value(0).toInt()+1;
        afterDeviceAllId = selectQuery.value(1).toInt()+1;
//        selectQuery.next();
//        afterDeviceId = selectQuery.value(0).toInt();
//        afterDeviceAllId = selectQuery.value(1).toInt();
         redirectMessageText = "Пустое сообщение";
//        selectQuery.next();

         QSqlQuery query("INSERT INTO RedirectMessages (before_device_allocation_id, after_device_allocation_id, text) "
                  "VALUES ('" + QString::number(this->beforeDeviceAllId) + "', '" + QString::number(this->afterDeviceAllId) + "', '" + redirectMessageText + "')");
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        this->id = query.lastInsertId().toInt();

    }
    else
    {
        this->id = id;

        QSqlQuery query("SELECT RedirectMessages.before_device_allocation_id, RedirectMessages.after_device_allocation_id , RedirectMessages.text, d1.id , d2.id, RedirectMessages.id "
                        "FROM RedirectMessages "
                        "JOIN AllocationDevices AS ad1 ON ad1.id =  RedirectMessages.before_device_allocation_id "
                        "JOIN AllocationDevices AS ad2 ON ad2.id =  RedirectMessages.after_device_allocation_id "
                        "JOIN Devices AS d1 ON d1.id = ad1.device_id "
                        "JOIN Devices AS d2 ON d2.id = ad2.device_id "
                        "WHERE RedirectMessages.id = " + QString::number(id));

        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
                    QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
                }

        if (!query.next()) {
                    QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
                }

        beforeDeviceAllId = query.value(0).toInt();
        afterDeviceAllId = query.value(1).toInt();
        redirectMessageText = query.value(2).toString();
        beforeDeviceId = query.value(3).toInt();
        afterDeviceId = query.value(4).toInt();
        //this->id = query.value("RedirectMessages.id").toInt();
        //qDebug() << this->id << " = THIS->ID" << endl;

    }



    QSqlQuery query;


    this->mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    QHBoxLayout *beforedLayout = new QHBoxLayout();
    mainLayout->addLayout(beforedLayout);

    QHBoxLayout *afterdLayout = new QHBoxLayout();
    mainLayout->addLayout(afterdLayout);

    QHBoxLayout *msgLayout = new QHBoxLayout();
    mainLayout->addLayout(msgLayout);


    QLabel * beforeDevLabel= new QLabel("Устройство 1");
    this->comboBeforeDevices = new QComboBox();
    comboBeforeDevices->installEventFilter(this);
    comboBeforeDevices->setFocusPolicy(Qt::StrongFocus);
    beforedLayout->addWidget(beforeDevLabel);
    beforedLayout->addWidget(this->comboBeforeDevices,Qt::AlignLeft);
// Склеить все девайс айди и девайс постфикс, добавить их все в комбобокс и проверерить с rm.id и поставить текущим. Но при этом, сначала собрать постфикс и девайс в запросе выше.
    /*
    query.exec("SELECT ad1.id, ad2.id, d1.name, d2.name, ad1.device_id, d1.id, ad2.device_id, ad1.device_postfix, ad2.device_postfix, text "
                               "FROM RedirectMessages   "
                               "LEFT JOIN AllocationDevices AS ad1 ON ad1.id =  RedirectMessages.before_device_allocation_id "
                               "LEFT JOIN AllocationDevices AS ad2 ON ad2.id =  RedirectMessages.after_device_allocation_id "
                               "LEFT JOIN Devices AS d1 ON d1.id = ad1.device_id "
                               "LEFT JOIN Devices AS d2 ON d2.id = ad2.device_id "//);
                              "WHERE RedirectMessages.id = " + QString::number(this->id));
                              */

    query.exec("SELECT  Devices.id, Devices.name, AllocationDevices.device_postfix, AllocationDevices.id "
                               "FROM Devices "
                               "JOIN AllocationDevices  ON AllocationDevices.device_id = Devices.id  ");

    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    for (int i = this->comboBeforeDevices->count(); query.next(); i++) {
        this->comboBeforeDevices->addItem(query.value(1).toString() +" " + query.value(2).toString() , query.value(3).toInt());
        if (query.value(3).toInt() == this->beforeDeviceAllId) {
            this->comboBeforeDevices->setCurrentIndex(i);
        }
    }
/*
//    for (int i = this->comboAfterDevices->count(); query.next(); i++) {
//        this->comboAfterDevices->addItem(query.value("d2.name").toString(), query.value("ad2.device_id").toInt());
//        if (query.value("ad2.id").toInt() == this->afterDeviceAllId) {
//            this->comboAfterDevices->setCurrentIndex(i);
//        }
//    }



//    QSqlQuery query ("SELECT  d1.name, d2.name, d1.device_postfix, d2.device_postfix, text "
//                "FROM RedirectMessages   "
//                "JOIN AllocationDevices AS ad1 ON ad1.id =  RedirectMessages.before_device_allocation_id "
//                "JOIN AllocationDevices AS ad2 ON ad2.id =  RedirectMessages.after_device_allocation_id "
//                "JOIN Devices AS d1 ON d1.id = ad1.device_id "
//                "JOIN Devices AS d2 ON d2.id = ad2.device_id "
//                "WHERE RedirectMessages.id = " + QString::number(this->id));

//    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
//        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
//    }
//    for (int i = this->comboBeforeDevices->count(); query.next(); i++) {
//        this->comboBeforeDevices->addItem(query.value(0).toString(), query.value(0).toInt());
//        if (query.value(0).toInt() == this->allocationUnitId) {
//            this->comboBeforeDevices->setCurrentIndex(i);
//        }
//    }
*/

    QLabel *afterDevLabel = new QLabel("Устройство 2");
    this->comboAfterDevices = new QComboBox();
    comboAfterDevices->installEventFilter(this);
    comboAfterDevices->setFocusPolicy(Qt::StrongFocus);
    afterdLayout->addWidget(afterDevLabel);
    afterdLayout->addWidget(this->comboAfterDevices,Qt::AlignLeft);


    query.exec("SELECT  Devices.id, Devices.name, AllocationDevices.device_postfix, AllocationDevices.id "
                               "FROM Devices "
                               "JOIN AllocationDevices  ON AllocationDevices.device_id = Devices.id  ");

    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    for (int i = this->comboAfterDevices->count(); query.next(); i++) {
        this->comboAfterDevices->addItem(query.value(1).toString() + " " + query.value(2).toString() , query.value(3).toInt());
        if (query.value(3).toInt() == this->afterDeviceAllId) {
            this->comboAfterDevices->setCurrentIndex(i);
        }
    }


    QLabel *textLabel = new QLabel("Текст Сообщения");
    this->editText = new QLineEdit();
    editText->setText(redirectMessageText);
    msgLayout->addWidget(textLabel);
    msgLayout->addWidget(editText);

    QPushButton *deleteButton = new QPushButton ("Удалить");
    deleteButton->setStyleSheet("background-color: Cornsilk;");
    this->mainLayout->addWidget(deleteButton);


    this->setTitle(redirectMessageText);

    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteFromDB()));
    //connect(this->editText, SIGNAL(editingFinished()), this, SLOT(slotUpdateMsgText()));
    //connect(this->comboBeforeDevices, SIGNAL(currentIndexChanged(int)), this, SLOT(updateBeforeDeviceComboBox(int)));
    //connect(this->comboAfterDevices, SIGNAL(currentIndexChanged(int)), this, SLOT(updateAfterDeviceComboBox(int)));

}

void RedirectMsg::slotUpdateMsgText()
{
    QString text = this->editText->text();

    QSqlQuery query;
    query.exec("UPDATE RedirectMessages "
              "SET text = '" + text + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void RedirectMsg::deleteFromDB()
{
    if (QMessageBox::question(this, "Подтвердите действие", "Вы точно хотите удалить?", QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
        QSqlQuery query;
        query.exec("DELETE FROM RedirectMessages "
                  "WHERE id = " + QString::number(this->id));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }

        emit wasDeleted(this);
    }
}



void RedirectMsg::updateBeforeDeviceComboBox()
{

    this->beforeDeviceId = this->comboBeforeDevices->itemData(comboBeforeDevices->currentIndex()).toInt();
    //qDebug() << "beforeDeviceId" << beforeDeviceId;
    beforeDeviceAllId = beforeDeviceId;
    QSqlQuery query;
    query.exec("UPDATE RedirectMessages "
               "SET before_device_allocation_id = " % QString::number(this->beforeDeviceAllId) % " "
               "WHERE id = " % QString::number(this->id));

}

void RedirectMsg::updateAfterDeviceComboBox()
{
    this->afterDeviceId = this->comboAfterDevices->itemData(comboAfterDevices->currentIndex()).toInt();
    //qDebug() << "afterDeviceId" << afterDeviceId;
    afterDeviceAllId = afterDeviceId;
    QSqlQuery query;
    query.exec("UPDATE RedirectMessages "
               "SET after_device_allocation_id = " % QString::number(this->afterDeviceAllId) % " "
                                                                                               "WHERE id = " % QString::number(this->id));
}

void RedirectMsg::slotSave()
{
    slotUpdateMsgText();
    updateBeforeDeviceComboBox();
    updateAfterDeviceComboBox();
}

bool RedirectMsg::eventFilter(QObject *target, QEvent *event)
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



    /*
    disconnect(this->comboBeforeDevices, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUnit(int)));

    this->comboBeforeDevices->clear();

    QSqlQuery query("SELECT AllocationUnits.id, Units.name, AllocationUnits.is_main, AllocationUnits.slot "
                    "FROM Units INNER JOIN AllocationUnits on ALlocationUnits.unit_id = Units.id "
                    "WHERE ALlocationUnits.device_id = " % QString::number(this->deviceId));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    for (int i = this->comboBeforeDevices->count(); query.next(); i++) {
        QString text = query.value(3).toString();
        if (!text.isEmpty()) {
            text += ": ";
        }
        text += query.value(1).toString() % (query.value(2).toBool() ? " (основной)" : " (резервный)");
        this->comboBeforeDevices->addItem(text, query.value(0).toInt());

        if (query.value(0).toInt() == this->allocationUnitId) {
            this->comboBeforeDevices->setCurrentIndex(i);
        }
    }

    connect(this->comboBeforeDevices, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUnit(int)));
    */







