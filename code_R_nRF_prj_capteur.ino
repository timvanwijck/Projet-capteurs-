#include <LiquidCrystal.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

#define CE_PIN 7
#define CSN_PIN 8

RF24 radio(CE_PIN, CSN_PIN);

const uint64_t addresses[2] = {0xa1a1a1a1a1, 0xd1d1d1d1d1} ;
const int rs = 9, en = 10, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
bool radioNumber = 1;
bool flag = false;
char loulou[3] = {'L', 'O', 'U'};

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(115200);
  printf_begin();
   
  radio.NRF24Initialization();
  radio.FastresestNRF24();
  radio.setRetries(5,15);
  
  radio.setDataRate( RF24_250KBPS );
  //radio.setDataRate( RF24_1MBPS );
  //radio.setDataRate( RF24_2MBPS );
  
  radio.setChannel(69);
  
  //radio.setPALevel( RF24_PA_MIN  );
  radio.setPALevel( RF24_PA_LOW  );
  //radio.setPALevel( RF24_PA_HIGH );
  //radio.setPALevel( RF24_PA_MAX  );

  if(radioNumber){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }

  radio.startListening();

  lcd.clear();

  lcdINIT();
}

void loop()
{
  unsigned long got_time;
  char RF_read[16] = "";
  int delay_ms = 5;
  
  if( radio.available())
  {                                                   // Variable for the received timestamp
    while (radio.available())
    {                                                 // While there is data ready
      radio.read(&RF_read, sizeof(RF_read));
      Serial.print("Message recu: ");
      Serial.println(RF_read);
    }
    flag = true;
  }
  
  radio.stopListening();                            // First, stop listening so we can talk   
  radio.write( &got_time, sizeof(unsigned long) );  // Send the final one back.      
  radio.startListening();
  
  if(flag)
  {
    for(int i = 0; i<15 ; i++)
    {
      if (i>=0&i<4)
      {
        lcd.setCursor(2+i,0);
        lcd.print(RF_read[i]);
        delay(delay_ms);
      }
      else if(i>=4&i<8)
      {
        lcd.setCursor(7+i,0);
        lcd.write(RF_read[i]);
        delay(delay_ms);
      }
      else if(i>=8&i<15)
      {
        lcd.setCursor(i-6,1);
        lcd.write(RF_read[i]);
        delay(delay_ms);
      }
    }
    flag = false;
  }
  delay(500);
}

void lcdINIT(){
  lcd.setCursor(0,0);
  lcd.print("t:");
  lcd.setCursor(6,0);
  lcd.print((char)223);
  lcd.setCursor(7,0);
  lcd.print("C");
  lcd.setCursor(9,0);
  lcd.print("h:");
  lcd.setCursor(15,0);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("p:");
  lcd.setCursor(9,1);
  lcd.print("mb");
  lcd.setCursor(14,1);
  lcd.print(":)");
}

