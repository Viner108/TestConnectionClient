#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QDebug>
#include "mydto.h"

class Client : public QGraphicsView {
    Q_OBJECT
public:
    Client(QWidget* parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket* socket;
    QGraphicsScene* scene;
    QGraphicsEllipseItem* circle;
    QPointF circlePosition;

    void sendPositionToServer();
    void updateCirclePosition(const QPointF& newPosition);
};

#endif // CLIENT_H
