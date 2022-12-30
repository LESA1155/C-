#include "errors.h"

Errors::Errors(QWidget *parent)
     :QWidget(parent)
{
    this->mainLayout = new QVBoxLayout();
    setLayout(this->mainLayout);

    this->scrollArea = new QScrollArea();
    this->mainLayout->addWidget(this->scrollArea);
    this->scrollArea->setWidgetResizable(true);

    this->scrollWidget = new QWidget();
    this->scrollArea->setWidget(this->scrollWidget);

    this->scrollLayout = new QVBoxLayout();
    this->scrollWidget->setLayout(this->scrollLayout);
    this->scrollLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    this->setWindowTitle("Перечень ошибок");
    //this->setMinimumWidth(1000);


    this->btnSave = new QPushButton("Сохранить");
    btnSave->setStyleSheet("background-color: #56887D; color: white");
    this->mainLayout->addWidget(this->btnSave);
    this->btnSave->setFocusPolicy(Qt::NoFocus);


    this->btnUp = new QPushButton("Обновить выпадающие списки");
    mainLayout->addWidget(this->btnUp);



    this->buttonAdd = new QPushButton("Добавить ошибку");
    buttonAdd->setStyleSheet("background-color: Cornsilk;");
    this->mainLayout->addWidget(this->buttonAdd);
    this->buttonAdd->setFocusPolicy(Qt::NoFocus);

    QSqlQuery query("SELECT id FROM Errors");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    while (query.next()) {
        Error *errorEdit = new Error(query.value(0).toInt());
        this->errorEdits.push_back(errorEdit);
        this->scrollLayout->addWidget(errorEdit);
        connect(errorEdit, SIGNAL(wasDeleted(Error *)), this, SLOT(remove(Error *)));
        connect(this->btnSave, SIGNAL(clicked()), errorEdit, SLOT(slotSave()));
        connect(this->btnUp, SIGNAL(clicked()), errorEdit, SLOT(slotUpdateCB()));
    }

    connect(this->buttonAdd, SIGNAL(clicked()), this, SLOT(addErrorEdit()));
}

Errors::~Errors()
{
//    delete this->mainLayout;
//    delete this->buttonAdd;

    while (this->errorEdits.size()) {
        delete this->errorEdits.back();
        this->errorEdits.pop_back();
    }
}

void Errors::remove(Error *errorEdit)
{
    std::vector<Error *>::iterator it = std::find(
            this->errorEdits.begin(),
            this->errorEdits.end(),
            errorEdit);
    if (it != this->errorEdits.end()) {
        this->errorEdits.erase(it);
        this->scrollLayout->removeWidget(errorEdit);
        delete errorEdit;
    }
    else {
        throw DeleteException();
    }
}

void Errors::addErrorEdit()
{
    Error *errorEdit = new Error();
    this->errorEdits.push_back(errorEdit);
    this->scrollLayout->addWidget(errorEdit);
    connect(errorEdit, SIGNAL(wasDeleted(Error *)), this, SLOT(remove(Error *)));
    connect(this->btnSave, SIGNAL(clicked()), errorEdit, SLOT(slotSave()));
    connect(this->btnUp, SIGNAL(clicked()), errorEdit, SLOT(slotUpdateCB()));


    this->scrollArea->verticalScrollBar()->setSliderDown(true);

    if (this->scrollArea->verticalScrollBar()->isVisible()) {
        this->scrollArea->verticalScrollBar()->setSliderPosition(this->scrollArea->verticalScrollBar()->maximum());
    }
}

void Errors::updateErrors()
{

}
