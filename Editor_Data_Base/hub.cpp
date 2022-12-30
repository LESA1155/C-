#include "hub.h"

Hub::Hub(int id, QWidget *parent)
    : QGroupBox(parent)
{
this->setStyleSheet("QGroupBox { background-color: LightGray }");

    QString name;

    int x;
    int y;
    int isVertical;
    int percent;
    int isHidden;
    QString defectiveUnitMain;
    QString defectiveUnitSpareMain;
    QString defectiveUniteReserve;
    QString defectiveUnitSpareReserve;


    if (id < 0) {

        QSqlQuery selectQuery;
        selectQuery.exec("SELECT Groups.id FROM Groups INNER JOIN Hubs ON Hubs.group_id = Groups.id");
        selectQuery.next();
        this->groupID = selectQuery.value(0).toInt();



        name = "Без имени";
        master = 0;
        x = 0;
        y = 0;
        isVertical = 0;
        percent = 0;
        isHidden = 0;
        defectiveUnitMain = "";
        defectiveUnitSpareMain = "";
        defectiveUniteReserve = "";
        defectiveUnitSpareReserve = "";
        QSqlQuery query;
        query.exec("INSERT INTO Hubs(name, master, x, y, is_vertical, percent, is_hidden, group_id, defective_unit_main, defective_unit_spare_main, defective_unit_reserve, defective_unit_spare_reserve) "
                   "VALUES ('" + name + "', " + QString::number(master) + ", " + QString::number(x) + "," + QString::number(y) + " , " + QString::number(isVertical) + ", " + QString::number(percent) + ", "
                   + QString::number(isHidden) + ", " + QString::number(groupID) + ", '" + defectiveUnitMain + "', '" + defectiveUnitSpareMain + "','" + defectiveUniteReserve + "' , '" + defectiveUnitSpareReserve + "')");

        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        this->id = query.lastInsertId().toInt();
    }
        else {
        this->id = id;


        QSqlQuery query ("SELECT "
                         "name, "
                         "master, "
                         "x, "
                         "y, "
                         "is_vertical, "
                         "percent, "
                         "is_hidden, "
                         "group_id, "
                         "defective_unit_main, "
                         "defective_unit_spare_main, "
                         "defective_unit_reserve, "
                         "defective_unit_spare_reserve "
                      "FROM Hubs "
                      "WHERE id =  " + QString::number(id));

                if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
                    QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
                }
                if (!query.next()) {
                    QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
                }

                name =  query.value(0).toString();
                master = query.value(1).toInt();
                x =  query.value(2).toInt();
                y = query.value(3).toInt();
                isVertical =  query.value(4).toInt();
                percent = query.value(5).toInt();
                isHidden =  query.value(6).toInt();
                groupID  = query.value(7).toInt();
//                qDebug() << "groupID = " << groupID << endl;
                defectiveUnitMain = query.value(8).toString();
                defectiveUnitSpareMain = query.value(9).toString();
                defectiveUniteReserve = query.value(10).toString();
                defectiveUnitSpareReserve= query.value(11).toString();
    }

    setTitle(name);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    QHBoxLayout *nameLayout = new QHBoxLayout();
    mainLayout->addLayout(nameLayout);

    QLabel *labelName = new QLabel("Имя Хаба: ");
    nameLayout->addWidget(labelName);

    this->editName = new QLineEdit();
    nameLayout->addWidget(editName);
    this->editName->setText(name);


    QLabel *masterLabel = new QLabel("Подключен к Хабу: ");
    nameLayout->addWidget(masterLabel);

    this->comboMaster = new QComboBox();
    comboMaster->installEventFilter(this);
    comboMaster->setFocusPolicy(Qt::StrongFocus);
    nameLayout->addWidget(comboMaster);
    fillComboMaster();

   /* this->editMaster = new QLineEdit();
    nameLayout->addWidget(editMaster);
    this->editMaster->setText(QString::number(master));
   */

    QLabel *percentLabel = new QLabel("Пиксели в процентах: ");
    nameLayout->addWidget(percentLabel);
    this->editPercent = new QLineEdit();

    nameLayout->addWidget(editPercent);
    this->editPercent->setText(QString::number(percent));

    QLabel *groupIDLabel = new QLabel("Группа");
    nameLayout->addWidget(groupIDLabel);

    this->comboGroups = new QComboBox();
    comboGroups->installEventFilter(this);
    comboGroups->setFocusPolicy(Qt::StrongFocus);
    nameLayout->addWidget(comboGroups);
    fillComboGroups();

    QHBoxLayout *xyvhBLayout = new QHBoxLayout();
    mainLayout->addLayout(xyvhBLayout);


    QLabel *xLabel = new QLabel("Координата X: ");
    xyvhBLayout->addWidget(xLabel);

    this->editX = new QLineEdit();
    xyvhBLayout->addWidget(editX);
    this->editX->setText(QString::number(x));

    QLabel *yLabel = new QLabel("Координата Y: ");
    xyvhBLayout->addWidget(yLabel);

    this->editY = new QLineEdit();
    xyvhBLayout->addWidget(editY);
    this->editY->setText(QString::number(y));


    this->checkBoxIsHidden = new QCheckBox("Скрывать");
    xyvhBLayout->addWidget(checkBoxIsHidden);
    this->checkBoxIsHidden->setChecked(isHidden);

    this->checkBoxIsVertical = new QCheckBox("Вертикально");
    xyvhBLayout->addWidget(checkBoxIsVertical);
    this->checkBoxIsVertical->setChecked(isVertical);

    this->buttonDelete = new QPushButton("Удалить");
    buttonDelete->setStyleSheet("background-color: Cornsilk;");
    xyvhBLayout->addWidget(buttonDelete);


    QGridLayout *defectiveLayout = new QGridLayout();
    mainLayout->addLayout(defectiveLayout);

    QLabel *defectiveUnitMainLabel = new QLabel("Неисправный модуль основной сети");
    defectiveLayout->addWidget(defectiveUnitMainLabel,0,0);

    this->editDefectiveUnitMain = new QLineEdit();
    defectiveLayout->addWidget(editDefectiveUnitMain,0,1);
    this->editDefectiveUnitMain->setText(defectiveUnitMain);
    this->editDefectiveUnitMain->setPlaceholderText("Неисправное главное устройство");

    this->editDefectiveUnitSpareMain = new QLineEdit();
    defectiveLayout->addWidget(editDefectiveUnitSpareMain,0,2);
    this->editDefectiveUnitSpareMain->setText(defectiveUnitSpareMain);


    QLabel *defectiveUnitReserveLabel = new QLabel("Неисправный модуль основной сети");
    defectiveLayout->addWidget(defectiveUnitReserveLabel,1,0);

    this->editDefectiveUniteReserve = new QLineEdit();
    defectiveLayout->addWidget(editDefectiveUniteReserve,1,1);
    this->editDefectiveUniteReserve->setText(defectiveUniteReserve);

    this->editDefectiveUnitSpareReserve = new QLineEdit();
    defectiveLayout->addWidget(editDefectiveUnitSpareReserve,1,2);
    this->editDefectiveUnitSpareReserve->setText(defectiveUnitSpareReserve);


    connect(this->buttonDelete,SIGNAL(clicked()),this , SLOT(deleteFromDB()));

