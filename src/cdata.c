#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "cdata.h"
#include "cthread.h"
#include "support.h"

void cinit(void) {
  CreateFila2(&controlBlock.allThreads);

  CreateFila2(controlBlock.blockedThreads);

  CreateFila2(controlBlock.prio0_Threads);
  CreateFila2(controlBlock.prio1_Threads);
  CreateFila2(controlBlock.prio2_Threads);
  CreateFila2(controlBlock.prio3_Threads);

  //TCB_t* mainThread;

  /* TO DO */
};
