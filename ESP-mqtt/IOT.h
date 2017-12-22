#include <ESP8266WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>

#include "defines.hpp"

class IOT {

  private:
    const char * m_wifi_ssid;
    const char * m_wifi_pwd;
    const char * m_mqtt_server;
    const char * m_mqtt_topic_in;
    const char * m_mqtt_topic_out;
    const char * m_mqtt_user;
    const char * m_mqtt_password;

    const char * m_toSEND;
    String m_serialRead;

    //uint8_t m_led_state;


    WiFiClient m_espClient;
    WiFiClientSecure m_espClientSec;
    PubSubClient *m_clientMqtt = NULL;

  public:
    IOT();
    ~IOT();
    void go(void);

    void setWIFI(const char * _wifi_ssid = WIFI_SSID,
                 const char * _wifi_pwd = WIFI_PASSWORD);

    void setMQTT(const char * _mqtt_server = MQTT_SERVER,
                 const char * _mqtt_topic_in = MQTT_TOPIC_IN,
                 const char * _mqtt_topic_out = MQTT_TOPIC_OUT,
                 const char * _mqtt_user = MQTT_USER,
                 const char * _mqtt_password = MQTT_PASSWORD);

    void setMessage(const char * _toSEND = "");

    void setLED(uint8_t _led_state = LED_STATE);

    void useSerial(const long _speed = SERIAL_SPEED);

    void startWifi(void);
    void reconnect(void);
    static void callback(char* topic, byte* payload, unsigned int length);

};

