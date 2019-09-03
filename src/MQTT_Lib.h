#ifndef __MQTT_H__
#define __MQTT_H__

//#include "esp_UART_MQTT_NJT.h"
#include <MQTT.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "c_Transmit_interface.h"
#include "lowpower_lib.h"
#include "defines.h"

void callback(const MQTT::Publish& pub);
void reconnect(void);
void subcribe_to_topics(void);
class MQTT_interface : public PubSubClient
{
    public:
    void callback(const MQTT::Publish& pub);
    //! Simple constructor
    MQTT_interface(Client& c);
    //! Constructor with the server ip address
    MQTT_interface(Client& c, IPAddress &ip, uint16_t port = 1883);
    //! Constructors with the host name
    MQTT_interface(Client& c, String hostname, uint16_t port = 1883);

    
    
    private:
    uint8_t buf[UART_MAX_TRANSFER_SIZE];
};


#endif 