#include "error.h"

Error::Error(int id, QWidget *parent) : QGroupBox(parent)
{
    this->setStyleSheet("QGroupBox { background-color: LightGray }");

    int errorCode;
    bool selectByBits;
    QString errorText;

    if (id < 0) {

        QSqlQuery selectQuery;
        selectQuery.exec("SELECT Devices.id, AllocationUnits.id FROM Devices INNER JOIN AllocationUnits ON AllocationUnits.device_id = Devices.id");
        selectQuery.next();

        this->deviceId = selectQuery.value(0).toInt();
        this->allocationUnitId = selectQuery.value(1).toInt();
        errorCode = 1;
        selectByBits = false;
        errorText = "Неизвестная ошибка";
        this->defectiveUnitId = -1;

        QSqlQuery query("INSERT INTO Errors (device_id, unit_allocation_id, error_code, select_by_bits, error_text) "
                  "VALUES ('" + QString::number(this->deviceId) + "', '" + QString::number(this->allocationUnitId) + "', '" + QString::number(errorCode) + "', '" + QString::number(selectByBits) + "', '" + errorText + "')");
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        this->id = query.lastInsertId().toInt();
    }
    else {
        this->id = id;

        QSqlQuery query("SELECT id, device_id, unit_allocation_id, error_code, select_by_bits, error_text, defective_unit_allocation_id "
                        "FROM Errors "
                        "WHERE id = " + QString::number(id));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }

        if (!query.next()) {
            QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }

        this->id = query.value(0).toInt();
        this->deviceId = query.value(1).toInt();
        this->allocationUnitId = query.value(2).toInt();
        errorCode = query.value(3).toInt();
        selectByBits = query.value(4).toInt();
        errorText = query.value(5).toString();
        if (query.value(6).isNull()) {
            this->defectiveUnitId = -1;
        }
        else {
            this->defectiveUnitId = query.value(6).toInt();
        }

    }

    QSqlQuery query;

    this->mainLayout = new QGridLayout();
    this->setLayout(this->mainLayout);

    this->comboDevices = new QComboBox();
    comboDevices->installEventFilter(this);
    comboDevices->setFocusPolicy(Qt::StrongFocus);

    this->mainLayout->addWidget(this->comboDevices, 1, 1, 1, 2);


     query.exec ("SELECT DISTINCT Devices.id, Devices.name FROM Devices INNER JOIN AllocationUnits ON AllocationUnits.device_id = Devices.id");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    for (int i = this->comboDevices->count(); query.next(); i++) {
        this->comboDevices->addItem(query.value(1).toString(), query.value(0).toInt());
        //qDebug() << "deviceID = " << deviceId << endl;
        if (query.value(0).toInt() == this->deviceId) {
            this->comboDevices->setCurrentIndex(i);
        }
    }

    this->comboUnits = new QComboBox();
    comboUnits->installEventFilter(this);
    comboUnits->setFocusPolicy(Qt::StrongFocus);



    this->mainLayout->addWidget(this->comboUnits, 1, 3, 1, 2);
    this->fillUnits();

    this->buttonDelete = new QPushButton("Удалить");
    buttonDelete->setStyleSheet("background-color: Cornsilk;");
    this->mainLayout->addWidget(this->buttonDelete, 1, 5, Qt::AlignRight);
    this->buttonDelete->setFocusPolicy(Qt::NoFocus);

    this->mainLayout->addWidget(new QLabel("Код ошибки:"), 2, 1, Qt::AlignRight);
    this->editErrorCode = new QLineEdit();
    this->mainLayout->addWidget(this->editErrorCode, 2, 2);
    this->editErrorCode->setText(QString::number(errorCode));
    this->editErrorCode->setMaximumWidth(75);

    this->checkboxSelectByBits = new QCheckBox("по битам");
    this->mainLayout->addWidget(this->checkboxSelectByBits, 2, 3);
    this->checkboxSelectByBits->setChecked(selectByBits);

    this->mainLayout->addWidget(new QLabel("Неисправный модуль:"), 2, 4, Qt::AlignRight);

    this->comboDefectiveUnits = new QComboBox();
    comboDefectiveUnits->installEventFilter(this);
    comboDefectiveUnits->setFocusPolicy(Qt::StrongFocus);

    this->mainLayout->addWidget(this->comboDefectiveUnits, 2, 5);
    this->fillDefectiveUnits();

    this->mainLayout->addWidget(new QLabel("Текст ошибки:"), 3, 1, Qt::AlignRight);
    this->editErrorText = new QLineEdit();
    this->mainLayout->addWidget(this->editErrorText, 3, 2, 1, 4);
    this->editErrorText->setText(errorText);

    connect(this->buttonDelete, SIGNAL(clicked()), this, SLOT(deleteFromDB()));
    //connect(this->comboDevices, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDevice(int)));
    connect(this->comboDevices, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDevice()));
    //connect(this->comboDefectiveUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDefectiveUnit(int)));
    //connect(this->comboDefectiveUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDefectiveUnit()));
    //connect(this->editErrorCode, SIGNAL(editingFinished()), this, SLOT(updateErrorCode()));
    connect(this->editErrorCode, SIGNAL(editingFinished()), this, SLOT(changeErrorTextForErrorCode()));
   // connect(this->checkboxSelectByBits, SIGNAL(toggled(bool)), this, SLOT(updateSelectByBits(bool)));
    //connect(this->editErrorText, SIGNAL(editingFinished()), this, SLOT(updateErrorText()));
}
Error::~Error()
{
    //delete this->mainLayout;

    //    delete this->buttonDelete;
}


