#ifndef UNIT_H
#define UNIT_H

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

class Unit : public QGroupBox
{
    Q_OBJECT
public:
    Unit(int id = -1, QWidget *parent =0);

private:
    int id;
    QVector <Unit*> unitEdits;
    QLineEdit * editName;
    QLineEdit * editTest;
    QLineEdit * editSpare;
    QCheckBox * checkboxIsOnLocalhost;
    QCheckBox * checkboxIsAutotest;
    QCheckBox * checkboxIsBlocking;
    QCheckBox * checkboxRunOnAnotherNode;
    QCheckBox * checkboxWaitForAddnetTest;

     QPushButton *buttonDelete;
    
    
private slots:
    void deleteFromDB();
    void updateName();
    void updateTest();
    void updateIsOnLocalhost();
    void updateIsAutotest();
    void updateIsBlocking();
    void updateRunOnAnotherNode();
    void updateWaitForAddnetTest();
    void updateSpare();
    void slotSave();
signals:
    void wasDeleted(Unit *unitEdit);
    void unitNameChanged(int id, const QString &name);



};

#endif // UNIT_H
