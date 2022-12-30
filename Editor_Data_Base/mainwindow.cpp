#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rooms.h"
#include "hubs.h"
#include "devices.h"
#include "allocationdevices.h"
#include "dependence.h"
#include "errors.h"
#include "redirectmessages.h"
#include "units.h"
#include "groups.h"
#include "generalsettings.h"
#include "table.h"



#include <QDebug>


//https://russianblogs.co+чсвфауиm/article/49771056644/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setWindowTitle(this->getProgramName());
    this->setMinimumSize(1000, 800);
    setWindowIcon(QIcon(":/logo/bdsql.png"));

// Создание меню
    this->menuBar = new QMenuBar();
    this->setMenuBar(menuBar);
    this->menuFile = new QMenu("Файл");
    this->menuBar->addMenu(menuFile);
    //this->newFile = new QAction("Создать");
    //this->menuFile->addAction(newFile);
    this->openFile = new QAction("Отрыть базу данных");
    this->menuFile->addAction(openFile);
    this->openFile->setEnabled(true);
//    this->menuFile->addSeparator();
//    this->saveBD = new QAction("Сохранить изменения");
//    this->menuFile->addAction(saveBD);
//    this->saveBD->setEnabled(true);
    this->menuFile->addSeparator();
    this->closeDataBase = new QAction("Закрыть текущую базу данных");
    this->menuFile->addAction(closeDataBase);
    this->closeDataBase->setEnabled(true);
    this->menuFile->addSeparator();
    this->closeWindow = new QAction("Закрыть все");
    this->menuFile->addAction(closeWindow);
    this->closeWindow->setEnabled(true);



    //Объявление SQL драйвера
    this->db = new QSqlDatabase();
    *this->db = this->db->addDatabase("QSQLITE");

    // Создать виджет, назначить его центральным. Назначить его layout. В Layout добавляем уже виджеты.
    this->wgt = new QWidget();
    this->setCentralWidget(wgt);
    this->mainLayout = new QHBoxLayout();
    this->leftLayout = new QVBoxLayout();
    this->wgt->setLayout(mainLayout);
    this->mainLayout->addLayout(leftLayout);

/*Создание пустых объектов
//    this->stack = NULL;
//    this->ob = NULL;
//    this->rooms = NULL;
//    this->hubs = NULL;
//    this->units = NULL;
//    this->groups = NULL;
//    this->allocation_devices = NULL;
//    this->table = NULL;
*/

/* Создание Кнопок
//    this->buttonAllocationDevices = NULL;
//    this->buttonDevices =NULL;
//    this->buttonErrors =NULL;
//    this->buttonGroups =NULL;
//    this->buttonHubs = NULL;
//    this->buttonRooms = NULL;
//    this->buttonGeneralSettings =NULL;
//    this->buttonUnits = NULL;
//    this->buttonTable= NULL;
//    this->buttonSql= NULL;
//    this->buttonNets = NULL;
//    this->buttonRedirectMsg = NULL;
*/
    //-------------------- Сигналы -----------------------

    connect(openFile, SIGNAL(triggered()), this, SLOT(openDB()));
    connect(closeDataBase, SIGNAL(triggered()), this, SLOT(slotCloseDataBasa()));
    connect(closeWindow, SIGNAL(triggered()), this, SLOT(quit()));


    //---------------Подключение CSS-------------------

    QFile file(":/css/style.css");
    QString textCss;
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Ошибка открытия для чтения";
    }
    textCss = file.readAll();
    //qDebug()<<file.isOpen();
    this->setStyleSheet(textCss);
    //qDebug ()<< "textCss = " <<textCss;


}



//------------------------ КОНЕЦ КОНСТРУКТОРА &&  Отработка деструктора -------------


MainWindow::~MainWindow()
{
    delete ui;

    delete openFile;
    delete closeWindow;
    delete closeDataBase;
    delete menuFile;
    delete menuBar;
    delete db;


//    delete this->stack;
//    delete leftLayout;
    delete mainLayout;
    delete wgt;

}

//------------------------НАЧАЛО МЕТОДОВ--------------------------------------------

// ------------------- Метод дающий название -----------------------------
const QString MainWindow::getProgramName() const
{
    return "Редактор БД Тестов";
}
//---------------------------- Методы открытия базы данных --------------------------

bool MainWindow::openDB(const QString &filename)   // SQL
{
    db->close();
    this->db->setDatabaseName(filename);

    if (!db->open()) {
        QMessageBox::warning(0, QObject::tr("Ошибка"),
                                  QObject::tr("Ошибка подключения к базе!"));
        return false;
    }
//    else {
//        QMessageBox::information(0, QObject::tr("Все хорошо"),
//                                     QObject::tr("Подключился к базе!!!"));
//        qDebug() << "Удалось подключиться";


    this->setWindowTitle(this->getProgramName() + " - " + filename);
    return true;
}

