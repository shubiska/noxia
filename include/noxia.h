#ifndef NOXIA_H
#define NOXIA_H

#define null 0
#define false 0
#define true 1
typedef unsigned char bool;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

typedef struct nContext nContext;

nContext *nContextCreate();
void nContextEvents(nContext *context);
void nContextClose(nContext *context);
void nContextSetTitle(nContext *context, char *title);
void nContextSetSize(nContext *context, uint32 width, uint32 height);
void nContextSetPosition(nContext *context, uint32 x, uint32 y);
void nContextCenter(nContext *context);
void nContextSetRate(nContext *context, uint32 rate);
void nContextSetVsync(nContext *context, bool vsync);

#endif // NOXIA_H
