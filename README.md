# The hydra communication protocol

The hydra communication protocol provides a way for communicating with a hydra core
remotely. This will be used with stuff like [discord-plays](https://github.com/OFFTKP/discord-plays)
or the Wii frontend for heavier cores like Panda3DS. Allows for using an emulator on a
less powerful device or on environments where it would be otherwise
impossible to use one (such as a Discord chat room).

HTTP was used in the past, but in an environment with tens of requests per second, every millisecond matters thus
this binary format was developed.

Examples of servers using this protocol:
- [hydra](https://github.com/hydra-emu/hydra)

Examples of clients using this protocol:
- [hydra/wii](https://github.com/hydra-emu/hydra/tree/master/wii)
- [discord-plays](https://github.com/OFFTKP/discord-plays)

### Header

A packet will always have its first byte define the packet type, followed by a size
as a u32 integer in little endian, followed by N bytes where N = size.

Example client->server packet:

```
+------+--------+------------------------+
| 0x04 | 131768 | <131768 bytes of data> |
+------+--------+------------------------+
```

Response packets (server->client) will always have the MSB of the packet type set

Unknown packet types by default will be ignored by the server. Officially supported packets are
guaranteed to never have the LSB set, in case you want to add your own.

Packets are always tightly packed.