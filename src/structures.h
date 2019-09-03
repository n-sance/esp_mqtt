#ifndef __STRUCTURES_H_
#define __STRUCTURES_H_

typedef struct 
{
        const char *ssid1;
        const char *pass1;
        const char *ssid2;
        const char *pass2;
        const char *ssid3;
        const char *pass3;
}WiFi_data_t;



typedef struct
{

        const char *mqtt_subscribe_topic;
        const char *mqtt_topic_1;
        const char *mqtt_topic_volume_set;
        const char *mqtt_topic_audio_start;
        const char *mqtt_topic_audio_pause;
        const char *mqtt_topic_audio_play;
        const char *mqtt_topic_audio_stop;
        const char *mqtt_topic_question_play;
        const char *mqtt_topic_phrase_play;

} MQTT_topics_t;




typedef struct
{
        const char *mqtt_pass;
        const char *mqtt_uid;
        int mqtt_port;
        const char *mqtt0_server;
}MQTT_auth_t;


#endif