//---------------------- Bool open ---------------------

void MainWindow::openDB()
{

    QFile FilePath("path.txt");
    QString filename = QFileDialog::getOpenFileName(
            this,
            "Открытие базы данных",
            "",
            "Файл базы данных (*.db);;Все файлы (*)");

    if (filename.length()) {
        if (!this->openDB(filename)) {
            return;
        }

        addWidgets();
    }


}

//---------------------------- Метод показывающий STACK --------------------------
//------------------ПЕРЕПИСАТЬ БОЛЕЕ КОМПАКТНО, ЧЕРЕЗ QMAP -----------------------

void MainWindow::showStack()
{
    QObject *foobar = sender();
    //qDebug() << foobar;
    if (foobar == this->buttonGeneralSettings)
    {
     this->stack->setCurrentIndex(0);
     buttonGeneralSettings->setChecked(true);
     buttonRooms->setChecked(false);
     buttonHubs->setChecked(false);
     buttonGroups->setChecked(false);
     buttonDevices->setChecked(false);
     buttonUnits->setChecked(false);
     buttonAllocationDevices->setChecked(false);
     buttonTable->setChecked(false);
     buttonSql->setChecked(false);
     buttonErrors->setChecked(false);
     buttonNets->setChecked(false);
     buttonRedirectMsg->setChecked(false);
     buttonAllocationUnits->setChecked(false);

    }
    else if (foobar == this->buttonRooms)
    {
       this->stack->setCurrentIndex(1);
       buttonGeneralSettings->setChecked(false);
       buttonRooms->setChecked(true);
       buttonHubs->setChecked(false);
       buttonGroups->setChecked(false);
       buttonDevices->setChecked(false);
       buttonUnits->setChecked(false);
       buttonAllocationDevices->setChecked(false);
       buttonTable->setChecked(false);
       buttonSql->setChecked(false);
       buttonErrors->setChecked(false);
       buttonNets->setChecked(false);
       buttonRedirectMsg->setChecked(false);
       buttonAllocationUnits->setChecked(false);

    }
    else if (foobar == this->buttonGroups)
    {
        this->stack->setCurrentIndex(3);
        buttonGeneralSettings->setChecked(false);
        buttonRooms->setChecked(false);
        buttonHubs->setChecked(false);
        buttonGroups->setChecked(true);
        buttonDevices->setChecked(false);
        buttonUnits->setChecked(false);
        buttonAllocationDevices->setChecked(false);
        buttonTable->setChecked(false);
        buttonSql->setChecked(false);
        buttonErrors->setChecked(false);
        buttonNets->setChecked(false);
        buttonRedirectMsg->setChecked(false);
        buttonAllocationUnits->setChecked(false);

    }
    else if (foobar == this->buttonDevices)
    {
        this->stack->setCurrentIndex(4);
        buttonGeneralSettings->setChecked(false);
        buttonRooms->setChecked(false);
        buttonHubs->setChecked(false);
        buttonGroups->setChecked(false);
        buttonDevices->setChecked(true);
        buttonUnits->setChecked(false);
        buttonAllocationDevices->setChecked(false);
        buttonTable->setChecked(false);
        buttonSql->setChecked(false);
        buttonErrors->setChecked(false);
        buttonNets->setChecked(false);
        buttonRedirectMsg->setChecked(false);
        buttonAllocationUnits->setChecked(false);

    }
    else if (foobar == this->buttonHubs)
    {
        this->stack->setCurrentIndex(2);
        buttonGeneralSettings->setChecked(false);
        buttonRooms->setChecked(false);
        buttonHubs->setChecked(true);
        buttonGroups->setChecked(false);
        buttonDevices->setChecked(false);
        buttonUnits->setChecked(false);
        buttonAllocationDevices->setChecked(false);
        buttonTable->setChecked(false);
        buttonSql->setChecked(false);
        buttonErrors->setChecked(false);
        buttonNets->setChecked(false);
        buttonRedirectMsg->setChecked(false);
        buttonAllocationUnits->setChecked(false);

    }
    else if (foobar == this->buttonUnits)
    {
        this->stack->setCurrentIndex(5);
        buttonGeneralSettings->setChecked(false);
        buttonRooms->setChecked(false);
        buttonHubs->setChecked(false);
        buttonGroups->setChecked(false);
        buttonDevices->setChecked(false);
        buttonUnits->setChecked(true);
        buttonAllocationDevices->setChecked(false);
        buttonTable->setChecked(false);
        buttonSql->setChecked(false);
        buttonErrors->setChecked(false);
        buttonNets->setChecked(false);
        buttonRedirectMsg->setChecked(false);
        buttonAllocationUnits->setChecked(false);

    }
    else if (foobar == this->buttonAllocationDevices)
    {
        this->stack->setCurrentIndex(6);
        buttonGeneralSettings->setChecked(false);
        buttonRooms->setChecked(false);
        buttonHubs->setChecked(false);
        buttonGroups->setChecked(false);
        buttonDevices->setChecked(false);
        buttonUnits->setChecked(false);
        buttonAllocationDevices->setChecked(true);
        buttonTable->setChecked(false);
        buttonSql->setChecked(false);
        buttonErrors->setChecked(false);
        buttonNets->setChecked(false);
        buttonRedirectMsg->setChecked(false);
        buttonAllocationUnits->setChecked(false);

    }
    else if (foobar == this->buttonTable)
    {
        this->stack->setCurrentIndex(7);
        buttonGeneralSettings->setChecked(false);
        buttonRooms->setChecked(false);
        buttonHubs->setChecked(false);
        buttonGroups->setChecked(false);
        buttonDevices->setChecked(false);
        buttonUnits->setChecked(false);
        buttonAllocationDevices->setChecked(false);
        buttonTable->setChecked(true);
        buttonSql->setChecked(false);
        buttonErrors->setChecked(false);
        buttonNets->setChecked(false);
        buttonRedirectMsg->setChecked(false);
        buttonAllocationUnits->setChecked(false);

    }

    else if (foobar == this->buttonSql)
    {
        this->stack->setCurrentIndex(8);
        buttonGeneralSettings->setChecked(false);
        buttonRooms->setChecked(false);
        buttonHubs->setChecked(false);
        buttonGroups->setChecked(false);
        buttonDevices->setChecked(false);
        buttonUnits->setChecked(false);
        buttonAllocationDevices->setChecked(false);
        buttonTable->setChecked(false);
        buttonSql->setChecked(true);
        buttonErrors->setChecked(false);
        buttonNets->setChecked(false);
        buttonRedirectMsg->setChecked(false);
        buttonAllocationUnits->setChecked(false);
    }
    else if (foobar == this->buttonErrors)
    {
        this->stack->setCurrentIndex(9);
        buttonGeneralSettings->setChecked(false);
        buttonRooms->setChecked(false);
        buttonHubs->setChecked(false);
        buttonGroups->setChecked(false);
        buttonDevices->setChecked(false);
        buttonUnits->setChecked(false);
        buttonAllocationDevices->setChecked(false);
        buttonTable->setChecked(false);
        buttonSql->setChecked(false);
        buttonErrors->setChecked(true);
        buttonNets->setChecked(false);
        buttonRedirectMsg->setChecked(false);
        buttonAllocationUnits->setChecked(false);

    }
    else if (foobar == this->buttonNets)
    {
        this->stack->setCurrentIndex(10);
        buttonGeneralSettings->setChecked(false);
        buttonRooms->setChecked(false);
        buttonHubs->setChecked(false);
        buttonGroups->setChecked(false);
        buttonDevices->setChecked(false);
        buttonUnits->setChecked(false);
        buttonAllocationDevices->setChecked(false);
        buttonTable->setChecked(false);
        buttonSql->setChecked(false);
        buttonErrors->setChecked(false);
        buttonNets->setChecked(true);
        buttonRedirectMsg->setChecked(false);
        buttonAllocationUnits->setChecked(false);

    }
    else if (foobar == this->buttonRedirectMsg)
    {
        this->stack->setCurrentIndex(11);
        buttonGeneralSettings->setChecked(false);
        buttonRooms->setChecked(false);
        buttonHubs->setChecked(false);
        buttonGroups->setChecked(false);
        buttonDevices->setChecked(false);
        buttonUnits->setChecked(false);
        buttonAllocationDevices->setChecked(false);
        buttonTable->setChecked(false);
        buttonSql->setChecked(false);
        buttonErrors->setChecked(false);
        buttonNets->setChecked(false);
        buttonRedirectMsg->setChecked(true);
        buttonAllocationUnits->setChecked(false);

    }
    else if (foobar == this->buttonAllocationUnits) // Добавить сюда кнопку
    {
        this->stack->setCurrentIndex(12);
        buttonGeneralSettings->setChecked(false);
        buttonRooms->setChecked(false);
        buttonHubs->setChecked(false);
        buttonGroups->setChecked(false);
        buttonDevices->setChecked(false);
        buttonUnits->setChecked(false);
        buttonAllocationDevices->setChecked(false);
        buttonTable->setChecked(false);
        buttonSql->setChecked(false);
        buttonErrors->setChecked(false);
        buttonNets->setChecked(false);
        buttonRedirectMsg->setChecked(false);
        buttonAllocationUnits->setChecked(true);

    }

}

