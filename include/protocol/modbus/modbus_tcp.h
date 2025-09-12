#ifndef core_include_protocols_modbus_tcp_h
#define core_include_protocols_modbus_tcp_h

#include <modbus/modbus.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <threads.h>

typedef int (*update_func_t)(void);

typedef struct {
    int port;
    int di;
    int co;
    int hr;
    int ir;

    modbus_t *ctx;
    modbus_mapping_t *mb_mapping;
    int server_socket;

    update_func_t *update_di;
    update_func_t *update_co;
    update_func_t *update_ir;
    update_func_t *update_hr;
    update_func_t *update_err;
} ModbusServer;

int start_modbus_server(ModbusServer *server);
int close_modbus_server(ModbusServer *server);
void poll_update_data();
void poll_error_state();

void init_modbus_server(
    ModbusServer *server,
    int port,
    int di,
    int co,
    int ir,
    int hr,
    update_func_t *update_di,
    update_func_t *update_co,
    update_func_t *update_hr,
    update_func_t *update_ir,
    update_func_t *update_err
) {
    server->port = port;
    server->ctx = NULL;
    server->mb_mapping = NULL;
    server->server_socket = -1;
    server->di = di;
    server->co = co;
    server->hr = hr;
    server->ir = ir;
    server->update_di = update_di;
    server->update_co = update_co;
    server->update_ir = update_ir;
    server->update_hr = update_hr;
    server->update_err = update_err;
}

/**
 * 
 * Start the Modbus TCP server and listen on all addresses
 * @return 0 on success and -1 on failure
 * 
 */
int start_modbus_server(ModbusServer *server) {
    if (server->ctx != NULL) {
        return 0;
    }
    server->ctx = modbus_new_tcp("0.0.0.0", server->port);
    if (server->ctx == NULL) {
        fprintf(stderr, "Unable to allocate Modbus context.\n");
        return -1;
    }
    server->mb_mapping = modbus_mapping_new(
        server->di,
        server->co,
        server->ir,
        server->hr
    );
    if (server->mb_mapping == NULL) {
        fprintf(stderr, "Failed to allocate the mapping: %s\n", modbus_strerror(errno));
        modbus_free(server->ctx);
        return -1;
    }
    server->server_socket = modbus_tcp_listen(server->ctx, 1);
    if (server->server_socket == -1) {
        fprintf(stderr, "Unable to listen TCP socket: %s\n", modbus_strerror(errno));
        modbus_mapping_free(server->mb_mapping);
        modbus_free(server->ctx);
        return -1;
    }
    return 0;
}

int close_modbus_server(ModbusServer *server) {
    if (server == NULL) {
        return -1;
    }
    if (server->server_socket != -1) {
        close(server->server_socket);
        server->server_socket = -1;
    }
    if (server->mb_mapping != NULL) {
        modbus_mapping_free(server->mb_mapping);
        server->mb_mapping = NULL;
    }
    if (server->ctx != NULL) {
        modbus_free(server->ctx);
        server->ctx = NULL;
    }
    return 0;
}


void poll_update_data() {
    while (1) {
        // to do
    }
}

void poll_error_state() {
    while (1) {
        // to do
    }
}

#endif