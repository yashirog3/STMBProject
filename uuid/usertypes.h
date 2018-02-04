#ifndef USERTYPES_H
#define USERTYPES_H
#define uint64 unsigned long
#define uint32 unsigned long
#define uint16 unsigned short
#define uint8 unsigned char
#define I64(C) C##LL
#define UUIDS_PER_TICK 1024
#define LOCK
#define UNLOCK
#ifdef WININC
#define COMANDO "ipconfig /all"
#else
#define COMANDO "ifconfig"
#endif

typedef struct{

    uint8 node[6];

}unode;

#endif
