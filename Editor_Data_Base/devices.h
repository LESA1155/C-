#ifndef DEVICEDIALOG_H
#define DEVICEDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>

#include <QScrollArea>
#include <QMessageBox>
#include <QVector>


#include<device.h>



class Devices:public QWidget
{
    Q_OBJECT
public:
    Devices(QWidget *parent =0);
    //~Devices();

    class DeleteException { };

private:
    QVBoxLayout *mainLayout;
    QPushButton *buttonAdd;
    QPushButton *btnSave;
    QVBoxLayout *scrollLayout;
    QWidget *scrollWidget;
    QScrollArea *scrollArea;
    QVector <Device *> deviceEdits;
public slots:
    void setNewUnitName(int id, const QString &name);
    void updateUnits();

private slots:
    void remove(Device *deviceEdit);
    void addDeviceEdit();
    void setNewDeviceName(int id, const QString &name);

signals:
    void deviceNameChanged(int id, const QString &name);
    void updated();
    void unitNameChanged(int id, const QString &name);
    void unitsChanged();

};

#endif // DEVICEDIALOG_H
