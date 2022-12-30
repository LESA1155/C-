#ifndef ERROR_H
#define ERROR_H

#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QtSql>
#include <QMessageBox>
#include <QCheckBox>
#include <QWheelEvent>

class Error :public QGroupBox
{
    Q_OBJECT
public:
    Error(int id = -1, QWidget *parent = 0);
   ~Error();



private:
    QGridLayout *mainLayout;

    QComboBox *comboDevices;
    QComboBox *comboUnits;
    QLineEdit *editErrorCode;
    QCheckBox *checkboxSelectByBits;
    QLineEdit *editErrorText;

    QComboBox *comboDefectiveUnits;

    QPushButton *buttonDelete;

    int id;

    int deviceId;
    int allocationUnitId;
    int defectiveUnitId;



public slots:
    void deleteFromDB();
    void updateDevice();
    void updateUnit();
    void updateErrorCode();
    void updateErrorText();
    void updateSelectByBits();
    void fillUnits();
    void fillDefectiveUnits();
    void updateDefectiveUnit();
    void slotSave();
    bool eventFilter(QObject *target, QEvent *event);
    void slotUpdateCB();
    void fillDevices();
    void changeErrorTextForErrorCode();


signals:
    void wasDeleted(Error *errorEdit);
};




#endif // ERROR_H
