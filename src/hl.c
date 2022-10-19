 #include "hl.h"

void HL_Default(HL* h) {
    h->sfd = 2;
    h->ser_len = 1;
    h->routes = sm_new(MAX_ROUTES);
    if (h->routes == NULL)
       panic("routes == NULL");
}

int HL_CreateServer(HL* h, char* ip, int port) {
    struct sockaddr_in socktmp = {0};
    socktmp.sin_family = AF_INET;
    socktmp.sin_port = htons(port);
    inet_aton(ip, (struct in_addr*)&socktmp.sin_addr.s_addr);
    
    h->sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > h->sfd)
       panic("| [NULL] Socket Error");

    
    if (0 > bind(h->sfd, (struct sockaddr*)&socktmp, sizeof(socktmp)))
       panic("| [NULL] Bind Error");

    h->ser = socktmp;
    return OK;
}

int HL_Get(HL* h, char* route, void (callback)()) {
    return OK;
}

int HL_Post(HL* h, char* route, void (callback)()) {
    return OK;
}

int HL_Delete(HL* h, char* route, void (callback)()) {
    return OK;
}

int HL_Put(HL* h, char* route, void (callback)()) {
    return OK;
}

void HL_Listen(HL* h) {
    struct sockaddr_in clitmp = {0};

    if (listen(h->sfd, 10) == -1) {
        panic("listen");
    }

    socklen_t siz = sizeof(clitmp);
    h->lsnb = 1;
    
    while(h->lsnb) {
        log("+++++++ Waiting for new connection ++++++++\n\n");

        if ((h->cfd = accept(h->sfd, NULL, NULL))<0)
        {
            panic("in accept");
        }

        int rtmp = recv(h->cfd, h->buffer, MAX_BUFFER_SIZE, 0);

        if (rtmp > 0 ) {
            printf("START\n%s\nEND\n", h->buffer);
            char* exm = "<h1>Hello, World!</h1>";
            send(h->cfd, exm, strlen(exm), 0);
        }
        else if (rtmp == 0) {
            log("connection closing...");
        } else {
            close(h->cfd);           
        }
    }
}

void HL_free(HL* h) {
    close(h->sfd);
    close(h->cfd);
}

int HL_Register_Callback(HL* h, callback_void_t clptr) {
    int indx = clindex;
    h->callback_func_ptrs[clindex] = clptr;
    if (h->callback_func_ptrs[clindex] == NULL)
       panic("callback == NULL");
    clindex += 1;

    return indx;
}
