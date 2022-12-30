#include "networkwidget.h"

NetworkWidget::NetworkWidget(QWidget *parent) : QWidget(parent)
{


    QSqlQuery query;

    query.exec("SELECT hub_height, hub_width, device_height, device_width, network_height, network_width, offset_x_1_1, offset_x_1_2, offset_x_2_1, offset_x_2_2, offset_x_2_3, offset_x_2_4, offset_y_1_1, offset_y_1_2, offset_y_2_1, offset_y_2_2, offset_y_2_3, offset_y_2_4 "
                    "FROM TestLauncherSettings");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    if (!query.next()) {
        QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    if (!(query.value(0).isNull() || query.value(1).isNull())) {
        this->hubSize.setHeight(query.value(0).toInt());
        this->hubSize.setWidth(query.value(1).toInt());
    }
    else {
        this->hubSize.setWidth(175);
        this->hubSize.setHeight(50);
    }
    if (!(query.value(2).isNull() || query.value(3).isNull())) {
        this->deviceSize.setHeight(query.value(2).toInt());
        this->deviceSize.setWidth(query.value(3).toInt());
    }
    else {
        this->deviceSize.setWidth(125);
        this->deviceSize.setHeight(80);
    }
    if (!(query.value(4).isNull() || query.value(5).isNull())) {
        this->networkSize.setHeight(query.value(4).toInt());
        this->networkSize.setWidth(query.value(5).toInt());
    }
    else {
        this->networkSize.setWidth(150);
        this->networkSize.setHeight(65);
    }

    this->offsetx11 = query.value(6).isNull() ? -5 : query.value(6).toInt();
    this->offsetx12 = query.value(7).isNull() ? 5 : query.value(7).toInt();
    this->offsetx21 = query.value(8).isNull() ? -38 : query.value(8).toInt();
    this->offsetx22 = query.value(9).isNull() ? -28 : query.value(9).toInt();
    this->offsetx23 = query.value(10).isNull() ? 28 : query.value(10).toInt();
    this->offsetx24 = query.value(11).isNull() ? 38 : query.value(11).toInt();
    this->offsety11 = query.value(12).isNull() ? -5 : query.value(12).toInt();
    this->offsety12 = query.value(13).isNull() ? 5 : query.value(13).toInt();
    this->offsety21 = query.value(16).isNull() ? -20 : query.value(14).toInt();
    this->offsety22 = query.value(15).isNull() ? -10 : query.value(15).toInt();
    this->offsety23 = query.value(16).isNull() ? 10 : query.value(16).toInt();
    this->offsety24 = query.value(17).isNull() ? 20 : query.value(17).toInt();

    noNets = false;
    noAddNets = false;

    this->clickedDevice = NULL;
    this->clickedNetwork = NULL;

    this->moveFrame.pos.setX(-1000);
    this->moveFrame.pos.setY(-1000);
    this->moveFrame.size.setHeight(0);
    this->moveFrame.size.setWidth(0);

    this->moveNetwork.pos.setX(-1000);
    this->moveNetwork.pos.setY(-1000);
    this->moveNetwork.size.setHeight(0);
    this->moveNetwork.size.setWidth(0);

    for (int i = 0; i < 4; i++) {
        networks[i] = new Network();
        networks[i]->index = i;
        networks[i]->size = this->networkSize;
    }

    query.exec("SELECT network_1_x, "
                    "network_1_y, "
                    "network_2_x, "
                    "network_2_y, "
                    "add_network_1_x, "
                    "add_network_1_y, "
                    "add_network_2_x, "
                    "add_network_2_y "
                    "FROM TestLauncherSettings");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    if (query.next()) {
        for (int i = 0; i < 4; i++) {
            networks[i]->pos = QPoint(query.value(2*i).toInt(), query.value(2*i+1).toInt());
        }
    }

    colorBackground = QColor(0, 0, 0, 0);
    colorText = QColor(246, 255, 219);
    colorUnknown = QColor(200, 200, 200);
    colorSuccess = QColor(106, 209, 68);
    colorFailed = QColor(223, 60, 60);
    colorUntestable = QColor(102, 103, 105);
    colorShadowDevice = QColor(0, 0, 0, 100);
    colorShadowConnection = QColor(40, 40, 40);

    colorDevice = QLinearGradient(0, 0, 0, 30);
    colorDevice.setColorAt(0.0, QColor(122, 123, 125));
    colorDevice.setColorAt(0.5, QColor(102, 103, 105));
    colorDevice.setColorAt(1.0, QColor(82, 83, 85));

    this->colorNetworkBackground = QColor(200, 200, 200);
    this->colorNetworkBackgroundChecked = QColor(64, 66, 68);
    this->colorNetworkBorder = QColor(38, 40, 41);

    this->updateTimer = new QTimer();
    this->updateTimer->setSingleShot(true);
    this->updateTimer->setInterval(500);

    this->fillDevicesAndConnections();

    connect(this->updateTimer, SIGNAL(timeout()), this, SLOT(update()));
}

void NetworkWidget::fillDevicesAndConnections()
{
    this->devices.clear();
    this->connections.clear();

    QSqlQuery query;

    query.exec("SELECT id, name, x, y FROM Hubs");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    while (query.next()) {
        Device *hub = new Device;
        hub->id = query.value(0).toInt();
        hub->name = query.value(1).toString();
        hub->pos = QPoint(query.value(2).toInt(), query.value(3).toInt());
        hub->size = hubSize;
        hub->type = TypeHub;
        hub->useReserve = false;
        this->devices.append(hub);
    }

    for (QVector<Device *>::iterator iter = this->devices.begin(); iter != this->devices.end(); ++iter) {
        Device *slave = *iter;

        if (slave->type == TypeHub) {
            QSqlQuery query("SELECT master, is_vertical, percent FROM Hubs WHERE id = " % QString::number(slave->id));
            if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
                QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
            }
            if (!query.next()) {
                QMessageBox::critical(this, "Can't query next", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
            }
            if (!query.value(0).isNull()) {
                Connection *connection = new Connection;
                Device *master = this->getHubById(query.value(0).toInt());
                if (master == NULL) {
                    continue;
                }
                connection->masterMain = master;
                connection->masterReserve = master;
                connection->slave = slave;
                connection->directionMain = query.value(1).toInt() ? Vertical : Horizontal;
                connection->directionReserve = query.value(1).toInt() ? Vertical : Horizontal;
                connection->percentMain = query.value(2).toInt();
                connection->percentReserve = query.value(2).toInt();
                for (int i = 0; i < 4; i++) {
                    connection->states[i] = i < 2 ? IsUnknown : Unused;
                }
                this->connections.append(connection);
            }
        }
    }

    query.exec("SELECT AllocationDevices.id, name, device_postfix, x, y, hub_id_main, hub_id_reserve, is_vertical_main, is_vertical_reserve, percent_main, percent_reserve, main_ip_1, main_ip_2, reserve_ip_1, reserve_ip_2, use_reserve "
               "FROM AllocationDevices INNER JOIN Devices ON AllocationDevices.device_id = Devices.id");
    if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
        QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
    }
    while (query.next()) {
        Device *device = new Device;
        device->id = query.value(0).toInt();
        device->name = query.value(1).toString();
        if (!query.value(2).isNull()) {
            QString postfix = query.value(2).toString();
            if (!postfix.isEmpty()) {
                device->name = device->name % postfix;
            }
        }
        device->pos = QPoint(query.value(3).toInt(), query.value(4).toInt());
        device->useReserve = query.value(15).toInt();
        device->size = deviceSize;
        device->type = TypeDevice;
        this->devices.append(device);

        if (!(query.value(5).isNull() && query.value(6).isNull())) {
            Connection *connection = new Connection;
            Device *hubMain = this->getHubById(query.value(5).toInt());
            Device *hubReserve = this->getHubById(query.value(6).toInt());
            if ((hubMain == NULL) || (hubReserve == NULL)) {
                continue;
            }
            connection->masterMain = hubMain;
            connection->masterReserve = hubReserve;
            connection->slave = device;
            connection->directionMain = query.value(7).toInt() ? Vertical : Horizontal;
            connection->directionReserve = query.value(8).toInt() ? Vertical : Horizontal;
            connection->percentMain = query.value(9).toInt();
            connection->percentReserve = query.value(10).toInt();
            for (int i = 0; i < 4; i++) {
                if (!query.value(11+i).isNull() && !query.value(11+i).toString().isEmpty()) {
                    connection->states[i] = IsUnknown;
                }
                else {
                    connection->states[i] = Unused;
                }
            }
            this->connections.append(connection);
        }
    }

    this->computeObjects();
    this->update();
}

