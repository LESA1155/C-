#ifndef DEPENDENS_H
#define DEPENDENS_H


#include <QWidget>
#include <QDialog>
#include <QtSql>
#include <QVBoxLayout>
#include <QMessageBox>
#include <dependenceedit.h>

class Dependence : public QDialog
{
    Q_OBJECT

public:
    explicit Dependence(int allocId, QWidget *parent = 0);



private:
    QVBoxLayout *mainLayout;

    int allocId;


    std::vector <DependenceEdit *> depens;
public slots:
    void deleteAll();



};

#endif // DEPENDENS_H
