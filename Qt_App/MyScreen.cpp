#include "myscreen.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>


MyScreen::MyScreen(QWidget *parent)
    : QWidget(parent)
{

    QRect rectangle = QApplication::desktop()->screenGeometry();
    rectangle.setX(rectangle.width()/4);
    rectangle.setY(rectangle.height()/4);
    rectangle.setWidth(rectangle.width()/2);
    rectangle.setHeight(rectangle.height()/2);

    m_subscriber = new mqtt_sub;
    m_subscriber->connectToHost();

    m_publisher = new mqtt_pub;
    m_publisher->connectToHost();

    m_push3 = new QPushButton("LED3",this);
    m_push4 = new QPushButton("LED4",this);
    m_push5 = new QPushButton("LED5",this);
    m_push6 = new QPushButton("LED6",this);
    m_rfid = new QPushButton("RFID TAG",this);

    m_push6->move((rectangle.width()/4)-50,(rectangle.height()/4)-50);
    m_push4->move((rectangle.width()*3/8)-50,(rectangle.height()/2)-50);
    m_push3->move((rectangle.width()/4)-50,(rectangle.height()*3/4)-50);
    m_push5->move((rectangle.width()/8)-50,(rectangle.height()/2)-50);
    m_rfid->move((rectangle.width()*4/6)-50,(rectangle.height()/4)-50);

    connect(m_push3, SIGNAL (clicked()),this, SLOT (handleButtonLED3()));
    connect(m_push4, SIGNAL (clicked()),this, SLOT (handleButtonLED4()));
    connect(m_push5, SIGNAL (clicked()),this, SLOT (handleButtonLED5()));
    connect(m_push6, SIGNAL (clicked()),this, SLOT (handleButtonLED6()));

    connect(m_subscriber, &mqtt_sub::received, this, &MyScreen::handleReadyRead);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(processOneThing()));

    // default state
    led3Off();
    led4Off();
    led5Off();
    led6Off();
    rfidIdle();


    m_ledState[0]='0';
    m_ledState[1]='0';
    m_ledState[2]='0';
    m_ledState[3]='0';

    this->setGeometry(rectangle);
    this->show();
}

MyScreen::~MyScreen()
{

}

void MyScreen::handleButtonLED3(void)
{
    if(m_ledState[0]=='0'){
        m_ledState[0] = '1';led3On();}

    else if(m_ledState[0]=='1'){
        m_ledState[0] = '0';led3Off();}

    char _myMessage[6];
    _myMessage[0]='0';
    _myMessage[1]=m_ledState[0];
    _myMessage[2]=m_ledState[1];
    _myMessage[3]=m_ledState[2];
    _myMessage[4]=m_ledState[3];
    _myMessage[5]='\0';

    QString str(_myMessage);
    qDebug() << str;
    QMQTT::Message message(0, TOPIC2, str.toUtf8());
    m_publisher->publish(message);
}

void MyScreen::handleButtonLED4(void)
{
    if(m_ledState[1]=='0'){
        m_ledState[1] = '1';led4On();}

    else if(m_ledState[1]=='1'){
        m_ledState[1] = '0';led4Off();}

    char _myMessage[6];
    _myMessage[0]='0';
    _myMessage[1]=m_ledState[0];
    _myMessage[2]=m_ledState[1];
    _myMessage[3]=m_ledState[2];
    _myMessage[4]=m_ledState[3];
    _myMessage[5]='\0';

    QString str(_myMessage);
    qDebug() << str;
    QMQTT::Message message(0, TOPIC2, str.toUtf8());
    m_publisher->publish(message);
}

void MyScreen::handleButtonLED5(void)
{
    if(m_ledState[2]=='0'){
        m_ledState[2] = '1';led5On();}

    else if(m_ledState[2]=='1'){
        m_ledState[2] = '0';led5Off();}

    char _myMessage[6];
    _myMessage[0]='0';
    _myMessage[1]=m_ledState[0];
    _myMessage[2]=m_ledState[1];
    _myMessage[3]=m_ledState[2];
    _myMessage[4]=m_ledState[3];
    _myMessage[5]='\0';

    QString str(_myMessage);
    qDebug() << str;
    QMQTT::Message message(0, TOPIC2, str.toUtf8());
    m_publisher->publish(message);
}

void MyScreen::handleButtonLED6(void)
{
    if(m_ledState[3]=='0'){
        m_ledState[3] = '1';led6On();}

    else if(m_ledState[3]=='1'){
        m_ledState[3] = '0';led6Off();}

    char _myMessage[6];
    _myMessage[0]='0';
    _myMessage[1]=m_ledState[0];
    _myMessage[2]=m_ledState[1];
    _myMessage[3]=m_ledState[2];
    _myMessage[4]=m_ledState[3];
    _myMessage[5]='\0';

    QString str(_myMessage);
    qDebug() << str;
    QMQTT::Message message(0, TOPIC2, str.toUtf8());
    m_publisher->publish(message);
}




