#include "generalsettings.h"

GeneralSettings::GeneralSettings(QWidget *parent)
    :QWidget(parent)
{
    this->mainLayout = new QGridLayout();
    this->setLayout(this->mainLayout);

    this->editName = new QLineEdit();
    this->mainLayout->addWidget(this->editName, 1, 1, 1, 1);
    this->editName->setPlaceholderText("Заголовок программы TestLauncher");

    this->editLogFolder = new QLineEdit();
    this->mainLayout->addWidget(this->editLogFolder, 1, 2, 1, 1);
    this->editLogFolder->setPlaceholderText("Папка для сохранения лога");

    this->comboMini = new QComboBox();
    comboMini->installEventFilter(this);
    comboMini->setFocusPolicy(Qt::StrongFocus);
    this->mainLayout->addWidget(this->comboMini, 2, 1, 1, 1);
    this->comboMini->addItem("Использовать полное отображение", 0);
    this->comboMini->addItem("Использовать сокращённое отображение", 1);

    this->comboNetwork = new QComboBox();
    comboNetwork->installEventFilter(this);
    comboNetwork->setFocusPolicy(Qt::StrongFocus);
    this->mainLayout->addWidget(this->comboNetwork, 2, 2, 1, 1);
    this->comboNetwork->addItem("Показывать сеть", 0);
    this->comboNetwork->addItem("Скрывать сеть", 1);

    this->editNetworkTitle = new QLineEdit();
    this->mainLayout->addWidget(this->editNetworkTitle, 3, 1, 1, 1);
    this->editNetworkTitle->setPlaceholderText("Заголовок основной сети");

    this->editAddNetworkTitle = new QLineEdit();
    this->mainLayout->addWidget(this->editAddNetworkTitle, 3, 2, 1, 1);
    this->editAddNetworkTitle->setPlaceholderText("Заголовок дополнительной сети");

    this->btnSave = new QPushButton("Сохранить изменения");
    btnSave->setStyleSheet("background-color: #56887D; color: white");

    //btnSave->setStyleSheet("background-color: #56887d");
    this->mainLayout->addWidget(this->btnSave,4,1,1,2);


    this->loadData();




    this->connect(this->btnSave, SIGNAL(clicked()),this, SLOT(slotSave()));

    /* Старые связи. Возможно пригодяться.
    //this->connect(this->editName, SIGNAL(editingFinished()), SLOT(updateName()));
    //this->connect(this->comboNetwork, SIGNAL(currentIndexChanged(int)), SLOT(updateComboNetwork(int)));
    //this->connect(this->editNetworkTitle, SIGNAL(editingFinished()), SLOT(updateCaptionNetwork()));
    //this->connect(this->editAddNetworkTitle, SIGNAL(editingFinished()), SLOT(updateCaptionAddNetwork()));
    //this->connect(this->editLogFolder, SIGNAL(editingFinished()), SLOT(updateLogFolder()));
    //this->connect(this.)
    */
}

GeneralSettings::~GeneralSettings()
{

}

void GeneralSettings::loadData()
{
    QSqlQuery query("SELECT programm_name, use_mini_mode, hide_networks, caption_network, caption_add_network, log_folder "
                    "FROM TestLauncherSettings");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    if (query.next()) {
        this->editName->setText(query.value(0).toString());
        for (int i = 0; i < this->comboMini->count(); i++) {
            if (this->comboMini->itemData(i).toInt() == query.value(1).toInt()) {
                this->comboMini->setCurrentIndex(i);
                break;
            }
        }
        for (int i = 0; i < this->comboNetwork->count(); i++) {
            if (this->comboNetwork->itemData(i).toInt() == query.value(2).toInt()) {
                this->comboNetwork->setCurrentIndex(i);
                break;
            }
        }
        this->editNetworkTitle->setText(query.value(3).toString());
        this->editAddNetworkTitle->setText(query.value(4).toString());
        this->editLogFolder->setText(query.value(5).toString());
    }
    else {
        QSqlQuery query("INSERT INTO TestLauncherSettings (programm_name, use_mini_mode, use_part_content, hide_networks, nw_width, nw_height, nw_step_x, nw_step_y, nw_x, nw_y, caption_network, caption_add_network, network_1_x, network_1_y, network_2_x, network_2_y, add_network_1_x, add_network_1_y, add_network_2_x, add_network_2_y, hub_height, hub_width, device_height, device_width, part_height, part_width, network_height, network_width, offset_x_1_1, offset_x_1_2, offset_x_2_1, offset_x_2_2, offset_x_2_3, offset_x_2_4, offset_y_1_1, offset_y_1_2, offset_y_2_1, offset_y_2_2, offset_y_2_3, offset_y_2_4, log_folder, semaphore_value) "
                  "VALUES ( '" + this->defaultName() + "', '" + this->comboMini->itemData(0).toString() + "', 0, '" + this->comboNetwork->itemData(0).toString() + "', 500, 300, 10, 10, 0, 0, \"\", \"\", \"\", \"\", \"\", \"\", \"\", \"\", \"\", \"\", 100, 100, 100, 100, 20, 20, 100, 100, -5, 5, -38, -18, 18, 38, -5, 5, -20, -10, 10, 20, \"\", 100 )");
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        this->editName->setText(this->defaultName());
    }
}


const QString GeneralSettings::defaultName() const
{
    return "Без названия";
}

void GeneralSettings::updateName()
{
    QString name = this->editName->text();

    QSqlQuery query("UPDATE TestLauncherSettings "
              "SET programm_name = '" + name + "'");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void GeneralSettings::updateComboMini()
{
    int indexCM = comboMini->currentIndex();
    QSqlQuery query("UPDATE TestLauncherSettings "
              "SET use_mini_mode = " + QString::number(this->comboMini->itemData(indexCM).toInt()));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void GeneralSettings::updateComboNetwork()
{
    int indexUN = comboNetwork->currentIndex();
    QSqlQuery query("UPDATE TestLauncherSettings "
              "SET hide_networks = " + QString::number(this->comboNetwork->itemData(indexUN).toInt()));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void GeneralSettings::updateCaptionNetwork()
{
    QString text = this->editNetworkTitle->text();
    QSqlQuery query;
    query.exec("UPDATE TestLauncherSettings "
              "SET caption_network = '" + text + "' ");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void GeneralSettings::updateCaptionAddNetwork()
{
    QString text = this->editAddNetworkTitle->text();
    QSqlQuery query;
    query.exec("UPDATE TestLauncherSettings "
              "SET caption_add_network = '" + text + "' ");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void GeneralSettings::updateLogFolder()
{
    QString text = this->editLogFolder->text();
    QSqlQuery query;
    query.exec("UPDATE TestLauncherSettings "
              "SET log_folder = '" + text + "' ");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void GeneralSettings::slotSave()
{
    updateName();
    updateCaptionNetwork();
    updateCaptionAddNetwork();
    updateLogFolder();
    updateComboNetwork();
    updateComboMini();
}

bool GeneralSettings::eventFilter(QObject *target, QEvent *event)
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


