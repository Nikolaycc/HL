#include "../src/hl.h"

#include <stdio.h>

void hello() {
    log("Hello 1");
}

void hello2() {
    log("Hello 2");
}

void hello3() {
    log("Hello 3");
}

int main(void) {

    HL http;
    HL_Default(&http);

    HL_CreateServer(&http, "127.0.0.1", 8000);
    
    int ind = HL_Register_Callback(&http, (callback_void_t)hello);
    int ind2 = HL_Register_Callback(&http, (callback_void_t)hello2);
    int ind3 = HL_Register_Callback(&http, (callback_void_t)hello3);

    //HL_Get(&http, "/user", exmp);x

    HL_Get_Callback(http.callback_func_ptrs, ind, callback_void_t)();
    HL_Get_Callback(http.callback_func_ptrs, ind2, callback_void_t)();
    HL_Get_Callback(http.callback_func_ptrs, ind3, callback_void_t)();

    log("Hello World");

    HL_Listen(&http);
    //HL_free(&http);
    
    exit(EXIT_SUCCESS);
}
