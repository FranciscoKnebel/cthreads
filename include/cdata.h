/*
 * cdata.h: arquivo de inclusão de uso apenas na geração da libpithread
 *
 * Esse arquivo pode ser modificado. ENTRETANTO, deve ser utilizada a TCB fornecida
 *
 * Versão de 25/04/2017
 *
 */
#ifndef __cdata__
#define __cdata__

#include <ucontext.h>
#include "support.h"

#define	PROCST_CRIACAO	0
#define	PROCST_APTO	1
#define	PROCST_EXEC	2
#define	PROCST_BLOQ	3
#define	PROCST_TERMINO	4

/* NÃO ALTERAR ESSA struct */
typedef struct s_TCB {
	int		tid; 		// identificador da thread
	int		state;		// estado em que a thread se encontra
					// 0: Criação; 1: Apto; 2: Execução; 3: Bloqueado e 4: Término
	int 		ticket;		// "bilhete" de loteria da thread, para uso do escalonador
	ucontext_t 	context;	// contexto de execução da thread (SP, PC, GPRs e recursos)
} TCB_t;


/* Definido pelo grupo */
#define FALSE 0
#define TRUE 1

#define DEBUG FALSE

#define prio ticket

struct control {
	int initiated;

	FILA2 allThreads;

	PFILA2 blockedThreads;

	PFILA2 prio0_Threads;
	PFILA2 prio1_Threads;
	PFILA2 prio2_Threads;
	PFILA2 prio3_Threads;

	TCB_t* runningThread;
	ucontext_t endThread;
};

extern struct control controlBlock;

int cinit(void);
void endThread(void);
void insertThreadToFila(int prio, void * thread);
void removeThreadFromFila(int prio, int tid);
int generateTID(void);

int scheduler(void);
int dispatcher(TCB_t *nextRunningThread);

#endif