//--------------------------  Метод для отображения всех виджетов после открытия --------------------------
void MainWindow::addWidgets()
{
    this->stack = new QStackedWidget ();
    this->mainLayout->addWidget(stack);

//    openFile->setEnabled(true);
//    closeWindow->setEnabled(true);

    //Создание кнопок
    this->buttonGeneralSettings = new QPushButton("Общие настройки");
    buttonGeneralSettings->setObjectName("buttonGeneralSettings");
    this->buttonGeneralSettings->setCheckable(true);


    this->buttonRooms = new QPushButton("Помещения");
    buttonRooms->setObjectName("buttonRooms");
    this->buttonRooms->setCheckable(true);


    this->buttonHubs = new QPushButton("Хабы");
    buttonHubs->setObjectName("buttonHubs");
    this->buttonHubs->setCheckable(true);


    this->buttonGroups = new QPushButton("Группы");
    buttonGroups->setObjectName("buttonGroups");
    this->buttonGroups->setCheckable(true);



    this->buttonDevices = new QPushButton("Приборы");
    buttonDevices->setObjectName("buttonDevices");
    this->buttonDevices->setCheckable(true);


    this->buttonUnits = new QPushButton("Модули");
    buttonUnits->setObjectName("buttonUnits");
    buttonUnits->setCheckable(true);


    this->buttonAllocationDevices = new QPushButton("Распределение устройств");
    buttonAllocationDevices->setObjectName("buttonAllocationDevices");
    buttonAllocationDevices->setCheckable(true);


    this->buttonTable = new QPushButton("Таблица");
    buttonTable->setObjectName("buttonTable");
    buttonTable->setCheckable(true);


    this->buttonSql  = new QPushButton("Редактор SQL");
    buttonSql->setObjectName("buttonSql");
    buttonSql->setCheckable(true);


    this->buttonErrors  = new QPushButton("Ошибки");
    buttonErrors->setObjectName("buttonErrors");
    buttonErrors->setCheckable(true);

    this->buttonNets  = new QPushButton("Сеть");
    buttonNets->setObjectName("buttonNets");
    buttonNets->setCheckable(true);

    this->buttonRedirectMsg  = new QPushButton("Сообщения");
    buttonRedirectMsg->setObjectName("buttonRedirectMsg");
    buttonRedirectMsg->setCheckable(true);

    buttonAllocationUnits = new QPushButton("Расположение AllocationUnits");
    buttonAllocationUnits->setObjectName("buttonAllocationUnits");
    buttonAllocationUnits->setCheckable(true);





    //Добавление кнопок в leftlayout
    this->leftLayout->addWidget(buttonGeneralSettings);
    this->leftLayout->addWidget(buttonRooms);
    this->leftLayout->addWidget(buttonHubs);
    this->leftLayout->addWidget(buttonGroups);
    this->leftLayout->addWidget(buttonDevices);
    this->leftLayout->addWidget(buttonUnits);
    leftLayout->addWidget(buttonAllocationDevices);
    leftLayout->addWidget(buttonTable);
    leftLayout->addWidget(buttonSql);
    leftLayout->addWidget(buttonErrors);
    leftLayout->addWidget(buttonNets);
    leftLayout->addWidget(buttonRedirectMsg);
    leftLayout->addWidget(buttonAllocationUnits);




//  Создание объектов после нажатия на кнопки
    // Добавить остальные классы по мере продвижения
    this->ob = new GeneralSettings();

    this->rooms = new Rooms();

    this->groups = new Groups();

    this->hubs = new Hubs();

    this->devices = new Devices();


    this->units = new Units();

    this->allocation_devices = new AllocationDevices();

    this->table = new Table(db);

    this->sql = new ToolBarWidget();

    this->errors = new Errors();

    this->networkDialog = new NetworkDialog();

    this->addNets = new AddNets();

    this->redirectMessages = new RedirectMessages();

    this->allocationUnits = new AllocationUnitsDialog();




    //  Добавление в Stack
    this->stack->addWidget(ob); //0
    this->stack->addWidget(rooms);//1
    this->stack->addWidget(hubs);//2
    this->stack->addWidget(groups);//3
    this->stack->addWidget(devices);//4
    this->stack->addWidget(units);//5
    this->stack->addWidget(networkDialog);//6
    this->stack->addWidget(table);//7
    this->stack->addWidget(sql);//8
    this->stack->addWidget(errors);//9
    this->stack->addWidget(addNets);//10
    this->stack->addWidget(redirectMessages);//11
    this->stack->addWidget(allocationUnits);//12

    buttonGeneralSettings->setChecked(true);
    buttonRooms->setChecked(false);
    buttonRooms->setChecked(false);
    buttonRooms->setChecked(false);
    buttonRooms->setChecked(false);
    buttonRooms->setChecked(false);
    buttonRooms->setChecked(false);


    //Установка   связи сигналов с showstack
    connect(buttonGeneralSettings,SIGNAL(clicked()),this,SLOT(showStack()));
    //connect(buttonGeneralSettings,SIGNAL(pressed()),this,SLOT(changedColorButton()));
    connect(buttonRooms,SIGNAL(clicked()),this,SLOT(showStack()));
    connect(buttonGroups,SIGNAL(clicked()),this,SLOT(showStack()));
    connect(buttonDevices,SIGNAL(clicked()),this,SLOT(showStack()));
    connect(buttonHubs,SIGNAL(clicked()),this,SLOT(showStack()));
    connect(buttonUnits,SIGNAL(clicked()),this,SLOT(showStack()));
    connect(buttonRooms,SIGNAL(clicked()),this,SLOT(showStack()));
    connect(buttonAllocationDevices,SIGNAL(clicked()),this,SLOT(showStack()));
    connect(buttonTable,SIGNAL(clicked()),this,SLOT(showStack()));
    connect(buttonSql,SIGNAL(clicked()),this,SLOT(showStack()));
    connect(buttonErrors,SIGNAL(clicked()),this,SLOT(showStack()));
    connect(buttonNets,SIGNAL(clicked()),this,SLOT(showStack()));
    connect(buttonRedirectMsg,SIGNAL(clicked()),this,SLOT(showStack()));
    connect(buttonAllocationUnits,SIGNAL(clicked()),this,SLOT(showStack()));



}