void NetworkWidget::computeObjects()
{
    for (QVector<Device *>::iterator iter = this->devices.begin(); iter != this->devices.end(); ++iter) {
        Device *d = *iter;

        d->rect.setX(d->pos.x() - d->size.width()/2);
        d->rect.setY(d->pos.y() - d->size.height()/2);
        d->rect.setSize(d->size);

        d->rectShadow = d->rect;

        d->rectShadow.translate(5, 5);
    }

    for (QVector<Connection *>::iterator iter = this->connections.begin(); iter != this->connections.end(); ++iter) {
        Connection *c = *iter;

        const int networkIndexesCount = 2;
        for (int networkIndex = 0; networkIndex < networkIndexesCount; networkIndex++) {
            const int testStatesCount = 4;
            for (int stateIndex = 0; stateIndex < testStatesCount; stateIndex++) {
                Device *master = (stateIndex < 2) ? c->masterMain : c->masterReserve;
                Direction direction = (stateIndex < 2) ? c->directionMain : c->directionReserve;
                int percent = (stateIndex < 2) ? c->percentMain : c->percentReserve;
                c->linesShadow[stateIndex].clear();
                c->lines[stateIndex].clear();

                int offsetFrom = getLineDrawOffset(master->type, direction, stateIndex, master->useReserve);
                int offsetTo = getLineDrawOffset(c->slave->type, direction, stateIndex, c->slave->useReserve);

                QPoint points[4];
                points[0] = master->pos;
                points[3] = c->slave->pos;

                int midValue;
                switch (direction) {
                    case Horizontal:
                        points[0].setX(points[0].x()+offsetFrom);
                        points[3].setX(points[3].x()+offsetTo);

                        midValue = points[3].y();
                        midValue += percent;
                        midValue += offsetFrom;

                        points[1].setX(points[0].x());
                        points[1].setY(midValue);
                        points[2].setX(points[3].x());
                        points[2].setY(midValue);
                        break;
                    case Vertical:
                        points[0].setY(points[0].y()+offsetFrom);
                        points[3].setY(points[3].y()+offsetTo);

                        midValue = points[3].x();
                        midValue += percent;
                        midValue += offsetFrom;

                        points[1].setX(midValue);
                        points[1].setY(points[0].y());
                        points[2].setX(midValue);
                        points[2].setY(points[3].y());
                        break;
                }

                for (int i = 0; i < 3; i++) {
                    int j = i+1;
                    if (qAbs(points[i].x() - points[j].x()) + qAbs(points[i].y() - points[j].y()) > 2) {
                        QLine line(points[i], points[j]);

                        c->lines[stateIndex].append(line);

                        line.translate(1, 1);

                        c->linesShadow[stateIndex].append(line);
                    }
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        networks[i]->rectNetwork.setX(networks[i]->pos.x() - networks[i]->size.width()/2);
        networks[i]->rectNetwork.setY(networks[i]->pos.y() - networks[i]->size.height()/2);
        networks[i]->rectNetwork.setSize(networks[i]->size);

        networks[i]->rectShadow = networks[i]->rectNetwork;
        networks[i]->rectShadow.adjust(-1, -1, 1, 1);


        networks[i]->rectText = networks[i]->rectNetwork;

        networks[i]->rectTextShadow = networks[i]->rectText;
        networks[i]->rectTextShadow.translate(1, 1);

        networks[i]->isHidden = i < 2 ? this->noNets : this->noAddNets;
        this->networks[i]->title = QString(i < 2 ? "Основная" : "Доп.") % " №" % QString::number(i%2+1);
    }
}

void NetworkWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), colorBackground);

    painter.setRenderHint(QPainter::Antialiasing, true);

    QFont f;
    f.setBold(true);
    f.setPixelSize(12);
    painter.setFont(f);

    drawGrid(&painter);

    drawConnections(&painter);
    drawDevices(&painter);
    drawNetworks(&painter);

    drawFrame(&painter);
}

