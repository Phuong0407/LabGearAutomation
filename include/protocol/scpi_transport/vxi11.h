#ifndef include_protocol_scpi_transport_vxi11_h
#define include_protocol_scpi_transport_vxi11_h

#include <lxi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int vxi11_device_t;


#ifdef VXI11_DEBUG
    #define VXI11_DBG(fmt, ...) fprintf(stderr, "[DEBUG] " fmt "\n", ##__VA_ARGS__)
#else
    #define VXI11_DBG(fmt, ...)
#endif


int vxi11_open(const char *ip, int port, const int timeout, vxi11_device_t *dev);
int vxi11_close(vxi11_device_t *dev);
int vxi11_send(vxi11_device_t *dev, const char *cmd);
int vxi11_recv(vxi11_device_t *dev, void *buff, size_t len, int timeout);

#endif /* include_protocol_scpi_transport_vxi11_h */