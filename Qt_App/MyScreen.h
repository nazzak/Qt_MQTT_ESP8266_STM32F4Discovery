#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QLineEdit>
#include "mqttmanager.h"

using namespace std;

class MyScreen : public QWidget
{
    Q_OBJECT

public:
    MyScreen(QWidget *parent = 0);
    QPushButton *m_push3, *m_push4, *m_push5, *m_push6;
    char m_ledState[4];
    QGridLayout* m_GLayout;
    QLineEdit* m_ipAddress;
    QLineEdit* m_port;
    QPushButton* m_connect;
    QLabel* m_status;
    MqttManager * m_mqtt;

    ~MyScreen();

private slots:
    void handleButton(void);
    void handleReadyRead(const QByteArray& message);
    void sl_connect(void);

private:
    void led3On(void);
    void led4On(void);
    void led5On(void);
    void led6On(void);
    void ledsOn(void);
    void led3Off(void);
    void led4Off(void);
    void led5Off(void);
    void led6Off(void);
    void ledsOff(void);
    
};

#endif // WIDGET_H
