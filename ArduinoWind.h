/*  <------------------------------------------>
    Library made to facilitate DIY arduino based
    weather stations to send data to windguru.cz.
    It depends on other libraries:
        - MD5
        - EthernetClient
        - HttpClient
    <------------------------------------------>
        Author: Arthur B. Grossi
*/

#ifndef ARDUINOWIND_H
#define ARDUINOWIND_H
#include "Arduino.h"


#include "MD5.h"
#include <EthernetClient.h>
#include <HttpClient.h>

#define fixed_url "www.windguru.cz"
#define no_info -49

class Station{

    private:
        char* uid;
        char* passphrase;
        char* salt;
        int interval_in_seconds = 60;
        //sensor data
        float wind_avg=no_info;
        float wind_max=no_info;
        float wind_min=no_info;
        float wind_dir=no_info;
        float temp=no_info;
        float rh=no_info;
        float msclp=no_info;
        float precip=no_info;
        float precip_interval=no_info;

        EthernetClient *c;
        HttpClient *http;

        
        String generate_url();
        char* generate_hash();
        void resetAll();
        
  
    public:
        Station(char* uid, char* passphrase, int interval_in_seconds=60);
        bool send_data();
        void set_wind_avg(float val);
        void set_wind_max(float val);
        void set_wind_min(float val);
        void set_wind_dir(float val);
        void set_temp(float val);
        void set_rh(float val);
        void set_msclp(float val);
        void set_precip(float val);
        void set_precip_interval(float val);
        float get_wind_avg();
        float get_wind_max();
        float get_wind_min();
        float get_wind_dir();
        float get_temp();
        float get_rh();
        float get_msclp();
        float get_precip();
        float get_precip_interval();

};

#endif