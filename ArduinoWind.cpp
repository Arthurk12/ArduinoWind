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

#include "ArduinoWind.h"

extern HttpClient http;

Station::Station(char* uid, char* passphrase, int interval_in_seconds) : http(c){
    this->uid = uid;
    this->passphrase = passphrase;
    this->interval_in_seconds = interval_in_seconds;
    randomSeed(analogRead(0));
    resetAll();
}

bool Station::send_data(){
	String url_with_variables = generate_url();

    int err =0;
    bool ret;

    err = http.get(fixed_url, url_with_variables.c_str());
    if (err == 0){
        Serial.println("startedRequest ok");
        err = http.responseStatusCode();
        if (err ==200){
            ret = 1;
        }else{    
            ret =  0;
        }
    }else{
        Serial.print("failed to connect: ");
        Serial.println(err);
        ret = 0;
    }
  	Serial.print(fixed_url);
  	Serial.println(url_with_variables.c_str());
    http.stop();

    return ret;
}

String Station::generate_hash(String salt){
    String temp;

    temp.concat(salt);
    temp.concat(this->uid);
    temp.concat(this->passphrase);


    //generate the MD5 hash for our string
    unsigned char* hash=MD5::make_hash(temp.c_str());
    //generate the digest (hex encoding) of our hash
    char *md5str = MD5::make_digest(hash, 16);
    
    String md5 = String(md5str);

    free(hash);
    free(md5str);

    return md5;
}

String Station::generate_url(){
	String url;
    String salt = String(random(233, 10009));

    url.concat("/upload/api.php?uid=");
    url.concat(this->uid);
    url.concat("&salt=");
    url.concat(salt.c_str());
    url.concat("&hash=");
    url.concat(generate_hash(salt));
	Serial.print("O SALT É: ");
	Serial.print(salt);
	Serial.println("      ");
    url.concat("&interval=");
    url.concat(this->interval_in_seconds);
    if(this->wind_avg!=no_info){
        url.concat("&wind_avg=");
        url.concat(this->wind_avg);
    }
    if(this->wind_max!=MAX_CTE){
        url.concat("&wind_max=");
        url.concat(this->wind_max);
    }
    if(this->wind_min!=MIN_CTE){
        url.concat("&wind_min=");
        url.concat(this->wind_min);
    }
    if(this->wind_dir!=no_info){
        url.concat("&wind_direction=");
        url.concat(this->wind_dir);
    }
    if(this->temp!=no_info){
        url.concat("&&temperature=");
        url.concat(this->temp);
    }
    if(this->rh!=no_info){
        url.concat("&rh=");
        url.concat(this->rh);
    }
    if(this->msclp!=no_info){
        url.concat("&msclp=");
        url.concat(this->msclp);
    }
    if(this->precip!=no_info){
        url.concat("&precip=");
        url.concat(this->precip);
    }
    if(this->precip_interval!=no_info){
        url.concat("&precip_interval=");
        url.concat(this->precip_interval);
    }
    resetAll();
    return url;
}

void Station::set_wind_velocity(float val){
	this->wind_measures++;
	this->wind_velocity_acumulator+=val;
	set_wind_avg(wind_velocity_acumulator/wind_measures);

	if(val > get_wind_max()){
		set_wind_max(val);	
	}
	
	if(val < get_wind_min()){
		set_wind_min(val);	
	}
	
}

void Station::set_wind_avg(float val){
    this->wind_avg = val;
}

void Station::set_wind_max(float val){
    this->wind_max = val;
}

void Station::set_wind_min(float val){
    this->wind_min = val;
}

void Station::set_wind_dir(float val){
    this->wind_dir = val;
}

void Station::set_temp(float val){
    this->temp = val;
}

void Station::set_rh(float val){
    this->rh = val;
}

void Station::set_msclp(float val){
    this->msclp = val;
}

void Station::set_precip(float val){
    this->precip = val;
}

void Station::set_precip_interval(float val){
    this->precip_interval = val;
}

float Station::get_wind_avg(){
    return this->wind_avg;
}

float Station::get_wind_max(){
    return this->wind_max;
}

float Station::get_wind_min(){
    return this->wind_min;
}

float Station::get_wind_dir(){
    return this->wind_dir;
}

float Station::get_temp(){
    return this->temp;
}

float Station::get_rh(){
    return this->rh;
}

float Station::get_msclp(){
    return this->msclp;
}

float Station::get_precip(){
    return this->precip;
}

float Station::get_precip_interval(){
    return this->precip_interval;
}

void Station::resetAll(){
	this->wind_measures=0;
	this->wind_velocity_acumulator=0;
	this->wind_avg=no_info;
    this->wind_max=MAX_CTE;
    this->wind_min=MIN_CTE;
    this->wind_dir=no_info;
    this->temp=no_info;
    this->rh=no_info;
    this->msclp=no_info;
    this->precip=no_info;
    this->precip_interval= no_info;
}
