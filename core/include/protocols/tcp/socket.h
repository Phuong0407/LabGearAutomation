#ifndef core_include_protocols_tcp_socket_h
#define core_include_protocols_tcp_socket_h

#include <tcp_utils.h>

#include <stdint.h>
#include <stdexcept>

namespace Protocols::TCP {

    class Socket {
        public:
        Socket(char *ip, uint16_t port) {
            if (!is_valid_ipv4(ip)) {
                throw std::invalid_argument("[Protocols/] Invalid IPv4 address.");
            }
            this->ip = ip;
            this->port = port;
        }

        private:
            char *ip;
            uint16_t port;
    };

}

#endif // core_include_protocols_tcp_socket_h