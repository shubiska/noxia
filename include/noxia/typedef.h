#ifndef NOXIATYPEDEF_H
#define NOXIATYPEDEF_H

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

typedef struct {
    uint32 x, y;
} u32Vector2;

typedef struct {
    int32 x, y;
} i32Vector2;

#define nClamp(x, low, high) ((x) < (low) ? (low) : ((x) > (high) ? (high) : (x)))
#define nAbs(x) ((x) < 0 ? -(x) : (x))

#endif // NOXIATYPEDEF_H
