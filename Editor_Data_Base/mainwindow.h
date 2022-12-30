#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QComboBox>
#include <QFile>
#include <QResource>
#include <QMap>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QtSql>
#include <QGraphicsScene>
#include <QPalette>



#include <generalsettings.h>
#include <rooms.h>
#include <hubs.h>
#include <groups.h>
#include <units.h>
#include "allocationunitsdialog.h"
#include <allocationdevices.h>
#include <devices.h>
#include <errors.h>

#include <redirectmessages.h>
#include <paintwidget.h>
#include <table.h>
#include <toolbarwidget.h>
#include <networkdialog.h>
#include <addnets.h>


//#include <device.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    // обхявление кнопо
    QPushButton *buttonDevices;
    QPushButton *buttonRooms; //Создаем кнопку Комнаты
    QPushButton *buttonHubs; //Создаем кнопку Хабы
    QPushButton *buttonAllocationDevices;
    QPushButton *buttonErrors;
    QPushButton *buttonGroups;
    QPushButton *buttonGeneralSettings;
    QPushButton *buttonUnits;
    QPushButton *buttonTable;
    QPushButton *buttonSql;
    QPushButton *buttonNets;
    QPushButton *buttonRedirectMsg;
    QPushButton *buttonAllocationUnits;

    QWidget *wgt;
    QHBoxLayout * mainLayout;
    QVBoxLayout * leftLayout;

    QStackedWidget *stack;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuScheme;
    //QAction *newFile;
    QAction *openFile;
    QAction *closeDataBase;
    QAction *closeWindow;
    QAction *saveBD;
    QSqlDatabase *db;


    GeneralSettings *ob;
    Rooms *rooms;
    Groups *groups;
    Hubs *hubs;
    Units *units ;
    Devices *devices ;
    AllocationDevices * allocation_devices;
    Errors *errors;
    Table *table;
    ToolBarWidget *sql;
    NetworkDialog *networkDialog;
    AddNets *addNets;
    RedirectMessages *redirectMessages;
    AllocationUnitsDialog *allocationUnits;


    const QString getProgramName() const;
    bool openDB(const QString &filename);


private slots:
    void showStack();
    //void selectStack();
    void openDB();
    void addWidgets();
    void quit();
    void slotCloseDataBasa();
    //bool eventFilter(QObject *target, QEvent *event);





};
#endif // MAINWINDOW_H
