#include <stdio.h>
#include <stdlib.h>

#include "cdata.h"
#include "cthread.h"
#include "support.h"

int ccreate (void* (*start)(void*), void *arg, int prio) {

  return 0;
};

int csetprio(int tid, int prio) {

  return 0;
};

int cyield(void) {

  return 0;
};

int cjoin(int tid) {

  return 0;
};

int csem_init(csem_t *sem, int count) {

  return 0;
};

int cwait(csem_t *sem) {

  return 0;
};

int csignal(csem_t *sem) {

  return 0;
};

int cidentify (char *name, int size) {

  return 0;
};
