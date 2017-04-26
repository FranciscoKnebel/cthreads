
/********************************************************************

	Support Library
	Vers. 1.0 - 10/08/16
	
********************************************************************/

#ifndef	__SUPPORTE_H__
#define	__SUPPORTE_H__

struct	sFilaNode2 {
	void 	*node;			// Ponteiro para a estrutura de dados do NODO
	struct	sFilaNode2 *ant;	// Ponteiro para o nodo anterior
	struct	sFilaNode2 *next;	// Ponteiro para o nodo posterior
};
struct sFila2 {
	struct	sFilaNode2 *it;		// Iterador para varrer a lista
	struct	sFilaNode2 *first;	// Primeiro elemento da lista
	struct	sFilaNode2 *last;	// �ltimo elemento da lista
};

typedef struct sFilaNode2	NODE2;
typedef struct sFila2		FILA2;
typedef struct sFilaNode2 *	PNODE2;
typedef struct sFila2 *		PFILA2;

/*-------------------------------------------------------------------
Fun��o:	Informa a versao da biblioteca
Ret:	Numero da versao
-------------------------------------------------------------------*/
#define Year	2017
#define	Term	1
#define Version()	((2*Year)+(Term-1))


/*-------------------------------------------------------------------
Fun��o:	Inicializa uma estrutura de dados do tipo FILA2
Ret:	==0, se conseguiu
	!=0, caso contr�rio (erro ou fila vazia)
-------------------------------------------------------------------*/
int	CreateFila2(PFILA2 pFila);


/*-------------------------------------------------------------------
Fun��o:	Seta o iterador da fila no primeiro elemento
Ret:	==0, se conseguiu
	!=0, caso contr�rio (erro ou fila vazia)
-------------------------------------------------------------------*/
int	FirstFila2(PFILA2 pFila);

/*-------------------------------------------------------------------
Fun��o:	Seta o iterador da fila no �ltimo elemento
Ret:	==0, se conseguiu
	!=0, caso contr�rio (erro ou fila vazia)
-------------------------------------------------------------------*/
int	LastFila2(PFILA2 pFila);

/*-------------------------------------------------------------------
Fun��o:	Seta o iterador da fila para o pr�ximo elemento
Ret:	==0, se conseguiu
	!=0, caso contr�rio (erro, fila vazia ou chegou ao final da fila)
	Fila vazia		=> -1
	Iterador inv�lido	=> -2
	Atingido final da fila	=> -3
-------------------------------------------------------------------*/
#define	NXTFILA_VAZIA		1
#define	NXTFILA_ITERINVAL	2
#define	NXTFILA_ENDQUEUE	3
int	NextFila2(PFILA2 pFila);

/*-------------------------------------------------------------------
Fun��o:	Retorna o conte�do do nodo endere�ado pelo iterador da lista "pFila"
Ret:	Ponteiro v�lido, se conseguiu
	NULL, caso contr�rio (erro, lista vazia ou iterador invalido)
-------------------------------------------------------------------*/
void 	*GetAtIteratorFila2(PFILA2 pFila);

/*-------------------------------------------------------------------
Fun��o:	Coloca o ponteiro "content" no final da fila "pFila"
Ret:	==0, se conseguiu
	!=0, caso contr�rio (erro)
-------------------------------------------------------------------*/
int	AppendFila2(PFILA2 pFila, void *content);

/*-------------------------------------------------------------------
Fun��o:	Coloca o ponteiro "content" logo ap�s o elemento 
	correntemente apontado pelo iterador da fila "pFila"
Ret:	==0, se conseguiu
	!=0, caso contr�rio (erro)
	Fila vazia		=> -1
	Iterador inv�lido	=> -2
-------------------------------------------------------------------*/
#define	INSITER_VAZIA	1
#define	INSITER_INVAL	2
int	InsertAfterIteratorFila2(PFILA2 pFila, void *content);

/*-------------------------------------------------------------------
Fun��o:	Remove o elemento indicado pelo iterador, da lista "pFila"
Ret:	==0, se conseguiu
	!=0, caso contr�rio (erro)
	Fila vazia		=> -1
	Iterador inv�lido	=> -2
-------------------------------------------------------------------*/
#define	DELITER_VAZIA	1
#define	DELITER_INVAL	2
int	DeleteAtIteratorFila2(PFILA2 pFila);

/*-------------------------------------------------------------------
Fun��o:	Gera um n�mero pseudo-aleat�rio entre 0 e 65535
Ret:	N�mero gerado
-------------------------------------------------------------------*/
unsigned int	Random2();


#endif




