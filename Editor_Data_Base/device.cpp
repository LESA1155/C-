#include "device.h"

Device::Device(int id, QWidget *parent)
    : QGroupBox(parent)
{

   // this->setStyleSheet("QGroupBox { background-color: LightGray }");

    QString name;

    int useReserve;
    QString mainTitle;
    QString mainShortTitle;
    QString reserveTitle;
    QString reserveShortTitle;
    QString captionNetwork;
    QString captionAddNetwork;
    int priority;

    if (id < 0) {

        name = "Без имени";
        useReserve = 1;
        mainTitle = "Основной";
        mainShortTitle = "О";
        reserveTitle = "Резервный";
        reserveShortTitle = "Р";
        captionNetwork = "Ethernet";
        captionAddNetwork = "Манчестер-2";
        priority = -1;

        QSqlQuery query;
        query.exec("INSERT INTO Devices (name, use_reserve, main_node_title, main_node_short_title, reserve_node_title, reserve_node_short_title, caption_network, caption_add_network, priority)"
                   "VALUES ('" + name + "', '" + QString::number(useReserve) + "', '" + mainTitle + "', '" +
                   mainShortTitle + "', '" + reserveTitle + "', '" + reserveShortTitle + "', '" +
                   captionNetwork + "', '" + captionAddNetwork + "', " + QString::number(priority) +")");
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }

        this->id = query.lastInsertId().toInt();
        }
     else {
        //qDebug() << "Я там где меня не должно быть! - мой id " << id <<  endl;
            this->id = id;

        QSqlQuery query("SELECT "
                            "name, "
                            "use_reserve, "
                            "main_node_title, "
                            "main_node_short_title, "
                            "reserve_node_title, "
                            "reserve_node_short_title, "
                            "caption_network, "
                            "caption_add_network, "
                            "priority "
                        "FROM Devices "
                        "WHERE id = " + QString::number(id));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        if (!query.next()) {
            QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }

        name = query.value(0).toString();
        useReserve = query.value(1).toInt();
        mainTitle = query.value(2).toString();
        mainShortTitle = query.value(3).toString();
        reserveTitle = query.value(4).toString();
        reserveShortTitle = query.value(5).toString();
        captionNetwork = query.value(6).toString();
        captionAddNetwork = query.value(7).toString();
        priority = query.value(8).toInt();
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

    this->checkboxUseReserve = new QCheckBox("Использовать резервный");
    nameLayout->addWidget(this->checkboxUseReserve);
    this->checkboxUseReserve->setChecked(useReserve);

    QGridLayout *nodeLayout = new QGridLayout();
    mainLayout->addLayout(nodeLayout);

    nodeLayout->addWidget(new QLabel("Имя основного узла:"), 0, 0, Qt::AlignRight);
    this->editMainTitle = new QLineEdit();
    nodeLayout->addWidget(this->editMainTitle, 0, 1);
    this->editMainTitle->setText(mainTitle);

    nodeLayout->addWidget(new QLabel("Краткое имя основного узла:"), 0, 2, Qt::AlignRight);
    this->editMainShortTitle = new QLineEdit();
    nodeLayout->addWidget(this->editMainShortTitle, 0, 3);
    this->editMainShortTitle->setText(mainShortTitle);
    this->editMainShortTitle->setFixedWidth(50);

    this->buttonContentMain = new QPushButton("Основной состав");
    nodeLayout->addWidget(this->buttonContentMain, 0, 4);

    nodeLayout->addWidget(new QLabel("Имя резервного узла:"), 1, 0, Qt::AlignRight);
    this->editReserveTitle = new QLineEdit();
    nodeLayout->addWidget(this->editReserveTitle, 1, 1);
    this->editReserveTitle->setText(reserveTitle);

    nodeLayout->addWidget(new QLabel("Краткое имя резервного узла:"), 1, 2, Qt::AlignRight);
    this->editReserveShortTitle = new QLineEdit();
    nodeLayout->addWidget(this->editReserveShortTitle, 1, 3);
    this->editReserveShortTitle->setText(reserveShortTitle);
    this->editReserveShortTitle->setFixedWidth(50);

    this->buttonContentReserve = new QPushButton("Резервный состав");
    nodeLayout->addWidget(this->buttonContentReserve, 1, 4);

    QGridLayout *captionLayout = new QGridLayout();
    mainLayout->addLayout(captionLayout);


    QHBoxLayout *proirityLayout = new QHBoxLayout();
    mainLayout->addLayout(proirityLayout);

    proirityLayout->addWidget(new QLabel("Приоритет:"));
    this->comboboxPriority = new QComboBox();
    comboboxPriority->installEventFilter(this);
    comboboxPriority->setFocusPolicy(Qt::StrongFocus);
    proirityLayout->addWidget(this->comboboxPriority, Qt::AlignLeft);
    this->comboboxPriority->addItem("очень низкий", -2);
    this->comboboxPriority->addItem("низкий", -1);
    this->comboboxPriority->addItem("средний", 0);
    this->comboboxPriority->addItem("высокий", 1);
    this->comboboxPriority->addItem("очень высокий", 2);
    for (int i = 0; i < this->comboboxPriority->count(); i++) {
        if (this->comboboxPriority->itemData(i) == priority) {
            this->comboboxPriority->setCurrentIndex(i);
            break;
        }
    }


    this->buttonDelete = new QPushButton("Удалить");
    buttonDelete->setStyleSheet("background-color: Cornsilk;");
    proirityLayout->addWidget(this->buttonDelete);
    this->buttonDelete->setFocusPolicy(Qt::NoFocus);

    this->setTitle(name);

    this->contentMain = new Content(this->id, true);  //Добавил this->
    this->contentReserve = new Content( this->id, false);   //Добавил this->

    connect(this->buttonDelete, SIGNAL(clicked()), this, SLOT(deleteFromDB()));
    connect(this->buttonContentMain, SIGNAL(clicked()), this->contentMain, SLOT(show()));
    connect(this->buttonContentReserve, SIGNAL(clicked()), this->contentReserve, SLOT(show()));

    /*
    connect(this->comboboxPriority, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePriority(int)));
    connect(this->editName, SIGNAL(editingFinished()), this, SLOT(updateName()));
    connect(this->checkboxUseReserve, SIGNAL(toggled(bool)), this, SLOT(updateUseReserve(bool)));
    connect(this->editMainTitle, SIGNAL(editingFinished()), this, SLOT(updateMainTitle()));
    connect(this->editMainShortTitle, SIGNAL(editingFinished()), this, SLOT(updateMainShortTitle()));
    connect(this->editReserveTitle, SIGNAL(editingFinished()), this, SLOT(updateReserveTitle()));
    connect(this->editReserveShortTitle, SIGNAL(editingFinished()), this, SLOT(updateReserveShortTitle()));
    */

}

