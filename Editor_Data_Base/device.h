#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDialog>
#include <QDebug>

#include <algorithm>
#include <vector>

#include <content.h>

class Device : public QGroupBox
{
    Q_OBJECT
public:
    Device(int id = -1, QWidget *parent =0);
    ~Device();
private:
    QLineEdit *editName;
    QLineEdit *editMainTitle;
    QLineEdit *editMainShortTitle;
    QLineEdit *editReserveTitle;
    QLineEdit *editReserveShortTitle;
    QPushButton *buttonContentMain;
    QPushButton *buttonContentReserve;
    QPushButton *buttonDelete;
    QComboBox *comboboxPriority;
    QCheckBox *checkboxUseReserve;
    std::vector <Device*> deviceEdits;
    int id;
    Content *contentMain;
    Content *contentReserve;

public slots:

private slots:
    void deleteFromDB();
    void updateName();
    void updateUseReserve();
    void updateMainTitle();
    void updateMainShortTitle();
    void updateReserveTitle();
    void updateReserveShortTitle();
    //void updateUnits();
   void  updatePriority();
   void slotSave();
   bool eventFilter(QObject *target, QEvent *event);


signals:
    void wasDeleted(Device *deviceEdit);
    void deviceNameChanged(int id, const QString &name);
    void unitNameChanged(int id, const QString &name);
    void unitsChanged();

};

#endif // DEVICE_H  ;
