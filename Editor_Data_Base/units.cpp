#include "units.h"

Units::Units(QWidget *parent)
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

    setWindowTitle("Перечень Модулей");
    setMinimumWidth(800);

    btnSave = new QPushButton("Сохранить изменения");
    btnSave->setStyleSheet("background-color: #56887D; color: white");
    mainLayout->addWidget(this->btnSave);
    btnSave->setFocusPolicy(Qt::NoFocus);


    buttonAdd = new QPushButton("Добавить Модуль");
    buttonAdd->setStyleSheet("background-color: Cornsilk;");
    mainLayout->addWidget(this->buttonAdd);
    buttonAdd->setFocusPolicy(Qt::NoFocus);

    QSqlQuery query("SELECT id "
                    "FROM Units");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    while (query.next()) {
        Unit *unitEdit = new Unit(query.value(0).toInt());
        unitEdits.push_back(unitEdit);
        scrollLayout->addWidget(unitEdit);

        connect(unitEdit, SIGNAL(unitNameChanged(int, const QString &)), this, SLOT(setNewUnitName(int, const QString &)));
        connect(btnSave, SIGNAL(clicked()), unitEdit, SLOT(slotSave()));
    }
    connect(this->buttonAdd, SIGNAL(clicked()), this, SLOT(addUnit()));
}


void Units::remove(Unit *unitEdit)
{
    QVector <Unit *>::iterator it = std::find(
            this->unitEdits.begin(),
            this->unitEdits.end(),                unitEdit);
    if (it != this->unitEdits.end()) {
        this->unitEdits.erase(it);
        this->scrollLayout->removeWidget(unitEdit);
        delete unitEdit;

        emit updated();
    }
    else {
        throw DeleteException();
    }
}

void Units::addUnit()
{
    Unit *unitEdit = new Unit();
    this->unitEdits.push_back(unitEdit);
    this->scrollLayout->addWidget(unitEdit);
    connect(unitEdit, SIGNAL(unitNameChanged(int, const QString &)), this, SLOT(setNewUnitName(int, const QString &)));
    connect(unitEdit, SIGNAL(wasDeleted(Unit *)), this, SLOT(remove(Unit *)));
    connect(btnSave, SIGNAL(clicked()), unitEdit, SLOT(slotSave()));
    emit updated();
    this->scrollArea->verticalScrollBar()->setSliderDown(true);
}

void Units::setNewUnitName(int id, const QString &name)
{
    emit unitNameChanged(id, name);
}


