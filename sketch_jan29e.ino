#include <SPI.h>
#include <SFE_BMP180.h>
#include <Wire.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include "DHT.h"

#define DHTPIN 9 // broche ou l'on a branche le capteur
#define DHTTYPE DHT22 // DHT 22 (AM2302)

#define CE_PIN 7
#define CSN_PIN 8

#define ALTITUDE 99.0 // Altitude du batiment Lavoisier

SFE_BMP180 pressure;
DHT dht(DHTPIN, DHTTYPE);
RF24 radio(CE_PIN, CSN_PIN);

const uint64_t addresses[2] = {0xa1a1a1a1a1, 0xd1d1d1d1d1} ;
bool radioNumber = false;
bool flag = false;
int sensorPin = 0;
int delay_tx = 750;

void setup()
{
  Serial.begin(115200);
  dht.begin();
  printf_begin();
   
  radio.NRF24Initialization();
  radio.FastresestNRF24();
  radio.setRetries(5,15);
  
  radio.setDataRate( RF24_250KBPS );
  radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX);

  if(radioNumber){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }
  
  radio.startListening();

  if (!pressure.begin()){
    Serial.println("BMP180 init fail!!");
  }
}

void loop(){
// ----------------------------------------------------------------------------------------------------------------------------
//  MESURE DHT22 - Humidité
// ----------------------------------------------------------------------------------------------------------------------------

  float h_dht = mesDHT22_h();
  
  char humidity[32] = "";

  dtostrf(h_dht, 5, 2, humidity);
  Serial.print(F("Humidity: "));
  Serial.println(humidity);

// ----------------------------------------------------------------------------------------------------------------------------
//  MESURE BMP180 - Pression relative
// ----------------------------------------------------------------------------------------------------------------------------

  float p_bmp = (float)mesBMP180();

  char pressure[32] = "";

  dtostrf(p_bmp, 5, 2, pressure);
  Serial.print(F("Pressure: "));
  Serial.println(pressure);

// ----------------------------------------------------------------------------------------------------------------------------
//  MESURE Température - TMP36
// ----------------------------------------------------------------------------------------------------------------------------

  float t_tmp = mesTMP36();
  
  char temperature[32] = "";

  dtostrf(t_tmp, 3, 2, temperature);
  Serial.print(F("Temperature: "));
  Serial.println(temperature);

// ----------------------------------------------------------------------------------------------------------------------------
//  CONCATENATION DES DONNEES
// ----------------------------------------------------------------------------------------------------------------------------

  char RF_write[16] = "";
  
  for(int i = 0; i<16; i++){
    if(i>=0 && i<4){
      RF_write[i] = temperature[i];
    }
    else if(i>=4 && i<8){
      RF_write[i] = humidity[i-4];
    }
    else if(i>=8 && i<15){
      if(p_bmp < 1000){
        if(i == 8){
          RF_write[i] = '0';
        }
        RF_write[i+1] = pressure[i-8];
      }
      else{
        RF_write[i] = pressure[i-8];
      }
    }
    else{
      
    }
  }

  Serial.print("Message a envoyer --> ");
  Serial.println(RF_write);

// ----------------------------------------------------------------------------------------------------------------------------
//  ENVOI DES DONNEES
// ----------------------------------------------------------------------------------------------------------------------------

  RF_write[sizeof(RF_write) - 1] = 0;
  radio.stopListening();
  
  Serial.print(F("Now sending... "));

  //for(int j=0; j<10; j++){
    if (!radio.write(&RF_write, sizeof(RF_write))){
      Serial.println(F("failed!"));
      Serial.println();
      flag = true;
    }
    else{
      Serial.print("Message envoyé! --> ");
      Serial.println(RF_write);
      flag = false;
    }
//    delay(5);
//  }

  if(!flag){
    radio.startListening();                                    // Now, continue listening
    
    unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
      
    while (!radio.available()){                             // While nothing is received
      if (micros() - started_waiting_at > 200000 ){
        timeout = true;
        break;
      }
    }
          
    if (timeout){
      Serial.println(F("Failed, response timed out."));
      Serial.println(F(""));
    }
    else{
      unsigned long got_time;
      radio.read( &got_time, sizeof(unsigned long) );
      unsigned long time = micros();
      
      Serial.print(F("Sent, "));
      Serial.println(F("Got response "));
      Serial.println(F(""));
    }
  }
  
  delay(delay_tx);
}

float mesDHT22_h()
{
  float h = dht.readHumidity();     //on lit l'hygrometrie

  if (isnan(h)){
   Serial.println("Failed to read humidity from DHT sensor!");
  }

  return h;
}

float mesDHT22_t()
{
  float t = dht.readTemperature();     //on lit l'hygrometrie

  if (isnan(t))
  {
   Serial.println("Failed to read humidity from DHT sensor!");
  }

  return t;
}

float mesTMP36()
{
    int reading = analogRead(sensorPin);
    float voltage = reading * 5.0;
    voltage /= 1024.0;

    return ((voltage - 0.5) * 100);
}

double mesBMP180()
{
  char status;
  double P,T,p0;

  status = pressure.startTemperature();
  if (status != 0)
  {
    delay(status);
    status = pressure.getTemperature(T);
    
    if (status != 0)
    {
      status = pressure.startPressure(3);
      if (status != 0)
      {
        delay(status);
        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          p0 = pressure.sealevel(P,ALTITUDE); // we're at 1655 meters (Boulder, CO)
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }

  return p0;
}

