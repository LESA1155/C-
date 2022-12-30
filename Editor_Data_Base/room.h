#ifndef ROOM_H
#define ROOM_H

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


class Room : public QGroupBox
{
    Q_OBJECT
public:
    Room(int id = -1, QWidget *parent =0);
    int GetId()
    {
        return  id;
    }


private:
        QLineEdit *editName;
       int id;
        QVector <Room *> roomEdits;
        QPushButton *buttonDelete;
        QPushButton *buttonAllocationDevices;
private slots:
    void deleteFromDB();
    void updateName();
    void slotDemoDelete();
    void slotSave();
signals:
    void wasDeleted(Room *roomEdit);
    void roomNameChanged(int id, const QString &name);
    void getID(int id);
};

#endif // ROOM_H
////////////////////////////