void Error::slotSave()
{
    updateUnit();
    updateDefectiveUnit();
    updateErrorCode();
    updateErrorText();
    updateSelectByBits();
}

void Error::deleteFromDB()
{
    if (QMessageBox::question(this, "Подтвердите действие", "Вы точно хотите удалить?", QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
        QSqlQuery query;
        query.exec("DELETE FROM Errors "
                  "WHERE id = " + QString::number(this->id));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }

        emit wasDeleted(this);
    }
}

void Error::updateDevice()
{
    this->deviceId = this->comboDevices->itemData(comboDevices->currentIndex()).toInt();
    qDebug() << deviceId << comboDevices->itemData(comboDevices->currentIndex()).toInt() << endl;
    this->defectiveUnitId = -1;

    QSqlQuery query;
    query.exec("SELECT id FROM AllocationUnits WHERE device_id = " % QString::number(this->deviceId));
    if (!query.next()) {
        QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText() + "This error");
    }
    this->allocationUnitId = query.value(0).toInt();

    query.exec("UPDATE Errors "
               "SET device_id = " % QString::number(this->deviceId) % ", "
               "unit_allocation_id = " % QString::number(this->allocationUnitId) % ", "
               "defective_unit_allocation_id = NULL WHERE id = " % QString::number(this->id));

    this->fillUnits();
    this->fillDefectiveUnits();
}

