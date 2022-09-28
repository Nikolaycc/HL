#include "hl.h"

void HL_Default(HL* h) {
    printf("world\n");
    h->sfd = 2;
    h->ser_len = 1;
    h->routes = sm_new(MAX_ROUTES);
    if (h->routes == NULL)
       panic("routes == NULL");
}

int HL_CreateServer(HL* h, char* ip, int port) {
    return OK;
}

int HL_Register_Callback(HL* h, callback_void_t clptr) {
    int tmp = clindex;
    h->callback_func_ptrs[clindex] = clptr;
    if (h->callback_func_ptrs[clindex] == NULL)
       panic("callback == NULL");
    clindex += 1;

    return tmp;
}
