#include "../src/hl.h"

#include <stdio.h>
#include <stdlib.h>

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

//    HL_Get(&app, "/user", exmp);

    Res res1 = HL_Get_Callback(app, ind)();
    Res res2 = HL_Get_Callback(app, ind2)();
    Res res3 = HL_Get_Callback(app, ind3)();

    char* string = HL_Format("AYEO %s hello\n", res1.res);

    log(string);

    log(res1.res);

    log(res2.res); // NULL
    log(res3.res); // NULL

    HL_Get(&app, "/", Index);

    char tst[20];

    sm_get(app.routes, "/", tst, 2);

    log(HL_Format("sm_get return -> %s", tst));

    int yum = atoi(tst);

    log(HL_Format("yum = %d", yum));

    Res test = HL_Get_Callback(app, yum)();

    log(HL_Format("RES: %s STATUS: %d", test.res, test.status));

    HL_Listen(&app);

    //HL_free(&app);
    
    exit(EXIT_SUCCESS);
}
