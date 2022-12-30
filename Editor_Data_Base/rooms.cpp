#include "rooms.h"

Rooms::Rooms( QWidget *parent)
    :QWidget(parent)
{

    mainLayout = new QVBoxLayout();
    setLayout(this->mainLayout);

    scrollArea = new QScrollArea();
    mainLayout->addWidget(this->scrollArea);
    scrollArea->setWidgetResizable(true);

    scrollWidget = new QWidget();
    scrollArea->setWidget(this->scrollWidget);

    scrollLayout = new QVBoxLayout();
    scrollWidget->setLayout(this->scrollLayout);
    scrollLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    setWindowTitle("Перечень комнат");
    setMinimumWidth(800);

    btnSave = new QPushButton("Записать изменения");
    mainLayout->addWidget(this->btnSave);
    btnSave->setStyleSheet("background-color: #56887D; color: white");

    buttonAdd = new QPushButton("Добавить комнату");
    mainLayout->addWidget(this->buttonAdd);
    buttonAdd->setFocusPolicy(Qt::NoFocus);
    buttonAdd->setStyleSheet("background-color: Cornsilk;");

  QSqlQuery query("SELECT id "
                  "FROM Rooms");
  if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
      QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
  }
  while (query.next()) {
      Room *roomEdit = new Room(query.value(0).toInt());
      roomEdits.push_back(roomEdit);
      scrollLayout->addWidget(roomEdit);
        connect(roomEdit, SIGNAL(wasDeleted(Room *)), this, SLOT(remove(Room *)));
        connect(roomEdit, SIGNAL(roomNameChanged(int, const QString &)), this, SLOT(setNewRoomName(int, const QString &)));
        connect(this->btnSave, SIGNAL(clicked()), roomEdit, SLOT(slotSave()));

}
    connect(this->buttonAdd, SIGNAL(clicked()), this, SLOT(addRoom()));

}


void Rooms::remove(Room *roomEdit)
{
    idRoomForDelete = roomEdit->GetId();
    if (QMessageBox::question(this, "Подтвердите действие", "Вы точно хотите удалить?", QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
        QVector <Room *>::iterator it = std::find(
            this->roomEdits.begin(),
            this->roomEdits.end(), roomEdit);
    if (it != this->roomEdits.end()) {
        this->roomEdits.erase(it);
        this->scrollLayout->removeWidget(roomEdit);
        delete roomEdit;
        emit updated();
    }
    else{
        throw DeleteException();
        }
    }


}
void Rooms::addRoom()
{
    Room *roomEdit = new Room();
    this->roomEdits.push_back(roomEdit);
    this->scrollLayout->addWidget(roomEdit);
    connect(roomEdit, SIGNAL(wasDeleted(Room *)), this, SLOT(remove(Room *)));
    connect(roomEdit, SIGNAL(roomNameChanged(int, const QString &)), this, SLOT(setNewRoomName(int, const QString &)));
    connect(this->btnSave, SIGNAL(clicked()), roomEdit, SLOT(slotSave()));


    emit updated();
}

void Rooms::setNewRoomName(int id, const QString &name)
{
    emit roomNameChanged(id, name);
}

void Rooms::deleteFromDB_Save(int id)
{
    QSqlQuery query;
    query.exec("DELETE FROM Rooms "
              "WHERE id = " + QString::number(id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

/*void Rooms::slotSave()
{
    deleteFromDB_Save(idRoomForDelete);
}
*/
