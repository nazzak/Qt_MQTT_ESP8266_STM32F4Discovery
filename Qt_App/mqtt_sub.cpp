#include "mqtt_sub.h"
#include <QDebug>

mqtt_sub::mqtt_sub(const QHostAddress& host,
                    const quint16 port)
    : QMQTT::Client(host, port)
    , _qout(stdout)
{
    connect(this, &mqtt_sub::connected, this, &mqtt_sub::onConnected);
    connect(this, &mqtt_sub::subscribed, this, &mqtt_sub::onSubscribed);
    connect(this, &mqtt_sub::received, this, &mqtt_sub::onReceived);
}

    void mqtt_sub::onConnected()
    {
        _qout << "connected" << endl;
        subscribe(TOPIC1, QoS);
    }

    void mqtt_sub::onSubscribed(const QString& topic)
    {
        _qout << "subscribed " << topic << endl;
    }

    void mqtt_sub::onReceived(const QMQTT::Message& message)
    {
        _qout << "publish received: \"" << QString::fromUtf8(message.payload())
              << "\"" << endl;
    }