Device::~Device()
{
//    delete this->editName;

//    delete this->buttonDelete;


}
// --------------------- Начало методо -------------------

// ----------------------Удаление из базы данных ---------

void Device::deleteFromDB()
{
    if (QMessageBox::question(this, "Подтвердите действие", "Вы точно хотите удалить?", QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
        QSqlQuery query;
        query.exec("DELETE FROM AllocationDevices "
                  "WHERE device_id = " + QString::number(this->id));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        query.exec("DELETE FROM AllocationUnits "
                  "WHERE device_id = " + QString::number(this->id));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        query.exec("DELETE FROM Devices "
                  "WHERE id = " + QString::number(this->id));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }

        emit wasDeleted(this);
    }
}
//------------------------ Метод обновления поля ИМЯ ------------
void Device::updateName()
{
    QString name = this->editName->text();

    QSqlQuery query;
    query.exec("UPDATE Devices "
              "SET name = '" + name + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

     setTitle(name);


    emit deviceNameChanged(this->id, name);
}

//----------------------Метод обновления поля  Use reverse -----------

void Device::updateUseReserve()
{

    QSqlQuery query;
    query.exec("UPDATE Devices "
              "SET use_reserve = '" + QString::number(checkboxUseReserve->isChecked()) + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

//----------------------Метод обновления поля  Main Title-----------
void Device::updateMainTitle()
{
    QString text = this->editMainTitle->text();
    QSqlQuery query;
    query.exec("UPDATE Devices "
              "SET main_node_title = '" + text + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

//------------------Метод обновления поля Main short Title----------

void Device::updateMainShortTitle()
{
    QString text = this->editMainShortTitle->text();
    QSqlQuery query;
    query.exec("UPDATE Devices "
              "SET main_node_short_title = '" + text + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

//----------------- Метод обновления поля Reverse Title --------------
void Device::updateReserveTitle()
{
    QString text = this->editReserveTitle->text();
    QSqlQuery query;
    query.exec("UPDATE Devices "
              "SET reserve_node_title = '" + text + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

//------------------ Метод обновления поля Reverse Short Title
void Device::updateReserveShortTitle()
{
    QString text = this->editReserveShortTitle->text();
    QSqlQuery query;
    query.exec("UPDATE Devices "
              "SET reserve_node_short_title = '" + text + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}



void Device::updatePriority()
{
    int index  = comboboxPriority->currentIndex();
    int priority = this->comboboxPriority->itemData(index).toInt();
    QSqlQuery query;
    query.exec("UPDATE Devices "
              "SET priority = " + QString::number(priority) + " "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void Device::slotSave()
{
    updateName();
    updateMainTitle();
    updateMainShortTitle();
    updateReserveTitle();
    updateReserveShortTitle();
    updatePriority();
    updateUseReserve();
}

bool Device::eventFilter(QObject *target, QEvent *event)
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


