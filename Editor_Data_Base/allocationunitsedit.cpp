#include "allocationunitsedit.h"

AllocationUnitsEdit::AllocationUnitsEdit(int id, QWidget *parent): QGroupBox(parent)
{
// Добавить обновление ComboBox
    bool isMain;
    bool isHidden;
    QString slotsValue;

    if (id < 0) {

        QSqlQuery selectQuery;
        selectQuery.exec("SELECT Devices.id, AllocationUnits.unit_id FROM Devices INNER JOIN AllocationUnits ON AllocationUnits.device_id = Devices.id");
        selectQuery.next();
        this->deviceId = selectQuery.value(0).toInt();
        this->allocationUnitId = selectQuery.value(1).toInt();
        isMain = false;
        isHidden = false;
        slotsValue = QString::number(0);

        QSqlQuery query("INSERT INTO AllocationUnits (device_id, unit_id, is_main, slot, is_hidden) "
                  "VALUES ('" + QString::number(this->deviceId) + "', '" + QString::number(this->allocationUnitId) + "', '" + QString::number(isMain) + "', '" + slotsValue + "', '" + QString::number(isHidden) + "')");
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        this->id = query.lastInsertId().toInt();
    }
    else {
        this->id = id;

        QSqlQuery query("SELECT id, device_id,unit_id, is_main, slot, is_hidden "
                        "FROM AllocationUnits "
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
        isMain = query.value(3).toInt();
        slotsValue = query.value(4).toString();
        isHidden = query.value(5).toInt();

    }

    QSqlQuery query;

    //this->setTitle(QString::number(this->id)); Возможно убрать название комбобокса
    this->mainLayout = new QGridLayout();
    this->setLayout(this->mainLayout);
    //======================================================================================================
    this->mainLayout->addWidget(new QLabel("Модуль:"), 1, 0, Qt::AlignRight);
    this->comboUnits = new QComboBox();
    comboUnits->installEventFilter(this);
    comboUnits->setFocusPolicy(Qt::StrongFocus);
    this->mainLayout->addWidget(this->comboUnits, 1, 1, 1, 2);
    fillUnitsComboBox();

 //======================================================================================================


    this->mainLayout->addWidget(new QLabel("Прибор:"), 2, 0, Qt::AlignRight);
    this->comboDevices = new QComboBox();
    comboDevices->installEventFilter(this);
    comboDevices->setFocusPolicy(Qt::StrongFocus);
    this->mainLayout->addWidget(this->comboDevices, 2, 1,1,2);
    fillDevicesComboBox();

      //=================================================================================================================

    this->checkBoxIsMain = new QCheckBox("Основной");
    this->mainLayout->addWidget(this->checkBoxIsMain, 1,3,Qt::AlignRight);
    this->checkBoxIsMain->setChecked(isMain);

    this->checkBoxIsHidden = new QCheckBox("Скрытый");
    this->mainLayout->addWidget(this->checkBoxIsHidden, 2, 3,Qt::AlignRight);
    this->checkBoxIsHidden->setChecked(isHidden);

    this->mainLayout->addWidget(new QLabel("Слот"),3,0, Qt::AlignRight);
    this->editSlots = new QLineEdit();
    QRegExp regExp("^[0-9]+\-[0-9]+");
    QRegExpValidator *slotsValidator = new QRegExpValidator(regExp);
    editSlots->setValidator(slotsValidator);
    this->editSlots->setText(slotsValue);
    this->mainLayout->addWidget(editSlots,3,1,1,2);


    this->buttonDelete = new QPushButton("Удалить");
    buttonDelete->setStyleSheet("background-color: Cornsilk;");
    this->mainLayout->addWidget(this->buttonDelete, 4,0,1,5);
    this->buttonDelete->setFocusPolicy(Qt::NoFocus);

     connect(this->buttonDelete, SIGNAL(clicked()), this, SLOT(deleteFromDB()));
     //connect(this->checkBoxIsMain, SIGNAL(toggled(bool)), this, SLOT(updateIsMain(bool)));
     //connect(this->checkBoxIsHidden, SIGNAL(toggled(bool)), this, SLOT(updateIsHidden(bool)));
     //connect(this->editSlots, SIGNAL(editingFinished()), this, SLOT(updateSlots()));
     //connect(this->comboDevices, SIGNAL(currentIndexChanged(int)), this, SLOT(updateComboDevices(int)));
     //connect(this->comboUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(updateComboUnit(int)));


}

void AllocationUnitsEdit::deleteFromDB()
{

        if (QMessageBox::question(this, "Подтвердите действие", "Вы точно хотите удалить?", QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
            QSqlQuery query;
            query.exec("DELETE FROM AllocationUnits "
                      "WHERE id = " + QString::number(this->id));
            if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
                QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
            }

            emit wasDeleted(this);
        }

}

void AllocationUnitsEdit::updateComboDevices()
{
    this->deviceId = this->comboDevices->itemData(comboDevices->currentIndex()).toInt();


      QSqlQuery query;

    query.exec("UPDATE AllocationUnits "
               "SET device_id = " % QString::number(this->deviceId) + " "
                "WHERE id = " + QString::number(this->id));


    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

}

void AllocationUnitsEdit::updateComboUnit()
{
    this->allocationUnitId = this->comboUnits->itemData(comboUnits->currentIndex()).toInt();

    QSqlQuery query;
    query.exec("UPDATE AllocationUnits "
              "SET unit_id = " %  QString::number(this->allocationUnitId) % " "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

}


void AllocationUnitsEdit::updateIsMain()
{
    QSqlQuery query;
    query.exec("UPDATE AllocationUnits "
              "SET is_main = '" + QString::number(checkBoxIsMain->isChecked()) + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

}

void AllocationUnitsEdit::updateIsHidden()
{
    QSqlQuery query;
    query.exec("UPDATE AllocationUnits "
              "SET is_hidden = '" % QString::number(checkBoxIsHidden->isChecked()) % "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void AllocationUnitsEdit::updateSlots()
{
    QString slotsText = this->editSlots->text();

    QSqlQuery query;
    query.exec("UPDATE AllocationUnits "
              "SET slot = '" + slotsText + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void AllocationUnitsEdit::slotSave()
{
    updateComboDevices();
    updateComboUnit();
    updateIsMain();
    updateIsHidden();
    updateSlots();

}

bool AllocationUnitsEdit::eventFilter(QObject *target, QEvent *event)
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

void AllocationUnitsEdit::fillDevicesComboBox()
{
    this->comboDevices->clear();

    QSqlQuery query("SELECT DISTINCT Devices.id, Devices.name FROM Devices INNER JOIN AllocationUnits ON AllocationUnits.device_id = Devices.id");
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

void AllocationUnitsEdit::fillUnitsComboBox()
{

    this->comboUnits->clear();

    QSqlQuery query("SELECT DISTINCT Units.id, Units.name FROM Units INNER JOIN AllocationUnits ON AllocationUnits.unit_id = Units.id");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    for (int i = this->comboUnits->count(); query.next(); i++) {
        this->comboUnits->addItem(query.value(1).toString(), query.value(0).toInt());
        if (query.value(0).toInt() == this->allocationUnitId) {
            this->comboUnits->setCurrentIndex(i);
        }
    }
}

void AllocationUnitsEdit::slotUp()
{
    fillUnitsComboBox();
    fillDevicesComboBox();

}




