#ifndef include_protocol_scpi_protocol_h
#define include_protocol_scpi_protocol_h

#define __usbtmc

#if defined(__ieee488)
#include <include/protocol/scpi_transport/ieee488.h>
#elif defined(__usbtmc)
#include <include/protocol/scpi_transport/usbtmc.h>
#elif defined(__rs232)
#include <include/protocol/scpi_transport/rs232.h>
#elif defined(__vxi11)
#include <include/protocol/scpi_transport/vxi11.h>
#elif defined(__lxi)
#include <include/protocol/scpi_transport/lxi.h>
#else
#error "No SCPI transport layer defined"
#endif

#endif /* include_protocol_scpi_protocol_h */