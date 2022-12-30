#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QSqlRelationalDelegate>
#include <QtWidgets>
#include <QAbstractListModel>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QSqlDatabase>



class Table:public QWidget
{
    Q_OBJECT
public:
    Table(QSqlDatabase*db,QWidget *parent = 0);

private:
   QSqlRelationalTableModel *modelAD;
   QVBoxLayout *mainLayout;
   QTableView *tvAD;
   QPushButton *btnRefresh;


private slots:
  void  slotRefreshTable();





};

#endif // TABLE_H
