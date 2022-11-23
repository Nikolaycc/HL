#include "hl.h"

void HL_Default(HL* h) {
    h->sfd = 2;
    h->ser_len = 1;
    h->routes = sm_new(MAX_ROUTES);
    if (h->routes == NULL)
       panic("routes == NULL");
}

Result HL_CreateServer(HL* h, const char* ip, int port) {
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
    return Ok;
}

Result HL_Get(HL* h, const char* route, Res (callback)()) {
    int i = HL_Register_Callback(h, callback);
    sm_put(h->routes, HL_Format("GET %s", route), HL_Format("%d", i));

    return Ok;
}

Result HL_Post(HL* h, const char* route, Res (callback)()) {
    int i = HL_Register_Callback(h, callback);
    sm_put(h->routes, HL_Format("POST %s", route), HL_Format("%d", i));    
    
    return Ok;
}

Result HL_Delete(HL* h, const char* route, Res (callback)()) {
    int i = HL_Register_Callback(h, callback);
    sm_put(h->routes, HL_Format("DELETE %s", route), HL_Format("%d", i));

    return Ok;
}

Result HL_Put(HL* h, const char* route, Res (callback)()) {
    int i = HL_Register_Callback(h, callback);
    sm_put(h->routes, HL_Format("PUT %s", route), HL_Format("%d", i));

    return Ok;
}

void HL_Listen(HL* h) {
    struct sockaddr_in clitmp = {0};

    if  (listen(h->sfd, 10) == -1) {
        panic("listen");
    }

    socklen_t siz = sizeof(clitmp);
    h->lsnb = 1;
    
    while(h->lsnb) {
        log("(Waiting for new connection..)");

        if ((h->cfd = accept(h->sfd, NULL, NULL))<0)
        {
            panic("in accept");
        }

        int rtmp = recv(h->cfd, h->buffer, MAX_BUFFER_SIZE, 0);

        if (rtmp > 0 ) {
            Req reqllp;
            reqllp = HL_Parse_Req(h->buffer);
            log(HL_Format("(Req) Method: %s Route: %s Size: %d", reqllp.method, reqllp.route, reqllp.size));
            Res resllp = HL_Check_Route(h, reqllp);
            char* exm = HL_Format("HTTP/1.1 %d ok\nContent-Type: text/html\nContent-Length: 20\n\n%s", resllp.status, resllp.res);
            log(HL_Format("(Res) %s\n", exm));
            send(h->cfd, exm, strlen(exm), 0);
        }
        else if (rtmp == 0) {
            log("connection closing...");
        } else {
            close(h->cfd);           
        }
    }
}

Req HL_Parse_Req(char *bufsr) {
    char *ptr = strtok(bufsr, WSPACE);
    char *buftmp[MAX_REQ_SIZE]; int ind = 0;
	while (ptr != NULL) {
        buftmp[ind] = ptr;
		ptr = strtok(NULL, WSPACE); ind++;
    }
    
    return (Req){buftmp[0], buftmp[1], ind-1, (struct Header){{"Host:", "Accept-Language:"}, {"127.0.0.1", "EN"}, 3}};
}

Res NotFound(Req r) {
    return (Res){404, "<p>Not found</p>"};
}

Res HL_Check_Route(const HL *h, Req r) {
    char *tst;
    if (!sm_exists(h->routes, HL_Format("%s %s", r.method, r.route))) {
        sm_get(h->routes, HL_Format("%s %s", r.method, r.route), tst, sizeof(tst));
    } else {
        tst = "404";
    }
    log(HL_Format("TST = %s", tst));
    if (strcmp(tst, "404")) {
        log("ret notf");
        return NotFound(r);
    }
    log("next");
    Res res = HL_Get_Callback(h, atoi(tst))(r);
    log("res ret");
    return res;
}

void HL_free(HL* h) {
    close(h->sfd);
    close(h->cfd);
    free(h);
}

int HL_Register_Callback(HL* h, callback_res_t clptr) {
    int indx = clindex;
    h->cl[clindex] = clptr;
    if (h->cl[clindex] == NULL)
       panic("callback == NULL");
    clindex += 1;

    return indx;
}

callback_res_t HL_Get_Callback(const HL *h, int e) { return (callback_res_t)h->cl[e]; }

char* HL_Format(const char *text, ...)
{
    static char buffers[MAX_TEXTFORMAT_BUFFERS][MAX_TEXT_BUFFER_LENGTH] = { 0 };
    static int index = 0;

    char *currentBuffer = buffers[index];
    memset(currentBuffer, 0, MAX_TEXT_BUFFER_LENGTH);

    va_list args;
    va_start(args, text);
    vsnprintf(currentBuffer, MAX_TEXT_BUFFER_LENGTH, text, args);
    va_end(args);

    index += 1;
    if (index >= MAX_TEXTFORMAT_BUFFERS) index = 0;

    return currentBuffer;
}
