#include "unit.h"

Unit::Unit (int id, QWidget *parent)
    : QGroupBox(parent)
{

    this->setStyleSheet("QGroupBox { background-color: LightGray }");

    QString name;
    QString test;
    bool IsOnLocalhost;
    bool IsAutotest;
    bool IsBlocking;
    int RunOnAnotherNode;
    int WaitForAddnetTest;
    QString spare;
    
    if (id < 0) {
        name = "Без имени";
        test = "Без имени";
        IsOnLocalhost = false;
        IsAutotest = false;
        IsBlocking = false;
        RunOnAnotherNode = 0;
        WaitForAddnetTest = 0;
        spare = "Без имени";
        
        QSqlQuery query;
        query.exec("INSERT INTO Units(name, test, is_on_localhost, is_autotest, is_blocking, run_on_another_node, wait_for_addnet_test, spare) "
                   "VALUES ('" + name + "', '" + test + "' , " + QString::number(IsOnLocalhost) + "," + QString::number(IsAutotest) + " , " + QString::number(IsBlocking) + ", " + QString::number(RunOnAnotherNode) + ", "
                   + QString::number(WaitForAddnetTest) + ", '" + spare + "')");
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        this->id = query.lastInsertId().toInt();
    }
    
        else {
        this->id = id;
        
        QSqlQuery query ("SELECT "
                         "name, "
                         "test, "
                         "is_on_localhost, "
                         "is_autotest, "
                         "is_blocking, "
                         "run_on_another_node, "
                         "wait_for_addnet_test, "
                         "spare "
                      "FROM Units "
                      "WHERE id =  " + QString::number(id));
        
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        if (!query.next()) {
            QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }

        
        name =  query.value(0).toString();
        test = query.value(1).toString();
        IsOnLocalhost = query.value(2).toInt();
        IsAutotest = query.value(3).toInt();
        IsBlocking = query.value(4).toInt();
        RunOnAnotherNode = query.value(5).toInt();
        WaitForAddnetTest = query.value(6).toBool();
        spare = query.value(7).toString();
    }
    setTitle(name);
    
    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    QHBoxLayout *nameLayout = new QHBoxLayout();
    mainLayout->addLayout(nameLayout);

    QLabel *labelName = new QLabel("Имя Модуля: ");
    nameLayout->addWidget(labelName);
    this->editName = new QLineEdit();
    nameLayout->addWidget(editName);
    this->editName->setText(name);


    QLabel *labelTest = new QLabel("Тест");
    nameLayout->addWidget(labelTest);
    this->editTest = new QLineEdit();
    nameLayout->addWidget(editTest);
    this->editTest->setText(test);
    
    QLabel *labelSpare = new QLabel("ЗИП");
    nameLayout->addWidget(labelSpare);
    this->editSpare = new QLineEdit();
    nameLayout->addWidget(editSpare);
    this->editSpare->setText(spare);
    
    
    QHBoxLayout *checkboxLayout = new QHBoxLayout();
    mainLayout->addLayout(checkboxLayout);
    
    this->checkboxIsOnLocalhost = new QCheckBox("Использование chroot");
    checkboxLayout->addWidget(checkboxIsOnLocalhost);
    this->checkboxIsOnLocalhost->setChecked(IsOnLocalhost);


    this->checkboxIsAutotest = new QCheckBox("Автотест");
    checkboxLayout->addWidget(checkboxIsAutotest);
    this->checkboxIsAutotest->setChecked(IsAutotest);

    this->checkboxIsBlocking = new QCheckBox("Блокирущий");
    checkboxLayout->addWidget(checkboxIsBlocking);
    this->checkboxIsBlocking->setChecked(IsBlocking);

    this->checkboxRunOnAnotherNode = new QCheckBox("Запуск на другом узле");
    checkboxLayout->addWidget(checkboxRunOnAnotherNode);
    this->checkboxRunOnAnotherNode->setChecked(RunOnAnotherNode);

    this->checkboxWaitForAddnetTest = new QCheckBox("Ожидать завершения теста доп сети");
    checkboxLayout->addWidget(checkboxWaitForAddnetTest);
    this->checkboxWaitForAddnetTest->setChecked(WaitForAddnetTest);


    this->buttonDelete = new QPushButton("Удалить");
    buttonDelete->setStyleSheet("background-color: Cornsilk;");
    mainLayout->addWidget(buttonDelete);

    connect(this->buttonDelete,SIGNAL(clicked()),this , SLOT(deleteFromDB()));
    //connect(this->editName,SIGNAL(editingFinished()),this , SLOT(updateName()));
    //connect(this->editTest,SIGNAL(editingFinished()),this , SLOT(updateTest()));
    //connect(this->checkboxIsOnLocalhost,SIGNAL(toggled(bool)),this , SLOT(updateIsOnLocalhost(bool)));
    //connect(this->checkboxIsAutotest,SIGNAL(toggled(bool)),this , SLOT(updateIsAutotest(bool)));
    //connect(this->checkboxIsBlocking,SIGNAL(toggled(bool)),this , SLOT(updateIsBlocking(bool)));
    //connect(this->checkboxRunOnAnotherNode,SIGNAL(toggled(bool)),this , SLOT(updateRunOnAnotherNode(bool)));
    //connect(this->checkboxWaitForAddnetTest,SIGNAL(toggled(bool)),this , SLOT(updateWaitForAddnetTest(bool)));
    //connect(this->editSpare,SIGNAL(editingFinished()),this , SLOT(updateSpare()));

}


