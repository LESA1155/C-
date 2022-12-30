#include "redirectmessages.h"

RedirectMessages::RedirectMessages(QWidget *parent)
    : QWidget(parent)
{
    this->mainLayout = new QVBoxLayout();
    this->setLayout(this->mainLayout);

    this->scrollArea = new QScrollArea();
    this->mainLayout->addWidget(this->scrollArea);
    this->scrollArea->setWidgetResizable(true);

    this->scrollWidget = new QWidget();
    this->scrollArea->setWidget(this->scrollWidget);

    this->scrollLayout = new QVBoxLayout();
    this->scrollWidget->setLayout(this->scrollLayout);
    this->scrollLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    btnSave = new QPushButton("Сохранить");
    mainLayout->addWidget(btnSave);
    btnSave->setStyleSheet("background-color: #56887D; color: white");

    this->buttonAdd = new QPushButton("Добавить сообщение");
    this->mainLayout->addWidget(this->buttonAdd);
    buttonAdd->setStyleSheet("background-color: Cornsilk;");
    this->buttonAdd->setFocusPolicy(Qt::NoFocus);




    QSqlQuery query("SELECT id FROM RedirectMessages");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    while (query.next()) {
        RedirectMsg *redMsg = new RedirectMsg(query.value(0).toInt());
        this->msgEdits.push_back(redMsg);
        this->scrollLayout->addWidget(redMsg);
        connect(redMsg, SIGNAL(wasDeleted(RedirectMsg *)), this, SLOT(remove(RedirectMsg *)));
        connect(this->btnSave, SIGNAL(clicked()), redMsg , SLOT(slotSave()));

    }


    connect(this->buttonAdd, SIGNAL(clicked()), this, SLOT(addMessage()));

}

void RedirectMessages::remove(RedirectMsg *redMsg)
{
    std::vector<RedirectMsg *>::iterator it = std::find(
            this->msgEdits.begin(),
            this->msgEdits.end(),
            redMsg);
    if (it != this->msgEdits.end()) {
        this->msgEdits.erase(it);
        this->scrollLayout->removeWidget(redMsg);
        delete redMsg;
    }
    else {
        throw DeleteException();
    }
}

void RedirectMessages::addMessage()
{
    RedirectMsg *redMsg = new RedirectMsg();
    this->msgEdits.push_back(redMsg);
    this->scrollLayout->addWidget(redMsg);
     connect(redMsg, SIGNAL(wasDeleted(RedirectMsg *)), this, SLOT(remove(RedirectMsg *)));
     connect(this->btnSave, SIGNAL(clicked()), redMsg , SLOT(slotSave()));
    //if (this->scrollArea->verticalScrollBar()->isVisible()) {
      //  this->scrollArea->verticalScrollBar()->setSliderPosition(this->scrollArea->verticalScrollBar()->maximum());
   //}
}
