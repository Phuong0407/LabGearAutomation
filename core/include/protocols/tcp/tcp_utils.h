#ifndef core_include_protocols_tcp_tcp_utils_h
#define core_include_protocols_tcp_tcp_utils_h

#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>

static bool is_valid_ipv4(const char *ip) {
    if (ip == NULL) return false;

    uint16_t digits = 0;
    uint16_t dots = 0;
    uint16_t num = 0;

    for (const char* p = ip; *p; ++p) {
        if (*p == '.') {
            if (++dots > 3) return false;
            if (digits == 0) return false;
            if (num > 255) return false;
            digits = 0;
            num = 0;
        } else if (isdigit(*p)) {
            num = num * 10 + (*p - '0');
            if (num > 255) return false;
            if (++digits >3) return false;
        } else {
            return false;
        }
    }
    return (dots == 3) && (digits > 0) && (num <= 255);
}

#endif // core_include_protocols_tcp_tcp_utils_h