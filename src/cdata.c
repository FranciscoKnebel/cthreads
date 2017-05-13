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
  TCB_t *mainThread;

  mainThread = (TCB_t*) malloc(sizeof(TCB_t));
  mainThread->tid = 0;
  mainThread->state = PROCST_EXEC;
  mainThread->prio = 0;

  insertFILA2(&controlBlock.allThreads, (void *) mainThread);

  /*
    Create context to main thread
    Set Main thread as running
  */
  getcontext(&mainThread->context);

  controlBlock.runningThread = mainThread;

  return 0;
};

void insertThreadToFila(int prio, void * thread) {
  switch (prio) {
    case 0:
      insertFILA2((PFILA2) &controlBlock.prio0_Threads, thread);
      break;
    case 1:
      insertFILA2((PFILA2) &controlBlock.prio1_Threads, thread);
      break;
    case 2:
      insertFILA2((PFILA2) &controlBlock.prio2_Threads, thread);
      break;
    case 3:
      insertFILA2((PFILA2) &controlBlock.prio3_Threads, thread);
      break;
    default:
      break;
  }
}

int generateTID(void) {
	static int globalTID = 0;

	return ++globalTID;
}
