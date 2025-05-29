#include "../include/noxia.h"
#include <stdio.h>

int32 main() {
    nContext *context = nContextCreate();
    if (context == null) {
        return 1;
    }

    printf("Hello Noxia\n");

    nContextEvents(context);

    return 0;
}
