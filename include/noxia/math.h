#ifndef NOXIAMATH_H
#define NOXIAMATH_H

#include "../noxia.h"

uint64 nClampU(uint64 val, uint64 min, uint64 max);
int64 nClampI(int64 val, int64 min, int64 max);
float nClampF(float val, float min, float max);

uint64 nClampU(uint64 val, uint64 min, uint64 max) {
    if (val < min) {
        return min;
    }
    if (val > max) {
        return max;
    }
    return val;
}

int64 nClampI(int64 val, int64 min, int64 max) {
    if (val < min) {
        return min;
    }
    if (val > max) {
        return max;
    }
    return val;
}

float nClampF(float val, float min, float max) {
    if (val < min) {
        return min;
    }
    if (val > max) {
        return max;
    }
    return val;
}

#endif // NOXIAMATH_H
