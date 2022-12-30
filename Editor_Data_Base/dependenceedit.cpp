#include "dependenceedit.h"

DependenceEdit::DependenceEdit(int allocId, int slaveAllocId, int depenId, QWidget *parent) : QWidget(parent)
{
    this->allocId = allocId;
    this->slaveAllocId = slaveAllocId;
    this->depenId = depenId;

    this->mainLayout = new QHBoxLayout();
    this->setLayout(this->mainLayout);

    this->labelSlot = new QLabel();
    this->mainLayout->addWidget(this->labelSlot, 0, Qt::AlignLeft);
//    this->labelSlot->setAlignment(Qt::AlignRight);
    this->labelSlot->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    this->labelName = new QLabel();
    this->mainLayout->addWidget(this->labelName, 0, Qt::AlignRight);
//    this->labelName->setAlignment(Qt::AlignRight);
    this->labelName->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    this->labelType = new QLabel();
    this->mainLayout->addWidget(this->labelType, 0, Qt::AlignRight);
    this->labelType->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//    this->labelType->setAlignment(Qt::AlignHCenter);

    this->checkBoxActive = new QCheckBox("Включить зависимость");
    this->mainLayout->addWidget(this->checkBoxActive, 0, Qt::AlignRight);
    this->checkBoxActive->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    this->checkBoxCritical = new QCheckBox("Критическая зависимость");
    this->mainLayout->addWidget(this->checkBoxCritical, 0, Qt::AlignRight);
    this->checkBoxCritical->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QSqlQuery query;

    query.exec(QString("SELECT AllocationUnits.slot, Units.name, AllocationUnits.is_main, Devices.main_node_title, Devices.reserve_node_title "
                       "FROM AllocationUnits "
                       "INNER JOIN Units ON AllocationUnits.unit_id = Units.id "
                       "INNER JOIN Devices ON AllocationUnits.device_id = Devices.id "
                       "WHERE AllocationUnits.id = " + QString::number(this->allocId)));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    if (!query.next()) {
        QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    this->labelSlot->setText(query.value(0).toString());
    this->labelName->setText(query.value(1).toString());
    this->labelType->setText(" (" + (query.value(2).toInt() ? query.value(3).toString() : query.value(4).toString()) + ")");

    bool isActive;
    bool isCritical;

    if (this->depenId <= 0) {
        isActive = false;
        isCritical = false;
    }
    else {
        query.exec(QString("SELECT Dependence.is_critical "
                           "FROM Dependence "
                           "WHERE Dependence.id = " + QString::number(this->depenId)));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        if (!query.next()) {
            QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }

        isActive = true;
        isCritical = query.value(0).toInt();
    }

    this->checkBoxActive->setChecked(isActive);
    this->checkBoxCritical->setChecked(isCritical);
    if (!isActive) {
        this->checkBoxCritical->setEnabled(false);
    }

    connect(this->checkBoxActive, SIGNAL(toggled(bool)), this, SLOT(updateActive(bool)));
    connect(this->checkBoxCritical, SIGNAL(toggled(bool)), this, SLOT(updateCritical(bool)));
}

void DependenceEdit::updateActive(bool isActive)
{
    if (isActive) {
        this->checkBoxCritical->setEnabled(true);
        QSqlQuery query;
        query.exec("INSERT INTO Dependence (slave, master, is_critical) "
                   "VALUES (" + QString::number(this->slaveAllocId) + ", " +
                   QString::number(this->allocId) + ", 0)");
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        this->depenId = query.lastInsertId().toInt();
    }
    else {
        this->checkBoxCritical->setChecked(false);
        this->checkBoxCritical->setEnabled(false);

        QSqlQuery query;
        query.exec("DELETE FROM Dependence "
                  "WHERE slave = " + QString::number(this->slaveAllocId) +
                  " AND master = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
}

void DependenceEdit::updateCritical(bool isCritical)
{
    QSqlQuery query;
    query.exec("UPDATE Dependence "
              "SET is_critical = " + QString::number(isCritical) + " "
              "WHERE id = " + QString::number(this->depenId));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}



