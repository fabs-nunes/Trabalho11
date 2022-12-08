#include <stdio.h>
#include <stdlib.h>

/*Definicao do tipo de funcao a ser utilizado para comparacao
Esta funcao recebe dois valores x e y e retorna

1 : se x menor que y.
0 : se x equivalente a y.
-1: se x maior que y na ordem.

*/
typedef int COMP(void* x, void* y);

//Vetor ordenado estatico. Os elementos do vetor estao colocados no vetor
//de acordo com a ordem indicada por comparador.
typedef struct vet{
	int N;//tamanho do vetor
	int P;//numero de elementos no vetor
	void** elems;//o vetor de elementos
	COMP* comparador;//a funcao de comparacao
}VETORORD;

/**
Cria um vetor ordernado vazio de tamanho n e com funcao de comparacao compara

parametro n: o tamanho do vetor
parametro compara: a funcao de comparacao

o retorno é um ponteiro para uma estrutura VETORORD, observe que este ponteiro ja
deve apontar para a estrutura, ou seja, a alocacao de memoria deve ser feita nele.
*/
VETORORD* VETORD_create(int n, COMP* compara){
	VETORORD *vetor = malloc(sizeof(VETORORD));
	vetor->N = n;
	vetor->P = 0;
	vetor->elems = malloc(n*sizeof(void*));
	vetor->comparador = compara;
	return vetor;
}

/**
Adiciona o elemento newelem ao vetor ordenado, na posicao correta se for possi­vel
ainda incluir o elemento (se existe espaco no vetor). O vetor deve estar ordenado em
ordem crescente, ou seja: x[i] menor que ou equivalente a x[j] para todo i < j.

parametro vetor: o vetor ordenado a ter o elemento incluÃ­do
parametro newelem: o elemento a ser adicionado
*/
void VETORD_add(VETORORD* vetor, void* newelem){
	if (vetor->P < vetor->N) {
		int posicao = vetor->P;

		for (int i = 0; i < vetor->P; i++) {
			if (vetor->comparador(vetor->elems[i], newelem) == -1) {
				posicao = i;
				break;
			}
		}

		for (int i = vetor->P; i > posicao; i--) {
			vetor->elems[i] = vetor->elems[i - 1];
		}

		vetor->elems[posicao] = newelem;
		vetor->P++;
	}	
}

/**
Remove o menor elemento do vetor, de acordo com a funcao compara.

parametro vetor: o vetor a ter seu elemento removido

o retorno é um ponteiro para o elemento que foi removido do vetor.
*/
void* VETORD_remove(VETORORD* vetor){
	void* menor = vetor->elems[0];
	int posicao = 0;
	for(int i=1; i< vetor->P; i++){
		if(vetor->comparador(vetor->elems[i],menor)<0){
			menor = vetor->elems;
			posicao = i;
		}
	}
	for(int i=posicao; i<vetor->P-1; i++){
		vetor->elems[i] = vetor->elems[i+1];
	}
	vetor->P--;
	return menor;
}

