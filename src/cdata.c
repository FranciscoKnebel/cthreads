#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "cdata.h"
#include "cthread.h"
#include "support.h"

int initFILA2(PFILA2 fila, int isPointer) {
  if(isPointer) {
    fila = (PFILA2) malloc(sizeof(PFILA2));
  }

  if (fila == NULL) {
    return FALSE;
  }

  if(CreateFila2(fila) == 0) {
    return TRUE;
  }

  return FALSE;
}

int cinit(void) {
  int check;
  TCB_t* mainThread;

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
  mainThread = (TCB_t*) malloc(sizeof(TCB_t));
  mainThread->tid = 0;
  mainThread->state = PROCST_EXEC;
  mainThread->ticket = 0;

  AppendFila2(&controlBlock.allThreads, (void *) mainThread);
  FirstFila2(&controlBlock.allThreads);

  /*TCB_t* copyThread = (TCB_t*) GetAtIteratorFila2(&controlBlock.allThreads);

  printf("%p - %p\n", mainThread, copyThread);
  printf("%d - %d\n", mainThread->tid, copyThread->tid);
  printf("%d - %d\n", mainThread->state, copyThread->state);
  printf("%d - %d\n", mainThread->ticket, copyThread->ticket); */

  /* TO DO */
  return 0;
};
