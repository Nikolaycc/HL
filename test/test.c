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

Res Index() {
    return (Res){200, "Hello, World!"};
}

int main(void) {
    HL app;
    HL_Default(&app);

    HL_CreateServer(&app, "127.0.0.1", 8000);
    
    int ind = HL_Register_Callback(&app, Index);
    int ind2 = HL_Register_Callback(&app, (callback_res_t)hello2);
    int ind3 = HL_Register_Callback(&app, (callback_res_t)hello3);

    //HL_Get(&app, "/user", exmp);

    Res res1 = HL_Get_Callback(app.cl, ind)();
    Res res2 = HL_Get_Callback(app.cl, ind2)();
    Res res3 = HL_Get_Callback(app.cl, ind3)();

    log(res1.res);

    log(res2.res); // NULL
    log(res3.res); // NULL

    HL_Listen(&app);

    //HL_free(&app);
    
    exit(EXIT_SUCCESS);
}
