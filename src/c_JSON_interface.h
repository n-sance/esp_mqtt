#ifndef __JSON_H_
#define __JSON_H_
#define JSON_BUFFER_SIZE 2500
#include <Arduino.h>

#include "c_Transmit_interface.h"
#include "ArduinoJson.h"
#include "defines.h"
#include "structures.h"

#include <list>
#include <vector>
using namespace std;
class c_JSON_interface
{
    char json_buffer[JSON_BUFFER_SIZE];
    public:
        void JSON_config_receive(void);
        void JsonHandler(void);
        void Sending_Response_message(void);
        void newData_set_state(boolean state);

        boolean newData_get_state(void) const {return json_newData;}

        void set_bufferSize(size_t);
        uint8_t get_bufferSize(void) const {return JSON_buffer_size;}
    
    private:
        uint8_t JSON_buffer_size = 0;
        boolean json_newData = false;
};

 

#endif