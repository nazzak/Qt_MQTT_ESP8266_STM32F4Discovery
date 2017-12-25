#include "mqttmanager.h"

MqttManager::MqttManager(const QHostAddress& _host, const quint16& _port, QObject *parent) : QObject(parent)
{
    m_subscriber = Q_NULLPTR;
    m_publisher = Q_NULLPTR;
    
    m_subscriber = new mqtt_sub(_host, _port);
    if(m_subscriber)
        m_subscriber->connectToHost();
    
    m_publisher = new mqtt_pub(_host, _port);
    if(m_publisher)
        m_publisher->connectToHost();
    
    connect(m_subscriber, &mqtt_sub::received, this, &MqttManager::sl_received);
}

MqttManager::~MqttManager()
{
    m_publisher->disconnectFromHost();
    m_subscriber->disconnectFromHost();
    delete m_subscriber;
    delete m_publisher;
    qDebug() << "MqttManager destroyed";
}

void MqttManager::sl_connect(void)
{
    if(m_subscriber != Q_NULLPTR)
    {
        m_subscriber->disconnectFromHost();
        delete m_subscriber;
        m_subscriber = new mqtt_sub(QHostAddress(m_ipAddress), m_port);
        m_subscriber->connectToHost();
    }
    
    if(m_publisher != Q_NULLPTR)
    {
        m_publisher->disconnectFromHost();
        delete m_publisher;
        m_publisher = new mqtt_pub(QHostAddress(m_ipAddress), m_port);
        m_publisher->connectToHost();
    }
}

void MqttManager::sl_received(const QMQTT::Message &message)
{
    emit sg_received(message);
}

void MqttManager::send(const QString &_msg)
{
    qDebug() << _msg;
    QMQTT::Message message(0, TOPIC2, _msg.toUtf8());
    m_publisher->publish(message);
}
