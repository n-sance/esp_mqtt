#ifndef __LOWPOWER_H__
#define __LOWPOWER_H__
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "c_Transmit_interface.h"
#include "MQTT_Lib.h"


void low_power_set(void);
void fpm_wakup_cb_func1(void);

#endif