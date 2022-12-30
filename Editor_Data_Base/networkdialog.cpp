#include "networkdialog.h"

NetworkDialog::NetworkDialog(QWidget *parent) : QWidget(parent)
{

    this->hubIdMain = -1;
    this->hubIdReserve = -1;

    this->mainLayout = new QVBoxLayout();
    this->setLayout(this->mainLayout);



    this->setWindowTitle("Схема сети");
    this->setMinimumSize(500, 500);



    this->validatorSize = new QIntValidator(100, 2000);
    this->validatorStep = new QIntValidator(1, 2000);
    this->validatorStart = new QIntValidator(0, 2000);

    this->windowSettings = new QGroupBox("Настройки поля");
    this->mainLayout->addWidget(this->windowSettings);
    this->windowSettings->setCheckable(true);
    this->windowSettingsLayout = new QGridLayout();
    this->windowSettings->setLayout(this->windowSettingsLayout);

    this->deviceSettings = new QGroupBox("Настройки прибора");
    this->mainLayout->addWidget(this->deviceSettings);
    this->deviceSettings->setCheckable(true);
    this->deviceSettingsLayout = new QGridLayout();
    this->deviceSettings->setLayout(this->deviceSettingsLayout);

    this->scrollArea = new QScrollArea();
    this->mainLayout->addWidget(this->scrollArea);
    this->scrollArea->setWidgetResizable(true);

    this->scrollWidget = new QWidget();
    this->scrollArea->setWidget(this->scrollWidget);

    this->scrollLayout = new QGridLayout();
    this->scrollWidget->setLayout(this->scrollLayout);
    this->scrollLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    this->network = new NetworkWidget();
    //network->setStyleSheet("background-color: Cornsilk;");
    this->scrollLayout->addWidget(this->network);

    connect(this->windowSettings, SIGNAL(toggled(bool)), this, SLOT(switchWindows(bool)));
    connect(this->deviceSettings, SIGNAL(toggled(bool)), this, SLOT(switchWindows(bool)));


    this->labelSize = new QLabel("Размер");
    this->windowSettingsLayout->addWidget(this->labelSize, 2, 1);

    this->editWidth = new QLineEdit();
    this->windowSettingsLayout->addWidget(this->editWidth, 2, 2);
    this->editWidth->setValidator(this->validatorSize);

    this->editHeight = new QLineEdit();
    this->windowSettingsLayout->addWidget(this->editHeight, 2, 3);
    this->editHeight->setValidator(this->validatorSize);


    this->labelGridStep = new QLabel("Шаг сетки");
    this->windowSettingsLayout->addWidget(this->labelGridStep, 3, 1);

    this->editGridStepX = new QLineEdit();
    this->windowSettingsLayout->addWidget(this->editGridStepX, 3, 2);
    this->editGridStepX->setValidator(this->validatorStep);

    this->editGridStepY = new QLineEdit();
    this->windowSettingsLayout->addWidget(this->editGridStepY, 3, 3);
    this->editGridStepY->setValidator(this->validatorStep);

    this->labelGridStart = new QLabel("Начало сетки");
    this->windowSettingsLayout->addWidget(this->labelGridStart, 4, 1);

    this->editGridStartX = new QLineEdit();
    this->windowSettingsLayout->addWidget(this->editGridStartX, 4, 2);
    this->editGridStartX->setValidator(this->validatorStart);

    this->editGridStartY = new QLineEdit();
    this->windowSettingsLayout->addWidget(this->editGridStartY, 4, 3);
    this->editGridStartY->setValidator(this->validatorStart);

    QSqlQuery query("SELECT nw_width, nw_height, nw_step_x, nw_step_y, nw_x, nw_y "
                    "FROM TestLauncherSettings");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    if (!query.next()) {
        QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

    QSize size(query.value(0).toInt(), query.value(1).toInt());
    QPoint step(query.value(2).toInt(), query.value(3).toInt());
    QPoint start(query.value(4).toInt(), query.value(5).toInt());

    this->editWidth->setText(QString::number(size.width()));
    this->editHeight->setText(QString::number(size.height()));
    this->network->setFixedSize(size);

    this->editGridStepX->setText(QString::number(step.x()));
    this->editGridStepY->setText(QString::number(step.y()));
    this->network->setGridStep(step);

    this->editGridStartX->setText(QString::number(start.x()));
    this->editGridStartY->setText(QString::number(start.y()));
    this->network->setGridStart(start);

    this->labelDeviceName = new QLabel("Наименование прибора: нет выбранного прибора");
    this->deviceSettingsLayout->addWidget(this->labelDeviceName, 6, 1, 1, 3);

    this->deviceSettingsLayout->addWidget(new QLabel("Позиция на схеме (x, y):"), 7, 1, 1, 2);

    this->editX = new QLineEdit();
    this->deviceSettingsLayout->addWidget(this->editX, 7, 3, 1, 1);
    this->editX->setPlaceholderText("x");
    this->editX->setMinimumWidth(100);
    this->editX->setDisabled(true);

    this->editY = new QLineEdit();
    this->deviceSettingsLayout->addWidget(this->editY, 7, 4, 1, 1);
    this->editY->setPlaceholderText("y");
    this->editY->setMinimumWidth(100);
    this->editY->setDisabled(true);

    this->deviceSettingsLayout->addWidget(new QLabel("Связан с хабом:"), 8, 1, 2, 1);

    this->comboboxHubsMain = new QComboBox();
    this->deviceSettingsLayout->addWidget(this->comboboxHubsMain, 8, 2, 1, 1);
    this->comboboxHubsMain->setDisabled(true);

    this->comboboxHubsReserve = new QComboBox();
    this->deviceSettingsLayout->addWidget(this->comboboxHubsReserve, 9, 2, 1, 1);
    this->comboboxHubsReserve->setDisabled(true);

    this->comboboxTypeMain = new QComboBox();
    this->deviceSettingsLayout->addWidget(this->comboboxTypeMain, 8, 3, 1, 3);
    this->comboboxTypeMain->addItem("горизонтальная связь");
    this->comboboxTypeMain->addItem("вертикальная связь");
    this->comboboxTypeMain->setDisabled(true);

    this->comboboxTypeReserve = new QComboBox();
    this->deviceSettingsLayout->addWidget(this->comboboxTypeReserve, 9, 3, 1, 3);
    this->comboboxTypeReserve->addItem("горизонтальная связь");
    this->comboboxTypeReserve->addItem("вертикальная связь");
    this->comboboxTypeReserve->setDisabled(true);

    this->percentValidator = new QIntValidator(-500, 500);

    this->editPercentMain = new QLineEdit();
    this->deviceSettingsLayout->addWidget(this->editPercentMain, 8, 4, 1, 1);
    this->editPercentMain->setValidator(this->percentValidator);
    this->editPercentMain->setDisabled(true);

    this->editPercentReserve = new QLineEdit();
    this->deviceSettingsLayout->addWidget(this->editPercentReserve, 9, 4, 1, 1);
    this->editPercentReserve->setValidator(this->percentValidator);
    this->editPercentReserve->setDisabled(true);

    connect(this->editWidth, SIGNAL(editingFinished()), this, SLOT(setNetworkWidth()));
    connect(this->editHeight, SIGNAL(editingFinished()), this, SLOT(setNetworkHeight()));
    connect(this->editGridStepX, SIGNAL(editingFinished()), this, SLOT(setNetworkGridStep()));
    connect(this->editGridStepY, SIGNAL(editingFinished()), this, SLOT(setNetworkGridStep()));
    connect(this->editGridStartX, SIGNAL(editingFinished()), this, SLOT(setNetworkGridStart()));
    connect(this->editGridStartY, SIGNAL(editingFinished()), this, SLOT(setNetworkGridStart()));

    this->windowSettings->setChecked(false);
    this->deviceSettings->setChecked(false);

    connect(this->network, SIGNAL(deviceWithIdSelected(int,bool)), SLOT(setActiveDevice(int,bool)));

    connect(this->editX, SIGNAL(editingFinished()), this, SLOT(updateX()));
    connect(this->editY, SIGNAL(editingFinished()), this, SLOT(updateY()));

    connect(this->comboboxTypeMain, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTypeMain(int)));
    connect(this->comboboxTypeReserve, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTypeReserve(int)));
    connect(this->editPercentMain, SIGNAL(editingFinished()), this, SLOT(updatePercentMain()));
    connect(this->editPercentReserve, SIGNAL(editingFinished()), this, SLOT(updatePercentReserve()));
}

