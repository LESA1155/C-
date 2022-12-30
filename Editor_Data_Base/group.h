#ifndef GROUP_H
#define GROUP_H

#include <QObject>
#include <QWidget>

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

#include<hub.h>
#include <algorithm>
#include <vector>

class Group : public QGroupBox
{
    Q_OBJECT
public:
    Group(int id = -1, QWidget *parent =0);
private:
    int id;
    int roomId;
   // QVector <Group*> groupEdits;
    QLineEdit * editName;
    QLineEdit * editRoomID;
    QPushButton *buttonDelete;
    QComboBox *comboBoxRoomNameForId;
private slots:
    void deleteFromDB();
    void updateName();
    void updatecomboBoxRoomNameForId();
    void slotSave();
    bool eventFilter(QObject *target, QEvent *event);
signals:
    void wasDeleted(Group *groupEdit);
    void groupNameChanged(int id, const QString &name);


};

#endif // GROUP_H
