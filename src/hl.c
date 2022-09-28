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
    struct sockaddr_in socktmp = {0};
    struct sockaddr_in cli = {0};
    socktmp.sin_family = AF_INET;
    socktmp.sin_port = htons(port);
    inet_aton(ip, (struct in_addr*)&socktmp.sin_addr.s_addr);
    
    h->sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > h->sfd)
       panic("sfd < 0 | [NULL] Socket Error");

    
    if (0 > bind(h->sfd, (struct sockaddr*)&socktmp, sizeof(socktmp)))
       panic("bind < 0 | [NULL] Bind Error");
       
    return OK;
}

int HL_Listen(HL* h) {
    return OK;
}

int HL_Register_Callback(HL* h, callback_void_t clptr) {
    int indx = clindex;
    h->callback_func_ptrs[clindex] = clptr;
    if (h->callback_func_ptrs[clindex] == NULL)
       panic("callback == NULL");
    clindex += 1;

    return indx;
}
