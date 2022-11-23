#include "hl_utlis.h"

void HL_Router_New(HL_Router* rou) {
    rou->len = 0;
    rou->cap = 1;
    rou->map = (HL_Route*) calloc(rou->cap, sizeof(HL_Route));
}

void HL_Router_Clear(HL_Router* rou) {
    free(rou->map);
    HL_Router_New(rou);
}

void HL_Router_Realloc(HL_Router* rou, uint16_t size) {
    rou->map = (HL_Route*) realloc(rou->map, size * sizeof(HL_Route));
}

Resu8 HL_Router_Get(const HL_Router* rou, const char* key) {
    Resu8 val;

    for (uint16_t i = 0; i < rou->len -1; i++) {
        if (rou->map[i].key == key) {
            val = (Resu8) {Ok, .result = rou->map[i].rou};
            break;
        }
    }

    if (val.success == Err) {
        return (Resu8) {Err, .error = 1};
    }

    return (Resu8) {Ok, .result = val.result};
}
