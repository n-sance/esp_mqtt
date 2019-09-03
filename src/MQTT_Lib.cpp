#include "MQTT_Lib.h"

//--------------------------------MQTT Parameters--------------------------------//
// Update these with values suitable for your network.
//char *mqtt_server = "super-carpenter.cloudmqtt.";

extern int timeout;
//char *mqtt_user = "3fb985fd-2030-4e4b-8ddb-8f55fb2731b9";
//char *mqtt_client_name = "3fb985fd-2030-4e4b-8ddb-8f55fb2731b9";

//extern const char *mqtt_uid;


//extern WiFiClient wclient;

extern MQTT_topics_t topics;
extern MQTT_auth_t MQTT_auth_data;
extern PubSubClient client;
//extern int mqtt_port;

  String start_symbol = "";
  char end_symbol = '\n';
  String div_symbol = "&";

void reconnect() {
    
    while (!client.connected()) {
      //Serial.println("intoWhile");
  client.set_server(MQTT_auth_data.mqtt0_server, MQTT_auth_data.mqtt_port);
    if (client.connect(MQTT::Connect(MQTT_auth_data.mqtt_uid)
                           .set_auth(MQTT_auth_data.mqtt_uid, MQTT_auth_data.mqtt_pass))) {
      Serial.println("Connected to MQTT server");
      client.set_callback(callback);
      Serial.println("callback set");
      } else {
        delay(5000);
    }
  }
}

void subcribe_to_topics(void)
{
        
        client.subscribe(topics.mqtt_subscribe_topic); // this is our receive filter. We able to receive only these topics
        client.subscribe(topics.mqtt_topic_1);
        client.subscribe(topics.mqtt_topic_audio_start);
        client.subscribe(topics.mqtt_topic_audio_pause);
        client.subscribe(topics.mqtt_topic_audio_play);
       client.subscribe(topics.mqtt_topic_audio_stop);
        client.subscribe(topics.mqtt_topic_volume_set);
        client.subscribe(topics.mqtt_topic_question_play);
        client.subscribe(topics.mqtt_topic_phrase_play);
       
}



// Callback function
//  Receive data from MQTT and send it to serial
uint8_t buf[UART_MAX_TRANSFER_SIZE];
void callback(const MQTT::Publish& pub) {
// Copy the payload to a new message
  //MQTT::Publish newpub("outTopic", pub.payload(), pub.payload_len());
  //client.publish(newpub);
  Serial.println("you are here");
  //Serial.println(pub.topic());
  if (pub.has_stream()) {
    int read;
    while (read = pub.payload_stream()->read(buf, UART_MAX_TRANSFER_SIZE)) {
      Serial.write(buf, read);    
    }
    pub.payload_stream()->stop();
  }
  
  else{
    char symbol = 1;

    String t = pub.topic();
    String m = pub.payload_string();
    String message = start_symbol + t + div_symbol + m + end_symbol;
    int str_len ;
      str_len = message.length();
      Serial.print(message);
  }
}