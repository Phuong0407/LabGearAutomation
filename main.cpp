#include <protocol/socket/tcp_utils.h>

#include <stdio.h>

int main() {
    const char *ip = "192.168.100.63";
    printf("%d\n", is_valid_ipv4(ip));
}