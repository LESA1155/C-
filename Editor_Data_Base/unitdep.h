#ifndef UNITDEP_H
#define UNITDEP_H

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QRegExp>
#include <QRegExpValidator>
#include <QtSql>
#include <QMessageBox>
#include <QGroupBox>
#include <QBoxLayout>
#include <QCheckBox>
#include "dependence.h"

class UnitDep : public QGroupBox
{
    Q_OBJECT
public:
    UnitDep(int deviceId, bool isMain, int allocId = -1, QWidget *parent = 0);

private:
    QHBoxLayout *mainLayout;

    QComboBox *comboUnits;

    QLineEdit *editSlot;

    QCheckBox *checkBoxIsHidden;

    QPushButton *buttonDependence;
    QPushButton *buttonDelete;

    Dependence *dependence;

    int allocId;
    int unitId;
    bool isMain;

public slots:
    void deleteFromDB();
    void setNewUnitName(int id, const QString &name);
    bool eventFilter(QObject *target, QEvent *event);

private slots:
    void updateUnit(); //void updateUnit(int index);
    void updateSlot();
    void updateIsHidden(); //    void updateIsHidden(int isHidden);
    void slotSave();

signals:
    void wasDeleted(UnitDep *unit);
};

#endif // UNITDEP_H
