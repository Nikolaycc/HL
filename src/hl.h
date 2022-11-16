#ifndef HL_H
#define HL_H

#pragma once

// include std libs
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

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

#define MAX_ROUTES 125
#define MAX_SIZE 257
#define MAX_BUFFER_SIZE 1025
#define MAX_HEAD 55
#define DEFAULT_HEAD 10
#define MAX_TEXT_BUFFER_LENGTH 1024
#define MAX_TEXTFORMAT_BUFFERS 4

#define HTTPV 1.1

// err - ok 
#define ERR 1
#define OK 0

typedef enum {
    Err = ERR,
    Ok = OK,
} Result;

// callback store index
static int clindex = 0;

typedef struct {
    char* body;
} Req;

typedef struct {
    size_t status;
    char* res;
} Res;

typedef struct {
    char** head;
    Res res;
} Resp;

// Callback ptr type
typedef Res (*callback_res_t)(void);

// HL struct 
typedef struct {
    int sfd;
    int cfd;
    int lsnb;
    char buffer[MAX_BUFFER_SIZE];
    struct sockaddr_in ser;
    socklen_t ser_len;
    StrMap *routes;
    callback_res_t cl[MAX_ROUTES];
} HL;

// Server Funcs
void HL_Default(HL* h);
Result HL_CreateServer(HL* h, const char* ip, int port); // Create Server (struct hl*, char* ip, int port)
void HL_Listen(HL* h); // Listen Requests

// Route Methods Funcs
Result HL_Get(HL* h, const char* route, Res (callback)()); // Get Method (stuct hl*, char* Route, Res Callback)
Result HL_Post(HL* h, const char* route, Res (callback)()); // Post Method (stuct hl*, char* Route, Res Callback)
Result HL_Delete(HL* h, const char* route, Res (callback)()); // Delete Method (stuct hl*, char* Route, Res Callback)
Result HL_Put(HL* h, const char* route, Res (callback)()); // Put Method (stuct hl*, char* Route, Res Callback)

int HL_Parse_Req(); // { PrivateFuncs }
int HL_Parse_Res(); // { PrivateFuncs }
int HL_Parse_Body(); // { PrivateFuncs }

void HL_free(HL* h);

// Register Callback Funcs                                                                                              
int HL_Register_Callback(HL* h, callback_res_t clptr); // Register CallBack (struct hl*, void Callback) return Index { PrivateFuncs }
callback_res_t HL_Get_Callback(HL h, int e);  // GET CALLBACK (h.callback_func_ptrs, int index, type)

char* HL_Format(const char *text, ...);

#endif
