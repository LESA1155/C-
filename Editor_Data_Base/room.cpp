#include "room.h"

Room::Room(int id, QWidget *parent)
: QGroupBox(parent)
{

    this->setStyleSheet("QGroupBox { background-color: LightGray }");

    QString name;
    int sort;

    if (id < 0) {

        name = "Без имени";
        sort = 1;

        QSqlQuery query;
        query.exec("INSERT INTO Rooms (name, sort) "
                                  "VALUES ('" + name + "', '" + sort + "')");
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        this->id = query.lastInsertId().toInt();
    }
    else {
        this->id = id;

        QSqlQuery query("SELECT "
                            "name "
                            "sort "
                        "FROM Rooms "
                        "WHERE id = " + QString::number(id));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        if (!query.next()) {
            QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        name = query.value(0).toString();
        sort =1;
    }



    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    QHBoxLayout *nameLayout = new QHBoxLayout();
    mainLayout->addLayout(nameLayout);
    QLabel *labelName = new QLabel("Наименование: ");
    nameLayout->addWidget(labelName);
    this->editName = new QLineEdit();
    nameLayout->addWidget(this->editName);
    this->editName->setText(name);

    this->buttonDelete = new QPushButton("Удалить");
    nameLayout->addWidget(this->buttonDelete);
    this->buttonDelete->setFocusPolicy(Qt::NoFocus);
    buttonDelete->setStyleSheet("background-color: Cornsilk;");


    this->setTitle(name);




    connect(this->buttonDelete, SIGNAL(clicked()), this, SLOT(deleteFromDB()));
    //connect(this->editName, SIGNAL(editingFinished()), this, SLOT(updateName()));
}


void Room::deleteFromDB()
{
    if (QMessageBox::question(this, "Подтвердите действие", "Вы точно хотите удалить?", QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
        QSqlQuery query;
        query.exec("DELETE FROM Rooms "
                  "WHERE id = " + QString::number(this->id));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        // Удалить из других таблиц если есть
//        query.exec("DELETE FROM Rooms "
//                  "WHERE device_id = " + QString::number(this->id));
//        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
//            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
//        }
//        query.exec("DELETE FROM Rooms "
//                  "WHERE id = " + QString::number(this->id));
//        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
//            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
//        }
        emit wasDeleted(this);
    }
    emit update();
}

void Room::updateName()
{
    QString name = this->editName->text();

    QSqlQuery query;
    query.exec("UPDATE Rooms "
              "SET name = '" + name + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

     setTitle(name);

     emit roomNameChanged(this->id, name);
}


void Room::slotDemoDelete()
{
        emit getID(this->id);
    emit wasDeleted(this);
}

void Room::slotSave()
{
    updateName();
}






