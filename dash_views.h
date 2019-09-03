#ifndef __DASH_VIEWS_H__
#define __DASH_VIEWS_H__

#include <Arduino.h>
#include <U8g2lib.h>
#include "constants.h"
#include "utils.h"
#include "sensorDataType.h"
#include "window_utils.h"

sensorDataType rpm("RPM", 5, 2);
sensorDataType clt("CLT", 3);
sensorDataType wspd("WSPD", 3);
sensorDataType bat("BAT", 3);
sensorDataType gear("GEAR", 1);
sensorDataType fpr("FPR", 2);

int xrpm = 1000;
int xclt = 0;
int xwspd = 0;
int xbat = 0;
int xgear = 1;
int xfpr = 0;

void updateVals(){
    xrpm = (xrpm > 15000) ? 1000 : ++xrpm;
    xclt = (xclt > 120) ? 0 : ++xclt;
    xwspd = (xwspd > 300) ? 0 : ++xwspd;
    xbat = (xbat > 999) ? 0 : ++xbat;
    xgear = (xgear > 9) ? 1 : ++xgear;
    xfpr = (xfpr > 99) ? 0 : ++xfpr;
}

void view1(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen){
    do{
        displayHorizontalThirdScreen(screen, &gear, xgear, 1);
        displayVerticalThirdScreen(screen, &wspd, xwspd, 0, 0);
        displayVerticalThirdScreen(screen, &clt, xclt, 1, 0);
        displayVerticalThirdScreen(screen, &bat, xbat, 0, 2);
        displayVerticalThirdScreen(screen, &fpr, xfpr, 1, 2);
    }while( screen->nextPage() );

    //delay(50);
    updateVals();
}

void view2(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen){
    do{
        displayHorizontalThirdScreen(screen, &clt, xclt, 0);
        displayHorizontalThirdScreen(screen, &gear, xgear, 1);
        displayHorizontalThirdScreen(screen, &rpm, xrpm, 2);
    }while( screen->nextPage() );
    updateVals();
}

void view3(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen){
    do{
        displayFullScreen(screen, &rpm, xrpm);
    }while( screen->nextPage() );
    updateVals();
}

void view4(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen){
    do{
        displayHorizontalHalfScreen(screen, &rpm, xrpm, 0);
        displayQuarterScreen(screen, &clt, xclt, 0, 1);
        displayQuarterScreen(screen, &wspd, xwspd, 1, 1);
    }while( screen->nextPage() );
    updateVals();
}

void view5(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen){
    do{
        displayVerticalTwoThirdScreen(screen, &rpm, xrpm, 0, 0);
        displayVerticalTwoThirdScreen(screen, &wspd, xwspd, 1, 0);
        displayVerticalThirdScreen(screen, &bat, xbat, 0, 2);
        displayVerticalThirdScreen(screen, &clt, xclt, 1, 2);
    }while( screen->nextPage() );
    updateVals();
}

void view6(U8G2_ST7565_LM6059_1_4W_SW_SPI* screen){
    do{
        displayVerticalHalfScreen(screen, &rpm, xrpm, 0);
        displayQuarterScreen(screen, &clt, xclt, 1, 0);
        displayQuarterScreen(screen, &fpr, xfpr, 1, 1);
    }while( screen->nextPage() );
    updateVals();
}

#endif