void NetworkWidget::drawDevices(QPainter *p)
{
    p->save();

    for (QVector<Device *>::iterator iter = this->devices.begin(); iter != this->devices.end(); ++iter) {
        Device *d = *iter;

        p->fillRect(d->rectShadow, colorShadowDevice);
        p->fillRect(d->rect, colorDevice);

        p->setPen(colorText);
        p->drawText(d->rect, Qt::AlignCenter, d->name);
    }

    p->restore();
}

void NetworkWidget::drawConnections(QPainter *p)
{
    p->save();

    this->drawConnections(p, false, true);
    this->drawConnections(p, false, false);
    this->drawConnections(p, true, true);
    this->drawConnections(p, true, false);

    p->restore();
}

void NetworkWidget::drawConnections(QPainter *p, bool isMain, bool isShadow)
{
    const int networkIndexesCount = 2;
    int networkIndexes[networkIndexesCount];

    if (isMain) {
        networkIndexes[0] = 2;
        networkIndexes[1] = 0;
    }
    else {
        networkIndexes[0] = 3;
        networkIndexes[1] = 1;
    }

    const int testStatesCount = 4;
    const NetworkState testStates[testStatesCount] = {Untestable, IsSuccess, IsUnknown, IsFailed};

    for (int stateIndex = 0; stateIndex < testStatesCount; stateIndex++) {
        for (int networkIndex = 0; networkIndex < networkIndexesCount; networkIndex++) {
            for (QVector<Connection *>::iterator iter = this->connections.begin(); iter != this->connections.end(); ++iter) {
                Connection *c = *iter;
                if (c->states[networkIndexes[networkIndex]] == testStates[stateIndex]) {
                    this->drawConnection(p, *iter, networkIndexes[networkIndex], isShadow);
                }
            }
        }
    }
}

