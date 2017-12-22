#include "MyScreen.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QBoxLayout>



MyScreen::MyScreen(QWidget *parent)
    : QWidget(parent)
{
    QRect rectangle = QApplication::desktop()->screenGeometry();
#ifdef DESKTOP
    rectangle.setX(rectangle.width()/4);
    rectangle.setY(rectangle.height()/4);
    rectangle.setWidth(rectangle.width()/2);
    rectangle.setHeight(rectangle.height()/2);
#endif

    m_GLayout = new QGridLayout(this);
    m_ipAddress = new QLineEdit;
    m_port = new QLineEdit;
    m_status = new QLabel;
    m_timer = new QTimer();
    m_timer->start(1000);
    
    m_connect = new QPushButton("Connect");
    
    m_subscriber = new mqtt_sub;
    m_subscriber->connectToHost();
    m_publisher = new mqtt_pub;
    m_publisher->connectToHost();
    
    m_push3 = new QPushButton("LED3",this);
    m_push4 = new QPushButton("LED4",this);
    m_push5 = new QPushButton("LED5",this);
    m_push6 = new QPushButton("LED6",this);
    
    m_GLayout->addWidget(new QLabel(tr("IP   :")), 0, 0, 1, 1, Qt::AlignLeft);
    m_GLayout->addWidget(new QLabel(tr("Port: ")), 1, 0, 1, 1, Qt::AlignLeft);
    m_GLayout->addWidget(m_ipAddress, 0, 0, 1, 3, Qt::AlignRight);
    m_GLayout->addWidget(m_port, 1, 0, 1, 3, Qt::AlignRight);
    m_GLayout->addWidget(m_connect, 2, 0, 1, 4);
    m_GLayout->addWidget(m_status, 3, 2, 1, 3, Qt::AlignRight);
    m_GLayout->addWidget(m_push3, 4, 1, Qt::AlignBottom);
    m_GLayout->addWidget(m_push4, 5, 0, Qt::AlignBottom);
    m_GLayout->addWidget(m_push5, 5, 2, Qt::AlignBottom);
    m_GLayout->addWidget(m_push6, 6, 1, Qt::AlignBottom);
    m_GLayout->setAlignment(Qt::AlignCenter);
    
    
    connect(m_push3, &QPushButton::clicked,this, &MyScreen::handleButton);
    connect(m_push4, &QPushButton::clicked,this, &MyScreen::handleButton);
    connect(m_push5, &QPushButton::clicked,this, &MyScreen::handleButton);
    connect(m_push6, &QPushButton::clicked,this, &MyScreen::handleButton);
    
    connect(m_connect, &QPushButton::clicked,this, &MyScreen::sl_connect);
    
    //connect(m_subscriber, &mqtt_sub::connected, this, &MyScreen::sl_statusMqtt);
    //connect(m_subscriber, &mqtt_sub::disconnected, this, &MyScreen::sl_statusMqtt);
    connect(m_timer, &QTimer::timeout, this, &MyScreen::sl_statusMqtt);
    connect(m_subscriber, &mqtt_sub::received, this, &MyScreen::handleReadyRead);
    
    m_ledState[0] = m_ledState[1] = m_ledState[2] = m_ledState[3] = '0';
    
    led3Off();
    led4Off();
    led5Off();
    led6Off();
    
    this->setGeometry(rectangle);
    this->show();
}

MyScreen::~MyScreen()
{
    delete m_subscriber;
    delete m_publisher;
    delete m_push3;
    delete m_push4;
    delete m_push5;
    delete m_push6;
    delete m_timer;
    delete m_status;
    delete m_GLayout;
    delete m_ipAddress;
    delete m_port;
}

void MyScreen::handleButton(void)
{
    
    QObject* obj = sender();
    if( obj == m_push4 )
        m_ledState[0] == '0' ? m_ledState[0] = '1' : m_ledState[0] = '0';
    
    if( obj == m_push3 )
        m_ledState[1] == '0' ? m_ledState[1] = '1' : m_ledState[1] = '0';
    
    if( obj == m_push5 )
        m_ledState[2] == '0' ? m_ledState[2] = '1' : m_ledState[2] = '0';
    
    if( obj == m_push6 )
        m_ledState[3] == '0' ? m_ledState[3] = '1' : m_ledState[3] = '0';
    
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

void MyScreen::handleReadyRead(const QMQTT::Message &message)
{
    
    QString string(QString::fromUtf8(message.payload()));
    const char* Rx = string.toStdString().c_str();
    
    m_ledState[0]=Rx[1];
    m_ledState[1]=Rx[2];
    m_ledState[2]=Rx[3];
    m_ledState[3]=Rx[4];
    
    Rx[2] == '0' ? led3Off():led3On();
    Rx[1] == '0' ? led4Off():led4On();
    Rx[3] == '0' ? led5Off():led5On();
    Rx[4] == '0' ? led6Off():led6On();
}

void MyScreen::sl_connect(void)
{
    if(m_subscriber != Q_NULLPTR)
    {
        m_subscriber->disconnectFromHost();
        delete m_subscriber;
    }
    
    if(m_publisher != Q_NULLPTR)
    {
        m_publisher->disconnectFromHost();
        delete m_publisher;
    }
    
    m_subscriber = new mqtt_sub(QHostAddress(m_ipAddress->text()), m_port->text().toShort());
    m_subscriber->connectToHost();
    
    m_publisher = new mqtt_pub(QHostAddress(m_ipAddress->text()), m_port->text().toShort());
    m_publisher->connectToHost();
    
    connect(m_timer, &QTimer::timeout, this, &MyScreen::sl_statusMqtt);
    connect(m_subscriber, &mqtt_sub::received, this, &MyScreen::handleReadyRead);
    
}
void MyScreen::sl_statusMqtt(void)
{
    m_status->setStyleSheet("QLabel { color : red; }");
    
    if(m_subscriber->connectionState() == QMQTT::STATE_DISCONNECTED)
        m_status->setText("Disconnected");
    
    if(m_subscriber->connectionState() == QMQTT::STATE_INIT)
        m_status->setText("---");//("Init");
    
    if(m_subscriber->connectionState() == QMQTT::STATE_CONNECTING)
        m_status->setText("Connecting");
    
    if(m_subscriber->connectionState() == QMQTT::STATE_CONNECTED){
        m_status->setText("Connected");
        m_status->setStyleSheet("QLabel { color : green; }");
    }
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
