#ifndef ALLOCATIONDEVICES_H
#define ALLOCATIONDEVICES_H

#include <QObject>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
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
#include <QFrame>
#include <QDebug>
#include <QScrollArea>
//#include <paintwidget.h>

class AllocationDevices : public QWidget
{
    Q_OBJECT
public:
    AllocationDevices(QWidget *parent =0);

private:

    QVBoxLayout *mainLayout;
    QGridLayout *settingsWindowLayout;
    QLineEdit *editGridStep;
    QLineEdit *editWidthWindow;
    QLineEdit *editHeightWindow;
    QPushButton *buttonAdd;
    QVBoxLayout *scrollLayout;
    QWidget *scrollWidget;
    QScrollArea *scrollArea;
    //PaintWidget *paintWidget;
    QGroupBox *gpWindowSettings;




private slots:

    void updateWidthWindow();
    void updateHeightWindow();
    void updateGridStep();




signals:
    void widthChanged(int width);
    void heightChanged(int height );
    void gridChanged(int gridStep);

   

};

#endif // ALLOCATIONDEVICES_H
