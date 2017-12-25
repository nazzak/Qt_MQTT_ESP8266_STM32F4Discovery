#ifndef MQTT_SUB_H
#define MQTT_SUB_H

#include "mqtt_sub.h"
#include <qmqtt.h>
#include <QCoreApplication>
#include <QTimer>
#include "define.h"

class mqtt_sub : public QMQTT::Client
{
    Q_OBJECT
public:
    explicit mqtt_sub(const QHostAddress& _host = MQTT_HOST, const quint16& _port = MQTT_PORT);
    ~mqtt_sub();

    QTextStream _qout;


public slots:
    void onConnected();
    void onSubscribed(const QString& _topic);
    void onReceived(const QMQTT::Message& _message);
};


#endif // MQTT_SUB_H