//    connect(this->editName,SIGNAL(editingFinished()),this , SLOT(updateName()));
//    connect(this->editX,SIGNAL(editingFinished()),this , SLOT(updateX()));
//    connect(this->editY,SIGNAL(editingFinished()),this , SLOT(updateY()));
//    connect(this->checkBoxIsHidden, SIGNAL(toggled(bool)), this, SLOT(updateIsHidden(bool)));
//    connect(this->checkBoxIsVertical, SIGNAL(toggled(bool)), this, SLOT(updateIsVertical(bool)));
//    connect(this->editPercent,SIGNAL(editingFinished()),this , SLOT(updatePercent()));
//    connect(this->editDefectiveUnitMain,SIGNAL(editingFinished()),this , SLOT(updatedefectiveUniteMain()));
//    connect(this->editDefectiveUnitSpareMain,SIGNAL(editingFinished()),this , SLOT(updatedefectiveUnitSpareMain()));
//    connect(this->editDefectiveUniteReserve,SIGNAL(editingFinished()),this , SLOT(updatedefectiveUniteReserve()));
//    connect(this->editDefectiveUnitSpareReserve,SIGNAL(editingFinished()),this , SLOT(updatedefectiveUnitSpareReserve()));
//    connect(this->comboGroups, SIGNAL(currentIndexChanged(int)), this, SLOT(updateComboGroups()));
//    connect(this->comboMaster, SIGNAL(currentIndexChanged(int)), this, SLOT(updateComboMaster()));



}

