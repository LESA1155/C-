#ifndef ALLOCATIONUNITSEDIT_H
#define ALLOCATIONUNITSEDIT_H

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QStringBuilder>
#include <QDebug>
#include <QApplication>




class AllocationUnitsEdit: public QGroupBox
{
    Q_OBJECT
public:
    AllocationUnitsEdit(int id = -1, QWidget *parent =0);

private:
    QGridLayout *mainLayout;
    QComboBox *comboDevices;
    QComboBox *comboUnits;
    QLineEdit *editSlots;
    QCheckBox *checkBoxIsMain;
    QCheckBox *checkBoxIsHidden;
    QPushButton *buttonDelete;

    int id;
    int deviceId;
    int unitId;
    int allocationUnitId;



private slots:
     void deleteFromDB();
     void updateComboDevices();
     void updateComboUnit();
     void updateIsMain();
     void updateIsHidden();
     void updateSlots();
     void slotSave();
     bool eventFilter(QObject *target, QEvent *event);
     void fillDevicesComboBox();
     void fillUnitsComboBox();
     void slotUp();

signals:
    void wasDeleted(AllocationUnitsEdit *allocUnitEdit);

};

#endif // ALLOCATIONUNITSEDIT_H
