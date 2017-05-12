#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "cdata.h"
#include "cthread.h"
#include "support.h"

struct control controlBlock = { .initiated = FALSE };

int ccreate (void* (*start)(void*), void *arg, int prio) {
  if (!controlBlock.initiated) {
    cinit();
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
    cinit();
  }

  /* TO DO */

  return -1;
};

int cyield(void) {
  if (!controlBlock.initiated) {
    cinit();
  }

  /* TO DO */

  return -1;
};

int cjoin(int tid) {
  if (!controlBlock.initiated) {
    cinit();
  }

  /* TO DO */

  return -1;
};

int csem_init(csem_t *sem, int count) {
  if (!controlBlock.initiated) {
    cinit();
  }

  /* TO DO */

  return -1;
};

int cwait(csem_t *sem) {
  if (!controlBlock.initiated) {
    cinit();
  }

  /* TO DO */

  return -1;
};

int csignal(csem_t *sem) {
  if (!controlBlock.initiated) {
    cinit();
  }

  /* TO DO */

  return -1;
};

int cidentify (char *name, int size) {
  if (!controlBlock.initiated) {
    cinit();
  }

  if (size == 0) {
    name[0] = '\0';

    return 0;
  }

  char info[] = "\n Douglas Lazaro S P Silva \t- 207305 \n Francisco Paiva Knebel \t- 243688 \n Guilherme Fonseca Ribeiro \t- 228415";
  int length = strlen(info);

  if(size < length) {
    memcpy(name, info, size);
    name[size] = '\0';
  } else {
    memcpy(name, info, length);
    name[length] = '\0';
  }

  return 0;
};
