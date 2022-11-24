#include "../src/hl.h"

#include <stdio.h>
#include <stdlib.h>
#include "../lib/hl_utlis.h"

// Res hello(Req r) {
//     log("Hello 1");
//     return (Res){404, "<h1>Not Found!</h1>"};
// }

// Res hello2(Req r) {
//     log("Hello 2");
//     return (Res){500, "<h1>Server Error!</h1>"};
// }

// Res hello3(Req r) {
//     log("Hello 3");
//     return (Res){403, "<h1>u dont have perm!</h1>"};
// }

Res Index(Req r) {
    return (Res){200, HL_Format("<h1>Method: %s</h1>", r.method)};
}

Res Route(Req r) {
    return (Res){200, HL_Format("<h1>where are im?: %s</h1>", r.route)};
}

int main(void) {
    HL app;
    HL_Default(&app);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // HL_CreateServer(&app, "127.0.0.1", 8001);                                                                  //
    //                                                                                                            //
    // //HL_free(&app);                                                                                           //
    //                                                                                                            //
    // // int ind = HL_Register_Callback(&app, Index);                                                            //
    // // int ind2 = HL_Register_Callback(&app, (callback_res_t)hello2);                                          //
    // // int ind3 = HL_Register_Callback(&app, (callback_res_t)hello3);                                          //
    //                                                                                                            //
    // // HL_Get(&app, "/user", exmp);                                                                            //
    //                                                                                                            //
    // Req ex = (Req){"POST", "/user",3, (struct Header){{"Host:", "Accept-Language:"}, {"127.0.0.1", "EN"}, 3}}; //
    //                                                                                                            //
    // // Res res1 = HL_Get_Callback(app, ind)(ex);                                                               //
    // // Res res2 = HL_Get_Callback(app, ind2)(ex);                                                              //
    // // Res res3 = HL_Get_Callback(app, ind3)(ex);                                                              //
    //                                                                                                            //
    // // char* string = HL_Format("FORMAT STRING %s", res1.res);                                                 //
    //                                                                                                            //
    // // log(string);                                                                                            //
    //                                                                                                            //
    // // log(res1.res);                                                                                          //
    //                                                                                                            //
    // // log(res2.res); // NULL                                                                                  //
    // // log(res3.res); // NULL                                                                                  //
    //                                                                                                            //
    // HL_Get(&app, "/", Index);                                                                                  //
    // HL_Get(&app, "/route", Route);                                                                             //
    //                                                                                                            //
    // // sm_get(app.routes, "GET /", tst, sizeof(tst));                                                          //
    //                                                                                                            //
    // // int yum = atoi(tst);                                                                                    //
    //                                                                                                            //
    // // Res test = HL_Get_Callback(app, yum)(ex);                                                               //
    //                                                                                                            //
    // // log(HL_Format("RES: %s STATUS: %d", test.res, test.status));                                            //
    //                                                                                                            //
    // HL_Listen(&app);                                                                                           //
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    HL_Router rou;
    HL_Router_New(&rou);

    HL_Router_Put(&rou, "/router1", 1);
    HL_Router_Put(&rou, "/router2", 2);
    HL_Router_Put(&rou, "/router3", 3);

    int a = HL_Router_Get(&rou, "/router1").result;

    printf("%d\n", a);

    exit(EXIT_SUCCESS);
}
