#ifndef GENERALSETTINGS_H
#define GENERALSETTINGS_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QtSql>
#include <QMessageBox>
#include <QPushButton>


class QCheckBox;
class QRadioButton;

class GeneralSettings: public QWidget
{
    Q_OBJECT
    QGridLayout *mainLayout;

    QLineEdit *editName;
    QLineEdit *editLogFolder;

    QComboBox *comboMini;
    QComboBox *comboNetwork;


    QLineEdit *editNetworkTitle;
    QLineEdit *editAddNetworkTitle;

    QPushButton *btnSave;


      const QString defaultName() const;
public:
    GeneralSettings(QWidget *parent = 0 );
    ~GeneralSettings();
private:

private slots:
    void loadData();
    void updateName();
    void updateComboMini();
    void updateComboNetwork();
    void updateCaptionNetwork();
    void updateCaptionAddNetwork();
    void updateLogFolder();
    void slotSave();
    bool eventFilter(QObject *target, QEvent *event);


};

#endif // GENERALSETTINGS_H
