#ifndef REDIRECTMSG_H
#define REDIRECTMSG_H

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QSqlQuery>
#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QtSql>
#include <QMessageBox>
#include <QCheckBox>
#include <QDebug>

class RedirectMsg:public QGroupBox
{
    Q_OBJECT
public:
    RedirectMsg(int id = -1, QWidget *parent = 0);

private:
    int id;
    int beforeDeviceId;
    int afterDeviceId;
    QString devicePostfix;
    QString deviceNameBefore;
    QString deviceNameAfter;
    int beforeDeviceAllId;
    int afterDeviceAllId;
    QComboBox *comboAfterDevices;
    QComboBox *comboBeforeDevices;
    QLineEdit * editText;
    QVBoxLayout *mainLayout;

private slots:
    void slotUpdateMsgText();
    void deleteFromDB();
    void updateBeforeDeviceComboBox();
    void updateAfterDeviceComboBox();
    void slotSave();
    bool eventFilter(QObject *target, QEvent *event);



signals:
    void wasDeleted(RedirectMsg *redMsg);



};

#endif // REDIRECTMSG_H
