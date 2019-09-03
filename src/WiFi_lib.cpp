
#include "WiFi_lib.h"

//-------------------------------WiFi Parameters---------------------------------//

extern WiFi_data_t Wifi_auth;


uint8_t wifi_flag = 0;
//extern WiFiClient wclient;
void WiFi_connect(){
  //SSID1 connect
  if ((WiFi.status() != WL_CONNECTED) && (wifi_flag == 0)) {
    Serial.print("Connecting to ");
    Serial.print(Wifi_auth.ssid1);
    Serial.println("...");
    WiFi.begin(Wifi_auth.ssid1, Wifi_auth.pass1);

    if (WiFi.waitForConnectResult() != WL_CONNECTED)
        {
          wifi_flag++;
          return;
        }
        Serial.println("WiFi connected");
        wifi_flag = 0;
      }
      //SSID2 connect
  else if ((WiFi.status() != WL_CONNECTED) && (wifi_flag == 1)) {
    Serial.print("Connecting to ");
    Serial.print(Wifi_auth.ssid2);
    Serial.println("...");
    WiFi.begin(Wifi_auth.ssid2, Wifi_auth.pass2);

    if (WiFi.waitForConnectResult() != WL_CONNECTED)
          {
            wifi_flag++;
          return;
          }
        Serial.println("WiFi connected");
        wifi_flag = 0;
      }
      //SSID3 connect
 else if ((WiFi.status() != WL_CONNECTED) && (wifi_flag == 2)) {
    Serial.print("Connecting to ");
    Serial.print(Wifi_auth.ssid3);
    Serial.println("...");
    WiFi.begin(Wifi_auth.ssid3, Wifi_auth.pass3);

    if (WiFi.waitForConnectResult() != WL_CONNECTED)
        {
    wifi_flag = 0;
          return;
      }
        Serial.println("WiFi connected");
        wifi_flag = 0;
      }
}
