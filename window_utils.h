#ifndef __WINDOW_UTILS_H__
#define __WINDOW_UTILS_H__

#include "constants.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include "utils.h"
#include "sensorDataType.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//////////////////////////////////////////////////////////////
// Auxillary Funtions
//////////////////////////////////////////////////////////////

int16_t getMiniValue(sensorDataType* sdt, int16_t num){
  double x = num / pow(10, (sdt->getDigits()-1));
  num = x * pow(10,(sdt->getMiniDigits()-1));
  return num;
}

//////////////////////////////////////////////////////////////
// Window Alignment Funtions
//////////////////////////////////////////////////////////////

//--------------/ Full Screen /--------------//

void displayFullScreen(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, sensorDataType* sdt, int16_t value){
  const uint8_t* font;
  int16_t digits = sdt->getDigits();

  char value_str[digits+1];
  strcpy(value_str, u8x8_u16toa(value, digits));

  screen->drawFrame(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

  font = optimizeFont(screen, value_str, 0, SCREEN_WIDTH, round(0.31*SCREEN_HEIGHT), round(0.94*SCREEN_HEIGHT));
  writeHorizontalCenter(screen, value_str, round(0.94*SCREEN_HEIGHT), font);
  
  font = optimizeFont(screen, value_str, 0, SCREEN_WIDTH, 0, round(0.31*SCREEN_HEIGHT));
  writeHorizontalCenter(screen, sdt->getName(), round(0.31*SCREEN_HEIGHT), font);
}

//--------------/ Half Screen /--------------// HORIZONTAL

void displayHorizontalHalfScreen(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, sensorDataType* sdt, int16_t value, int16_t side){

  char sensorName[MAX_CHARS];
  strcpy(sensorName,sdt->getName());

  screen->drawFrame(side*(SCREEN_WIDTH/2),0,SCREEN_WIDTH/2,SCREEN_HEIGHT);

  char value_str[sdt->getDigits()+1];
  strcpy(value_str, u8x8_u16toa(value, sdt->getDigits()));

  const uint8_t* font;

  if(sdt->getMiniDigits() != 999){

    writeVerticalText(screen, sensorName, round(0.03*SCREEN_WIDTH)+(side*(SCREEN_WIDTH/2)), round(0.15*SCREEN_HEIGHT), FONT_5);

    int16_t mini_value = getMiniValue(sdt, value);
    char mini_value_str[sdt->getMiniDigits()+1];
    strcpy(mini_value_str, u8x8_u16toa(mini_value, sdt->getMiniDigits()));
  
    font = optimizeFont(screen, mini_value_str, round(0.03*SCREEN_WIDTH)+side*(SCREEN_WIDTH/2), (SCREEN_WIDTH/2)+side*(SCREEN_WIDTH/2), 0, round(0.62*SCREEN_HEIGHT));
    writeCenter(screen, 
                mini_value_str,
                round(0.03*SCREEN_WIDTH)+side*(SCREEN_WIDTH/2),
                (SCREEN_WIDTH/2)+side*(SCREEN_WIDTH/2),
                0,
                round(0.62*SCREEN_HEIGHT),
                font);
    
    font = optimizeFont(screen, value_str, side*(SCREEN_WIDTH/2), (SCREEN_WIDTH/2)+side*(SCREEN_WIDTH/2), round(0.62*SCREEN_HEIGHT), SCREEN_HEIGHT);
    writeHorizontalCenter(screen, value_str, side*(SCREEN_WIDTH/2), (SCREEN_WIDTH/2)+side*(SCREEN_WIDTH/2), round(0.94*SCREEN_HEIGHT), font);

  }else{
    
    font = optimizeFont(screen, value_str, side*(SCREEN_WIDTH/2), (SCREEN_WIDTH/2)+side*(SCREEN_WIDTH/2), 0, round(0.31*SCREEN_HEIGHT));
    writeHorizontalCenter(screen, sensorName, side*(SCREEN_WIDTH/2), (SCREEN_WIDTH/2)+side*(SCREEN_WIDTH/2), round(0.31*SCREEN_HEIGHT), font);

    font = optimizeFont(screen, value_str, side*(SCREEN_WIDTH/2), (SCREEN_WIDTH/2)+side*(SCREEN_WIDTH/2), round(0.31*SCREEN_HEIGHT), SCREEN_HEIGHT);
    writeCenter(screen, 
                value_str,
                side*(SCREEN_WIDTH/2),
                (SCREEN_WIDTH/2)+side*(SCREEN_WIDTH/2),
                round(0.31*SCREEN_HEIGHT),
                SCREEN_HEIGHT,
                font);

  }
}

//--------------/ Half Screen /--------------// VERTICAL

void displayVerticalHalfScreen(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, sensorDataType* sdt, int16_t value, int16_t level){
  char sensorName[MAX_CHARS];
  strcpy(sensorName,sdt->getName());

  screen->drawFrame(0,level*(SCREEN_HEIGHT/2),SCREEN_WIDTH,SCREEN_HEIGHT/2);

  char value_str[sdt->getDigits()+1];
  strcpy(value_str, u8x8_u16toa(value, sdt->getDigits()));

  const uint8_t* font;

  font = optimizeFont(screen, sensorName, 0, round(0.40*SCREEN_WIDTH), level*(SCREEN_HEIGHT/2), (SCREEN_HEIGHT/2)+level*(SCREEN_HEIGHT/2));
  writeCenter(screen,
              sensorName,
              0,
              round(0.40*SCREEN_WIDTH),
              level*(SCREEN_HEIGHT/2),
              (SCREEN_HEIGHT/2)+level*(SCREEN_HEIGHT/2),
              font);
  
  font = optimizeFont(screen, sensorName, round(0.40*SCREEN_WIDTH), SCREEN_WIDTH, level*(SCREEN_HEIGHT/2), (SCREEN_HEIGHT/2)+level*(SCREEN_HEIGHT/2));
  writeCenter(screen, 
              value_str,
              round(0.40*SCREEN_WIDTH),
              SCREEN_WIDTH,
              level*(SCREEN_HEIGHT/2),
              (SCREEN_HEIGHT/2)+level*(SCREEN_HEIGHT/2),
              FONT_3);
}

//--------------/ Third Screen /--------------// HORIZONTAL

void displayHorizontalThirdScreen(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, sensorDataType* sdt, int16_t value, int16_t side){
  if(side < 0 && side > 2){
    side = 0;
  }

  char sensorName[MAX_CHARS];
  strcpy(sensorName,sdt->getName());

  screen->drawFrame(side*(SCREEN_WIDTH/3),0,SCREEN_WIDTH/3,SCREEN_HEIGHT);

  char value_str[sdt->getDigits()+1];
  strcpy(value_str, u8x8_u16toa(value, sdt->getDigits()));

  const uint8_t* font;

  font = optimizeFont(screen, sensorName, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+SCREEN_WIDTH/3, 0, round(0.26*SCREEN_HEIGHT));
  writeCenter(screen, sensorName, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+SCREEN_WIDTH/3, 0, round(0.26*SCREEN_HEIGHT),font);


  if(sdt->getMiniDigits() == 999){
    font = optimizeFont(screen, value_str, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+SCREEN_WIDTH/3, round(0.26*SCREEN_HEIGHT), SCREEN_HEIGHT);
    writeCenter(screen, value_str, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+SCREEN_WIDTH/3, round(0.26*SCREEN_HEIGHT), SCREEN_HEIGHT, font);
  }else{
    font = optimizeFont(screen, value_str, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+SCREEN_WIDTH/3, round(0.7*SCREEN_HEIGHT), SCREEN_HEIGHT);
    writeCenter(screen, value_str, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+SCREEN_WIDTH/3, round(0.7*SCREEN_HEIGHT), SCREEN_HEIGHT, font);

    int16_t mini_value = getMiniValue(sdt, value);
    char mini_value_str[sdt->getMiniDigits()+1];
    strcpy(mini_value_str, u8x8_u16toa(mini_value, sdt->getMiniDigits()));

    font = optimizeFont(screen, mini_value_str, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+SCREEN_WIDTH/3, round(0.26*SCREEN_HEIGHT), round(0.7*SCREEN_HEIGHT));
    writeCenter(screen, mini_value_str, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+SCREEN_WIDTH/3, round(0.26*SCREEN_HEIGHT), round(0.7*SCREEN_HEIGHT), font);
  }
}

//--------------/ Third Screen /--------------// VERTICAL

void displayVerticalThirdScreen(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, sensorDataType* sdt, int16_t value, int16_t level, int16_t side){
  if(side < 0 && side > 1){
    side = 0;
  }
  if(level < 0 && level > 1){
    level = 0;
  }

  

  screen->drawFrame(side*(SCREEN_WIDTH/3),level*SCREEN_HEIGHT/2, SCREEN_WIDTH/3, SCREEN_HEIGHT/2);

  char value_str[sdt->getDigits()+1];
  strcpy(value_str, u8x8_u16toa(value, sdt->getDigits()));

  char sensorName[MAX_CHARS];
  strcpy(sensorName,sdt->getName());

  const uint8_t* font;

  font = optimizeFont(screen, sensorName, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+SCREEN_WIDTH/3, round(0.03*SCREEN_HEIGHT)+level*SCREEN_HEIGHT/2, round(0.2*SCREEN_HEIGHT)+level*SCREEN_HEIGHT/2);
  writeCenter(screen, sensorName, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+SCREEN_WIDTH/3, round(0.03*SCREEN_HEIGHT)+level*SCREEN_HEIGHT/2, round(0.2*SCREEN_HEIGHT)+level*SCREEN_HEIGHT/2, font);
  
  font = optimizeFont(screen, value_str, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+SCREEN_WIDTH/3, round(0.2*SCREEN_HEIGHT)+level*SCREEN_HEIGHT/2, (level*SCREEN_HEIGHT/2)+SCREEN_HEIGHT/2);
  writeCenter(screen, value_str, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+SCREEN_WIDTH/3, round(0.2*SCREEN_HEIGHT)+level*SCREEN_HEIGHT/2, (level*SCREEN_HEIGHT/2)+SCREEN_HEIGHT/2, font);

}

//--------------/ Two Third Screen /--------------// HORIZONTAL

void displayHorizontalTwoThirdScreen(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, sensorDataType* sdt, int16_t value, int16_t side){
  if(side < 0 && side > 1){
    side = 0;
  }

  char sensorName[MAX_CHARS];
  strcpy(sensorName,sdt->getName());

  screen->drawFrame(side*(SCREEN_WIDTH/3),0,2*SCREEN_WIDTH/3,SCREEN_HEIGHT);

  char value_str[sdt->getDigits()+1];
  strcpy(value_str, u8x8_u16toa(value, sdt->getDigits()));

  const uint8_t* font;

  font = optimizeFont(screen, sensorName, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+(2*SCREEN_WIDTH/3), 0, round(0.26*SCREEN_HEIGHT));
  writeCenter(screen, sensorName, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+(2*SCREEN_WIDTH/3), 0, round(0.26*SCREEN_HEIGHT),font);


  if(sdt->getMiniDigits() == 999){
    font = optimizeFont(screen, value_str, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+(2*SCREEN_WIDTH/3), round(0.26*SCREEN_HEIGHT), SCREEN_HEIGHT);
    writeCenter(screen, value_str, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+(2*SCREEN_WIDTH/3), round(0.26*SCREEN_HEIGHT), SCREEN_HEIGHT, font);
  }else{
    font = optimizeFont(screen, value_str, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+(2*SCREEN_WIDTH/3), round(0.7*SCREEN_HEIGHT), SCREEN_HEIGHT);
    writeCenter(screen, value_str, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+(2*SCREEN_WIDTH/3), round(0.7*SCREEN_HEIGHT), SCREEN_HEIGHT, font);

    int16_t mini_value = getMiniValue(sdt, value);
    char mini_value_str[sdt->getMiniDigits()+1];
    strcpy(mini_value_str, u8x8_u16toa(mini_value, sdt->getMiniDigits()));

    font = optimizeFont(screen, mini_value_str, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+(2*SCREEN_WIDTH/3), round(0.26*SCREEN_HEIGHT), round(0.7*SCREEN_HEIGHT));
    writeCenter(screen, mini_value_str, side*(SCREEN_WIDTH/3), (side*(SCREEN_WIDTH/3))+(2*SCREEN_WIDTH/3), round(0.26*SCREEN_HEIGHT), round(0.7*SCREEN_HEIGHT), font);
  }
}

//--------------/ Two Third Screen /--------------// VERTICAL

void displayVerticalTwoThirdScreen(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, sensorDataType* sdt, int16_t value, int16_t level, int16_t side){
  if(side < 0 && side > 1){
    side = 0;
  }
  if(level < 0 && level > 1){
    level = 0;
  }

  char sensorName[MAX_CHARS];
  strcpy(sensorName,sdt->getName());

  screen->drawFrame(side*(SCREEN_WIDTH/3), (level*SCREEN_HEIGHT/2), 2*SCREEN_WIDTH/3, (SCREEN_HEIGHT/2));

  char value_str[sdt->getDigits()+1];
  strcpy(value_str, u8x8_u16toa(value, sdt->getDigits()));

  const uint8_t* font;

  font = optimizeFont(screen, sensorName, side*(SCREEN_WIDTH/3), round(0.30*SCREEN_WIDTH)+side*(SCREEN_WIDTH/3), (level*SCREEN_HEIGHT/2), (level*SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/2));
  writeCenter(screen, sensorName, side*(SCREEN_WIDTH/3), round(0.30*SCREEN_WIDTH)+side*(SCREEN_WIDTH/3), (level*SCREEN_HEIGHT/2), (level*SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/2), font);

  font = optimizeFont(screen, value_str, round(0.30*SCREEN_WIDTH)+side*(SCREEN_WIDTH/3), side*(SCREEN_WIDTH/3)+(2*SCREEN_WIDTH/3), (level*SCREEN_HEIGHT/2), (level*SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/2));
  writeCenter(screen, value_str, round(0.30*SCREEN_WIDTH)+side*(SCREEN_WIDTH/3), side*(SCREEN_WIDTH/3)+(2*SCREEN_WIDTH/3), (level*SCREEN_HEIGHT/2), (level*SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/2), font);
}

//--------------/ Quarter Screen /--------------// QUADRANTS

void displayQuarterScreen(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, sensorDataType* sdt, int16_t value, int16_t level, int16_t side){
  if(side < 0 && side > 1){
    side = 0;
  }
  if(level < 0 && level > 1){
    level = 0;
  }

  char sensorName[MAX_CHARS];
  strcpy(sensorName,sdt->getName());

  screen->drawFrame(side*(SCREEN_WIDTH/2), (level*SCREEN_HEIGHT/2), SCREEN_WIDTH/2, (SCREEN_HEIGHT/2));

  char value_str[sdt->getDigits()+1];
  strcpy(value_str, u8x8_u16toa(value, sdt->getDigits()));

  const uint8_t* font;

  font = optimizeFont(screen, sensorName, side*(SCREEN_WIDTH/2), round(0.20*SCREEN_WIDTH)+side*(SCREEN_WIDTH/2), (level*SCREEN_HEIGHT/2), (level*SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/2));
  writeCenter(screen, sensorName, side*(SCREEN_WIDTH/2), round(0.20*SCREEN_WIDTH)+side*(SCREEN_WIDTH/2), (level*SCREEN_HEIGHT/2), (level*SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/2), font);

  font = optimizeFont(screen, value_str, round(0.20*SCREEN_WIDTH)+side*(SCREEN_WIDTH/2), side*(SCREEN_WIDTH/2)+(SCREEN_WIDTH/2), (level*SCREEN_HEIGHT/2), (level*SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/2));
  writeCenter(screen, value_str, round(0.20*SCREEN_WIDTH)+side*(SCREEN_WIDTH/2), side*(SCREEN_WIDTH/2)+(SCREEN_WIDTH/2), (level*SCREEN_HEIGHT/2), (level*SCREEN_HEIGHT/2)+(SCREEN_HEIGHT/2), font);
}

#endif