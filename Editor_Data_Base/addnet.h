#ifndef ADDNET_H
#define ADDNET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QSqlError>
#include <QSqlQuery>
#include <QRegExp>
#include <QRegExpValidator>


class AddNet:public QGroupBox
{
    Q_OBJECT
public:
    AddNet(int id = -1, QWidget *parent = 0);
    ~AddNet();


private:
    int id;
    int deviceId;
    int unitId;
    int defectiveUnitId;
    int defectiveDeviceId;


    int defDeviceId;
    int defUnitId;

    QComboBox *comboDevice;
    QComboBox *comboDefectiveUnits;
    QLineEdit * editLog;
    QLineEdit *editNetIndex;

    QLineEdit *editX0;
    QLineEdit *editY0;
    QLineEdit *editX1;
    QLineEdit *editY1;
    QLineEdit *editX2;
    QLineEdit *editY2;
    QLineEdit *editX3;
    QLineEdit *editY3;
    QLineEdit *editX4;
    QLineEdit *editY4;
    QPushButton *buttonDelete;

private slots:
    void slotUpdateEditLog();
    void slotUpdatededitNetIndex();
    void slotUpdateX0();
    void slotUpdateX1();
    void slotUpdateX2();
    void slotUpdateX3();
    void slotUpdateX4();
    void slotUpdateY0();
    void slotUpdateY1();
    void slotUpdateY2();
    void slotUpdateY3();
    void slotUpdateY4();

 void deleteFromDB();
 void fillDefectiveUnits();
 void updateDefectiveUnit();
 void updateComboBoxDevices();
 void slotSave();
 bool eventFilter(QObject *target, QEvent *event);

signals:
void wasDeleted(AddNet* net);


};

#endif // ADDNET_H