void Error::updateUnit()
{
    this->allocationUnitId = this->comboUnits->itemData(comboUnits->currentIndex()).toInt();

    QSqlQuery query;
    query.exec("UPDATE Errors "
              "SET unit_allocation_id = " % QString::number(this->allocationUnitId) % " "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void Error::updateErrorCode()
{
    QString text = this->editErrorCode->text();
    QSqlQuery query;
    query.exec("UPDATE Errors "
              "SET error_code = '" + text + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }


}

void Error::updateErrorText()
{
    QString text = this->editErrorText->text();
    QSqlQuery query;
    query.exec("UPDATE Errors "
              "SET error_text = '" + text + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void Error::updateSelectByBits()
{
    QSqlQuery query;
    query.exec("UPDATE Errors "
              "SET select_by_bits = '" + QString::number(checkboxSelectByBits->isChecked()) + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void Error::updateDefectiveUnit()
{
    if (comboDefectiveUnits->currentIndex() == 0) {
        this->defectiveUnitId = -1;
    }
    else {
        this->defectiveUnitId = this->comboDefectiveUnits->itemData(comboDefectiveUnits->currentIndex()).toInt();
    }

    QSqlQuery query;
    query.exec("UPDATE Errors SET defective_unit_allocation_id = " % (this->defectiveUnitId < 0 ? "NULL" : QString::number(this->defectiveUnitId)) %
               " WHERE id = " % QString::number(this->id));

    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void Error::slotUpdateCB()
{
    this->fillUnits();
    this->fillDefectiveUnits();
    // this->fillDevices();

}
// Пока что этот метод мы не будем использовать
void Error::fillDevices()
{
    this->comboDevices->clear();

    QSqlQuery query ("SELECT  Devices.id, Devices.name FROM Devices INNER JOIN AllocationUnits ON AllocationUnits.device_id = Devices.id");
   if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
       QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText() + "Привет"); // добавил немного текста для проверки
   }
   for (int i = this->comboDevices->count(); query.next(); i++) {
       this->comboDevices->addItem(query.value(1).toString(), query.value(0).toInt());
       if (query.value(0).toInt() == this->deviceId) {
           this->comboDevices->setCurrentIndex(i);
       }
   }




   query.exec("SELECT DISTINCT Devices.id, Devices.name FROM Devices INNER JOIN AllocationUnits ON AllocationUnits.device_id = Devices.id");
   if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
       QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
   }
   for (int i = this->comboDevices->count(); query.next(); i++) {
       this->comboDevices->addItem(query.value(1).toString(), query.value(0).toInt());
       if (query.value(0).toInt() == this->deviceId) {
           this->comboDevices->setCurrentIndex(i);
       }
   }

}

void Error::changeErrorTextForErrorCode()
{
    int codeError = editErrorCode->text().toInt();

    QSqlQuery query("SELECT error_code, error_text, id FROM Errors WHERE error_code = "  + QString::number(codeError));


        if (!query.next()) {
            editErrorText->clear();
            editErrorText->setPlaceholderText("Введите название ошибки");
            //QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        if(query.value(0).toInt() == codeError)
        {
            qDebug() << "query.value(0).toInt() = " << query.value(0).toInt() << "и codeError =  " << codeError << endl;
            qDebug() << "ЗАШЕЛ в IF" << endl;
            editErrorText->clear();
            qDebug() << query.value(2).toString() << endl;
            editErrorText->setText(query.value(1).toString());
        }

}

void Error::fillUnits()
{
//    disconnect(this->comboUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUnit(int)));
    //disconnect(this->comboUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUnit()));
    this->comboUnits->clear();

    QSqlQuery query("SELECT AllocationUnits.id, Units.name, AllocationUnits.is_main, AllocationUnits.slot "
                    "FROM Units INNER JOIN AllocationUnits on ALlocationUnits.unit_id = Units.id "
                    "WHERE ALlocationUnits.device_id = " % QString::number(this->deviceId));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    for (int i = this->comboUnits->count(); query.next(); i++) {
        QString text = query.value(3).toString();
        if (!text.isEmpty()) {
            text += ": ";
        }
        text += query.value(1).toString() % (query.value(2).toBool() ? " (основной)" : " (резервный)");
        this->comboUnits->addItem(text, query.value(0).toInt());

        if (query.value(0).toInt() == this->allocationUnitId) {
            this->comboUnits->setCurrentIndex(i);
        }
    }


    //connect(this->comboUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUnit(int)));
        //connect(this->comboUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUnit()));
}

void Error::fillDefectiveUnits() //
{
    //disconnect(this->comboDefectiveUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDefectiveUnit(int)));

    this->comboDefectiveUnits->clear();

    this->comboDefectiveUnits->addItem("Отсутствует", -1);
    this->comboDefectiveUnits->setCurrentIndex(0);

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


    //connect(this->comboDefectiveUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDefectiveUnit(int)));
}

bool Error::eventFilter(QObject *target, QEvent *event)
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