void NetworkWidget::drawConnection(QPainter *p, Connection *connection, int stateIndex, bool isShadow)
{
    QVector <QLine> *lineVector;

    if (isShadow) {
        lineVector = &(connection->linesShadow[stateIndex]);

        switch (connection->states[stateIndex]) {
            case IsSuccess:
            case IsFailed:
            case IsUnknown:
            case Untestable:
                p->setPen(QPen(colorShadowConnection, 6));
                break;
            default:
                return;
        }
    }
    else {
        lineVector = &(connection->lines[stateIndex]);

        switch (connection->states[stateIndex]) {
            case IsSuccess:
                p->setPen(QPen(colorSuccess, 2));
                break;
            case IsFailed:
                p->setPen(QPen(colorFailed, 2));
                break;
            case IsUnknown:
                p->setPen(QPen(colorUnknown, 2));
                break;
            case Untestable:
                p->setPen(QPen(colorUntestable, 2));
                break;
            default:
                return;
        }
    }

    for (QVector<QLine>::iterator iter = lineVector->begin(); iter != lineVector->end(); ++iter) {
        p->drawLine(*iter);
    }
}

void NetworkWidget::drawFrame(QPainter *p)
{
    p->save();

    this->moveFrame.rect.setX(this->moveFrame.pos.x() - this->moveFrame.size.width()/2);
    this->moveFrame.rect.setY(this->moveFrame.pos.y() - this->moveFrame.size.height()/2);
    this->moveFrame.rect.setSize(this->moveFrame.size);

    this->moveFrame.rectShadow = this->moveFrame.rect;
    this->moveFrame.rectShadow.translate(5, 5);

    p->fillRect(this->moveFrame.rectShadow, colorShadowDevice);
    p->fillRect(this->moveFrame.rect, colorDevice);

    p->setPen(colorText);
    p->drawText(this->moveFrame.rect, Qt::AlignCenter, this->moveFrame.name);

    p->restore();
}

