#include <stdio.h>
#include <stdlib.h>

#include "cdata.h"
#include "cthread.h"
#include "support.h"

struct control controlBlock = { .initiated = FALSE };

int ccreate (void* (*start)(void*), void *arg, int prio) {
  if (!controlBlock.initiated) {
    initiateLibrary();
  }

  // TCB_t* newThread;

  // getcontext();
  // makecontext();

  // if error
  return -1;

  // return newThread->tid;
};

int csetprio(int tid, int prio) {
  if (!controlBlock.initiated) {
    initiateLibrary();
  }

  /* TO DO */

  return -1;
};

int cyield(void) {
  if (!controlBlock.initiated) {
    initiateLibrary();
  }

  /* TO DO */

  return -1;
};

int cjoin(int tid) {
  if (!controlBlock.initiated) {
    initiateLibrary();
  }

  /* TO DO */

  return -1;
};

int csem_init(csem_t *sem, int count) {
  if (!controlBlock.initiated) {
    initiateLibrary();
  }

  /* TO DO */

  return -1;
};

int cwait(csem_t *sem) {
  if (!controlBlock.initiated) {
    initiateLibrary();
  }

  /* TO DO */

  return -1;
};

int csignal(csem_t *sem) {
  if (!controlBlock.initiated) {
    initiateLibrary();
  }

  /* TO DO */

  return -1;
};

int cidentify (char *name, int size) {
  if (!controlBlock.initiated) {
    initiateLibrary();
  }

  /* TO DO */

  return -1;
};
