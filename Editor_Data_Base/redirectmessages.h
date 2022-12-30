#ifndef REDIRECTMESSAGE_H
#define REDIRECTMESSAGE_H

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

#include <vector>
#include <algorithm>

#include "redirectmsg.h"

class RedirectMessages : public QWidget
{
    Q_OBJECT
public:
    RedirectMessages(QWidget *parent = 0);

    class DeleteException { };
private:
    QVBoxLayout *mainLayout;
    QPushButton *buttonAdd;
    QPushButton *btnSave;

    QVBoxLayout *scrollLayout;
    QWidget *scrollWidget;
    QScrollArea *scrollArea;

    std::vector <RedirectMsg *> msgEdits;

private slots:
   void remove(RedirectMsg *redMsg);
   void addMessage();



};

#endif // REDIRECTMESSAGE_H
