#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPainter>
#include <QBoxLayout>
#include "mqtt_sub.h"
#include "mqtt_pub.h"
#include <QLineEdit>

class MyScreen : public QWidget
{
    Q_OBJECT

public:
    MyScreen(QWidget *parent = 0);
    QPushButton *m_push3, *m_push4, *m_push5, *m_push6, *m_rfid;
    char m_readmqtt[4];
    char m_ledState[4];
    mqtt_sub *m_subscriber;
    mqtt_pub *m_publisher;
    QTimer *timer;
    QGridLayout* GLayout;
    QLineEdit* m_ipAddress;
    QLineEdit* m_port;
    QPushButton* m_connect;

    ~MyScreen();

private slots:
    void handleButton(void);
    void handleReadyRead(const QMQTT::Message& message);
    void sl_connect(void);

private:
    void led3On(void);
    void led4On(void);
    void led5On(void);
    void led6On(void);
    void led3Off(void);
    void led4Off(void);
    void led5Off(void);
    void led6Off(void);
};

#endif // WIDGET_H
