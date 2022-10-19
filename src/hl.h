#ifndef HL_H
#define HL_H

// include std libs
#include <stdio.h>
#include <stdlib.h>

#include <string.h>	// strlen
#include <sys/socket.h> // socket 
#include <arpa/inet.h> // ip family
#include <netinet/in.h> // inet_aton
#include <unistd.h> // mem
#include <time.h> // time
#include "../lib/strmap.h" // sm

#define panic(_msg_) { \
    time_t t = time(NULL); \
    struct tm tm = *localtime(&t); \
    fprintf(stderr, "panic: [%02d:%02d:%02d] (%s:%d)\n    ->\t %s\n", tm.tm_hour, tm.tm_min, tm.tm_sec, __FILE__, __LINE__, (_msg_)); \
    exit(1); \
}

#define log(_msg_) {\
    time_t t = time(NULL); \
    struct tm tm = *localtime(&t); \
    fprintf(stdout, "log: [%02d:%02d:%02d] (%s:%d)\n    ->\t %s\n", tm.tm_hour, tm.tm_min, tm.tm_sec, __FILE__, __LINE__, (_msg_)); \
}

#define HL_Get_Callback(h, e, T) ((T)h[e]) // GET CALLBACK (h.callback_func_ptrs, int index, type)

#define MAX_ROUTES 125
#define MAX_SIZE 257
#define MAX_BUFFER_SIZE 1025
#define MAX_HEAD 55

// err | ok 
#define ERR 1
#define OK 0

// callback store index
static int clindex = 0;

// Callback ptr type
typedef void (*callback_void_t)(void);

struct Header {
    char* head[MAX_HEAD];
};

typedef struct {
    struct Header h;
    char* body;
} Req;

typedef struct {
    struct Header h;
    char* body;
} Res;

// HL struct 
typedef struct {
    int sfd;
    int cfd;
    int lsnb;
    char buffer[MAX_BUFFER_SIZE];
    struct sockaddr_in ser;
    socklen_t ser_len;
    StrMap *routes;
    callback_void_t callback_func_ptrs[MAX_ROUTES];
} HL;

// Server Funcs
void HL_Default(HL* h);
int HL_CreateServer(HL* h, char* ip, int port); // Create Server (struct hl*, char* ip, int port)
void HL_Listen(HL* h); // Listen Requests

// Route Methods Funcs
int HL_Get(HL* h, char* route, void (callback)()); // Get Method (stuct hl*, char* Route, void Callback)
int HL_Post(HL* h, char* route, void (callback)()); // Post Method (stuct hl*, char* Route, void Callback)
int HL_Delete(HL* h, char* route, void (callback)()); // Delete Method (stuct hl*, char* Route, void Callback)
int HL_Put(HL* h, char* route, void (callback)()); // Put Method (stuct hl*, char* Route, void Callback)

int HL_Parse_Req(); // { PrivateFuncs }
int HL_Parse_Res(); // { PrivateFuncs }
int HL_Parse_Data(); // { PrivateFuncs }

void HL_free(HL* h);

// Register Callback Funcs
int HL_Register_Callback(HL* h, callback_void_t clptr); // Register CallBack (struct hl*, void Callback) return Index[CALLback] { PrivateFuncs }

#endif
