#include "group.h"

Group::Group(int id, QWidget *parent)
    : QGroupBox(parent)
{

    this->setStyleSheet("QGroupBox { background-color: LightGray }");

    QString name;

    if (id < 0) {


        QSqlQuery selectQuery;
        selectQuery.exec("SELECT Rooms.id FROM Rooms INNER JOIN Groups ON Groups.room_id = Rooms.id");
        selectQuery.next();
        this->roomId = selectQuery.value(0).toInt();


        ///////////////////////
        name = "  ";
        QSqlQuery query;
        query.exec("INSERT INTO Groups (name, room_id) "
                   "VALUES ('" + name + "', '" + QString::number(roomId)  + "')");
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        this->id = query.lastInsertId().toInt();
    }
    else {
        this->id = id;
        QSqlQuery query("SELECT "
                            "name, "
                            "room_id "
                        "FROM Groups "
                        "WHERE id = " + QString::number(id));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        if (!query.next()) {
            QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        name = query.value(0).toString();
        roomId = query.value(1).toInt();
    }
    QSqlQuery query;
    setTitle(name);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    QHBoxLayout *nameLayout = new QHBoxLayout();
    mainLayout->addLayout(nameLayout);
    QLabel *labelName = new QLabel("Наименование: ");
    nameLayout->addWidget(labelName);
    this->editName = new QLineEdit();
    nameLayout->addWidget(this->editName);
    this->editName->setText(name);

    QLabel *labelRoomID = new QLabel("Связь с комнатой: ");
    nameLayout->addWidget(labelRoomID);

    comboBoxRoomNameForId = new QComboBox();
    comboBoxRoomNameForId->installEventFilter(this);
    comboBoxRoomNameForId->setFocusPolicy(Qt::StrongFocus);
    nameLayout->addWidget(comboBoxRoomNameForId);

    query.exec("SELECT DISTINCT Rooms.id, Rooms.name FROM Rooms INNER JOIN Groups ON Groups.room_id = Rooms.id");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    for (int i = this->comboBoxRoomNameForId->count(); query.next(); i++) {
        this->comboBoxRoomNameForId->addItem(query.value(1).toString(), query.value(0).toInt());
        if (query.value(0).toInt() == this->roomId) {
            this->comboBoxRoomNameForId->setCurrentIndex(i);
        }
    }

    this->buttonDelete = new QPushButton("Удалить");
    buttonDelete->setStyleSheet("background-color: Cornsilk;");
    nameLayout->addWidget(this->buttonDelete);
    this->buttonDelete->setFocusPolicy(Qt::NoFocus);
    this->setTitle(name);

    connect(this->buttonDelete,SIGNAL(clicked()),this , SLOT(deleteFromDB()));
    //connect(this->comboBoxRoomNameForId, SIGNAL(currentIndexChanged(int)), this, SLOT(updatecomboBoxRoomNameForId(int)));
    //connect(this->editName,SIGNAL(editingFinished()),this , SLOT(updateName()));
    //connect(this->editRoomID,SIGNAL(editingFinished()),this , SLOT(updateRoomID()));

}

void Group::deleteFromDB()
{
    if (QMessageBox::question(this, "Подтвердите действие", "Вы точно хотите удалить?", QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
        QSqlQuery query;
        query.exec("DELETE FROM Groups "
                  "WHERE id = " + QString::number(this->id));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        emit wasDeleted(this);
    }
}
void Group::updateName()
{
    QString name = this->editName->text();
    QSqlQuery query;
    query.exec("UPDATE Groups "
              "SET name = '" + name + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

     setTitle(name);

     emit groupNameChanged(this->id, name);

}

void Group::updatecomboBoxRoomNameForId()
{
    this->roomId = this->comboBoxRoomNameForId->itemData(comboBoxRoomNameForId->currentIndex()).toInt();
    QSqlQuery query;

    query.exec("UPDATE Groups "
               "SET room_id = " % QString::number(this->roomId) %
               " WHERE id = " % QString::number(this->id));



// userData попробовать использовать

}

void Group::slotSave()
{
    updateName();
    updatecomboBoxRoomNameForId();

}

bool Group::eventFilter(QObject *target, QEvent *event)
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

// "VALUES ('" + name + "', '" + QString::number(roomID)  + "')");
