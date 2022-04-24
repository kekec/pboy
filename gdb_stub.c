#include <stdio.h>
#include "gdb_stub.h"
#include "minigdbstub.h"
#include "mmu.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#define REG_COUNT 2
int connfd;

typedef struct {
    int regfile[REG_COUNT];
    // ...
} myCustomData;

void gdbServerInit()
{
  int listenfd = 0;
  struct sockaddr_in serv_addr;
  memset(&serv_addr, '0', sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(5000);

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
  listen(listenfd, 1);
  printf("Waiting for GDB connect on port 5000\n");
  connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
}

void gdbserverCall(myCustomData *myCustomData) {
    // Update regs
    int regs[REG_COUNT];
    for (int i=0; i<REG_COUNT; ++i) {
        regs[i] = myCustomData->regfile[i];
    }

    // Create and write values to minigdbstub process call object
    mgdbProcObj mgdbObj = {0};
    mgdbObj.regs = (char*)regs;
    mgdbObj.regsSize = sizeof(regs);
    mgdbObj.regsCount = REG_COUNT;
    mgdbObj.opts.o_signalOnEntry = 0;
    mgdbObj.opts.o_enableLogging = 1;
    mgdbObj.usrData = (void*)myCustomData;

    // Call into minigdbstub
    minigdbstubProcess(&mgdbObj);
    return;
}

void initGdb()
{
  gdbServerInit();
  myCustomData data;
  gdbserverCall(&data);
}

// User-defined minigdbstub handlers
static void minigdbstubUsrWriteMem(size_t addr, unsigned char data, void *usrData) {
    myCustomData *dataHandle = (myCustomData*)usrData;
    mmuWriteMem(addr, data);
}

static unsigned char minigdbstubUsrReadMem(size_t addr, void *usrData) {
    myCustomData *dataHandle = (myCustomData*)usrData;
    return mmuReadMem(addr);
}

static void minigdbstubUsrContinue(void *usrData) {
    myCustomData *dataHandle = (myCustomData*)usrData;
    // User code here ...
}

static void minigdbstubUsrStep(void *usrData) {
    myCustomData *dataHandle = (myCustomData*)usrData;
    // User code here ...
}

static char minigdbstubUsrGetchar(void *usrData)
{
    myCustomData *dataHandle = (myCustomData*)usrData;
    char character;
    read(connfd, &character, 1);
    return character;
}

static void minigdbstubUsrPutchar(char data, void *usrData)
{
    myCustomData *dataHandle = (myCustomData*)usrData;
    write(connfd, &data, 1);
}

static void minigdbstubUsrProcessBreakpoint(int type, size_t addr, void *usrData) {
    myCustomData *dataHandle = (myCustomData*)usrData;
    // User code here ...
}

static void minigdbstubUsrKillSession(void *usrData) {
    myCustomData *dataHandle = (myCustomData*)usrData;
    // User code here ...
}
