#ifndef HL_UTLIS_H
#define HL_UTLIS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define Ok 0
#define Err 1

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
void HL_Router_Realloc(HL_Router*, uint16_t);

Resu8 HL_Router_Get(const HL_Router*, const char*);
Resu8 HL_Router_Put(HL_Router*, const char*, CallBackIdx);

#endif
