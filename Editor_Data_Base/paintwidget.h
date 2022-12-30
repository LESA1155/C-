#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QCheckBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>






class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    PaintWidget(int w,int h,int gs ,QWidget *parent =0);

private:
//--  К Консруктору
    int width;
    int height;
    int gridStep;


// -----К функции PaintRects ----

    int device_width;
    int device_height;
    int hub_width;
    int hub_height;
    int nw_width;
    int nw_height;
    int x;
    int y;

//----


    QRect *rect;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QVBoxLayout *mainLayout;

    QGraphicsRectItem *RectItem;
    QGraphicsTextItem *nameItem;
    QVector <QGraphicsTextItem*> fullNameItems;

    QVector <int> listOfID;



private slots:
    void drawGrid();
    void setWidth(int width);
    void setHeight(int height);
    void setGridStep(int gridStep);
    void paintRects();
    void paintRectsNames();



};

#endif // GRAPHICSSCENE_H
