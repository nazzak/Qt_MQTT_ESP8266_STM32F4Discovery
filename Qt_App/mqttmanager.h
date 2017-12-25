#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include <QObject>
#include "mqtt_sub.h"
#include "mqtt_pub.h"

using namespace std;

class MqttManager : public QObject
{
    Q_OBJECT
public:
    MqttManager(const QHostAddress& _host = MQTT_HOST, const quint16& _port = MQTT_PORT, QObject *parent = nullptr);
    mqtt_sub *m_subscriber;
    mqtt_pub *m_publisher;
    QString m_ipAddress;
    qint16 m_port;

    ~MqttManager();
    void send(const QString &_msg = "");

public slots:
    void sl_connect(void);
    void sl_received(const QMQTT::Message &message);

signals:
    void sg_received(const QMQTT::Message &message);
};

#endif // MQTTMANAGER_H
