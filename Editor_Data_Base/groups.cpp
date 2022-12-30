#include "groups.h"

Groups::Groups(QWidget *parent)
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

    setWindowTitle("Перечень Групп");
    setMinimumWidth(800);

    btnSave = new QPushButton("Сохранить изменения");
    btnSave->setStyleSheet("background-color: #56887D; color: white");
    mainLayout->addWidget(this->btnSave);
    btnSave->setFocusPolicy(Qt::NoFocus);

    buttonAdd = new QPushButton("Добавить Группу");
    buttonAdd->setStyleSheet("background-color: Cornsilk;");
    mainLayout->addWidget(this->buttonAdd);
    buttonAdd->setFocusPolicy(Qt::NoFocus);

    QSqlQuery query("SELECT id "
                    "FROM Groups");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    while (query.next()) {
        Group *groupEdit = new Group(query.value(0).toInt());
        groupEdits.push_back(groupEdit);
        scrollLayout->addWidget(groupEdit);
        connect(groupEdit, SIGNAL(wasDeleted(Group *)), this, SLOT(remove(Group *)));
        connect(groupEdit, SIGNAL(groupNameChanged(int, const QString &)), this, SLOT(setNewGroupName(int, const QString &)));
        connect(this->btnSave, SIGNAL(clicked()), groupEdit, SLOT(slotSave()));
    }
    connect(this->buttonAdd, SIGNAL(clicked()), this, SLOT(addGroup()));
}

void Groups::remove(Group *groupEdit)
{
    QVector <Group *>::iterator it = std::find(
            this->groupEdits.begin(),
            this->groupEdits.end(),
            groupEdit);
    if (it != this->groupEdits.end()) {
        this->groupEdits.erase(it);
        this->scrollLayout->removeWidget(groupEdit);
        delete groupEdit;

        emit updated();
    }
    else {
        throw DeleteException();
    }
}

void Groups::addGroup()
{
    Group *groupEdit = new Group();
    this->groupEdits.push_back(groupEdit);
    this->scrollLayout->addWidget(groupEdit);
    connect(groupEdit, SIGNAL(groupNameChanged(int, const QString &)), this, SLOT(setNewGroupName(int, const QString &)));
    connect(groupEdit, SIGNAL(wasDeleted(Group *)), this, SLOT(remove(Group *)));
    connect(this->btnSave, SIGNAL(clicked()), groupEdit, SLOT(slotSave()));
    emit updated();
}

void Groups::setNewGroupName(int id, const QString &name)
{
    emit groupNameChanged(id, name);
}