void Unit::deleteFromDB()
{
    if (QMessageBox::question(this, "Подтвердите действие", "Вы точно хотите удалить?", QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
        QSqlQuery query;
        query.exec("DELETE FROM Units "
                  "WHERE id = " + QString::number(this->id));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }
        emit wasDeleted(this);
    }
}

void Unit::updateName()
{
    QString name = this->editName->text();
    QSqlQuery query;
    query.exec("UPDATE Units "
              "SET name = '" + name + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

     setTitle(name);

     emit unitNameChanged(this->id, name);
}

void Unit::updateTest()
{
    QString name = this->editTest->text();
    QSqlQuery query;
    query.exec("UPDATE Units "
              "SET test = '" + name + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }

}

void Unit::updateIsOnLocalhost() // void Unit::updateIsOnLocalhost(bool isBlocking)
{
    QSqlQuery query;
    query.exec("UPDATE Units "
              "SET is_on_localhost = '" + QString::number(checkboxIsOnLocalhost->isChecked()) + "' "  //              "SET is_on_localhost = '" + QString::number(isBlocking) + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void Unit::updateIsAutotest()
{
    QSqlQuery query;
    query.exec("UPDATE Units "
              "SET is_autotest = '" + QString::number(checkboxIsAutotest->isChecked()) + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void Unit::updateIsBlocking()
{
    QSqlQuery query;
    query.exec("UPDATE Units "
              "SET is_blocking = '" + QString::number(checkboxIsBlocking->isChecked()) + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void Unit::updateRunOnAnotherNode()
{
    QSqlQuery query;
    query.exec("UPDATE Units "
              "SET run_on_another_node = '" + QString::number(checkboxRunOnAnotherNode->isChecked()) + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void Unit::updateWaitForAddnetTest()
{
    QSqlQuery query;
    query.exec("UPDATE Units "
              "SET wait_for_addnet_test = '" + QString::number(checkboxWaitForAddnetTest->isChecked()) + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void Unit::updateSpare()
{
    QString name = this->editSpare->text();
    QSqlQuery query;
    query.exec("UPDATE Units "
              "SET spare = '" + name + "' "
              "WHERE id = " + QString::number(this->id));
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
}

void Unit::slotSave()
{
    updateName();
    updateTest();
    updateIsOnLocalhost();
    updateIsAutotest();
    updateIsBlocking();
    updateRunOnAnotherNode();
    updateWaitForAddnetTest();
    updateSpare();
}

