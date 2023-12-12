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

int targeted_hour = 5;
int targeted_minute = 54;

void setup()
{
    Serial.begin(9600);
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(15); // Set initial brightness to 50%
    pinMode(buzzer, OUTPUT);

    // initialize the RTC
    rtc.init();

    // Start session
    digitalWrite(buzzer, HIGH);
    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;  // Set the i'th LED to red
    FastLED.setBrightness(200);
    FastLED.show();  
      }
    delay(500);
    digitalWrite(buzzer, LOW);
    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255,255,255);  // Set the i'th LED to red
    FastLED.setBrightness(15);
    FastLED.show();  
      }
    delay(500);
    digitalWrite(buzzer, HIGH);
    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;  // Set the i'th LED to red
    FastLED.setBrightness(200);
    FastLED.show();  
      }
    delay(500);
    digitalWrite(buzzer, LOW);
    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;  // Set the i'th LED to red
    FastLED.setBrightness(0);
    FastLED.show();  
      }
    delay(500);


    
  
    // test if clock is halted and set a date-time (see example 2) to start it
    if (rtc.isHalted())
      {
        Serial.println("RTC is halted. Setting time...");
        /*
        Ds1302::DateTime dt = {
            .year = 23,
            .month = Ds1302::MONTH_DEC,
            .day = 7,
            .hour = 18,
            .minute = 20,
            .second = 00,
            .dow = Ds1302::DOW_THU
        };

        rtc.setDateTime(&dt);
        */
    }
    
    
}


void rozni(){
  FastLED.setBrightness(0);

  for(int j = 0; j<255; j++){
    FastLED.setBrightness(j);
        delay(250);
        FastLED.show();

        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = CRGB(255,0,0);
           FastLED.show();  
    
  }  
    }


     for(int j = 0; j<255; j++){
        delay(100);
        FastLED.show();

        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = CRGB(255,0,j);
           FastLED.show();  
    
  }  
    }


    
     for(int j = 0; j<255; j++){
        delay(100);
        FastLED.show();

        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = CRGB(255,j,255);
           FastLED.show();  
    
  }  
    }

  
    

   
    }


   
void play(){
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
    for(int i = 0; i<10;i++){
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
    }
    
}

void zhasni(){
  Ds1302::DateTime now;
  if(now.hour == targeted_hour && now.minute == targeted_minute+10){
    FastLED.clear();  
  
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

   while (now.hour == targeted_hour && now.minute == targeted_minute)
   {
    rozni();
    play();//ff
    zhasni();
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