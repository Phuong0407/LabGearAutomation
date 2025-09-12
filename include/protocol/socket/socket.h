#ifndef include_protocol_socket_h
#define include_protocol_socket_h

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

typedef struct {
    char ip[16];
    uint16_t port;
    int socketfd;
} TCP_Socket;

static inline bool is_valid_ipv4(const char *ip) {
    struct sockaddr_in sa;
    return inet_pton(AF_INET, ip, &(sa.sin_addr)) == 1;
}

static inline int tcp_socket_init(TCP_Socket *sock, const char *ip, uint16_t port) {
    if (!is_valid_ipv4(ip)) {
        fprintf(stderr, "[Protocols/] Invalid IPv4 address.\n");
        return -1;
    }
    strncpy(sock->ip, ip, sizeof(sock->ip) - 1);
    sock->ip[sizeof(sock->ip) - 1] = '\0';
    sock->port = port;
    sock->socketfd = -1;
    return 0;
}

static inline int tcp_open_connection(TCP_Socket *sock) {
    sock->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->socketfd < 0) {
        perror("socket");
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(sock->port);

    if (inet_pton(AF_INET, sock->ip, &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(sock->socketfd);
        sock->socketfd = -1;
        return -1;
    }

    if (connect(sock->socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sock->socketfd);
        sock->socketfd = -1;
        return -1;
    }

    return 0;
}

static inline void tcp_close_connection(TCP_Socket *sock) {
    if (sock->socketfd >= 0) {
        close(sock->socketfd);
        sock->socketfd = -1;
    }
}

#endif /* include_protocol_socket_h */