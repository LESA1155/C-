#include "unitdep.h"

UnitDep::UnitDep(int deviceId, bool isMain, int allocId, QWidget *parent)
    : QGroupBox(parent)
{
    this->isMain = isMain;
    QString slot;
    bool isHidden;

    if (allocId < 0) {
        isHidden = 0;

    QSqlQuery query;
    query.exec("SELECT id "
               "FROM Units");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    if (!query.next()) {
        QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    this->unitId = query.value(0).toInt();

    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    query.exec("INSERT INTO AllocationUnits (unit_id, device_id, is_hidden, is_main) "
               "VALUES ('" + QString::number(this->unitId) + "', '" + QString::number(deviceId) +  + "', '" + QString::number(isHidden) + "', '" +
                        QString::number(this->isMain) + "')");
    this->allocId = query.lastInsertId().toInt();
    slot = "";
    }
    else {
    this->allocId = allocId;

    QSqlQuery query("SELECT Units.id, AllocationUnits.slot, AllocationUnits.is_hidden "
                    "FROM Units JOIN AllocationUnits ON Units.id = AllocationUnits.unit_id "
                    "WHERE AllocationUnits.id = " + QString::number(this->allocId));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    if (!query.next()) {
        QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

    this->unitId = query.value(0).toInt();
    slot = query.value(1).toString();
    isHidden = query.value(2).toInt();
}

    this->dependence = new Dependence(this->allocId);

    this->mainLayout = new QHBoxLayout();
    this->setLayout(this->mainLayout);

    this->comboUnits = new QComboBox();
    comboUnits->installEventFilter(this);
    comboUnits->setFocusPolicy(Qt::StrongFocus);
    this->mainLayout->addWidget(this->comboUnits);

    this->checkBoxIsHidden = new QCheckBox("Скрытый");
    this->mainLayout->addWidget(this->checkBoxIsHidden);
    this->checkBoxIsHidden->setChecked(isHidden);

    this->mainLayout->addWidget(new QLabel("Слот: "));
    this->editSlot = new QLineEdit();
    this->mainLayout->addWidget(this->editSlot);
    this->editSlot->setValidator(new QRegExpValidator(QRegExp("(^$)|(([1-2][0-9]-)?([1-2][0-9]))|(([1-9]-)?([1-9]|([1-2][0-9])))")));
    this->editSlot->setText(slot);

    this->buttonDependence = new QPushButton("Зависимости");
    this->mainLayout->addWidget(this->buttonDependence);
    connect(this->buttonDependence, SIGNAL(clicked(bool)), this->dependence, SLOT(show()));
    connect(this, SIGNAL(wasDeleted(UnitDep*)), this->dependence, SLOT(deleteAll()));

    this->buttonDelete = new QPushButton("Удалить");
    this->mainLayout->addWidget(this->buttonDelete);
    this->buttonDelete->setFocusPolicy(Qt::NoFocus);


    QSqlQuery query;
    query.exec(QString("SELECT name "
                       "FROM Units "
                       "WHERE id = ") + QString::number(this->unitId));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    if (!query.next()) {
        QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    this->setTitle(query.value(0).toString());

    query.exec("SELECT id, name "
               "FROM Units");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    int i = 0;
    while (query.next()) {
        this->comboUnits->addItem(query.value(1).toString(), query.value(0).toInt());
        if (query.value(0).toInt() == this->unitId) {
            this->comboUnits->setCurrentIndex(i);
        }
        i++;
    }

    connect(this->buttonDelete, SIGNAL(clicked()), this, SLOT(deleteFromDB()));
    //connect(this->comboUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUnit(int)));
    //connect(this->editSlot, SIGNAL(editingFinished()), this, SLOT(updateSlot()));
    //connect(this->checkBoxIsHidden, SIGNAL(stateChanged(int)), this, SLOT(updateIsHidden(int)));
}

void UnitDep::deleteFromDB()
{
    if (QMessageBox::question(this, "Подтвердите действие", "Вы точно хотите удалить?", QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
        QSqlQuery query("DELETE FROM AllocationUnits "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }

        emit wasDeleted(this);
    }
}

void UnitDep::setNewUnitName(int id, const QString &name)
{
    if (this->unitId == id) {
        int size = this->comboUnits->count();
        for (int i = 0; i < size; i++) {
            if (this->comboUnits->itemData(i) == id) {
                this->comboUnits->setItemText(i, name);
                this->setTitle(name);
                break;
                
            }
        }
    }
}

bool UnitDep::eventFilter(QObject *target, QEvent *event)
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

void UnitDep::updateUnit() // void UnitDep::updateUnit(int index)
{
    this->unitId = this->comboUnits->itemData(comboUnits->currentIndex()).toInt(); //this->unitId = this->comboUnits->itemData(index).toInt();
    this->setTitle(this->comboUnits->itemText(comboUnits->currentIndex()));        //this->setTitle(this->comboUnits->itemText(index));

    QSqlQuery query("UPDATE AllocationUnits "
              "SET unit_id = " + QString::number(this->unitId) + " "
              "WHERE id = " + QString::number(this->allocId));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

}

void UnitDep::updateSlot()
{
    QString slot = this->editSlot->text();
    if (!slot.isEmpty()) {
        QSqlQuery query("UPDATE AllocationUnits "
                  "SET slot = '" + slot + "' "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
}

void UnitDep::updateIsHidden()  //void UnitDep::updateIsHidden(int isHidden)
{
    QSqlQuery query("UPDATE AllocationUnits "
              "SET is_hidden = " + QString::number(checkBoxIsHidden->isHidden()) + " "    //              "SET is_hidden = " + QString::number(isHidden) + " "
              "WHERE id = " + QString::number(this->allocId));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void UnitDep::slotSave()
{
    updateUnit();
    updateSlot();
    updateIsHidden();

}
