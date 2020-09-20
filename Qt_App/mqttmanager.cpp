#include "mqttmanager.h"

MqttManager::MqttManager(const QString& _host, const quint16& _port, QObject *parent) :
    QObject(parent),
    m_client{nullptr}
{
    m_client = new QMqttClient(this);
    m_client->setHostname(_host);
    m_client->setPort(_port);

    connect(m_client, &QMqttClient::stateChanged, this, &MqttManager::sl_checkState);

    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
        const QString content = QDateTime::currentDateTime().toString()
                + QLatin1String(" Received Topic: ")
                + topic.name()
                + QLatin1String(" Message: ")
                + message
                + QLatin1Char('\n');

        emit sg_received(message);

        qDebug() << content;
    });
}

MqttManager::~MqttManager()
{
    if(m_client)
    {
        delete m_client;
        m_client = nullptr;
    }
    qDebug() << "MqttManager destroyed";
}

void MqttManager::sl_connect()
{
    qDebug() << "Connect signal received";
    m_client->connectToHost();
}

void MqttManager::sl_disconnect()
{
    m_client->disconnectFromHost();
}

void MqttManager::send(const QString &_msg)
{
    qDebug() << _msg;
    m_client->publish(TOPIC2, _msg.toUtf8());
}

void MqttManager::sl_checkState(QMqttClient::ClientState _state)
{
    if(_state == QMqttClient::ClientState::Disconnected)
    {

    }
    else if(_state == QMqttClient::ClientState::Connected)
    {
        auto subscription = m_client->subscribe(TOPIC1, QoS);
        if (!subscription) {
            qDebug() << "Could not subscribe. Is there a valid connection?";
            return;
        }
        qDebug() << "subscribed to " + TOPIC1;
    }
    else if(_state == QMqttClient::ClientState::Connecting)
    {
    }
}
