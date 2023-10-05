#include "packet.h"
#include <stdlib.h>
#include <string.h>

void* malloc_packet(uint8_t type, void* body, uint32_t body_size, uint32_t* packet_size)
{
    uint8_t* packet = (uint8_t*)malloc(sizeof(uint8_t) + sizeof(uint32_t) + body_size);
    memset(packet, type, 1);
    memcpy(packet + 1, &body_size, 4);
    if (body_size != 0)
        memcpy(packet + 1 + 4, body, body_size);
    *packet_size = sizeof(uint8_t) + sizeof(uint32_t) + body_size;
    return packet;
}

void free_packet(void* packet)
{
    free(packet);
}