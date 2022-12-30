#ifndef ADDNETS_H
#define ADDNETS_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QScrollArea>
#include <QScrollBar>

#include <addnet.h>

#include <vector>

class AddNets:public QWidget
{
    Q_OBJECT
public:
    AddNets(QWidget *parent = 0);
    ~AddNets();

    class DeleteException{};

private:
    QVBoxLayout *pMainLayout;
    QScrollArea *scrollArea;
    QWidget *scrollWidget;
    QVBoxLayout *scrollLayout;
    QPushButton *buttonAdd;
    QPushButton *btnSave;
    QVector <AddNet*> nets;

private slots:
    void slotSetNewName(int id, QString &name);
    void slotAddNet();
    void slotRemove(AddNet* net);

signals:
    void roomNameChanged(int id, QString& name);
};

#endif // ADDNETS_H