void MainWindow::quit()
{
    this->db->close();

    exit(0);
}

void MainWindow::slotCloseDataBasa()
{


    this->db->close();

    this->mainLayout->removeWidget(this->stack);
    delete this->stack;
    this->stack = NULL;

    this->leftLayout->removeWidget(this->buttonDevices);
    delete this->buttonDevices;
    this->buttonDevices = NULL;

    this->leftLayout->removeWidget(this->buttonRooms);
    delete this->buttonRooms;
    this->buttonRooms = NULL;

    this->leftLayout->removeWidget(this->buttonHubs);
    delete this->buttonHubs;
    this->buttonHubs = NULL;

    this->leftLayout->removeWidget(this->buttonAllocationDevices);
    delete this->buttonAllocationDevices;
    this->buttonAllocationDevices = NULL;

    this->leftLayout->removeWidget(this->buttonErrors);
    delete this->buttonErrors;
    this->buttonErrors = NULL;

    this->leftLayout->removeWidget(this->buttonGroups);
    delete this->buttonGroups;
    this->buttonGroups = NULL;

    this->leftLayout->removeWidget(this->buttonGeneralSettings);
    delete this->buttonGeneralSettings;
    this->buttonGeneralSettings = NULL;

    this->leftLayout->removeWidget(this->buttonUnits);
    delete this->buttonUnits;
    this->buttonUnits = NULL;

    this->leftLayout->removeWidget(this->buttonTable);
    delete this->buttonTable;
    this->buttonTable = NULL;

    this->leftLayout->removeWidget(this->buttonSql);
    delete this->buttonSql;
    this->buttonSql = NULL;

    this->leftLayout->removeWidget(this->buttonNets);
    delete this->buttonNets;
    this->buttonNets = NULL;

    this->leftLayout->removeWidget(this->buttonRedirectMsg);
    delete this->buttonRedirectMsg;
    this->buttonRedirectMsg = NULL;

    this->leftLayout->removeWidget(this->buttonAllocationUnits);
    delete this->buttonAllocationUnits;
    this->buttonAllocationUnits = NULL;
}

//bool MainWindow::eventFilter(QObject *target, QEvent *event)
//{

//        if(event->type() == QEvent::Wheel)
//        {
//            const char *className = target->metaObject()->className();
//            if(QString(className) == QString("QComboBox"))
//            {
//                 QCoreApplication::sendEvent(this, event);
//                             return true;
//            }

//        }
//        return QWidget::eventFilter(target, event);

//}
