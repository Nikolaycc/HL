#ifndef HL_UTLIS_H
#define HL_UTLIS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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
#define MAX_HEAD 30
#define DEFAULT_HEAD 10
#define MAX_TEXT_BUFFER_LENGTH 1024
#define MAX_TEXTFORMAT_BUFFERS 4
#define MAX_REQ_SIZE 35

#define HTTPV 1.1

#define WSPACE " "
#define NLINE "\n"

#define ERR 1
#define OK 0

typedef enum {
    Err = ERR,
    Ok = OK,
} Result;


#define HL_DEFINE_RESULT(T, E, NAME) \
typedef struct { \
  uint8_t success; \
  union { \
    T result; \
    E error; \
  }; \
} NAME;

HL_DEFINE_RESULT(uint8_t, uint8_t, Resu8);
HL_DEFINE_RESULT(uint8_t, char*, ResStrErr);
HL_DEFINE_RESULT(char*, char*, ResStr);
HL_DEFINE_RESULT(char*, uint8_t, Resu8Err);

typedef uint16_t CallBackIdx;

typedef struct {
    char* key;
    CallBackIdx rou;
} HL_Route;

typedef struct {
    HL_Route* map;
    uint16_t len;
    uint16_t cap;
} HL_Router;

void HL_Router_New(HL_Router*);
void HL_Router_Clear(HL_Router*);

Resu8 HL_Router_Get(const HL_Router*, const char*);
Resu8 HL_Router_Put(HL_Router*, const char*, CallBackIdx);

#endif
