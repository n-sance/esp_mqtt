
#include "c_Transmit_interface.h"


//extern WiFiClient wclient;

//extern PubSubClient client;

char *message;
char service_symbol[6] = {'*','d','s','m', 'n', 'j'};
 char message_arr[UART_MAX_TRANSFER_SIZE];  //try to UART_MAX_TRANSFER_SIZE 


//----------------Here we can receive message from our Serial and have a kind of parcing to send it to MQTT or to do some sevice activities//
//----------------Format of messages must be topic&{message}   And the maximum length is 100 symbols-------------//    
void c_Transmit_interface::recvWithEndMarker() {
    static int ndx = 0;
    char endMarker = '\n';
    char rc;
  
  while (Serial.available() > 0 && newData == false){
    rc = Serial.read();
    
    if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= UART_MAX_TRANSFER_SIZE) {
          ndx = UART_MAX_TRANSFER_SIZE - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        ndx = 0;
        newData = true;
        parseData();
      }
}
}




// Parcing Serial message into two parts: topic ("topik" in this program) and message("message")
// This library needs to have only "char[ ]" type, so we need to convert our "char*" variables
void c_Transmit_interface::parseData(){
  topik = strtok (receivedChars,divider);
    Serial.println(topik);
    message = strtok (NULL,divider);
    Serial.println(message);
    
    for (int i = 0; i <= UART_MAX_TRANSFER_SIZE; i++)
    {
      topik_arr[i] = topik[i];
    }
//  check if there any service messages and configurate if they are existing
    if (message[0] == service_symbol[0]){
      low_power_set();
     Serial.println("Here we are");
    }
    else if (message[0] == service_symbol[5]){
      Serial.println("JSON");
      ESP.restart();
    }
    
}



// ---------Here we send our parcing message to MQTT //
void c_Transmit_interface::showNewData(PubSubClient& client) {
 
  if (newData == true) {
    Serial.println("ok");
    client.publish(topik_arr, String(message)); // publish: ESPuart -> mqtt bus
    newData = false;
  }
}
