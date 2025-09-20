#ifndef include_wattmeter_yokogawa_yokogawa_h
#define include_wattmeter_yokogawa_yokogawa_h

#include<include/protocol/scpi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef YOKOGAWA_WATTMETER_DEBUG
    #define YW_DEG(fmt, ...) fprintf(stderr, "[DEBUG] " fmt "\n", ##__VA_ARGS__)
#else
    #define YW_DEG(fmt, ...)
#endif



int parse_block(const uint8_t* data, size_t data_len, float* out_array, size_t* out_count) {
    if (data_len < 2 || data[0] != '#') {
        YW_DEG("Invalid block data");
        return -1;
    }

    int N = data[1] - '0';
    if (data_len < 2 + N) {
        YW_DEG("Invalid block data");
        return -1;
    }

    char len_str[16];
    if (N >= sizeof(len_str))
    if (data_len < 2 + N) {
        YW_DEG("Invalid block data");
        return -1;
    }

    memcpy(len_str, data + 2, N);
    len_str[N] = '\0';
    int len = atoi(len_str);

    if (data_len < 2 + N + len) {
        YW_DEG("Invalid block data");
        return -1;
    }

    int numfp = len / 4;
    *out_count = numfp;

    const uint8_t* fpdat = data + 2 + N;
    for (int i = 0; i < numfp; ++i) {
        uint32_t tmp = 
            ((uint32_t)fpdat[i*4 + 0] << 24) |
            ((uint32_t)fpdat[i*4 + 1] << 16) |
            ((uint32_t)fpdat[i*4 + 2] << 8)  |
            ((uint32_t)fpdat[i*4 + 3]);

        float f;
        memcpy(&f, &tmp, sizeof(float));
        out_array[i] = f;
    }
    return 1;
}

typedef struct {
    int model;
    int serial;
    char firmware[5];
    int option;
} YokogawaWattmeter;

int query_yokogawa_option(YokogawaWattmeter* w) {
    
}



#endif // include_wattmeter_yokogawa_yokogawa_h