void NetworkDialog::setNetworkHeight()
{
    QString text = this->editHeight->text();
    int pos = 0;
    if (this->validatorSize->validate(text, pos) == QValidator::Acceptable) {
        this->network->setFixedHeight(text.toInt());
        QSqlQuery query("UPDATE TestLauncherSettings SET nw_height = " + text);
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
}

void NetworkDialog::setNetworkWidth()
{
    QString text = this->editWidth->text();
    int pos = 0;
    if (this->validatorSize->validate(text, pos) == QValidator::Acceptable) {
        this->network->setFixedWidth(text.toInt());
        QSqlQuery query("UPDATE TestLauncherSettings SET nw_width = " % text);
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
}

void NetworkDialog::setNetworkGridStep()
{
    QString textX = this->editGridStepX->text();
    QString textY = this->editGridStepY->text();
    int pos = 0;
    if (this->validatorStep->validate(textX, pos) == QValidator::Acceptable &&
            this->validatorStep->validate(textY, pos) == QValidator::Acceptable) {
        this->network->setGridStep(textX.toInt(), textY.toInt());
        QSqlQuery query("UPDATE TestLauncherSettings SET nw_step_x = " % textX % ", nw_step_y = " % textY);
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
}

void NetworkDialog::setNetworkGridStart()
{
    QString textX = this->editGridStartX->text();
    QString textY = this->editGridStartY->text();
    int pos = 0;
    if (this->validatorStart->validate(textX, pos) == QValidator::Acceptable &&
            this->validatorStart->validate(textY, pos) == QValidator::Acceptable) {
        this->network->setGridStart(textX.toInt(), textY.toInt());
        QSqlQuery query("UPDATE TestLauncherSettings SET nw_x = " % textX % ", nw_y = " % textY);
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
}

void NetworkDialog::switchWindows(bool isActive)
{
    QObject *obj = sender();

    QGroupBox *gb = qobject_cast <QGroupBox *> (obj);

//    setItemsInGroupboxHidden(this->deviceSettings, true);
//    setItemsInGroupboxHidden(this->windowSettings, true);

    setItemsInGroupboxHidden(gb, !isActive);
}

void NetworkDialog::setItemsInGroupboxHidden(QGroupBox *groupbox, bool hidden)
{
    if (groupbox != NULL) {
//        groupbox->setChecked(!hidden);

        int count = groupbox->layout()->count();
        for (int i = 0; i < count; i++) {
            groupbox->layout()->itemAt(i)->widget()->setHidden(hidden);
        }
    }
}

void NetworkDialog::setActiveDevice(int allocId, bool isHub)
{
    this->allocId = allocId;
    this->isHub = isHub;

    QSqlQuery query;

    if (this->isHub) {
        query.exec("SELECT "
                       "name, "
                       "0, "
                       "x, "
                       "y, "
                       "master, "
                       "is_vertical, "
                       "percent "
                   "FROM Hubs "
                   "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
    else {
        query.exec("SELECT "
                       "Devices.name, "
                       "AllocationDevices.device_postfix, "
                       "AllocationDevices.x, "
                       "AllocationDevices.y, "
                       "AllocationDevices.hub_id_main, "
                       "AllocationDevices.hub_id_reserve, "
                       "AllocationDevices.is_vertical_main, "
                       "AllocationDevices.is_vertical_reserve, "
                       "AllocationDevices.percent_main, "
                       "AllocationDevices.percent_reserve "
                   "FROM Devices "
                   "JOIN AllocationDevices "
                   "ON Devices.id = AllocationDevices.device_id "
                   "WHERE AllocationDevices.id = " + QString::number(this->allocId));
            if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
                QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
            }
    }

    if (!query.next()) {
        QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

    if (query.value(1).toInt()) {
        this->labelDeviceName->setText("Наименование прибора: " % query.value(0).toString() % query.value(1).toString());
    }
    else {
        this->labelDeviceName->setText("Наименование прибора: " % query.value(0).toString());
    }

    this->editX->setText(query.value(2).toString());
    this->editY->setText(query.value(3).toString());

    if (this->isHub) {
        if (!query.value(4).isNull()) {
            this->hubIdMain = query.value(4).toInt();
        }
        this->hubIdReserve = -1;
        this->comboboxTypeMain->setCurrentIndex(query.value(5).toInt());
        this->editPercentMain->setText(query.value(6).toString());

        this->comboboxHubsReserve->setEnabled(false);
        this->comboboxTypeReserve->setEnabled(false);
        this->editPercentReserve->setEnabled(false);
    }
    else {
        if (!query.value(4).isNull()) {
            this->hubIdMain = query.value(4).toInt();
        }
        if (!query.value(5).isNull()) {
            this->hubIdReserve = query.value(5).toInt();
        }
        this->comboboxTypeMain->setCurrentIndex(query.value(6).toInt());
        this->comboboxTypeReserve->setCurrentIndex(query.value(7).toInt());
        this->editPercentMain->setText(query.value(8).toString());
        this->editPercentReserve->setText(query.value(9).toString());

        this->comboboxHubsReserve->setEnabled(true);
        this->comboboxTypeReserve->setEnabled(true);
        this->editPercentReserve->setEnabled(true);
    }

    this->fillHubs(true);
}

void NetworkDialog::fillHubs(bool clear)
{
    disconnect(this->comboboxHubsMain, SIGNAL(currentIndexChanged(int)), this, SLOT(updateHubMain(int)));
    disconnect(this->comboboxHubsReserve, SIGNAL(currentIndexChanged(int)), this, SLOT(updateHubReserve(int)));

    if (clear) {
        this->comboboxHubsMain->clear();
        this->comboboxHubsReserve->clear();
    }

    this->editX->setDisabled(false);
    this->editY->setDisabled(false);
    this->comboboxHubsMain->setDisabled(false);
    this->comboboxHubsReserve->setDisabled(false);
    this->comboboxTypeMain->setDisabled(false);
    this->comboboxTypeReserve->setDisabled(false);
    this->editPercentMain->setDisabled(false);
    this->editPercentReserve->setDisabled(false);

    this->comboboxHubsMain->addItem("связь отсутствует", -1);
    this->comboboxHubsReserve->addItem("связь отсутствует", -1);

    QSqlQuery query;
    query.exec("SELECT id, name FROM Hubs ");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    while (query.next()) {
        if (!this->isHub || query.value(0).toInt() != this->allocId) {
            this->comboboxHubsMain->addItem(query.value(1).toString(), query.value(0).toInt());
            this->comboboxHubsReserve->addItem(query.value(1).toString(), query.value(0).toInt());
        }
    }

    if (this->hubIdMain < 0) {
        this->comboboxTypeMain->setEnabled(false);
        this->editPercentMain->setEnabled(false);
    }
    else {
        for (int i = 0; i < this->comboboxHubsMain->count(); i++) {
            if (this->comboboxHubsMain->itemData(i).toInt() == this->hubIdMain) {
                this->comboboxHubsMain->setCurrentIndex(i);
                break;
            }
        }
        this->comboboxTypeMain->setEnabled(true);
        this->editPercentMain->setEnabled(true);
    }

    if (this->hubIdReserve < 0) {
        this->comboboxTypeReserve->setEnabled(false);
        this->editPercentReserve->setEnabled(false);
    }
    else {
        for (int i = 0; i < this->comboboxHubsReserve->count(); i++) {
            if (this->comboboxHubsReserve->itemData(i).toInt() == this->hubIdReserve) {
                this->comboboxHubsReserve->setCurrentIndex(i);
                break;
            }
        }
        this->comboboxTypeReserve->setEnabled(true);
        this->editPercentReserve->setEnabled(true);
    }

    connect(this->comboboxHubsMain, SIGNAL(currentIndexChanged(int)), this, SLOT(updateHubMain(int)));
    connect(this->comboboxHubsReserve, SIGNAL(currentIndexChanged(int)), this, SLOT(updateHubReserve(int)));
}

void NetworkDialog::updateX()
{
    if (this->isHub) {
        QSqlQuery query;
        query.exec("UPDATE Hubs "
                  "SET x = '" + this->editX->text() + "' "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
    else {
        QString name = this->editX->text();

        QSqlQuery query;
        query.exec("UPDATE AllocationDevices "
                  "SET x = '" + name + "' "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
    this->network->fillDevicesAndConnections();
}

void NetworkDialog::updateY()
{
    if (this->isHub) {
        QSqlQuery query;
        query.exec("UPDATE Hubs "
                  "SET y = '" + this->editY->text() + "' "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
    else {
        QString name = this->editY->text();

        QSqlQuery query;
        query.exec("UPDATE AllocationDevices "
                  "SET y = '" + name + "' "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
    this->network->fillDevicesAndConnections();
}

void NetworkDialog::updateHubMain(int index)
{
    if (this->isHub) {
        int hubId = this->comboboxHubsMain->itemData(index).toInt();

        QSqlQuery query;
        query.exec("UPDATE Hubs "
                  "SET master = " + QString::number(hubId) + " "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }

        if (hubId < 0) {
            this->comboboxTypeMain->setEnabled(false);
            this->editPercentMain->setEnabled(false);
        }
        else {
            this->comboboxTypeMain->setEnabled(true);
            this->editPercentMain->setEnabled(true);
        }
    }
    else {
        int hubId = this->comboboxHubsMain->itemData(index).toInt();

        QSqlQuery query;
        query.exec("UPDATE AllocationDevices "
                  "SET hub_id_main = " + (hubId < 0 ? "NULL" : QString::number(hubId)) + " "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }

        if (hubId < 0) {
            this->comboboxTypeMain->setEnabled(false);
            this->editPercentMain->setEnabled(false);
        }
        else {
            this->comboboxTypeMain->setEnabled(true);
            this->editPercentMain->setEnabled(true);
        }
    }
    this->network->fillDevicesAndConnections();
}

void NetworkDialog::updateHubReserve(int index)
{
    if (this->isHub) {
        int hubId = this->comboboxHubsReserve->itemData(index).toInt();

        QSqlQuery query;
        query.exec("UPDATE Hubs "
                  "SET master = " + QString::number(hubId) + " "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }

        if (hubId < 0) {
            this->comboboxTypeReserve->setEnabled(false);
            this->editPercentReserve->setEnabled(false);
        }
        else {
            this->comboboxTypeReserve->setEnabled(true);
            this->editPercentReserve->setEnabled(true);
        }
    }
    else {
        int hubId = this->comboboxHubsReserve->itemData(index).toInt();

        QSqlQuery query;
        query.exec("UPDATE AllocationDevices "
                  "SET hub_id_reserve = " + (hubId < 0 ? "NULL" : QString::number(hubId)) + " "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }

        if (hubId < 0) {
            this->comboboxTypeReserve->setEnabled(false);
            this->editPercentReserve->setEnabled(false);
        }
        else {
            this->comboboxTypeReserve->setEnabled(true);
            this->editPercentReserve->setEnabled(true);
        }
    }
    this->network->fillDevicesAndConnections();
}

void NetworkDialog::updateTypeMain(int index)
{
    if (this->isHub) {
        QSqlQuery query;
        query.exec("UPDATE Hubs "
                  "SET is_vertical = " + QString::number(index) + " "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
    else {
        QSqlQuery query;
        query.exec("UPDATE AllocationDevices "
                  "SET is_vertical_main = " + QString::number(index) + " "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
    this->network->fillDevicesAndConnections();
}

void NetworkDialog::updateTypeReserve(int index)
{
    if (this->isHub) {
        QSqlQuery query;
        query.exec("UPDATE Hubs "
                  "SET is_vertical = " + QString::number(index) + " "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
    else {
        QSqlQuery query;
        query.exec("UPDATE AllocationDevices "
                  "SET is_vertical_reserve = " + QString::number(index) + " "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
    this->network->fillDevicesAndConnections();
}

void NetworkDialog::updatePercentMain()
{
    int percent = this->editPercentMain->text().toInt();
    if (this->isHub) {
        QSqlQuery query;
        query.exec("UPDATE Hubs "
                  "SET percent = " + QString::number(percent) + " "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
    else {

        QSqlQuery query;
        query.exec("UPDATE AllocationDevices "
                  "SET percent_main = " + QString::number(percent) + " "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
    this->network->fillDevicesAndConnections();
}

void NetworkDialog::updatePercentReserve()
{
    int percent = this->editPercentReserve->text().toInt();

    if (this->isHub) {
        QSqlQuery query;
        query.exec("UPDATE Hubs "
                  "SET percent = " + QString::number(percent) + " "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
    else {
        QSqlQuery query;
        query.exec("UPDATE AllocationDevices "
                  "SET percent_reserve = " + QString::number(percent) + " "
                  "WHERE id = " + QString::number(this->allocId));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
    }
    this->network->fillDevicesAndConnections();
}

