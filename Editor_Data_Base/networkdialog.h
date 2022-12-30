#ifndef NETWORKDIALOG_H
#define NETWORKDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QStringBuilder>
#include <QPushButton>
#include <QFrame>
#include <QGroupBox>
#include <QComboBox>
#include <networkwidget.h>

class NetworkDialog : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkDialog(QWidget *parent = 0);

private:
    QVBoxLayout *mainLayout;

    QGridLayout *scrollLayout;
    QWidget *scrollWidget;
    QScrollArea *scrollArea;

    NetworkWidget *network;  // Не забыть про это

    QGroupBox *windowSettings;
    QGridLayout *windowSettingsLayout;

    QGroupBox *deviceSettings;
    QGridLayout *deviceSettingsLayout;

    QLabel *labelSize;
    QLineEdit *editWidth;
    QLineEdit *editHeight;

    QLabel *labelGridStep;
    QLineEdit *editGridStepX;
    QLineEdit *editGridStepY;

    QLabel *labelGridStart;
    QLineEdit *editGridStartX;
    QLineEdit *editGridStartY;

    QIntValidator *validatorSize;
    QIntValidator *validatorStep;
    QIntValidator *validatorStart;

    QLabel *labelDeviceName;

    QLineEdit *editX;
    QLineEdit *editY;

    QComboBox *comboboxHubsMain;
    QComboBox *comboboxHubsReserve;
    QComboBox *comboboxTypeMain;
    QComboBox *comboboxTypeReserve;
    QLineEdit *editPercentMain;
    QLineEdit *editPercentReserve;
    QIntValidator *percentValidator;

    int hubIdMain;
    int hubIdReserve;

    int allocId;
    bool isHub;

private slots:
    void setNetworkHeight();
    void setNetworkWidth();
    void setNetworkGridStep();
    void setNetworkGridStart();
    void switchWindows(bool isActive);
    void setItemsInGroupboxHidden(QGroupBox *groupbox, bool hidden);
    void setActiveDevice(int allocId, bool isHub);
    void fillHubs(bool clear = false);
    void updateX();
    void updateY();
    void updateHubMain(int index);
    void updateHubReserve(int index);
    void updateTypeMain(int index);
    void updateTypeReserve(int index);
    void updatePercentMain();
    void updatePercentReserve();
};

#endif // NETWORKDIALOG_H