void NetworkWidget::drawGrid(QPainter *p)
{
    p->save();

    QSize size = this->size();
    for (int x = 0; x < this->gridStart.x(); x += this->gridStep.x()) {
        p->drawLine(x, 0, x, size.height());
    }
    for (int x = this->gridStart.x(); x < size.width(); x += this->gridStep.x()) {
        p->drawLine(x, 0, x, size.height());
    }
    for (int y = 0; y < this->gridStart.y(); y += this->gridStep.y()) {
        p->drawLine(0, y, size.width(), y);
    }
    for (int y = this->gridStart.y(); y < size.height(); y += this->gridStep.y()) {
        p->drawLine(0, y, size.width(), y);
    }

    p->restore();
}

void NetworkWidget::drawNetworks(QPainter *p)
{
    p->save();

    QFont f = p->font();
    f.setBold(true);
    p->setFont(f);

    for (int i = 0; i < 4; i++) {
//        if (this->networks[i]->isHidden) continue;

        p->fillRect(this->networks[i]->rectShadow, colorNetworkBorder);

        if (this->networks[i]->isChecked) {
            p->fillRect(this->networks[i]->rectNetwork, colorNetworkBackgroundChecked);
        }
        else {
            p->fillRect(this->networks[i]->rectNetwork, colorNetworkBackground);
        }

        f.setPixelSize(14);
        p->setFont(f);
        p->setPen(QPen(colorShadowDevice, 2));
        p->drawText(this->networks[i]->rectTextShadow, Qt::AlignCenter, this->networks[i]->title);

        switch (this->networks[i]->state) {
            case IsSuccess:
                p->setPen(QPen(colorSuccess, 2));
                break;
            case IsFailed:
                p->setPen(QPen(colorFailed, 2));
                break;
            case IsUnknown:
                p->setPen(QPen(colorUnknown, 2));
                break;
            case Untestable:
                p->setPen(QPen(colorUntestable, 2));
                break;
            default:
                return;
        }
        f.setPixelSize(14);
        p->setFont(f);
        p->drawText(this->networks[i]->rectText, Qt::AlignCenter, this->networks[i]->title);
    }

    this->moveNetwork.rectNetwork.setX(this->moveNetwork.pos.x() - this->moveNetwork.size.width()/2);
    this->moveNetwork.rectNetwork.setY(this->moveNetwork.pos.y() - this->moveNetwork.size.height()/2);
    this->moveNetwork.rectNetwork.setSize(this->moveNetwork.size);

    this->moveNetwork.rectShadow = this->moveNetwork.rectNetwork;
    this->moveNetwork.rectShadow.adjust(-1, -1, 1, 1);

    this->moveNetwork.rectText = this->moveNetwork.rectNetwork;

    this->moveNetwork.rectTextShadow = this->moveNetwork.rectText;
    this->moveNetwork.rectTextShadow.translate(1, 1);

//    d->rect.setY(d->pos.y() - d->size.height()/2);
//    d->rect.setSize(d->size);

//    d->rectShadow = d->rect;
//    d->rectShadow.translate(5, 5);


    p->fillRect(this->moveNetwork.rectShadow, colorNetworkBorder);
    p->fillRect(this->moveNetwork.rectNetwork, colorNetworkBackground);

    f.setPixelSize(14);
    p->setFont(f);
    p->setPen(QPen(colorShadowDevice, 2));
    p->drawText(moveNetwork.rectTextShadow, Qt::AlignCenter, moveNetwork.title);

    f.setPixelSize(14);
    p->setFont(f);
    p->setPen(QPen(colorUnknown, 2));
    p->drawText(moveNetwork.rectText, Qt::AlignCenter, moveNetwork.title);

    p->restore();
}

void NetworkWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (this->clickedDevice != NULL) {
        this->moveFrame.pos.setX(this->moveFrame.pos.x() + event->pos().x() - this->clickPos.x());
        this->moveFrame.pos.setY(this->moveFrame.pos.y() + event->pos().y() - this->clickPos.y());

        this->clickedDevice->pos = this->moveFrame.pos;

        int dx = (clickedDevice->pos.x()-this->gridStart.x()) % this->gridStep.x();
        dx = dx < this->gridStep.x()/2 ? -dx : this->gridStep.x()-dx;
        int dy = (clickedDevice->pos.y()-this->gridStart.y()) % this->gridStep.y();
        dy = dy < this->gridStep.y()/2 ? -dy : this->gridStep.y()-dy;

        clickedDevice->pos.setX(clickedDevice->pos.x()+dx);
        clickedDevice->pos.setY(clickedDevice->pos.y()+dy);

        if (clickedDevice->type == TypeHub) {
            QSqlQuery query("UPDATE Hubs SET x = " % QString::number(this->clickedDevice->pos.x()) %
                                ", y = " % QString::number(this->clickedDevice->pos.y()) %
                                " WHERE id = " + QString::number(clickedDevice->id));
            if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
                QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
            }
            emit this->deviceWithIdSelected(clickedDevice->id, true);
        }
        else if (clickedDevice->type == TypeDevice) {
            QSqlQuery query("UPDATE AllocationDevices SET x = " % QString::number(this->clickedDevice->pos.x()) %
                                ", y = " % QString::number(this->clickedDevice->pos.y()) %
                                " WHERE id = " + QString::number(clickedDevice->id));
            if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
                QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
            }

            emit this->deviceWithIdSelected(clickedDevice->id, false);
        }

        this->clickedDevice = NULL;

        this->moveFrame.pos.setX(-1000);
        this->moveFrame.pos.setY(-1000);

        this->computeObjects();
        this->update();
    }

    if (this->clickedNetwork != NULL) {
        this->moveNetwork.pos.setX(this->moveNetwork.pos.x() + event->pos().x() - this->clickPos.x());
        this->moveNetwork.pos.setY(this->moveNetwork.pos.y() + event->pos().y() - this->clickPos.y());

        this->clickedNetwork->pos = this->moveNetwork.pos;

        int dx = (clickedNetwork->pos.x()-this->gridStart.x()) % this->gridStep.x();
        dx = dx < this->gridStep.x()/2 ? -dx : this->gridStep.x()-dx;
        int dy = (clickedNetwork->pos.y()-this->gridStart.y()) % this->gridStep.y();
        dy = dy < this->gridStep.y()/2 ? -dy : this->gridStep.y()-dy;

        clickedNetwork->pos.setX(clickedNetwork->pos.x()+dx);
        clickedNetwork->pos.setY(clickedNetwork->pos.y()+dy);

        const char *networkName;
        switch (this->clickedNetwork->index) {
            case 0:
                networkName = "network_1";
                break;
            case 1:
                networkName = "network_2";
                break;
            case 2:
                networkName = "add_network_1";
                break;
            case 3:
                networkName = "add_network_2";
                break;
        }

        QSqlQuery query(QString("UPDATE TestLauncherSettings ") %
                        "SET " % networkName % "_x = " % QString::number(this->clickedNetwork->pos.x()) %
                            ", " % networkName % "_y = " % QString::number(this->clickedNetwork->pos.y()));
        if (!(query.lastError().driverText().isEmpty() && query.lastError().databaseText().isEmpty())) {
            QMessageBox::critical(this, "SQL error", query.lastQuery() + "\n\n" + query.lastError().driverText() + "\n\n" + query.lastError().databaseText());
        }

        this->clickedNetwork = NULL;

        this->moveNetwork.pos.setX(-1000);
        this->moveNetwork.pos.setY(-1000);

        this->computeObjects();
        this->update();
    }
}

