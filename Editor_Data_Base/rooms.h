#ifndef ROOMS_H
#define ROOMS_H
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
#include <QVector>
#include <room.h>

class Rooms: public QWidget
{
    Q_OBJECT
public:
    Rooms( QWidget *parent = 0);

    class DeleteException { };


private:
    int idRoomForDelete;
    QVBoxLayout *mainLayout;
    QPushButton *buttonAdd;
    QPushButton *btnSave;
    QVBoxLayout *scrollLayout;
    QWidget *scrollWidget;
    QScrollArea *scrollArea;
    QVector <Room *> roomEdits;

private slots:
    void remove(Room *roomEdit);
    void addRoom();
    void setNewRoomName(int id, const QString &name);
    void deleteFromDB_Save(int id);
    //void slotSave();

signals:
    void roomNameChanged(int id, const QString &name);
    void updated();


};

#endif // ROOMS_H


