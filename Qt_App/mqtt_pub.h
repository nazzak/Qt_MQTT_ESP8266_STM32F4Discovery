#ifndef MQTT_H
#define MQTT_H

#include "mqtt_pub.h"
#include <qmqtt.h>
#include <QCoreApplication>
#include <QTimer>
#include "define.h"

class mqtt_pub : public QMQTT::Client
{
    Q_OBJECT
public:
    explicit mqtt_pub(const QHostAddress& _host = MQTT_HOST, const quint16& _port = MQTT_PORT);
    virtual ~mqtt_pub() {}

    QTimer _timer;
    quint16 _number;

public slots:
    void onConnected();
    void onTimeout();
    void onDisconnected();
};

#endif // MQTT_H
