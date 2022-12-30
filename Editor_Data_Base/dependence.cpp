#include "dependence.h"

Dependence::Dependence(int allocId, QWidget *parent) : QDialog(parent)

{

    this->allocId = allocId;


    this->mainLayout = new QVBoxLayout();
    this->setLayout(this->mainLayout);

    QSqlQuery query;

    query.exec(QString("SELECT Units.name, Devices.name "
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

    QString unitName = query.value(0).toString();
    QString deviceName = query.value(1).toString();
    this->setWindowTitle(QString("Зависимости для " + unitName + " (" + deviceName + ") "));

    query.exec(QString("SELECT AllocationUnits.id, Dependence.id "
                       "FROM AllocationUnits "
                       "LEFT JOIN Dependence ON Dependence.master = AllocationUnits.id AND Dependence.slave = " + QString::number(this->allocId) + " "
                       "WHERE AllocationUnits.is_hidden = 0 AND AllocationUnits.device_id = "
                       "(SELECT device_id FROM AllocationUnits WHERE id = ") + QString::number(this->allocId) + ") ORDER BY AllocationUnits.is_main DESC");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

    while (query.next()) {
        int unitAllocId = query.value(0).toInt();
        int depenId = -1;
        if (!query.value(1).isNull()) {
            depenId = query.value(1).toInt();
        }

        if (unitAllocId != this->allocId) {
            DependenceEdit *depen = new DependenceEdit(unitAllocId, allocId, depenId);
            this->mainLayout->addWidget(depen);
            this->depens.push_back(depen);
        }
    }


}

void Dependence::deleteAll()
{
    QSqlQuery query;
    query.exec("DELETE FROM Dependence "
              "WHERE slave = " + QString::number(this->allocId));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}
