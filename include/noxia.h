#ifndef NOXIA_H
#define NOXIA_H

#include "noxia/typedef.h"

typedef struct nContext nContext;

nContext *nContextCreate();
void nContextEvents(nContext *context);
void nContextClose(nContext *context);
void nContextCenter(nContext *context);

void nContextSetTitle(nContext *context, char *title);
void nContextSetSize(nContext *context, uint32 width, uint32 height);
void nContextSetPosition(nContext *context, uint32 x, uint32 y);
void nContextSetRate(nContext *context, uint32 rate);
void nContextSetVsync(nContext *context, bool vsync);

// TODO:
//  char* nContextGetTitle(nContext *context);
//  u32Vector2 nContextGetSize(nContext *context);
//  u32Vector2 nContextGetPosition(nContext *context);
//  uint32 nContextGetRate(nContext *context);
//  bool nContextGetVsync(nContext *context);
//  u32Vector2 nContextGetDisplaySize(nContext *context);
//  uint32 nContextGetDisplayRate(nContext *context);

#endif // NOXIA_H
