#ifndef GROUPS_H
#define GROUPS_H

#include <QMainWindow>
#include <QWidget>
#include <QObject>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QScrollArea>
#include <QVector>
#include <group.h>


class Groups :  public QWidget
{
    Q_OBJECT
public:
    Groups(QWidget *parent =0);
     class DeleteException { };
private:

    QVBoxLayout *mainLayout;
    QPushButton *buttonAdd;
    QPushButton *btnSave;
    QVBoxLayout *scrollLayout;
    QWidget *scrollWidget;
    QScrollArea *scrollArea;
    QVector <Group *> groupEdits;

private slots:
    void remove(Group *groupEdit);
    void addGroup();
    void setNewGroupName(int id, const QString &name);

signals:
        void updated();
        void groupNameChanged(int id, const QString &name);

};

#endif // GROUPS_H
