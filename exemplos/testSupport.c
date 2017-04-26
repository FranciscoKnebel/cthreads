
/********************************************************************
	Support Library Test Program
	Vers. 17.1 - 25/04/2017
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "support.h"

int	vetor[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int	Verifica(PFILA2 fila, int value);
int	ClearFila2(PFILA2 fila);
void	printGrade(int current);
void	printCurrentGrade(char *texto, int current);

#define	TOTAL_COUNT	15	// Numero total de testes

int main() {
	int	err;
	int	i,n;
	FILA2	fila;
	FILA2	fila2;
	int	correctCount;
	
	correctCount = 0;
	
	// Informa a versao da biblioteca
	printf ("Support Version: %d/%d\n", Version()/2, 1+(Version()&1) );
	
	// Teste da ramdom
	printf ("Sequencia: %d - %d - %d\n", Random2(), Random2(), Random2() );
	
	// Inicializa a fila
	if (CreateFila2(&fila)) {
		printf ("Erro: não conseguiu criar a fila\n");
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printCurrentGrade("CreateFila2", correctCount);
	
	// Teste de fila vazia
	n = FirstFila2(&fila);
	if (n==0) {
		printf ("Erro: FirstFila2 should return an error as queue is empty.\n");
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printCurrentGrade("FirstFila2 returned empty queue information.", correctCount);
	
	// Preenche a fila com 5 itens
	for (i=0; i<5; ++i) {
		if (AppendFila2(&fila, (void *)(vetor+i))) {
			printf ("Error: could not append item to the queue\n");
			printGrade(correctCount);
			exit(0);
		}
	}
	correctCount++;
	printCurrentGrade("5 itens appended (AppendFila2).", correctCount);
	
	// Teste de First
	// Verifica se posicionou no inicio da fila
	// Verifica se pegou o elemento correto
	if (FirstFila2(&fila)) {
		printf ("Error: FirstFila2 is NOT working\n");
		printGrade(correctCount);
		exit(0);
	}	
	correctCount++;
	printCurrentGrade("First queue returned correctly.", correctCount);
	
	// Essa é aprimeira vez que o Verifica é chamado. Então, vale 1 ponto!
	if (Verifica(&fila, 0)) {
		printf ("Error: first queue content IS NOT correct\n");
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printCurrentGrade("GetAtIteratorFila2 got correct item.", correctCount);

	// Teste de Last
	// Verifica se posicionou no final da fila
	if (LastFila2(&fila)) {
		printf ("Error: LastFila2 is NOT working\n");
		printGrade(correctCount);
		exit(0);
	}	
	if (Verifica(&fila, 4)) {
		printf ("Error: last queue content IS NOT correct\n");
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printCurrentGrade("Last queue item was correctly read.", correctCount);
	
	// Teste de Next
	FirstFila2(&fila);
	for (n=i=0; i<5; ++i) {
		n += (*(int *)GetAtIteratorFila2(&fila));
		err = NextFila2(&fila);
		if (err!=0 && err!=(-NXTFILA_ENDQUEUE)) {
			printf ("Error: NextFila2 is NOT working (errcode=%d)\n", err);
			printGrade(correctCount);
			exit(0);
		}
	}
	if (err!=(-NXTFILA_ENDQUEUE)) {
		printf ("Error: NextFila2 should return END OF QUEUE, but is not (errcode=%d)\n", err);
		printGrade(correctCount);
		exit(0);
	}
	if (n!=10) {
		printf ("Error: NextFila2 IS NOT pointing to next item ot the queue.\n");
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printCurrentGrade("NextFila2 is working.", correctCount);

	// Teste de insersao no meio da lista
	FirstFila2(&fila);
	NextFila2(&fila);
	NextFila2(&fila);	
	if (InsertAfterIteratorFila2(&fila, (void *)(vetor+9))) {
		printf ("Error: InsertAfterIteratorFila2 is NOT working\n");
		printGrade(correctCount);
		exit(0);
	}
	FirstFila2(&fila);
	NextFila2(&fila);
	NextFila2(&fila);	
	NextFila2(&fila);
	if (Verifica(&fila, 9)) {
		printf ("Error: inserted node IS NOT at correct place\n");
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printCurrentGrade("InsertAfterIteratorFila2 is working.", correctCount);	
	
	// Teste de DELETE
	FirstFila2(&fila);
	NextFila2(&fila);
	NextFila2(&fila);	
	NextFila2(&fila);	
	if (DeleteAtIteratorFila2(&fila)) {
		printf ("Error: DeleteAtIteratorFila2 is NOT working\n");
		printGrade(correctCount);
		exit(0);
	}
	if (Verifica(&fila, 3)) {
		printf ("Error: DeleteAtIteratorFila2 get away wrong node\n");
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printCurrentGrade("DeleteAtIteratorFila2 is working.", correctCount);	
	
	// Clear fila2 to verify empty queue
	FirstFila2(&fila);
	for (i=0; i<10; ++i) {
		if (DeleteAtIteratorFila2(&fila))
			break;
	}
	if (AppendFila2(&fila, (void *)(&vetor[7]))) {
		printf ("Error: Could not append item after clear queue\n");
		printGrade(correctCount);
		exit(0);
	}
	FirstFila2(&fila);
	err = Verifica(&fila, 7);
	if (err) {
		switch(err) {
			case -1: printf ("Error: GetAtIteratorFila2 IS NOT working, after clear fila2\n"); break;
			case -2: printf ("Error: GetAtIteratorFila2 is getting a wrong item, after clear fila2\n"); break;
			default: printf ("Error: GetAtIteratorFila2 returned an error code\n"); break;
		}
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printCurrentGrade("Clear queue is working properlly.", correctCount);	
	
	// Interferencia entre duas filas
	if (CreateFila2(&fila2)) {
		printf ("Error: Cound not create the second queue\n");
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printCurrentGrade("Second queue was created.", correctCount);	
	
	// Limpa as duas filas
	int	exitOnError = 0;
	if (ClearFila2(&fila)) {
		printf ("Error: Could not CLEAR first queue\n");
		exitOnError = 1;
	}	
	if (ClearFila2(&fila2)) {
		printf ("Erro: Could not CLEAR an empty queue (the second queue)\n");
		exitOnError = 1;
	}
	if (exitOnError) {
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printCurrentGrade("Both queues were cleared.", correctCount);	
	
	// Preenche as duas filas com conteúdos diferentes
	for (i=0; i<3; ++i) {
		if (AppendFila2(&fila, (void *)(vetor+i))) {
			printf ("Error: Could not append item to the first queue\n");
			exitOnError = 1;
			break;
		}
	}
	for (i=5; i<8; ++i) {
		if (AppendFila2(&fila2, (void *)(vetor+i))) {
			printf ("Error: Could not append item to the second queue\n");
			exitOnError = 1;
			break;
		}
	}
	if (exitOnError) {
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printCurrentGrade("Both queue were appended.", correctCount);	

	// Verifica o conteúdo da primeira fila
	FirstFila2(&fila);
	NextFila2(&fila);
	NextFila2(&fila);
	if (Verifica(&fila, 2)) {
		printf ("Error: Third node content in the first queue IS NOT correct\n");
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printCurrentGrade("Third node content in the first queue IS CORRECT.", correctCount);	
	
	// Verifica o conteúdo da segunda fila
	FirstFila2(&fila2);
	NextFila2(&fila2);
	NextFila2(&fila2);
	if (Verifica(&fila2, 7)) {
		printf ("Error: Third node content in the second queue IS NOT correct\n");
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printCurrentGrade("Third node content in the second queue IS CORRECT.", correctCount);	
	
	
	printf ("SEM ERRO!\n");
	printGrade(correctCount);
	exit(0);
}


int	Verifica(PFILA2 fila, int value) {
	
	int *p;
	
	p = (int *)GetAtIteratorFila2(fila);
	if (p==NULL) {
		return -1;
	}
	if (*p!=value) {
		//printf ("VERIFICA %d==%d?", value, *p);
		return -2;
	}
	return 0;
}


int	ClearFila2(PFILA2 pFila) {
	
	FirstFila2(pFila);
	while (GetAtIteratorFila2(pFila)!=NULL) {
		if (DeleteAtIteratorFila2(pFila)) {
			return -1;
		}
	}
	return 0;
}

void	printGrade(int current) {
	printf ("GRADE IS (%d/%d): %d\n", current, TOTAL_COUNT, (100*current)/TOTAL_COUNT);
}

void	printCurrentGrade(char *texto, int current) {
	printf ("OK: %s (%d/%d): grade=%d\n", texto, current, TOTAL_COUNT, (100*current)/TOTAL_COUNT);
}






