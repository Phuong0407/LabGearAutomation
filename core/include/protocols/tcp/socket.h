#ifndef core_include_protocols_tcp_socket_h
#define core_include_protocols_tcp_socket_h

#include <tcp_utils.h>

#include <stdint.h>
#include <stdexcept>
#include <string.h>

namespace Protocols::TCP {

    class Socket {
        public:
        Socket(char *ip, uint16_t port) {
            if (!is_valid_ipv4(ip)) {
                throw std::invalid_argument("[Protocols/] Invalid IPv4 address.");
            }
            strncpy(this->ip, ip, 16);
            this->ip[16] = '\0';
            this->port = port;
        }

        private:
            char ip[16];
            uint16_t port;
    };

}

#endif // core_include_protocols_tcp_socket_h