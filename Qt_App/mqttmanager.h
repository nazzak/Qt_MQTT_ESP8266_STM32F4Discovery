#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include <QObject>
#include "define.h"
#include <QMqttClient>

using namespace std;

class MqttManager : public QObject
{
    Q_OBJECT
public:
    MqttManager(const QString& _host = MQTT_HOST, const quint16& _port = MQTT_PORT, QObject *parent = nullptr);
    QMqttClient * m_client;
    QString m_ipAddress;
    qint16 m_port;

    ~MqttManager();
    void send(const QString &_msg = "");

public slots:
    void sl_connect();
    void sl_disconnect();
    void sl_checkState(QMqttClient::ClientState);

signals:
    void sg_received(const QByteArray &message);
};

#endif // MQTTMANAGER_H
