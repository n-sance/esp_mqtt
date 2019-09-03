#ifndef __SENDRECEIVE_H__
#define __SENDRECEIVE_H__
#include <Arduino.h>
#include "lowpower_lib.h"
#include "c_JSON_interface.h"
#include "defines.h"
#include "PubSubClient.h"



class c_Transmit_interface
{
    public:
        boolean newData = false;

        char *topik;
        
        char topik_arr[UART_MAX_TRANSFER_SIZE];
        char divider[3] = "&";   //split symbol for uart message
        

        char receivedChars[UART_MAX_TRANSFER_SIZE]; // an array to store the received data

        void recvWithEndMarker(void);
        void parseData(void);
        void showNewData(PubSubClient& client);

        void set_receivedChars(char*);


    private:

        


};







#endif