// #include <include/protocol/usbtmc.h>

// #include <unistd.h>
// #include <fcntl.h>
// #include <string.h>
// #include <errno.h>
// #include <stdio.h> 

// namespace protocol {

// usbtmc::usbtmc() : fd(-1), bufferlen(0) {}

// usbtmc::~usbtmc() {}

// int usbtmc::open(const char *device_path) {
//     int fd = ::open("/dev/usbtmc0", O_RDWR);
//     return fd;
// }

// int usbtmc::close() {
//     if (fd >= 0) {
//         ::close(fd);
//         fd = -1;
//     }
//     return 0;
// }

// int usbtmc::send(const char *cmd) {
//     if (fd < 0) {
//         return -1;
//     }

//     size_t len = strlen(cmd);
//     ssize_t byte_written = ::write(fd, cmd, len);
    
//     if (byte_written < 0) {
//         perror("write failed");
//         return -1;
//     }
//     return (int)byte_written;
// }

// int usbtmc::recv() {

// }

// int usbtmc::send_recv(const char *cmd) {

// }

// int usbtmc::send_recv_byte(const char *cmd, char *resp) {

// }

// int usbtmc::send_recv_str(const char *cmd, char *resp) {

// }

// int usbtmc::send_recv_int(const char *cmd, int resp) {
    
// }

// }