void Hub::deleteFromDB()
{
    if (QMessageBox::question(this, "Подтвердите действие", "Вы точно хотите удалить?", QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
        QSqlQuery query;
        query.exec("DELETE FROM Hubs "
                  "WHERE id = " + QString::number(this->id));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        emit wasDeleted(this);
    }
}

void Hub::updateName()
{
    QString name = this->editName->text();
    QSqlQuery query;
    query.exec("UPDATE Hubs "
              "SET name = '" + name + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

     setTitle(name);

     emit hubNameChanged(this->id, name);
}

//void Hub::updateMaster()
//{
//    QString master = this->editMaster->text();
//    QSqlQuery query;
//    query.exec("UPDATE Hubs "
//              "SET master = '" + master + "' "
//              "WHERE id = " + QString::number(this->id));
//    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
//        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
//    }
//}

void Hub::updateX()
{
    QString X = this->editX->text();
    QSqlQuery query;
    query.exec("UPDATE Hubs "
              "SET x = '" + X + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}


void Hub::updateY()
{
    QString Y = this->editY->text();
    QSqlQuery query;
    query.exec("UPDATE Hubs "
              "SET y = '" + Y + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}


void Hub::updateIsHidden()
{

    QSqlQuery query;
    query.exec("UPDATE Hubs "
              "SET is_hidden = '" + QString::number(checkBoxIsHidden->isChecked()) + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void Hub::updateIsVertical()
{
    QSqlQuery query;
    query.exec("UPDATE Hubs "
              "SET is_vertical = '" + QString::number(checkBoxIsVertical->isChecked()) + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void Hub::updatePercent()
{
    QString percent = this->editPercent->text();
    QSqlQuery query;
    query.exec("UPDATE Hubs "
              "SET percent = '" + percent + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}




void Hub::updatedefectiveUniteMain()
{
    QString  defectiveUniteMain = this->editDefectiveUnitMain->text();
    QSqlQuery query;
    query.exec("UPDATE Hubs "
              "SET defective_unit_main = '" + defectiveUniteMain + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

}


void Hub::updatedefectiveUnitSpareMain()
{
    QString  defectiveUniteSpareMain = this->editDefectiveUnitSpareMain->text();
    QSqlQuery query;
    query.exec("UPDATE Hubs "
              "SET defective_unit_spare_main = '" + defectiveUniteSpareMain + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}



void Hub::updatedefectiveUniteReserve()
{
    QString  defectiveUniteReserve = this->editDefectiveUniteReserve->text();
    QSqlQuery query;
    query.exec("UPDATE Hubs "
              "SET defective_unit_reserve = '" + defectiveUniteReserve + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void Hub::updatedefectiveUnitSpareReserve()
{
    QString  defectiveUniteSpareReserve = this->editDefectiveUnitSpareReserve->text();
    QSqlQuery query;
    query.exec("UPDATE Hubs "
              "SET defective_unit_spare_reserve = '" + defectiveUniteSpareReserve + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}




void Hub::updateComboGroups()
{
    int indexCG = comboGroups->currentIndex();


    this->groupID = this->comboGroups->itemData(indexCG).toInt();
    QSqlQuery query;
    query.exec("UPDATE Hubs "
               "SET group_id = " % QString::number(this->groupID) %
               " WHERE id = " % QString::number(this->id));
}

void Hub::updateComboMaster()
{

    int indexCM = comboMaster->currentIndex();


    this->master = this->comboMaster->itemData(indexCM).toInt();
    QSqlQuery query;
    query.exec("UPDATE Hubs "
               "SET master = " % QString::number(this->master) %
               " WHERE id = " % QString::number(this->id));
}


void Hub::fillComboGroups()
{
   comboGroups->clear();
   QSqlQuery query("SELECT DISTINCT Groups.id, Groups.name FROM Groups ");
   if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
       QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
   }
   for (int i = this->comboGroups->count(); query.next(); i++) {
       this->comboGroups->addItem(query.value(1).toString(), query.value(0).toInt());
       if (query.value(0).toInt() == this->groupID) {
           this->comboGroups->setCurrentIndex(i);
       }
   }
}

void Hub::fillComboMaster()
{
    comboMaster->clear();

    QSqlQuery query("SELECT DISTINCT Hubs.id, Hubs.name FROM Hubs ");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    comboMaster->addItem("Не подключен",0);
    for (int i = this->comboMaster->count(); query.next(); i++) {
        this->comboMaster->addItem(query.value(1).toString(), query.value(0).toInt());
 //       qDebug() << "номер id " <<  query.value(0).toInt() << " - " << " Название группы " <<  query.value(1).toString() << endl;
        if (master == 0)
        {
            this->comboMaster->setCurrentIndex(0);
        }
        else if (query.value(0).toInt() == master )
        {
            this->comboMaster->setCurrentIndex(i);
        }

    }
}

void Hub::slotSave()
{
    updateX();
    updateY();
    updatePercent();
    updatedefectiveUniteMain();
    updatedefectiveUnitSpareMain();
    updateIsHidden();
    updateIsVertical();
    updateComboGroups();
    updateComboMaster();
}

bool Hub::eventFilter(QObject *target, QEvent *event)
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

//     bool eventFilter(QObject *target, QEvent *event);

//     comboMaster->installEventFilter(this);
//     comboMaster->setFocusPolicy(Qt::StrongFocus);
