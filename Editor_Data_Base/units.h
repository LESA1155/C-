#ifndef UNITS_H
#define UNITS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QLineEdit>
#include <QScrollArea>
#include <QScrollBar>

#include <QVector>
#include <unit.h>

class Units : public QWidget
{
    Q_OBJECT
public:
    Units( QWidget *parent = 0 );
    class DeleteException { };




private:
    QVBoxLayout *mainLayout;
    QPushButton *buttonAdd;
    QPushButton *btnSave;
    QVBoxLayout *scrollLayout;
    QWidget *scrollWidget;
    QScrollArea *scrollArea;
    QVector <Unit *> unitEdits;

private slots:
    void remove(Unit *unitEdit);
    void addUnit();
    void setNewUnitName(int id, const QString &name);


signals:
        void updated();
        void unitNameChanged(int id, const QString &name);



};

#endif // UNITS_H
