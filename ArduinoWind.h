/*  <------------------------------------------>
    Library made to facilitate DIY arduino based
    weather stations to send data to windguru.cz.
    Libraries dependencies:
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
#include <SPI.h>
#include <HttpClient.h>
#include <Ethernet.h>
#include <EthernetClient.h>

#define fixed_url "www.windguru.cz"
#define no_info -49
#define MIN_CTE	200
#define MAX_CTE	-200

class Station{

    private:
        char* uid;
        char* passphrase;
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
	  
	  	EthernetClient c;
	  	HttpClient http;

    private:


        String generate_url();
        String generate_hash(String salt);
        void resetAll();

		/*
		Set average wind(KNOTS)
		*/
		void set_wind_avg(float val);

		/*
		Set min wind(KNOTS)
		*/
		void set_wind_min(float val);

		/*
		Set max wind(KNOTS)
		*/
		void set_wind_max(float val);
        
  
    public:
        Station(char* uid, char* passphrase, int interval_in_seconds=60);

		/*
		Send data according to Windguru API Documentation [https://stations.windguru.cz/upload_api.php]
		*/        
		bool send_data();

		/*
		Set wind velocity measure(KNOTS)
		*/
		void set_wind_velocity(float val);

		/*
		Set wind average(KNOTS)
		*/
		void set_wind_dir(float val);

		/*
		Set temperature(Celsius)
		*/
		void set_temp(float val);

		/*
		Set relative humidity(%)
		*/
		void set_rh(float val);

		/*
		Set pressure reduced to sea level(hPa)
		*/
		void set_msclp(float val);

		/*
		Set precipitaion level(mm)
		*/
        void set_precip(float val);

		/*
		Set precipitation interval(seconds)
		*/
        void set_precip_interval(float val);

		/*
		Retun wind average(KNOTS)
		*/        
		float get_wind_avg();

		/*
		Retun max wind(KNOTS)
		*/
        float get_wind_max();

		/*
		Retun min wind(KNOTS)
		*/
        float get_wind_min();

		/*
		Retun wind direction(degrees)
		*/
        float get_wind_dir();
	
		/*
		Retun temperature(Celsius)
		*/
        float get_temp();

		/*
		Retun relative humidity(%)
		*/
        float get_rh();

		/*
		Get pressure reduced to sea level(hPa)
		*/
        float get_msclp();

		/*
		Get precipitation level(mm)
		*/
        float get_precip();

		/*
		Get precipitation interval(seconds)
		*/
        float get_precip_interval();

};

#endif
