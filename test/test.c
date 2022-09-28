#include "../src/hl.h"

#include <stdio.h>

void hello() {
    int a = 10 + 2 + 56;
    printf("HELLO, WORLD! %d\n", a);
}

void hello2() {
    int a = 10 + 22 + 56;
    printf("HELLO! %d\n", a);
}

void hello3() {
    int a = 10 + 6 + 56;
    printf("WORLD! %d\n", a);
}

int main(void) {

    HL http;
    HL_Default(&http);

    HL_CreateServer(&http, "127.0.0.1", 8000);
    
    int ind = HL_Register_Callback(&http, (callback_void_t)hello);
    int ind2 = HL_Register_Callback(&http, (callback_void_t)hello2);
    int ind3 = HL_Register_Callback(&http, (callback_void_t)hello3);

    HL_Get_Callback(http.callback_func_ptrs, ind, callback_void_t)();
    HL_Get_Callback(http.callback_func_ptrs, ind2, callback_void_t)();
    HL_Get_Callback(http.callback_func_ptrs, ind3, callback_void_t)();

    log("Hello World");
    
    printf("%d, %d\n", http.sfd, ind);

    //panic("not bound a[1]");
    
    exit(EXIT_SUCCESS);
}
