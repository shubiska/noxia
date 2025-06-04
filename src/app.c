#include "../include/noxia.h"

int32 main() {
    nContext *context = nContextCreate();
    if (context == null) {
        return 1;
    }

    nContextEvents(context);

    return 0;
}
