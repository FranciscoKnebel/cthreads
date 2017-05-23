/*
  Métodos de manipulação de filas.
  Utiliza os operadores de support.h
*/

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

void insertFILA2(PFILA2 fila, void* element) {
  AppendFila2(fila, element);
  FirstFila2(fila);

  return;
}

int searchFILA2(PFILA2 fila, int tid, int resetIterator) {
  int found = FALSE;
  int finished = FALSE;
  int status;

  TCB_t* node;

  #if DEBUG
    printf("\nsearchFILA2 function. Looking for TID %d.\n", tid);
  #endif

  if(resetIterator == TRUE) {
    FirstFila2(fila);
  }

  do {
    node = (TCB_t*) GetAtIteratorFila2(fila);

    if(node == NULL) {
      #if DEBUG
       printf("Node NULL. Ending search.\n");
      #endif

      finished = TRUE;
      status = -1;
    } else {
      #if DEBUG
        printf("\nNode TID %d.", node->tid);
      #endif

      if(node->tid == tid) {
        #if DEBUG
          printf(" <-- Found it!\n");
        #endif

        found = TRUE;
        status = found;
      } else {
        status = NextFila2(fila);

        if(status != 0) {
          status = -1;
          finished = TRUE;

          #if DEBUG
            printf("\nTID %d not found.\n", tid);
          #endif
        }
      }
    }
  } while(!found && !finished);

  return status;
}

int removeFILA2(PFILA2 fila, int tid) {
  int found = searchFILA2(fila, tid, TRUE);

  if(found == TRUE) {
    DeleteAtIteratorFila2(fila);
  }

  return found;
}

int searchFILA2join(PFILA2 fila, int tid, int resetIterator) {
  int found = FALSE;
  int finished = FALSE;
  int status;

  Pjoin* node;

  #if DEBUG
    printf("\nsearchFILA2 function. Looking for TID %d.\n", tid);
  #endif

  if(resetIterator == TRUE) {
    FirstFila2(fila);
  }

  do {
    node = (Pjoin*) GetAtIteratorFila2(fila);

    if(node == NULL) {
      #if DEBUG
       printf("Node NULL. Ending search.\n");
      #endif

      finished = TRUE;
      status = -1;
    } else {
      #if DEBUG
        printf("\nNode TID %d.", node->awaited->tid);
      #endif

      if(node->awaited->tid == tid) {
        #if DEBUG
          printf(" <-- Found it!\n");
        #endif

        found = TRUE;
        status = found;
      } else {
        status = NextFila2(fila);

        if(status != 0) {
          status = -1;
          finished = TRUE;

          #if DEBUG
            printf("\nTID %d not found.\n", tid);
          #endif
        }
      }
    }
  } while(!found && !finished);

  return status;
}

int removeFILA2join(PFILA2 fila, int tid) {
  int found = searchFILA2join(fila, tid, TRUE);

  if(found == TRUE) {
    DeleteAtIteratorFila2(fila);
  }

  return found;
}