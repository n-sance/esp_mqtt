
#include "lowpower_lib.h"

boolean deepsleep_flag = false;




extern char *message;
extern char service_symbol[6];
extern char message_arr[UART_MAX_TRANSFER_SIZE]; 
extern WiFiClient wclient;
extern char *mqtt_server;
extern int mqtt_port;
extern PubSubClient client;


void low_power_set(){
    
  if (message[1] == service_symbol[3]){       
      Serial.println("sleep mode is set to FORCED MODEM");             //FORCED MODEM MODE
      Serial.println("activating FORCED MODEM");
      wifi_set_sleep_type(MODEM_SLEEP_T);
      delay(100);
      WiFi.forceSleepBegin(); // Wifi off
      delay(100);
      WiFi.forceSleepWake(); // Wifi on
      Serial.println("deactivating FORCED MODEM");
    }
  
  
  
    if (message_arr[1] == service_symbol[4]){                     //NONE SLEEP MODE
      wifi_set_sleep_type(NONE_SLEEP_T);
      Serial.println("sleep mode is set to None");    
    }


    

    if (message_arr[1] == service_symbol[1]){  
      int time_in_us = 10000000;//DEEP SLEEP MODE
      Serial.println("activating DEEPSLEEP");
      Serial.println(time_in_us + " sec or set LOW to RST pin");
      client.publish("dev/uuid/lowpower", "deepsleep");
       delay(100);
      ESP.deepSleep(time_in_us);
      
    }

  
    if (message_arr[1] == service_symbol[2]){                     //LIGHT SLEEP MODE
      Serial.println("activating LIGHT MODE");
      delay(100);
      gpio_pin_wakeup_enable(GPIO_ID_PIN(2), GPIO_PIN_INTR_HILEVEL);
      wifi_fpm_open();
      wifi_fpm_do_sleep(0xFFFFFFF);
      delay(100);
      Serial.println("deactivating LIGHT MODE");
  }

}




void fpm_wakup_cb_func1(void)                                   //CALLBACK FOR LIGHT SLEEP MODE WAKE UP
  {
    Serial.println("callbCK");
     wifi_fpm_close();      // disable force sleep function
     wifi_set_opmode(STATION_MODE);         // set station mode
     wifi_station_connect();            // connect to AP
  }