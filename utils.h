#ifndef __UTILS_H__
#define __UTILS_H__

#include "constants.h"
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//U8G2_ST7565_LM6059_1_4W_SW_SPI u8g2;

//////////////////////////////////////////////////////////////
// Text Optimization Funtions
//////////////////////////////////////////////////////////////

const uint8_t* optimizeFont(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, const char* text, int16_t startX, int16_t endX, int16_t startY, int16_t endY){
  int i=0;
  while(i<NUMBEROFFONTS){
    screen->setFont(fontNames[i]);
    if(screen->getAscent() < (endY-startY)){
      if(screen->getStrWidth(text) < (endX-startX)){
        return fontNames[i];
      }
    }
    i++;
  }
  return fontNames[NUMBEROFFONTS-1];
}

//////////////////////////////////////////////////////////////
// Text Alignment Funtions
//////////////////////////////////////////////////////////////

///// HORIZONTAL CENTER

//Returns start pixel for string when centered between startX and endX.
//Horizontally centers text
int16_t horizontalCenter(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, const char* text, int16_t startX, int16_t endX, const uint8_t* font){
  screen->setFont(font);
  int16_t diff = endX - startX;
  int16_t width = screen->getStrWidth(text);
  return startX + (diff - width)/2;
}

//Overloaded. 
//Horizontally centers text along screens width
int16_t horizontalCenter(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, const char* text, const uint8_t* font){
  screen->setFont(font);
  int16_t diff = SCREEN_WIDTH - 0;
  int16_t width = screen->getStrWidth(text);
  return (diff - width)/2;
}

//Writes text in horizontal center of startX and endX
void writeHorizontalCenter(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, const char* text, int16_t startX, int16_t endX, int16_t y, const uint8_t* font){
  int x = horizontalCenter(screen, text,startX,endX,font);
  screen->drawStr(x, y, text);
}

//Overloaded.
//Writes text in horizontal center of screen
void writeHorizontalCenter(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, const char* text, int16_t y, const uint8_t* font){
  int x = horizontalCenter(screen, text, font);
  screen->drawStr(x, y, text);
}

///// VERTICAL CENTER

/** Returns start pixel for string when centered between startY and endY
 * */
int16_t verticalCenter(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, const char* text, int16_t startY, int16_t endY, const uint8_t* font){
  screen->setFont(font);
  int16_t diff = endY - startY;
  int16_t height = screen->getAscent();
  return startY + ((diff - height)/2) + height;
}

/** Overloaded. 
 *  Vertically centers text along screens height
 * */
int16_t verticalCenter(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, const char* text, const uint8_t* font){
  screen->setFont(font);
  int16_t diff = SCREEN_HEIGHT - 0;
  int16_t height = screen->getAscent();
  return ((diff - height)/2) + height;
}

/** Writes text in vertical center of startY and endY
 * */
void writeVerticalCenter(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, const char* text, int16_t x, int16_t startY, int16_t endY, const uint8_t* font){
  int y = verticalCenter(screen, text, startY, endY, font);
  screen->drawStr(x, y, text);
}

/** Overloaded.
 *  Writes text in vertical center of screen
 * */
void writeVerticalCenter(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, const char* text, int16_t x, const uint8_t* font){
  int y = verticalCenter(screen, text, font);
  screen->drawStr(x, y, text);
} 

///// HORIZONTAL AND VERTICAL CENTER

/** Returns start pixel for string when centered between startX and endX and startX and endY
 * */
void center(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, const char* text, int16_t startX, int16_t endX, int16_t startY, int16_t endY, const uint8_t* font, int16_t* coords){
  coords[0] = horizontalCenter(screen, text,startX,endX,font);
  coords[1] = verticalCenter(screen, text, startY, endY, font);
}

/** Returns start pixel for string when centered in middle of screen
 * */
void center(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, const char* text, int16_t* coords, const uint8_t* font){
  coords[0] = horizontalCenter(screen, text, font);
  coords[1] = verticalCenter(screen, text, font);
}

/** Writes text in middle of specified startX, endX and startY, endY
 * */
void writeCenter(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, const char* text, int16_t startX, int16_t endX, int16_t startY, int16_t endY, const uint8_t* font){
  int16_t coords[2] = {0,0};
  center(screen, text, startX, endX, startY, endY, font, coords);
  screen->drawStr(coords[0], coords[1], text);
}

/** Writes test in middle of screen
 * */
void writeCenter(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, const char* text, const uint8_t* font){
  int16_t coords[2] = {0,0};
  center(screen, text, coords, font);
  screen->drawStr(coords[0], coords[1], text);
}

///// VERTICAL TEXT
void writeVerticalText(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen, const char* text, int16_t x, int16_t y, const uint8_t* font){
  screen->setFont(font);

  y += screen->getAscent();
  //screen->drawStr(x,y,letter);
  for(int i=0; i<strlen(text) ; i++){
    char letter[2] = {text[i], 0};
    screen->setCursor(x, y);
    screen->print(letter);
    y += 1 + screen->getAscent();
  }
}

#endif