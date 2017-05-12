#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "cfila.h"
#include "cdata.h"
#include "cthread.h"
#include "support.h"

int cinit(void) {
  int check;

  /*
    Initiate control block elements
  */
  controlBlock.initiated = TRUE;
  check = initFILA2(&controlBlock.allThreads, FALSE);
  if(!check) return -1;

  check = initFILA2(controlBlock.blockedThreads, TRUE);
  if(!check) return -2;

  check = initFILA2(controlBlock.prio0_Threads, TRUE);
  if(!check) return -3;

  check = initFILA2(controlBlock.prio1_Threads, TRUE);
  if(!check) return -4;

  check = initFILA2(controlBlock.prio2_Threads, TRUE);
  if(!check) return -5;

  check = initFILA2(controlBlock.prio3_Threads, TRUE);
  if(!check) return -6;

  /*
    Creates the main thread.
    Appends it to the allThreads structure.
  */
  TCB_t *mainThread, *thread1, *thread2;

  mainThread = (TCB_t*) malloc(sizeof(TCB_t));
  mainThread->tid = 0;
  mainThread->state = PROCST_EXEC;
  mainThread->ticket = 0;

  insertFILA2(&controlBlock.allThreads, (void *) mainThread);

  /* Create end functions to threads*/
  /* getcontext(&control.ended_thread);
  control.ended_thread.uc_link = NULL;
  control.ended_thread.uc_stack.ss_sp = (char*) malloc(SIGSTKSZ);
  control.ended_thread.uc_stack.ss_size = SIGSTKSZ;
  makecontext(&control.ended_thread, (void (*)(void))ended_thread, 0); */

  /* Set Main thread as running*/
  controlBlock.runningThread = mainThread;

  /* Create context to main thread*/
  /* getcontext(&main_thread->context);
  main_thread->context.uc_link = &control.ended_thread;
  main_thread->context.uc_stack.ss_sp = (char*) malloc(SIGSTKSZ);
  main_thread->context.uc_stack.ss_size = SIGSTKSZ; */

  return 0;
};
