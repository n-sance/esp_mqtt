
#include "c_JSON_interface.h"





//extern const size_t bufferSize;
//extern DynamicJsonBuffer jsonBuffer;
const size_t bufferSize = STATIC_JSON_BUFFER_SIZE;
DynamicJsonBuffer jsonBuffer(bufferSize);
extern WiFi_data_t Wifi_auth;
extern MQTT_topics_t topics;
extern MQTT_auth_t MQTT_auth_data;


extern int timeout;




void c_JSON_interface::JSON_config_receive()
 {
   char rc;
    static int cnt = 0;
    char endMarker = '\n';
   
  while (Serial.available() > 0 && (newData_get_state() == 0)){
    rc = Serial.read();
  if (rc != endMarker) {
        json_buffer[cnt] = rc;
        cnt++;
        if (cnt >= UART_MAX_TRANSFER_SIZE) {
          cnt = UART_MAX_TRANSFER_SIZE - 1;
        }
      }
      else {
        json_buffer[cnt] = '\0'; // terminate the string
        cnt = 0;
        newData_set_state(true);
      } 
 }
 }



 void c_JSON_interface::JsonHandler(void)
 {

  JsonObject& root = jsonBuffer.parseObject(json_buffer);

  
  JsonArray& wificonfig = root["wificonfig"];

  Wifi_auth.ssid1 = wificonfig[0]["ssid"]; 
  Wifi_auth.pass1 = wificonfig[0]["passwd"]; 

  Wifi_auth.ssid2 = wificonfig[1]["ssid"];
  Wifi_auth.pass2 = wificonfig[1]["passwd"]; 
   
  Wifi_auth.ssid3 = wificonfig[2]["ssid"]; // "Redmi1"
  Wifi_auth.pass3 = wificonfig[2]["passwd"]; // "123456"
  
  
    JsonArray& mqtt = root["mqtt"];

    MQTT_auth_data.mqtt0_server = mqtt[0]["server"]; // "super-carpenter.cloudmqtt.com"
    MQTT_auth_data.mqtt_port = mqtt[1]["port"]; // 18028
    MQTT_auth_data.mqtt_pass = mqtt[2]["mqtt_pass"]; // "ssvwYnWja9uww80kHuvVxv27pVWk1QGz"
    MQTT_auth_data.mqtt_uid = mqtt[3]["mqtt_uid"]; // "3fb985fd-2030-4e4b-8ddb-8f55fb2731b9"
    
//----------------------------MQTT Topics parsing-----------------------------------//
  JsonArray& mqtt_topics1 = root["mqtt_topics1"];

  topics.mqtt_subscribe_topic = mqtt_topics1[0]["mqtt_subscribe_topic"]; 
  topics.mqtt_topic_1 = mqtt_topics1[1]["mqtt_topic_1"];
  topics.mqtt_topic_volume_set = mqtt_topics1[2]["mqtt_topic_volume_set"];
  topics.mqtt_topic_audio_start = mqtt_topics1[3]["mqtt_topic_audio_start"];
  

  JsonArray& mqtt_topics2 = root["mqtt_topics2"];
  
  topics.mqtt_topic_audio_pause = mqtt_topics2[0]["mqtt_topic_audio_pause"];
  topics.mqtt_topic_audio_play = mqtt_topics2[1]["mqtt_topic_audio_play"]; 
  topics.mqtt_topic_audio_stop = mqtt_topics2[2]["mqtt_topic_audio_stop"]; 
  topics.mqtt_topic_question_play = mqtt_topics2[3]["mqtt_topic_question_play"]; 
  

  JsonArray& mqtt_topics3 = root["mqtt_topics3"];
  
  topics.mqtt_topic_phrase_play = mqtt_topics3[0]["mqtt_topic_phrase_play"]; // "/devices/3fb985fd-2030-4e4b-8ddb-8f55fb2731b9/device/game/phrase/play"
  
  timeout = root["timeout"]; // 5  
  


/*

   Serial.println(Wifi_auth.ssid1);
  Serial.println(Wifi_auth.pass1);
  Serial.println(Wifi_auth.ssid2);
  Serial.println(Wifi_auth.pass2);
  Serial.println(Wifi_auth.ssid3);
   Serial.println(Wifi_auth.pass3);
   Serial.println(MQTT_auth_data.mqtt0_server);
   Serial.println(MQTT_auth_data.mqtt_port);
   Serial.println(MQTT_auth_data.mqtt_pass);
   Serial.println(MQTT_auth_data.mqtt_uid);
  Serial.println(topics.mqtt_subscribe_topic);
  Serial.println(topics.mqtt_topic_1);
  Serial.println(topics.mqtt_topic_volume_set);
  Serial.println(topics.mqtt_topic_audio_start);
  Serial.println(topics.mqtt_topic_audio_pause);
  Serial.println(topics.mqtt_topic_audio_play);
  Serial.println(topics.mqtt_topic_audio_stop);
  Serial.println(topics.mqtt_topic_question_play);
  Serial.println("topic_phrase_after");
  Serial.println(topics.mqtt_topic_phrase_play);
  Serial.println("this is topic");
  */
 }



 void c_JSON_interface::Sending_Response_message(void)
 {
    Serial.println("waiting_for_config");
 }


void c_JSON_interface::newData_set_state(boolean state)
{
    json_newData = state;
}


