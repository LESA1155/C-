#ifndef DEPENDENSEDIT_H
#define DEPENDENSEDIT_H

#include <QObject>
#include <QWidget>
#include <QtSql>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QMessageBox>

class DependenceEdit  :  public QWidget
{
    Q_OBJECT
public:
    DependenceEdit(int allocId, int slaveAllocId, int depenId, QWidget *parent = 0);
private:
    int allocId;
    int slaveAllocId;
    int depenId;

    QHBoxLayout *mainLayout;
    QLabel *labelSlot;
    QLabel *labelName;
    QLabel *labelType;

    QCheckBox *checkBoxActive;
    QCheckBox *checkBoxCritical;


private slots:
    void updateActive(bool isActive);
    void updateCritical(bool isCritical);
};

#endif // DEPENDENSEDIT_H
