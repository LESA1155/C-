#include "content.h"

Content::Content(int deviceId, bool isMain, QWidget *parent)
    : QDialog(parent)
{

    //this->setMinimumSize(1000, 800);
    setWindowIcon(QIcon(":/logo/device.png"));
    this->id = deviceId;
    this->isMain = isMain;
    QSqlQuery query;
    query.exec("SELECT name "
                    "FROM Devices "
                    "WHERE id = " + QString::number(id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    if (!query.next()) {
        QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    this->setWindowTitle(query.value(0).toString());


    query.exec(QString("SELECT ") % (this->isMain ? "main_" : "reserve_") % "defective_unit_allocation_id, " %
                                    (this->isMain ? "main_" : "reserve_") % "defective_add_unit_allocation_id "
               "FROM Devices "
               " WHERE id = " % QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    if (!query.next()) {
        QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    if (query.value(0).isNull()) {
        this->defectiveUnitId = -1;
    }
    else {
        this->defectiveUnitId = query.value(0).toInt();
    }
    if (query.value(1).isNull()) {
        this->defectiveAddUnitId = -1;
    }
    else {
        this->defectiveAddUnitId = query.value(1).toInt();
    }


    this->mainLayout = new QGridLayout();
    this->setLayout(this->mainLayout);

    QLabel *label = new QLabel(this->isMain ? "Основной состав" : "Резервный состав");
    this->mainLayout->addWidget(label, 1, 1, 1, 2);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 24px;");

    this->mainLayout->addWidget(new QLabel("Модуль отвечающий за основную сеть:"), 2, 1, Qt::AlignRight);


    this->comboDefectiveUnits = new QComboBox();
    comboDefectiveUnits->installEventFilter(this);
    comboDefectiveUnits->setFocusPolicy(Qt::StrongFocus);
    this->mainLayout->addWidget(this->comboDefectiveUnits, 2, 2);

    this->mainLayout->addWidget(new QLabel("Модуль отвечающий за доп. сеть:"), 3, 1, Qt::AlignRight);

    this->comboDefectiveAddUnits = new QComboBox();
    comboDefectiveAddUnits->installEventFilter(this);
    comboDefectiveAddUnits->setFocusPolicy(Qt::StrongFocus);
    this->mainLayout->addWidget(this->comboDefectiveAddUnits, 3, 2);

    this->fillDefectiveUnits();

    this->scrollArea = new QScrollArea();
    this->mainLayout->addWidget(this->scrollArea, 4, 1, 1, 2);
    this->scrollArea->setWidgetResizable(true);
    this->scrollArea->setMinimumWidth(750);

    this->scrollWidget = new QWidget();
    this->scrollArea->setWidget(this->scrollWidget);

    this->scrollLayout = new QVBoxLayout();
    this->scrollWidget->setLayout(this->scrollLayout);
    this->scrollLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);


    btnSave = new QPushButton("Записать данные");
    mainLayout->addWidget(btnSave, 5, 1, 1, 2);
    btnSave->setFocusPolicy(Qt::NoFocus);

    buttonAdd = new QPushButton("Добавить плату");
    mainLayout->addWidget(buttonAdd, 6, 1, 1, 2);
    buttonAdd->setFocusPolicy(Qt::NoFocus);

    addUnits();

    connect(this->buttonAdd, SIGNAL(clicked()), this, SLOT(addUnit()));

//        QFile file(":/css/style.css");
//        QString textCss;
//        if (!file.open(QIODevice::ReadOnly))
//        {
//            qDebug() << "Ошибка открытия для чтения";
//        }
//        textCss = file.readAll();
//        //qDebug()<<file.isOpen();
//        this->setStyleSheet(textCss);

}

Content::~Content()
{
    removeUnits();

    delete this->buttonAdd;

    delete this->mainLayout;
}

void Content::addUnits()
{
    QSqlQuery query("SELECT id "
                    "FROM AllocationUnits "
                    "WHERE device_id = " + QString::number(this->id) + " AND is_main = " + QString::number(this->isMain));
    QSqlError error = query.lastError();
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    while (query.next()) {
        UnitDep *unit = new UnitDep(this->id, this->isMain, query.value(0).toInt());
        this->units.push_back(unit);
        this->scrollLayout->addWidget(unit);
        connect(unit, SIGNAL(wasDeleted(UnitDep *)), this, SLOT(remove(UnitDep *)));
        connect(this, SIGNAL(unitNameChanged(int, const QString &)), unit, SLOT(setNewUnitName(int, const QString &)));

    }
}

void Content::removeUnits()
{
    while (this->units.size()) {
        delete this->units.back();
        this->units.pop_back();
    }
}

void Content::setNewUnitName(int id, const QString &name)
{
    emit unitNameChanged(id, name);
}

void Content::updateUnits()
{
    removeUnits();
    addUnits();
}

void Content::remove(UnitDep *unit)
{
    std::vector<UnitDep *>::iterator it = std::find(
            this->units.begin(),
            this->units.end(),
            unit);
    if (it != this->units.end()) {
        this->units.erase(it);
        this->scrollLayout->removeWidget(unit);
        delete unit;

        fillDefectiveUnits();
    }
    else {
        throw DeleteException();
    }
}

void Content::addUnit()
{
    UnitDep *unit = new UnitDep(this->id, this->isMain);
    this->units.push_back(unit);
    this->scrollLayout->addWidget(unit);
    connect(unit, SIGNAL(wasDeleted(UnitDep *)), this, SLOT(remove(UnitDep *)));
    connect(this, SIGNAL(unitNameChanged(int, const QString &)), unit, SLOT(setNewUnitName(int, const QString &)));
    connect(btnSave, SIGNAL(clicked()), unit, SLOT(slotSave()));
    //connect(btnSave, SIGNAL(ckicked()), this, SLOT(slotSave()));


    fillDefectiveUnits();
}

bool Content::eventFilter(QObject *target, QEvent *event)
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

void Content::fillDefectiveUnits()
{
//    disconnect(this->comboDefectiveUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDefectiveUnit(int)));
//    disconnect(this->comboDefectiveAddUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDefectiveAddUnit(int)));

    this->comboDefectiveUnits->clear();
    this->comboDefectiveAddUnits->clear();

    this->comboDefectiveUnits->addItem("Отсутствует", -1);
    this->comboDefectiveUnits->setCurrentIndex(0);

    this->comboDefectiveAddUnits->addItem("Отсутствует", -1);
    this->comboDefectiveAddUnits->setCurrentIndex(0);

    QSqlQuery query("SELECT AllocationUnits.id, Units.name, AllocationUnits.slot "
                    "FROM Units INNER JOIN AllocationUnits on ALlocationUnits.unit_id = Units.id "
                    "WHERE ALlocationUnits.device_id = " % QString::number(this->id) % " AND is_main = " % QString::number(this->isMain));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

    int index = this->comboDefectiveUnits->count();
    int addIndex = this->comboDefectiveAddUnits->count();
    while (query.next()) {
        int id = query.value(0).toInt();

        QString name = query.value(2).toString();
        if (!name.isEmpty()) {
            name += ": ";
        }
        name += query.value(1).toString();

        this->comboDefectiveUnits->addItem(name, id);
        this->comboDefectiveAddUnits->addItem(name, id);

        if (id == this->defectiveUnitId) {
            this->comboDefectiveUnits->setCurrentIndex(index);
        }
        if (id == this->defectiveAddUnitId) {
            this->comboDefectiveAddUnits->setCurrentIndex(addIndex);
        }

        index++;
        addIndex++;
    }

//    connect(this->comboDefectiveUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDefectiveUnit(int)));
//    connect(this->comboDefectiveAddUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDefectiveAddUnit(int)));
}

void Content::updateDefectiveUnit(int index)
{
    if (index == 0) {
        this->defectiveUnitId = -1;
    }
    else {
        this->defectiveUnitId = this->comboDefectiveUnits->itemData(comboDefectiveUnits->currentIndex()).toInt();
    }

    QSqlQuery query;
    query.exec(QString("UPDATE Devices SET ") % (this->isMain ? "main_" : "reserve_") % "defective_unit_allocation_id" % " = "
                 % (this->defectiveUnitId < 0 ? "NULL" : QString::number(this->defectiveUnitId)) %
               " WHERE id = " % QString::number(this->id));

    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void Content::updateDefectiveAddUnit(int index)
{
    if (index == 0) {
        this->defectiveAddUnitId = -1;
    }
    else {
        this->defectiveAddUnitId = this->comboDefectiveAddUnits->itemData(comboDefectiveAddUnits->currentIndex()).toInt();
    }

    QSqlQuery query;
    query.exec(QString("UPDATE Devices SET ") % (this->isMain ? "main_" : "reserve_") % "defective_add_unit_allocation_id" % " = "
                 % (this->defectiveAddUnitId < 0 ? "NULL" : QString::number(this->defectiveAddUnitId)) %
               " WHERE id = " % QString::number(this->id));

    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

//void Content::slotSave()
//{
//    updateDefectiveUnit();
//    updateDefectiveAddUnit();
//}


