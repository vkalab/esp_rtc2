#include <Arduino.h>
#define FASTLED_INTERNAL // add this before including FastLED.h
#include <FastLED.h>
#include <Ds1302.h>

#define NUM_LEDS    60  // Number of LEDs in your strip
#define DATA_PIN    13  // Pin where the data line is connected to
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];



Ds1302 rtc(5, 2, 4);//RST, CLD, DAT
/**/

const static char* WeekDays[] =
{
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};


int buzzer = 21;

void setup()
{
    Serial.begin(9600);
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(15); // Set initial brightness to 50%
    pinMode(buzzer, OUTPUT);

    // initialize the RTC
    rtc.init();
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);

  
    // test if clock is halted and set a date-time (see example 2) to start it
    if (rtc.isHalted())
      {
        Serial.println("RTC is halted. Setting time...");
        /*
        Ds1302::DateTime dt = {
            .year = 23,
            .month = Ds1302::MONTH_OCT,
            .day = 26,
            .hour = 22,
            .minute = 20,
            .second = 20,
            .dow = Ds1302::DOW_THU
        };

        rtc.setDateTime(&dt);
        */
    }
    
    
}


void rozni(){
  static uint8_t last_second = 0;
  Ds1302::DateTime now;
  int hour = 11;
  int minute = 11;
  rtc.getDateTime(&now);
   if(now.hour==hour && now.minute == minute && now.second==0){
    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;  // Set the i'th LED to red
    FastLED.setBrightness(15);
    FastLED.show();  
      }
    }

    if(now.hour==hour && now.minute == minute && now.second==10){
    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;  // Set the i'th LED to red
    FastLED.setBrightness(30);
    FastLED.show();  
      }
    }

    if(now.hour==hour && now.minute == minute && now.second==20){
    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;  // Set the i'th LED to red
    FastLED.setBrightness(60);
    FastLED.show();  
      }
    }


    if(now.hour==hour && now.minute == minute && now.second==30){
    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;  // Set the i'th LED to red
    FastLED.setBrightness(120);
    FastLED.show();  
      }
    }

    if(now.hour==hour && now.minute == minute && now.second==40){
    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;  // Set the i'th LED to red
    FastLED.setBrightness(240);
    FastLED.show();  
      }
    }

if(now.hour==hour && now.minute == minute && now.second==50){
    
    
    if (last_second != now.second)
    {
        last_second = now.second;

        for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::White;  // Set the i'th LED to red
         FastLED.setBrightness(240);
        FastLED.show();  
          }

       
    }else{
       for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::White;  // Set the i'th LED to red
         FastLED.setBrightness(0);
        FastLED.show();  
          }
    }
}

 if(now.hour==hour && now.minute == minute+1 ){
    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;  // Set the i'th LED to red
    FastLED.setBrightness(0);
    FastLED.show();  
      }
    }

}


void loop()
{
    // get the current time
    Ds1302::DateTime now;
    rtc.getDateTime(&now);

    static uint8_t last_second = 0;
    if (last_second != now.second)
    {
        last_second = now.second;

        Serial.print("20");
        Serial.print(now.year);    // 00-99
        Serial.print('-');
        if (now.month < 10) Serial.print('0');
        Serial.print(now.month);   // 01-12
        Serial.print('-');
        if (now.day < 10) Serial.print('0');
        Serial.print(now.day);     // 01-31
        Serial.print(' ');
        Serial.print(WeekDays[now.dow - 1]); // 1-7
        Serial.print(' ');
        if (now.hour < 10) Serial.print('0');
        Serial.print(now.hour);    // 00-23
        Serial.print(':');
        if (now.minute < 10) Serial.print('0');
        Serial.print(now.minute);  // 00-59
        Serial.print(':');
        if (now.second < 10) Serial.print('0');
        Serial.print(now.second);  // 00-59
        Serial.println();
    }

    //delay(100);
   //rozni();

   while (now.hour == 5 && now.minute == 50)
   {
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
   }
   
}



/*
void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(15); // Set initial brightness to 50%
}

void loop() {
  // Fill the dots one after the other with a color
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;  // Set the i'th LED to red
    FastLED.show();  
    delay(30);
    leds[i] = CRGB::Black;  // Turn the i'th LED off
  }
}


*/
