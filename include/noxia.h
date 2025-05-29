#ifndef NOXIA_H
#define NOXIA_H
#include "noxia/typedef.h"

#ifdef _WIN64
#include "noxia/win/syswindow.h"
#endif

nContext *nContextCreate();
void nContextEvents(nContext *context);
void nContextClose(nContext *context);

#endif // NOXIA_H
