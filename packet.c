#include "packet.h"
#include <stdlib.h>
#include <string.h>

void* malloc_packet(uint8_t type, void* body, uint32_t size)
{
    uint8_t* packet = (uint8_t*)malloc(sizeof(uint8_t) + sizeof(uint32_t) + size);
    memset(packet, type, 1);
    memcpy(packet + 1, &size, 4);
    if (size != 0)
        memcpy(packet + 1 + 4, body, size);
    return packet;
}

void free_packet(void* packet)
{
    free(packet);
}