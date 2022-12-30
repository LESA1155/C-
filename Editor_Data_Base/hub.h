#ifndef HUB_H
#define HUB_H

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
#include <QStringBuilder>

#include <algorithm>
#include <vector>



class Hub:public QGroupBox
{
    Q_OBJECT
public:
    Hub(int id = -1, QWidget *parent =0);

private:
    int id;
    int groupID;
    int master;
    QVector <Hub*> hubEdits;
    QLineEdit * editName;
    //QLineEdit * editMaster;
    QLineEdit * editX;
    QLineEdit * editY;
    QCheckBox * checkBoxIsVertical;
    QCheckBox * checkBoxIsHidden;
    QLineEdit * editPercent;
    QLineEdit *editDefectiveUnitMain;
    QLineEdit *editDefectiveUnitSpareMain;
    QLineEdit *editDefectiveUniteReserve;
    QLineEdit *editDefectiveUnitSpareReserve;
    QPushButton *buttonDelete;

    QComboBox *comboGroups;
    QComboBox *comboMaster;


private slots:
    void deleteFromDB();
    void updateName();
    //void updateMaster();
    void updateX();
    void updateY();
    void updateIsVertical();
    void updateIsHidden();
    void updatePercent();
    void updatedefectiveUniteMain();
    void updatedefectiveUnitSpareMain();
    void updatedefectiveUniteReserve();
    void updatedefectiveUnitSpareReserve();
    void updateComboGroups();
    void updateComboMaster();
//void updateComboGroups(int index);
    void fillComboGroups();
    void fillComboMaster();
    void slotSave();
    bool eventFilter(QObject *target, QEvent *event);


signals:
    void wasDeleted(Hub *hubEdit);
    void hubNameChanged(int id, const QString &name);


};

#endif // HUB_H
