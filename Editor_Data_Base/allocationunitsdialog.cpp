#include "allocationunitsdialog.h"

AllocationUnitsDialog::AllocationUnitsDialog()
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

    btnUptAll= new QPushButton("Обновить выпадающие списки");
    mainLayout->addWidget(btnUptAll);


    this->buttonAdd = new QPushButton("Добавить модуль в прибор");
    this->mainLayout->addWidget(this->buttonAdd);
    buttonAdd->setStyleSheet("background-color: Cornsilk;");
    this->buttonAdd->setFocusPolicy(Qt::NoFocus);

    QSqlQuery query("SELECT id FROM AllocationUnits");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    while (query.next()) {
        AllocationUnitsEdit *allocUnitEdit = new AllocationUnitsEdit(query.value(0).toInt());
        this->VectorAllocationUnitsEdits.push_back(allocUnitEdit);
        this->scrollLayout->addWidget(allocUnitEdit);
        connect(allocUnitEdit, SIGNAL(wasDeleted(AllocationUnitsEdit *)), this, SLOT(remove(AllocationUnitsEdit *)));
        connect(this->btnSave, SIGNAL(clicked()), allocUnitEdit , SLOT(slotSave()));
        connect(this->btnUptAll, SIGNAL(clicked()), allocUnitEdit , SLOT(slotUp()));
    }

     connect(this->buttonAdd, SIGNAL(clicked()), this, SLOT(addUnit()));
}

void AllocationUnitsDialog::remove(AllocationUnitsEdit *allocUnitEdit)
{
    std::vector<AllocationUnitsEdit *>::iterator it = std::find(
            this->VectorAllocationUnitsEdits.begin(),
            this->VectorAllocationUnitsEdits.end(),
            allocUnitEdit);
    if (it != this->VectorAllocationUnitsEdits.end()) {
        this->VectorAllocationUnitsEdits.erase(it);
        this->scrollLayout->removeWidget(allocUnitEdit);
        delete allocUnitEdit;
    }
    else {
        throw DeleteException();
    }
}

void AllocationUnitsDialog::addUnit()
{
    AllocationUnitsEdit *allocUnitEdit = new AllocationUnitsEdit();
    this->VectorAllocationUnitsEdits.push_back(allocUnitEdit);
    this->scrollLayout->addWidget(allocUnitEdit);
     connect(allocUnitEdit, SIGNAL(wasDeleted(AllocationUnitsEdit *)), this, SLOT(remove(AllocationUnitsEdit *)));
     connect(this->btnSave, SIGNAL(clicked()), allocUnitEdit , SLOT(slotSave()));
     connect(this->btnUptAll, SIGNAL(clicked()), allocUnitEdit , SLOT(slotUp()));
     this->scrollArea->verticalScrollBar()->setSliderDown(true);
}
