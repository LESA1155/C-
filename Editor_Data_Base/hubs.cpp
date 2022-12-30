#include "hubs.h"

Hubs::Hubs(QWidget *parent)
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

    setWindowTitle("Перечень Хабов");
    setMinimumWidth(800);

    btnSave = new QPushButton("Сохранить");
    mainLayout->addWidget(this->btnSave);
    buttonAdd = new QPushButton("Добавить Хаб");
    mainLayout->addWidget(this->buttonAdd);

    buttonAdd->setFocusPolicy(Qt::NoFocus);
    buttonAdd->setStyleSheet("background-color: Cornsilk;");
    btnSave->setStyleSheet("background-color: #56887D; color: white");


    QSqlQuery query("SELECT id "
                    "FROM Hubs");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    while (query.next()) {
        Hub *hubEdit = new Hub(query.value(0).toInt());
        hubEdits.push_back(hubEdit);
        scrollLayout->addWidget(hubEdit);

        connect(hubEdit, SIGNAL(hubNameChanged(int, const QString &)), this, SLOT(setNewHubName(int, const QString &)));
        connect(this->btnSave, SIGNAL(clicked()), hubEdit , SLOT(slotSave()));
    }
    connect(this->buttonAdd, SIGNAL(clicked()), this, SLOT(addHub()));

}


//Метод удаления
void Hubs::remove(Hub *hubEdit)
{
    QVector <Hub *>::iterator it = std::find(
            this->hubEdits.begin(),
            this->hubEdits.end(),
                hubEdit);
    if (it != this->hubEdits.end()) {
        this->hubEdits.erase(it);
        this->scrollLayout->removeWidget(hubEdit);
        delete hubEdit;

        emit updated();
    }
    else {
        throw DeleteException();
    }
}


//// Метод добавления ХАба

void Hubs::addHub()
{
    Hub *hubEdit = new Hub();
    this->hubEdits.push_back(hubEdit);
    this->scrollLayout->addWidget(hubEdit);

    connect(hubEdit, SIGNAL(hubNameChanged(int, const QString &)), this, SLOT(setNewHubName(int, const QString &)));
    connect(hubEdit, SIGNAL(wasDeleted(Hub *)), this, SLOT(remove(Hub *)));
    connect(this->btnSave, SIGNAL(clicked()), hubEdit, SLOT(slotSave()));

    emit updated();
        this->scrollArea->verticalScrollBar()->setSliderDown(true);
}


////  Метод присвоения нового имени
void Hubs::setNewHubName(int id, const QString &name)
{
    emit hubNameChanged(id, name);
}





