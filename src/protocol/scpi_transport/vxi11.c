#include <vxi11.h>

int vxi11_open(const char *ip, const int port, const int timeout, vxi11_device_t *dev) {
    VXI11_DBG("Trying to connect to VXI11 device %s:%d", ip, port);

    *dev = lxi_connect(ip, port, NULL, timeout, VXI11);

    if (*dev < 0) {
        VXI11_DBG("Failed to connect to %s:%d", ip, port);
        return -1;
    }

    VXI11_DBG("VXI11 device %s:%d connected successfully", ip, port);
    return 0;
}


int vxi11_close(vxi11_device_t *dev) {
    VXI11_DBG("Trying to close VXI11 device.");

    if (*dev < 0) {
        VXI11_DBG("No connected VXI11 device");
        return -1;
    }

    int close_st = lxi_disconnect(*dev);

    if (close_st == -1) {
        VXI11_DBG("Failed to close VXI11 device, errno=%d");
        return -1;
    }

    VXI11_DBG("VXI11 device closed successfully");
    return 0;
}

int vxi11_send(vxi11_device_t *dev, const char *cmd) {
    if (*dev < 0) {
        VXI11_DBG("VXI11 device not open");
        return -1;
    }

    int send_st = lxi_send(*dev, cmd, (int)strlen(cmd), 2000);
    if (send_st < 0) {
        VXI11_DBG("Failed to send command to VXI11 device");
        return -1;
    }

    VXI11_DBG("Command sent successfully '%s'", cmd);
    return 0;
}

int vxi11_recv(vxi11_device_t *dev, void *buff, size_t len, const int timeout) {
    if (*dev < 0) {
        VXI11_DBG("VXI11 device not open");
        return -1;
    }

    int recv_st = lxi_receive(*dev, buff, (int)len, timeout);

    if (recv_st < 0) {
        VXI11_DBG("Failed to receive data from VXI11 device");
        return -1;
    }

    ((char *)buff)[recv_st] = '\0';
    VXI11_DBG("Received: %d", recv_st);
    return recv_st;
}