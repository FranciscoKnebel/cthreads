#include <stdio.h>
#include <stdlib.h>
#include "../include/cfila.h"
#include "../include/cdata.h"

void searchArrayTID(PFILA2 allThreads, int TIDs[], int size) {
	size_t j;

	for (j = 0; j < size; j++) {
		if(searchFILA2(allThreads, TIDs[j], TRUE) == TRUE) {
			TCB_t* copyThread = (TCB_t*) GetAtIteratorFila2(allThreads);
			printf("Pointer: %p - TID: %d\n", copyThread, copyThread->tid);
		} else {
			printf("TID %d not found.\n", TIDs[j]);
		}
	}
}

int main() {
  struct control controlBlock = { .initiated = FALSE };
  TCB_t *thread0, *thread1, *thread2, *thread3;

	int searchTID[6] = { 0, 1, 5, 100, 2, 3 };
	cinit();
	PFILA2 allThreads = &controlBlock.allThreads;

	// Inicializando threads
  thread0 = (TCB_t*) malloc(sizeof(TCB_t));
  thread0->tid = 0;
  thread1 = (TCB_t*) malloc(sizeof(TCB_t));
  thread1->tid = searchTID[5];
  thread2 = (TCB_t*) malloc(sizeof(TCB_t));
  thread2->tid = searchTID[3];
  thread3 = (TCB_t*) malloc(sizeof(TCB_t));
  thread3->tid = searchTID[2];

  // Inserção na fila
  insertFILA2(allThreads, (void *) thread0);
  insertFILA2(allThreads, (void *) thread1);
  insertFILA2(allThreads, (void *) thread2);
  insertFILA2(allThreads, (void *) thread3);

  // Pesquisa usando o TID, dentro da fila.
	printf("Efetuando buscas por TID.\n");
	searchArrayTID(allThreads, searchTID, 6);

	// Remoção de elemento da fila
	removeFILA2(allThreads, searchTID[5]);
	removeFILA2(allThreads, searchTID[2]);

	// Pesquisa usando os mesmos TIDs anteriores.
	printf("\nElementos com TID %d e TID %d removidos. Efetuando busca novamente.\n", searchTID[5], searchTID[2]);
	searchArrayTID(allThreads, searchTID, 6);

	// Inserção novamento dos elementos removidos.
	insertFILA2(allThreads, (void *) thread1);
	insertFILA2(allThreads, (void *) thread3);

	// Pesquisa usando os mesmos TIDs anteriores.
	printf("\nElementos TID %d e TID %d reinseridos. Efetuando busca...\n", searchTID[5], searchTID[2]);
	searchArrayTID(allThreads, searchTID, 6);

  return 0;
}
