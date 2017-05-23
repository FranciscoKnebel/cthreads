#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cdata.h"
#include "cfila.h"
#include "cthread.h"
#include "support.h"

struct control controlBlock = { .initiated = FALSE };

int ccreate (void* (*start)(void*), void *arg, int prio) {
  if (!controlBlock.initiated) {
    cinit();
  }

  TCB_t* newThread;
  newThread = (TCB_t*) malloc(sizeof(TCB_t));
  newThread->tid = generateTID();
  newThread->state = PROCST_APTO;
  newThread->prio = prio;

  getcontext(&newThread->context);

  newThread->context.uc_link = &controlBlock.endThread;
  newThread->context.uc_stack.ss_sp = (char*) malloc(SIGSTKSZ);
  newThread->context.uc_stack.ss_size = SIGSTKSZ;

  if(newThread->context.uc_stack.ss_sp == NULL) {
    return -1;
  }

  makecontext(&newThread->context, (void(*))start, 1, arg);

  insertFILA2(&controlBlock.allThreads, (void *) newThread);
  insertThreadToFila(prio, (void *) newThread);

  return newThread->tid;
};

int csetprio(int tid, int prio) {
  if (!controlBlock.initiated) {
    cinit();
  }
  PFILA2 allThreads = &controlBlock.allThreads;

  if(searchFILA2(allThreads, tid, TRUE) == TRUE) {
    TCB_t* copyThread = (TCB_t*) GetAtIteratorFila2(allThreads);

    int oldprio = copyThread->prio;
    copyThread->prio = prio;

    removeThreadFromFila(oldprio, tid);
    insertThreadToFila(prio, (void *) copyThread);

    return 0;
  } else {
    return -1;
  }
};

int cyield(void) {
  if (!controlBlock.initiated) {
    cinit();
  }

  TCB_t* lastRunningThread = controlBlock.runningThread;
  lastRunningThread->state = PROCST_APTO;

  insertThreadToFila(lastRunningThread->prio, lastRunningThread);
  scheduler();

  return 0;
};

int cjoin(int tid) {
  if (!controlBlock.initiated) {
    cinit();
  }

  TCB_t* joinThread;
  if(searchFILA2(&controlBlock.allThreads, tid, TRUE) == TRUE) {
    joinThread = (TCB_t*) GetAtIteratorFila2(&controlBlock.allThreads);
  } else {
    /* TID not found */
    return -1;
  }

  /* runningThread é a thread procurada */
  if (controlBlock.runningThread->tid == tid) {
    return -2;
  }

  if(joinThread->state == PROCST_TERMINO) {
    return 0;
  }

  /* TO DO */

  /* Verificações de bloqueio */
  if (searchFILA2join(controlBlock.blockedThreads, tid, TRUE) == TRUE)
  {
    return -3;
  }

  /* Coloca thread ativa na fila de bloqueados */
  TCB_t* currentThread = controlBlock.runningThread;
  currentThread->state = PROCST_BLOQ;

  Pjoin * block;

  block = (Pjoin*) malloc(sizeof(Pjoin));

  block->waiting = currentThread;
  block-> awaited = joinThread;

  insertFILA2((PFILA2) &controlBlock.blockedThreads,(void*) block);

  /* troca de contexto */
  scheduler();

  return 0;
};

int csem_init(csem_t *sem, int count) {
  if (!controlBlock.initiated) {
    cinit();
  }

  sem->count = count;
  sem->fila = (PFILA2) malloc(sizeof(PFILA2));

  if (CreateFila2(sem->fila) == 0) {
    return 0;
  } else {
    return -1;
  }
};

int cwait(csem_t *sem) {
  if (!controlBlock.initiated) {
    cinit();
  }

  TCB_t* RunningThread = controlBlock.runningThread;

  if(sem->count > 0){
    sem->count = 0;
    return 0;
  }
  else{
        if(AppendFila2(sem->fila, (void *) RunningThread)==0){
            sem->count--;
            RunningThread->state = PROCST_BLOQ;
            scheduler();
            return 0;
        }
  }
    return -1;
};

int csignal(csem_t *sem) {
  if (!controlBlock.initiated) {
    cinit();
  }
  sem->count++;
  if (sem->count>0){
    return 0;
  }
  else{
    FirstFila2(sem->fila);
    TCB_t *aux;
    aux = GetAtIteratorFila2(sem->fila);
    if (aux==NULL){
        return -1;
    }
    DeleteAtIteratorFila2(sem->fila);
    aux->state = PROCST_APTO;
    insertThreadToFila(aux->prio, (void *) aux);
    return 0;
  }
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
