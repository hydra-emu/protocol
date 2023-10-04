// Hydra protocol packet definitions
// See README.md for more information
// This file makes heavy use of X macros in order to reduce code duplication
// and make additions to the protocol easier
// Viewing a preprocessed version of this file is recommended
// You can create one using gcc -E packet.h

#include <stdint.h>

#define HC_PROTOCOL_VERSION_MAJOR 1
#define HC_PROTOCOL_VERSION_MINOR 0
#define HC_PROTOCOL_VERSION ((HC_PROTOCOL_VERSION_MAJOR << 8) | (HC_PROTOCOL_VERSION_MINOR))

typedef enum
{
    #define X(name, args, type) HC_PACKET_TYPE_##name = type,
    #include "client.def"
    #undef X
} hc_client_packet_type_e;

#define X(name, args, type) + 1
inline const int HC_CLIENT_PACKETS_SIZE = 0
#include "client.def"
;
#undef X

typedef enum
{
    #define X(name, args, type) HC_PACKET_TYPE_##name = type,
    #define X_UNKNOWN_BODY(name, type) HC_PACKET_TYPE_##name = type,
    #include "server.def"
    #undef X
    #undef X_UNKNOWN_BODY
} hc_server_packet_type_e;

#define X(name, args, type) + 1
#define X_UNKNOWN_BODY(name, type) + 1
inline const int HC_SERVER_PACKETS_SIZE = 0
#include "server.def"
;
#undef X
#undef X_UNKNOWN_BODY

#define X_RESPONSES \
    X(OK, 0x00) \
    X(ERROR, 0x01)

typedef enum
{
    #define X(name, type) HC_RESPONSE_##name = type,
    X_RESPONSES
    #undef X
} hc_response_e;

#define X(name, type) + 1
inline const int HC_RESPONSES_SIZE = 0 X_RESPONSES;
#undef X

void* malloc_packet(uint8_t type, void* body, uint32_t size);
void free_packet(void* packet);

#pragma pack(push, 1)
#define X(name, args, type) typedef struct { args } hc_client_##name##_t;
#define Y(type, name) type name;
#define CHAR(name, size) char name[size];
#include "client.def"
#undef X
#define X(name, args, type) typedef struct { args } hc_server_##name##_t;
#define X_UNKNOWN_BODY(name, type) typedef void* hc_server_##name##_t;
#include "server.def"
#undef X
#undef X_UNKNOWN_BODY
#undef Y
#undef CHAR
#pragma pack(pop)

// Size asserts
#define X(name, args, type) \
    static_assert(sizeof(hc_client_##name##_t) == 0 args, "Invalid size for hc_client_" #name "_t");
#define Y(type, name) + sizeof(type)
#define CHAR(name, size) + size
#include "client.def"
#undef X
#define X(name, args, type) \
    static_assert(sizeof(hc_server_##name##_t) == 0 args, "Invalid size for hc_server_" #name "_t");
#define X_UNKNOWN_BODY(name, type)
#include "server.def"
#undef X
#undef X_UNKNOWN_BODY
#undef Y
#undef CHAR

#undef X_HC_CLIENT_PACKETS
#undef X_HC_SERVER_PACKETS