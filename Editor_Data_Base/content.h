#ifndef CONTENT_H
#define CONTENT_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QScrollArea>
#include <QPushButton>
#include <QtSql>
#include <unitdep.h>


class Content : public QDialog
{
   Q_OBJECT
public:
    Content(int deviceId, bool isMain, QWidget *parent = 0);
    ~Content();
     class DeleteException { };

private:
    int id;
    bool isMain;
    QGridLayout *mainLayout;
    QVBoxLayout *scrollLayout;
    QWidget *scrollWidget;
    QScrollArea *scrollArea;
    QPushButton *btnSave;
    QPushButton *buttonAdd;
    QComboBox *comboDefectiveUnits;
    QComboBox *comboDefectiveAddUnits;
    int defectiveUnitId;
    int defectiveAddUnitId;
    std::vector <UnitDep *> units;
    void addUnits();
    void removeUnits();
    void fillDefectiveUnits();

public slots:
    void setNewUnitName(int id, const QString &name);
    void updateUnits();
    void updateDefectiveUnit(int index);
    void updateDefectiveAddUnit(int index);


private slots:
    void remove(UnitDep *unit);
    void addUnit();
    bool eventFilter(QObject *target, QEvent *event);

signals:
    void unitNameChanged(int id, const QString &name);
};

#endif // CONTENT_H
