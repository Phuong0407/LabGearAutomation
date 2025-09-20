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



int usbtmc_open(const char *dev) {
    TMC_DBG("Trying to open USBTMC device: %s", dev);

    if (!check_usbtmc_device_path(dev)) {
        TMC_DBG("Device %s does not exist or is not a char device", dev);
        errno = ENODEV;
        return -1;
    }

    int fd = open(dev, O_RDWR);
    if (fd < 0) {
        TMC_DBG("Failed to open device %s, errno=%d", dev, errno);
        return -1;
    }

    TMC_DBG("Device %s opened successfully, fd=%d", dev, fd);
    return fd;
}

int usbtmc_close(int fd) {
    TMC_DBG("Trying to close USBTMC device.");
    
    if (fd == -1) {
        TMC_DBG("Invalid device %d", fd);
        errno = EBADF;
        return -1;
    }

    int close_st = close(fd);
    if (close_st == -1) {
        TMC_DBG("Failed to close device %d, errno=%d", fd, errno);
        return -1;
    }

    TMC_DBG("Device %d closed successfully, fd=%d", fd);
    return 0;
}

ssize_t usbtmc_send(int fd, const char *cmd) {
    if (fd < 0) {
        TMC_DBG("Invalid fd %d", fd);
        errno = EINVAL;
        return -1;
    }
    if (cmd == NULL) {
        TMC_DBG("Null SCPI command");
        errno = EINVAL;
        return -1;
    }
    
    char buff[1024];
    size_t len = strlen(cmd);
    if (len >= sizeof(buff) -1) {
        errno = E2BIG;
        return -1;
    }
    strcpy(buff, cmd);
    if (buff[len-1] != '\n') {
        buff[len] = '\n';
        buff[len+1] = '\0';
        len++;
    }

    ssize_t t_send = 0;
    while (t_send < (ssize_t)len) {
        ssize_t st_send = write(fd, buff + t_send, len - t_send);
        if (st_send == -1) {
            if (errno == EINTR) {
                TMC_DBG("Write to USBTMC is interrupted by system, retrying...");
                continue;
            }
            TMC_DBG("Failed to send command '%s', errno=%d: %s", cmd, errno, strerror(errno));
            return -1;
        }
        t_send += st_send;
    }
    TMC_DBG("Command sent successfully '%s'", cmd);
    return t_send;
}

ssize_t usbtmc_recv(int fd, void *buf, size_t len) {
    if (fd < 0) {
        TMC_DBG("Invalid fd %d", fd);
        errno = EINVAL;
        return -1;
    }
    if (buf == NULL) {
        TMC_DBG("Invalid response buffer size %p", buf);
        errno = EINVAL;
        return -1;
    }
    if (fd < 0) {
        TMC_DBG("Invalid len %zu", len);
        errno = EINVAL;
        return -1;
    }

    ssize_t t_read = 0;
    while (t_read < (ssize_t)len) {
        ssize_t st_read = read(fd, (char*)buf + t_read, len - t_read);
        if (st_read == -1) {
            if (errno == EINTR) {
                TMC_DBG("Read from USBTMC is interrupted by system, retrying...");
                continue;
            }
            TMC_DBG("Failed to read from USBTMC, errno=%d: %s", errno, strerror(errno));
            return -1;
        } else if (st_read == 0) {
            break;
        }
        t_read += st_read;
        break;
    }
    TMC_DBG("Received %zd bytes from USBTMC", t_read);
    return t_read;
}




int check_usbtmc_device_path(const char *dev) {
    struct stat st;
    if (stat(dev, &st) == 0) {
        if (S_ISCHR(st.st_mode)) {
            return 1;
        }
    }
    return 0;
}

#endif /* include_protocol_scpi_transport_usbtmc_h */