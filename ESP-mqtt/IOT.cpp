#include "IOT.h"


IOT::IOT()
{
  Serial.setTimeout(100); //setup serial readString timeout
}

IOT::~IOT()
{
  delete m_clientMqtt;
}

void IOT::setWIFI(const char * _wifi_ssid,
                  const char * _wifi_pwd)
{
  m_wifi_ssid = _wifi_ssid;
  m_wifi_pwd = _wifi_pwd;
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
}

void IOT::setMQTT(const char * _mqtt_server,
                  const char * _mqtt_topic,
                  const char * _mqtt_user,
                  const char * _mqtt_password)
{
  m_mqtt_server = _mqtt_server;
  m_mqtt_topic = _mqtt_topic;
  m_mqtt_user = _mqtt_user;
  m_mqtt_password = _mqtt_password;
  m_clientMqtt = new PubSubClient(m_espClient);
}

void IOT::setMessage(const char * _toSEND)
{
  m_toSEND = _toSEND;
}

void IOT::go()
{
  startWifi();
  if (m_clientMqtt != NULL) {
    m_clientMqtt->setServer(m_mqtt_server, 1883);
    m_clientMqtt->setCallback(IOT::callback);
  }
  else
    return;

  do
  {
    if (m_clientMqtt != NULL)
    {
      if (!m_clientMqtt->connected())
        reconnect();

      m_clientMqtt->loop();
    }

    if (Serial.available() > 0)
    {
      m_serialRead = Serial.readString();
      if (m_clientMqtt != NULL)
        m_clientMqtt->publish(m_mqtt_topic, m_serialRead.c_str(), true);
      else
        Serial.println("Mqtt not used");
    }

  } while (1);
}

void IOT::useSerial(const long _speed)
{
  Serial.begin(_speed);
}

void IOT::startWifi()
{
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(m_wifi_ssid);

  WiFi.begin(m_wifi_ssid, m_wifi_pwd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    //digitalWrite(m_led_state, LOW);
    //delay(50);
    //digitalWrite(m_led_state, HIGH);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("MAC address: ");
  Serial.println(WiFi.macAddress());
}

void IOT::reconnect()
{

  while (!m_clientMqtt->connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (m_clientMqtt->connect("ESP8266Client", m_mqtt_user, m_mqtt_password))
    {
      Serial.println("connected");
      m_clientMqtt->subscribe("test2");
    } else {
      Serial.print("failed, rc=");
      Serial.print(m_clientMqtt->state());
      Serial.println(" try again in 5 seconds");
      // Wait 10 seconds before retrying
      delay(10000);
    }
  }
}

void IOT::callback(char* topic, byte* payload, unsigned int length) {

  for (int i = 0; i < length; i++)
    Serial.print((char)payload[i]);

}

