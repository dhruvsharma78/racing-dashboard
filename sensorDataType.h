#ifndef __SENSORDATATYPE_H__
#define __SENSORDATATYPE_H__

#include "constants.h"

class sensorDataType{
    public:
        sensorDataType(char* name, int digits){
            strncpy(m_name, name, MAX_CHARS);
            m_digits = digits;
        };
        sensorDataType(char* name, int digits, int miniDigits){
            strncpy(m_name, name, MAX_CHARS);
            m_digits = digits;
            m_miniDigits = miniDigits;
        };
        char* getName(){ return  m_name; };
        int getDigits(){ return m_digits; };
        int getMiniDigits(){ return m_miniDigits; };
    private:
        char m_name[MAX_CHARS];
        int m_digits;
        int m_miniDigits = 999;
};

#endif