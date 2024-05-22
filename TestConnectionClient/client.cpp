#include "client.h"

Client::Client(QWidget* parent) : QGraphicsView(parent), circlePosition(0, 0) {
    scene = new QGraphicsScene(this);
    setScene(scene);

    circle = scene->addEllipse(0, 0, 20, 20, QPen(Qt::black), QBrush(Qt::blue));
    circle->setPos(circlePosition);

    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    socket->connectToHost("127.0.0.1", 1234);
}


void Client::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Space) {
        sendPositionToServer();
    }
}

void Client::sendPositionToServer() {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    MyDTO dto(circlePosition.x(), circlePosition.y());
    out << dto;
    socket->write(block);
}

void Client::onConnected() {
    qDebug() << "Connected to server";
}

void Client::onReadyRead() {
    QByteArray data = socket->readAll();
    QDataStream in(&data, QIODevice::ReadOnly);
    double x, y;
    in >> x >> y;
    QPointF newPosition(x, y);
    updateCirclePosition(newPosition);
}

void Client::onDisconnected() {
    qDebug() << "Disconnected from server";
}

void Client::updateCirclePosition(const QPointF& newPosition) {
    circlePosition = newPosition;
    circle->setPos(circlePosition);
}
