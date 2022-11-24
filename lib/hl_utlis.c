#include "hl_utlis.h"
#include <stdio.h>

void HL_Router_New(HL_Router* rou) {
    rou->len = 0;
    rou->cap = 1;
    rou->map = (HL_Route*) malloc(rou->cap * sizeof(HL_Route));
}

void HL_Router_Clear(HL_Router* rou) {
    free(rou->map);
    HL_Router_New(rou);
}

Resu8 HL_Router_Get(const HL_Router* rou, const char* key) {
    Resu8 val;

    for (uint16_t i = 0; i < rou->len; i++) {
        if (strcmp(key, rou->map[i].key) == 0) {
            val = (Resu8) {Ok, .result = rou->map[i].rou};
            printf("MATCH IDX: %d", val.result);
            break;
        } else {
            val = (Resu8) {Err, .error = 1};
        }
        printf(".");
    }

    if (val.success == Err) {
        return (Resu8) {Err, .error = 1};
    }

    return (Resu8) {Ok, .result = val.result};
}

Resu8 HL_Router_Put(HL_Router* rou, const char* key, CallBackIdx val) {
    rou->cap += 1;
    rou->map[rou->len].key = (char*) key;
    rou->map[rou->len].rou = val;
    rou->len += 1;

    return (Resu8) {Ok, .result = val};
}
