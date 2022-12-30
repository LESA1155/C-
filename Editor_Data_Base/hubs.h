#ifndef HUBS_H
#define HUBS_H

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
#include <hub.h>

class Hubs : public QWidget
{
    Q_OBJECT
public:
    Hubs( QWidget *parent = 0 );
    class DeleteException { };

private:
    QVBoxLayout *mainLayout;
    QPushButton *buttonAdd;
    QPushButton *btnSave;
    QVBoxLayout *scrollLayout;
    QWidget *scrollWidget;
    QScrollArea *scrollArea;
    QVector <Hub *> hubEdits;

private slots:
    void remove(Hub *hubEdit);
    void addHub();
    void setNewHubName(int id, const QString &name);

signals:
        void updated();
        void hubNameChanged(int id, const QString &name);



};

#endif // HUBS_H

#ifndef ROOMS_H
#define ROOMS_H




#endif // ROOMS_H
