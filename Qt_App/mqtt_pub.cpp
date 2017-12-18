#include "mqtt_pub.h"

mqtt_pub::mqtt_pub(const QHostAddress& host,
                   const quint16 port)
    :QMQTT::Client(host, port), _number(0)
{

    connect(this, &mqtt_pub::connected, this, &mqtt_pub::onConnected);
    connect(&_timer, &QTimer::timeout, this, &mqtt_pub::onTimeout);
    connect(this, &mqtt_pub::disconnected, this, &mqtt_pub::onDisconnected);
}

    void mqtt_pub::onConnected()
    {
        subscribe(TOPIC2, QoS);
    }

    void mqtt_pub::onTimeout()
    {
        QMQTT::Message message(_number, TOPIC2,
                               QString("Number is %1").arg(_number).toUtf8());
        publish(message);
        _number++;
        if(_number >= 10)
        {
            _timer.stop();
            disconnectFromHost();
        }
    }

    void mqtt_pub::onDisconnected()
    {
        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
    }






