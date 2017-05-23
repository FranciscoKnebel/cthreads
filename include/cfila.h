/*
  Header dos métodos de manipulação de filas.
  Utiliza os operadores de support.h
*/

#include "support.h"

#ifndef __cfila__
#define __cfila__

int initFILA2(PFILA2 fila, int isPointer);
void insertFILA2(PFILA2 fila, void* element);
int searchFILA2(PFILA2 fila, int tid, int resetIterator);
int removeFILA2(PFILA2 fila, int tid);

int searchFILA2join(PFILA2 fila, int tid, int resetIterator);
int removeFILA2join(PFILA2 fila, int tid);

#endif