void MyScreen::led3On()
{
    m_push3->setStyleSheet("color: white; "
                           "background-color: orange;"
                           "border-style: solid;"
                           "border-width:1px;"
                           "border-radius:50px;"
                           "border-color: orange;"
                           "max-width:100px;"
                           "max-height:100px;"
                           "min-width:100px;"
                           "min-height:100px;");
}
void MyScreen::led3Off()
{
    m_push3->setStyleSheet("color: orange; "
                           "background-color: white;"
                           "border-style: solid;"
                           "border-width:1px;"
                           "border-radius:50px;"
                           "border-color: white;"
                           "max-width:100px;"
                           "max-height:100px;"
                           "min-width:100px;"
                           "min-height:100px;");
}

void MyScreen::led4On()
{
    m_push4->setStyleSheet("color: white; "
                           "background-color: green;"
                           "border-style: solid;"
                           "border-width:1px;"
                           "border-radius:50px;"
                           "border-color: green;"
                           "max-width:100px;"
                           "max-height:100px;"
                           "min-width:100px;"
                           "min-height:100px;");
}
void MyScreen::led4Off()
{
    m_push4->setStyleSheet("color: green; "
                           "background-color: white;"
                           "border-style: solid;"
                           "border-width:1px;"
                           "border-radius:50px;"
                           "border-color: white;"
                           "max-width:100px;"
                           "max-height:100px;"
                           "min-width:100px;"
                           "min-height:100px;");
}

void MyScreen::led5On()
{
    m_push5->setStyleSheet("color: white; "
                           "background-color: red;"
                           "border-style: solid;"
                           "border-width:1px;"
                           "border-radius:50px;"
                           "border-color: red;"
                           "max-width:100px;"
                           "max-height:100px;"
                           "min-width:100px;"
                           "min-height:100px;");
}
void MyScreen::led5Off()
{
    m_push5->setStyleSheet("color: red; "
                           "background-color: white;"
                           "border-style: solid;"
                           "border-width:1px;"
                           "border-radius:50px;"
                           "border-color: white;"
                           "max-width:100px;"
                           "max-height:100px;"
                           "min-width:100px;"
                           "min-height:100px;");
}

void MyScreen::led6On()
{
    m_push6->setStyleSheet("color: white; "
                           "background-color: blue;"
                           "border-style: solid;"
                           "border-width:1px;"
                           "border-radius:50px;"
                           "border-color: blue;"
                           "max-width:100px;"
                           "max-height:100px;"
                           "min-width:100px;"
                           "min-height:100px;");
}
void MyScreen::led6Off()
{
    m_push6->setStyleSheet("color: blue; "
                           "background-color: white;"
                           "border-style: solid;"
                           "border-width:1px;"
                           "border-radius:50px;"
                           "border-color: white;"
                           "max-width:100px;"
                           "max-height:100px;"
                           "min-width:100px;"
                           "min-height:100px;");
}

void MyScreen::rfidGranted()
{
    m_rfid->setStyleSheet("color: white; "
                          "background-color: green;"
                          "border-style: solid;"
                          "border-width:1px;"
                          "border-radius:100px;"
                          "border-color: white;"
                          "max-width:300px;"
                          "max-height:400px;"
                          "min-width:300px;"
                          "min-height:400px;");
    timer->start();
}

void MyScreen::rfidDenied()
{
    m_rfid->setStyleSheet("color: white; "
                          "background-color: red;"
                          "border-style: solid;"
                          "border-width:1px;"
                          "border-radius:100px;"
                          "border-color: white;"
                          "max-width:300px;"
                          "max-height:400px;"
                          "min-width:300px;"
                          "min-height:400px;");
    timer->start(1000);
}

void MyScreen::rfidIdle()
{
    m_rfid->setStyleSheet("color: white; "
                          "background-color: grey;"
                          "border-style: solid;"
                          "border-width:1px;"
                          "border-radius:100px;"
                          "border-color: white;"
                          "max-width:300px;"
                          "max-height:400px;"
                          "min-width:300px;"
                          "min-height:400px;");
    timer->start(1000);
}

void MyScreen::processOneThing()
{
    rfidIdle();
}

void MyScreen::handleReadyRead(const QMQTT::Message &message)
{

    QString string(QString::fromUtf8(message.payload()));
    const char* c= string.toStdString().c_str();

    if(c[0]=='0')
    {
        m_ledState[0]=c[1];
        m_ledState[1]=c[2];
        m_ledState[2]=c[3];
        m_ledState[3]=c[4];

        if(c[1]=='1')
            led3On();
        else
            led3Off();

        if(c[2]=='1')
            led4On();
        else
            led4Off();

        if(c[3]=='1')
            led5On();
        else
            led5Off();

        if(c[4]=='1')
            led6On();
        else
            led6Off();
    }
    else if(c[0]=='1')
    {
        if(c[1]=='1')
            rfidDenied();
        else
            rfidGranted();
    }

}
