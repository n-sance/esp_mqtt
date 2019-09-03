
#include "defines.h"
#include "main.h"
#include "MQTT_Lib.h"
#include "WiFi_lib.h"
#include "c_Transmit_interface.h"
#include "lowpower_lib.h"
#include "c_JSON_interface.h"
#include "structures.h"
#include "Ticker.h"
/*
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include "ArduinoOTA.h"
*/

using namespace std;
void wait_for_json_message(void);
void wait_for_JSON_handling(void);
int timeout = DEFAULT_TIMEOUT_S;


c_JSON_interface JSON_int;
c_Transmit_interface Transmit;
Ticker timer_request_for_JSON(wait_for_json_message, timeout, 0, MILLIS);
extern MQTT_auth_t MQTT_auth_data;
//-------------------------------------------------------------------------------//





//-------------------------------------------------------------------------------//
char *device_id = "device1";

char message_char[MQTT_MAX_TRANSFER_SIZE];
//-----------------------------------------------------------------------------------------------------------//






void setup() {
    // Setup console
    delay(100);
    Serial.begin(115200);
    delay(500);

     wait_for_JSON_handling();
 
}
WiFiClient wclient;
PubSubClient client(wclient, MQTT_auth_data.mqtt0_server, MQTT_auth_data.mqtt_port);

void loop() {

  WiFi_connect();
  if (WiFi.status() == WL_CONNECTED) {
    
	if (!client.connected()) {
    reconnect();
    subcribe_to_topics();  
  }
  client.loop();
  Transmit.recvWithEndMarker();
  Transmit.showNewData(client);
      }
  delay(5000);

}
     







void wait_for_json_message(void)
{
  Serial.print("waiting for message");
}


void wait_for_JSON_handling(void)
{
  JSON_int.newData_set_state(false);
   
      timer_request_for_JSON.start();
    while (JSON_int.newData_get_state() != true)
    {
      timer_request_for_JSON.update();
      JSON_int.JSON_config_receive();
    }
      JSON_int.JsonHandler();
    if (JSON_int.newData_get_state())
    {
      timer_request_for_JSON.stop();
    }
}
 




























