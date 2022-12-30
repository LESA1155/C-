#include "paintwidget.h"

PaintWidget::PaintWidget(int w,int h,int gs, QWidget *parent): QWidget(parent)
{
    this->width=w;
    this->height=h;
    this->gridStep=gs;


    this->mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    this->view = new QGraphicsView();
    mainLayout->addWidget(view);

    this->scene = new QGraphicsScene();
    view->setScene(scene);
    rect = new QRect(0,0,width,height);
    scene->setSceneRect(*rect);
    drawGrid();
    paintRects();

//    npw = new NetworkPaintWidget();
//    mainLayout->addWidget(npw);

    //paintRectsNames();
}









void PaintWidget::drawGrid()
{
    if (gridStep!=0)
    {
    //Рисование горизонтальных линий
        int y=0,xBegin=0,xEnd=width;
         for (int rows = 0; rows <= height; rows+=gridStep) {
            scene->addLine(xBegin,y,xEnd,y);
            y+=gridStep;
        }

    //Рисование вертикальных Линий
    int yBegin = 0,yEnd = height,x=0;
    for (int columns = 0; columns <= width; columns+=gridStep) {
        scene->addLine(x,yBegin,x,yEnd);
        x+=gridStep;
            }
        }
}

void PaintWidget::setWidth(int width)
{
    this->width = width;
    scene->clear();
    scene->setSceneRect(0,0,width,height);
    drawGrid();
    paintRects();
}

void PaintWidget::setHeight(int height)
{
    this->height= height;
    scene->clear();
    scene->setSceneRect(0,0,width,height);
    drawGrid();
    paintRects();
}

void PaintWidget::setGridStep(int gridStep)
{
    this->gridStep = gridStep;
    scene->clear();
    drawGrid();
    paintRects();
}

void PaintWidget::paintRects()
{

    QSqlQuery query;
    query.exec("SELECT hub_height, hub_width, device_height, device_width "
                "FROM TestLauncherSettings ");

       if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty()))
       {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());

       }
       if (!query.next()) {
           QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
       }

       //query.first(); СПРОСИТЬ У РУСЛАНА почему какие-то запросы написаны в строчку, какие-то в столбец (SELECT), вляет ли это на работу или просто удобно читать.
       // Почмеу где-то пишет query(SELECT) и сразу запрос, а где-то через query.exec.



       //Добавить проверку на 0 при чтении из базы данных. Вдруг 0 будет в базе данных
       //if (!query.value(0).isNull())
       device_height = query.value(0).toInt();
       device_width = query.value(1).toInt();
       hub_height = query.value(2).toInt();
       hub_width = query.value(3).toInt();

//     nw_width = query.value(4).toInt(); Если это останется после выхода Руслана на работу, то узнать зачем нужен network_width  и network_height
//     nw_height = query.value(5).toInt(); и добавить чтение этих полей  в запрос выше


       query.exec("SELECT id "
                  "FROM AllocationDevices");
       while(query.next())
       {

           int id = query.value(0).toInt();
           listOfID.push_back(id);
           //qDebug() << "id = " << id << endl;

       }





             for (QVector<int>::iterator iter = listOfID.begin(); iter!=listOfID.end();iter++)
             {
             query.exec("SELECT x,y "
                        "FROM AllocationDevices "
                        "WHERE id = " + QString::number(*iter));
             if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty()))
             {
              QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());

             }
             if (!query.next()) {
                 QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
             }

                   //qDebug() << "query.value(0).toInt() = " << query.value(0).toInt() << endl;
                   //qDebug() << "query.value(1).toInt() = " << query.value(1).toInt() << endl;
                   x = query.value(0).toInt();
                   y = query.value(1).toInt();
                   RectItem = scene->addRect(x,y,hub_width,hub_height);
                   RectItem->setBrush(Qt::gray);
                   RectItem->setFlags(QGraphicsItem::ItemIsMovable);
                   nameItem = scene->addText("Прибор");
                   nameItem->setParentItem(RectItem);

                   // qDebug() << "iter = " << *iter << endl;

             }

//       qDebug() << "device_width = " << device_width << endl;
//       qDebug() << "device_height = " << device_height << endl;
//       qDebug() << "hub_width = " << hub_width << endl;
//       qDebug() << "hub_height = " << hub_height << endl;


}

void PaintWidget::paintRectsNames()
{

    int id;
    int deviceID;
    QString deviceNameFromGroupID;
    QString fullNameDevice;
    QString devicePostfix;
    QSqlQuery query ("SELECT id "
                     "FROM AllocationDevices");

    while (query.next())
    {
        id = query.value(0).toInt();
        QSqlQuery query1 ("SELECT  "
                         "device_id,"
                         "device_postfix "
                         "FROM AllocationDevices "
                         "WHERE id = " + QString::number(id));
        while (query.next())
        {
             deviceID = query1.value(0).toInt();
             devicePostfix =  query1.value(1).toString();

             if (deviceID==1)
              {
                  deviceNameFromGroupID = "170H1";
              }
              else if (deviceID==2)
              {
                  deviceNameFromGroupID = "172Э";
              }
              else if (deviceID==3)
              {
                  deviceNameFromGroupID = "176H";
              }
              else
              {
                  deviceNameFromGroupID = "172H";
                }
         }
        fullNameDevice = deviceNameFromGroupID + " " + devicePostfix ;
        QGraphicsTextItem *textItem = new QGraphicsTextItem(fullNameDevice);
        fullNameItems.push_back(textItem);
        textItem->setFlags(QGraphicsItem::ItemIsMovable);



    }










       qDebug() << "id = " << id << endl;
       //qDebug() << "groupID = " << groupID << endl;



    for (int column = 0 ; column < 500;column+=100)
    {

        for (int rows = 0; rows < 500; rows+=100)
        {
             QVector <QGraphicsTextItem *>::iterator it = fullNameItems.begin();
             while (it!=fullNameItems.end())
             {
                 scene->addItem(*it);
                 it++;



             }
        }
     }




//      qDebug() << "countDeviceID = " << countDeviceID << endl;
//      qDebug() << "id = " << id << endl;
//      qDebug() << "groupID = " << groupID << endl;
//      qDebug() << "device_postfix = " << devicePostfix << endl;while (query.next())
//      textItem->setPos(,column);
//      textItem->setFlags(QGraphicsItem::ItemIsMovable);
//



//
//






}





