void NetworkWidget::mousePressEvent(QMouseEvent *event)
{
    this->clickPos = event->pos();

    this->clickedNetwork = NULL;
    for (int i = 0; i < 4; i++) {
        if (!this->networks[i]->isHidden && this->networks[i]->rectNetwork.contains(event->pos())) {
            this->clickedNetwork = this->networks[i];
            this->moveNetwork.pos = this->clickedNetwork->pos;
            this->moveNetwork.size = this->clickedNetwork->size;
            this->moveNetwork.title = this->clickedNetwork->title;
            return;
        }
    }

    this->clickedDevice = this->deviceAtPoint(event->pos());

    if (this->clickedDevice != NULL) {
        this->moveFrame.pos = this->clickedDevice->pos;
        this->moveFrame.size = this->clickedDevice->size;
        this->moveFrame.name = this->clickedDevice->name;

    }
}

void NetworkWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (this->clickedNetwork != NULL) {
        this->moveNetwork.pos.setX(this->moveNetwork.pos.x() + event->pos().x() - this->clickPos.x());
        this->moveNetwork.pos.setY(this->moveNetwork.pos.y() + event->pos().y() - this->clickPos.y());
        this->clickPos = event->pos();
        this->update();
    }
    else if (this->clickedDevice != NULL) {
        this->moveFrame.pos.setX(this->moveFrame.pos.x() + event->pos().x() - this->clickPos.x());
        this->moveFrame.pos.setY(this->moveFrame.pos.y() + event->pos().y() - this->clickPos.y());
        this->clickPos = event->pos();
        this->update();
    }
}

void NetworkWidget::testNetworkForDevice(Device *device)
{
    if (device == NULL) {
        return;
    }

    if (device->type == TypeDevice) {
        for (QVector<Connection *>::iterator iter = this->connections.begin(); iter != this->connections.end(); ++iter) {
            Connection *c = *iter;
            if (c->slave == device) {
                emit this->testNetworkForDevice(c->slave->id);
            }
        }
    }
    else {
        for (QVector<Connection *>::iterator iter = this->connections.begin(); iter != this->connections.end(); ++iter) {
            Connection *c = *iter;
            if ((c->masterMain == device || c->masterReserve == device) && c->slave->type == TypeDevice) {
                emit this->testNetworkForDevice(c->slave->id);
            }
        }
    }
}

NetworkWidget::Device *NetworkWidget::deviceAtPoint(const QPoint &point)
{
    QVector<Device *>::iterator iter = this->devices.end();
    while (iter != this->devices.begin()) {
        --iter;
        Device *d = *iter;

        if (d->rect.contains(point)) {
            return d;
        }
    }
    return NULL;
}

int NetworkWidget::getLineDrawOffset(const DeviceType &type, Direction direction, int networkIndex, bool useReserve)
{
    if (type == TypeDevice && useReserve) {
        switch (networkIndex) {
            case 0:
                return (direction == Horizontal) ? offsetx21 : offsety21;
            case 1:
                return (direction == Horizontal) ? offsetx22 : offsety22;
            case 2:
                return (direction == Horizontal) ? offsetx23 : offsety23;
            case 3:
                return (direction == Horizontal) ? offsetx24 : offsety24;
            default:
                return 0;
        }
    }
    else if (type == TypeHub || (type == TypeDevice && !useReserve)) {
        switch (networkIndex) {
            case 0:
            case 2:
                return (direction == Horizontal) ? offsetx11 : offsety11;
            case 1:
            case 3:
                return (direction == Horizontal) ? offsetx12 : offsety12;
            default:
                return 0;
        }
    }

    return 0;
}

NetworkWidget::Device *NetworkWidget::getHubById(int id)
{
    for (QVector<Device *>::iterator iter = this->devices.begin(); iter != this->devices.end(); ++iter) {
        Device *d = *iter;

        if (d->type == TypeHub) {
            if (d->id == id) {
                return d;
            }
        }
    }

    return NULL;
}

void NetworkWidget::setGridStep(int x, int y)
{
    this->setGridStep(QPoint(x, y));
}

void NetworkWidget::setGridStep(QPoint step)
{
    this->gridStep = step;
    this->update();
}

void NetworkWidget::setGridStart(int x, int y)
{
    this->setGridStart(QPoint(x, y));
}

void NetworkWidget::setGridStart(QPoint point)
{
    this->gridStart = point;
    this->update();
}

