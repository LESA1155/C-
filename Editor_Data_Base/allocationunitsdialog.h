#ifndef ALLOCATIONUNITSDIALOG_H
#define ALLOCATIONUNITSDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QtSql>
#include <QScrollArea>
#include <QScrollBar>
#include <QMessageBox>


#include "allocationunitsedit.h"

class AllocationUnitsDialog : public QWidget
{
    Q_OBJECT
public:
    AllocationUnitsDialog();
    class DeleteException { };
private:
    QVBoxLayout *mainLayout;
    QPushButton *buttonAdd;
    QPushButton *btnUptAll;

    QPushButton *btnSave;

    QVBoxLayout *scrollLayout;
    QWidget *scrollWidget;
    QScrollArea *scrollArea;

    std::vector <AllocationUnitsEdit *> VectorAllocationUnitsEdits;


private slots:
    void remove(AllocationUnitsEdit *allocUnitEdit);
    void addUnit();


};

#endif // ALLOCATIONUNITSDIALOG_H
