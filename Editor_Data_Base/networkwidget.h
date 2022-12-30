#ifndef NETWORKWIDGET_H
#define NETWORKWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QFont>
#include <QVector>
#include <QMouseEvent>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringBuilder>
#include <QTimer>
#include <QMessageBox>

class NetworkWidget: public QWidget
{
    Q_OBJECT

private:
    enum DeviceType {
        TypeDevice,
        TypeHub,
    };

    enum Direction {
        Horizontal,
        Vertical,
    };

    enum NetworkState {
        IsSuccess,
        IsFailed,
        IsUnknown,
        Untestable,
        Unused,
    };

    struct Device {
        DeviceType type;
        int id;
        QPoint pos;
        QSize size;
        QString name;
        QRect rect;
        QRect rectShadow;
        bool useReserve;
    };

    struct Connection {
        Device *masterMain;
        Device *masterReserve;
        Device *slave;
        Direction directionMain;
        Direction directionReserve;
        int percentMain;
        int percentReserve;
        NetworkState states[4];
        QVector <QLine> lines[4];
        QVector <QLine> linesShadow[4];
    };

    struct Network {
        int index;
        QPoint pos;
        QSize size;
        QRect rectNetwork;
        QRect rectShadow;
        QRect rectText;
        QRect rectTextShadow;
        bool isHidden;
        bool isChecked;
        QString title;
        NetworkState state;
    };

public:
    explicit NetworkWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QColor colorBackground;
    QColor colorText;
    QColor colorUnknown;
    QColor colorSuccess;
    QColor colorFailed;
    QColor colorUntestable;
    QColor colorShadowDevice;
    QColor colorShadowConnection;
    QColor colorNetworkBackground;
    QColor colorNetworkBackgroundChecked;
    QColor colorNetworkBorder;
    QLinearGradient colorDevice;

    QVector <Device *> devices;
    QVector <Connection *> connections;

    Network *networks[4];

    QSize hubSize;
    QSize deviceSize;
    QSize networkSize;

    int offsetx11;
    int offsetx12;
    int offsetx21;
    int offsetx22;
    int offsetx23;
    int offsetx24;
    int offsety11;
    int offsety12;
    int offsety21;
    int offsety22;
    int offsety23;
    int offsety24;

    QTimer *updateTimer;

    QPoint gridStep;
    QPoint gridStart;

    bool noNets;
    bool noAddNets;

    void computeObjects();

    void drawHubs(QPainter *p);
    void drawDevices(QPainter *p);
    void drawConnections(QPainter *p);
    void drawConnections(QPainter *p, bool isMain, bool isShadow);
    void drawConnection(QPainter *p, Connection *connection, int stateIndex, bool isShadow);
    void drawFrame(QPainter *p);
    void drawGrid(QPainter *p);
    void drawNetworks(QPainter *p);

    Device *deviceAtPoint(const QPoint &point);
    void testNetworkForDevice(Device *device);
    int getLineDrawOffset(const DeviceType &type, Direction direction, int networkIndex, bool useReserve);

    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    Device *clickedDevice;
    Network *clickedNetwork;
    Device moveFrame;
    Network moveNetwork;
    QPoint clickPos;

    Device *getHubById(int id);

public slots:
    void setGridStep(int x, int y);
    void setGridStep(QPoint step);
    void setGridStart(int x, int y);
    void setGridStart(QPoint point);
    void fillDevicesAndConnections();

signals:
    void testNetworkForDevice(int id);
    void deviceWithIdSelected(int allocId, bool isHub);
};



#endif // NETWORKWIDGET_H
