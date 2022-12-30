#ifndef ERRORS_H
#define ERRORS_H

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
#include <QScrollArea>
#include <QScrollBar>
#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

#include<error.h>

class Errors : public QWidget
{
    Q_OBJECT
public:
    Errors(QWidget *parent =0);
    ~Errors();

    class DeleteException { };

private:
    QVBoxLayout *mainLayout;
    QPushButton *buttonAdd;
    QPushButton *btnSave;
    QPushButton *btnUp;

    QVBoxLayout *scrollLayout;
    QWidget *scrollWidget;
    QScrollArea *scrollArea;

    std::vector <Error *> errorEdits;

private slots:
    void remove(Error *errorEdit);
    void addErrorEdit();
    void updateErrors();
};

#endif // ERRORS_H
