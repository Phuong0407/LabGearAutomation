#ifndef include_wattmeter_yokogawa_yokogawa_h
#define include_wattmeter_yokogawa_yokogawa_h

#include<include/protocol/scpi.h>

typedef struct {
    int model;
    int serial;
    char firmware[5];
    int option;
} YokogawaWattmeter;

int query_yokogawa_option(YokogawaWattmeter* w) {
    
}

#endif // include_wattmeter_yokogawa_yokogawa_h