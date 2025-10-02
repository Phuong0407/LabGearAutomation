#ifndef include_protocol_scpi_transport_usbtmc_h
#define include_protocol_scpi_transport_usbtmc_h

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


#ifdef USBTMC_DEBUG
    #define TMC_DBG(fmt, ...) fprintf(stderr, "[DEBUG] " fmt "\n", ##__VA_ARGS__)
#else
    #define TMC_DBG(fmt, ...)
#endif


int check_usbtmc_device_path(const char *dev);
int usbtmc_open(const char *dev);
int usbtmc_close(int fd);
ssize_t usbtmc_send(int fd, const char *cmd);
ssize_t usbtmc_recv(int fd, void *buf, size_t len);


#endif /* include_protocol_scpi_transport_usbtmc_h */
