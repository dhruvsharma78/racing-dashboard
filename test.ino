#include <Arduino.h>
#include <U8g2lib.h>
#include "constants.h"
#include "utils.h"
#include "dash_views.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define BACKLIGHT_LED 4
#define BUTTON1PIN 6
#define BUTTON2PIN 7

/**
 * CODES FOR WRITING DATA TO DISPLAY
 * 
 * 
 * RPM             - 0 or RPM
 * COOLANT TEMP    - 1 or CLT
 * WHEEL SPEED     - 2 or WSPD
 * BATTERY VOLTAGE - 3 or BAT 
 * GEAR            - 4 or GEAR
 * FUEL PRESSURE   - 5 or FPR
 * 
 * */

// U8G2_ST7565_LM6059_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 8, /* data=*/ 9, /* cs=*/ 5, /* dc=*/ 7, /* reset=*/ 6);		// Adafruit ST7565 GLCD
// U8G2_ST7565_LM6059_1_4W_SW_SPI s2(U8G2_R0, /* clock=*/ 8, /* data=*/ 9, /* cs=*/ 5, /* dc=*/ 7, /* reset=*/ 6);		// Adafruit ST7565 GLCD


// Teensy Setup
U8G2_ST7565_LM6059_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 9, /* data=*/ 8, /* cs=*/ 12, /* dc=*/ 10, /* reset=*/ 11);		// Adafruit ST7565 GLCD

void setup(void) {
  Serial.begin(9600);
  u8g2.begin( BUTTON2PIN,  BUTTON1PIN,  U8X8_PIN_NONE);
  // Screen direction normal
  u8g2.setDisplayRotation(U8G2_R0);
  // Screen direction upside down
  //u8g2.setDisplayRotation(U8G2_R2);
  //u8g2.enableUTF8Print();

  pinMode(BUTTON1PIN, INPUT_PULLUP);
  pinMode(BUTTON2PIN, INPUT_PULLUP);

  u8g2.drawXBMP(0,0, 128, 64, myBitmap);
  delay(5000);
}

boolean newData = false;
int x = 1;
char buff;
bool rotated = false;

void loop(void) {
  int b1Val = digitalRead(BUTTON1PIN);
  int b2Val = digitalRead(BUTTON2PIN);
  u8g2.firstPage();
  switch(x){
    case 1:
      view1(&u8g2);
      // view1(&s2);
      break;
    case 2:
      view2(&u8g2);
      // view2(&s2);
      break;
    case 3:
      view3(&u8g2);
      // view3(&s2);
      break;
    case 4:
      view4(&u8g2);
      // view4(&s2);
      break; 
    case 5:
      view5(&u8g2);
      // view5(&s2);
      break; 
    case 6:
      view6(&u8g2);
      // view6(&s2);
      break; 
  }
  if(b1Val == LOW){
    int z = u8g2.userInterfaceSelectionList("Select:", 1, "Race\nDebug\nFlip\nPower Save\nContrast");
    if(z == 3){
      rotated = !rotated;
      if(rotated){
        u8g2.setDisplayRotation(U8G2_R2);
      }else{
        u8g2.setDisplayRotation(U8G2_R0);
      }
    }
    if(z == 5){
      uint8_t v;
      u8g2.userInterfaceInputValue("Select Contrast", "Contrast= ", &v, 1, 10, 2, "");
      u8g2.setContrast(v*25.5);
    }
  }
  if(b2Val == LOW){
    x++;
    if(x>6){
      x=1;
    }
  }
  
}

void recvOneChar() {
 if (Serial.available() > 0) {
  buff = Serial.read();
  x++;
  if(x>6){
    x=1;
  }
 }
}

