#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>

#include <stdlib.h>
#include <string.h>

#include "common/callback.h"
#include "common/minIni.h"

#define MAJOR_VER 0
#define MINOR_VER 3

PSP_MODULE_INFO("hello-raehik", PSP_MODULE_USER, MAJOR_VER, MINOR_VER);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);
PSP_HEAP_SIZE_MAX();

//#define INI_FILE "ms0:/initest-raehik.ini"
#define INI_FILE "ms0:/initest-raehik.ini"
#define printf pspDebugScreenPrintf

char *get_test_value() {
    // minIni {{{
    //char test_value[32];
    //int rc = ini_gets(NULL, "test", NULL, test_value, sizeof(test_value), INI_FILE);
    //if (rc != 0) { strcpy(test_value,  "Couldn't read..."); }
    // }}}
    // basic {{{
    SceIoStat info;
    sceIoGetstat(INI_FILE, &info);
    char *test_value = malloc(info.st_size + 1);
    SceUID f = sceIoOpen(INI_FILE, PSP_O_RDONLY, 0777);
    sceIoRead(f, test_value, info.st_size);
    sceIoClose(f);
    test_value[info.st_size] = '\0';
    // }}}

    return test_value;
}

int main() {
    pspDebugScreenInit();
    setupExitCallback();

    char *test_value = get_test_value();

    int running = isRunning();
    while (running) {
        sceDisplayWaitVblankStart();
        //pspDebugScreenClear();
        pspDebugScreenSetXY(0, 0);
        printf("Hello raehik!\n");
        sceDisplayWaitVblankStart();
        //printf("test value: %s", test_value);
        printf("test value: asdasdkjlasdlajkdslk jasdl kajsd WHY IS THIS HAPPENING\n");
        printf("1234567891123456789212345678931234567894123456789512345678961234567897123456789812345678991234567890");

        running = isRunning();
    }

    free(test_value);
    sceKernelExitGame();
    return 0;
}
