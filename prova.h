#ifndef PROVA_H
#define PROVA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAM_LISTA 10
#define TAM_HASH 10

//tipo de dados tratados pelas funções
typedef int type;

//estrutura da lista sequencial
typedef struct {
	type dados[TAM_LISTA];
	int inicio, fim, qnt;
}lista;

//estrutura de nos da lista duplamente encadeada
typedef struct no_lista{
	struct no_lista* prox;
	struct no_lista* ant;
	type dado;
}no_lista;

//vetor de ponteiros de no_lista com TAM_HASH posicoes
typedef no_lista* hash[TAM_HASH];

//estrutura de nos da arvore encadeada
typedef struct no_arvore{
	struct no_arvore* esq;
	struct no_arvore* dir;
	type dado;
	int ocorrencias, bal, altura;
}no_arvore;

//estrutura da lista duplamente encadeada
typedef struct {
	no_lista* inicio;
	no_lista* fim;
	int qnt;
}lista_encadeada;

//estrutura da arvore encadeada
typedef struct {
	no_arvore* raiz;
	int qnt;
}arvore;

//inicializa os valores da lista
void init_lista(lista* lista);

//insere o dado n na posicao pos e retorna true se foi possivel e false caso contrario
bool inserir(lista* lista, type n, int pos);

//insere o dado na ultima posicao e retorna true se foi possivel e false caso contrario
bool adicionar(lista* lista, type n);

//insere o dado n de forma a manter a lista ordenada. Retorna true se for possivel e false caso contrario
bool inserir_ordenado(lista* lista, type n);

//remove e armazena o valor da posicao pos em n. Retorna true se for possivel ou false caso contrario
bool remover(lista* lista, int pos, type* n);

//retorna o elemento na posicao pos ou -1 caso nao seja possivel
type acessar_n(lista lista, int pos);

//altera o dado na posicao pos por n. Retorna true caso seja possivel e false caso contrario
bool alterar(lista* lista, type n, int pos);

//junta lista1 e lista2 em lista3 e devolve true se foi possivel ou false caso contrario
bool juntar(lista lista1, lista lista2, lista* lista3);

//junta lista1 e lista2 em lista3 de maneira ordenada e devolve true se foi possivel ou false caso contrario 
//(lista1 e lista2 devem ser previamente ordenadas)
bool juntar_ordenado(lista lista1, lista lista2, lista* lista3);

//retorna a posicao da k-esima ocorrencia de n na lista ou -1 caso nao haja
int localizar(lista lista, type n, int k);

//insere o elemento n no topo da pilha. Retorna true se possivel e false caso contrario
bool empilhar(lista* lista, type n);

//remove e retorna o elemento do topo da pilha. Caso nao seja possivel retornara o endereco dos dados da pilha
type desempilhar(lista* lista);

//retorna true caso a lista esteja cheia e false caso nao esteja
bool lista_cheia(lista lista);

//retorna true caso a lista esteja vazia e false caso nao esteja
bool lista_vazia(lista lista);

//adiciona o elemento n no fim da fila e retorna true se possivel e false caso contrario
bool enfileirar(lista* lista, type n);

//remove e retorna o primeiro elemento da fila se possivel e o endereco de dados caso contrario
type desenfileirar(lista* lista);

//retorna o primeiro elemento da fila se possivel e o endereco de dados caso contrario
type acessar_primeiro(lista lista);

//retorna o ultimo elemento da fila se possivel e o endereco de dados caso contrario
type acessar_ultimo(lista lista);

//constroi um heap minimo
void heap_minimo (lista* lista);

//constroi um heap maximo
void heap_maximo (lista* lista);

//exibe os elementos de estruturas sequenciais. Talvez seja necessario mudar o tipo de formatação no printf() dependendo do tipo dos dados
void print_sequencial(lista l);

//inicializa a lista encadeada
void init_lista_encadeada(lista_encadeada* lista_encadeada);

//adiciona o elemento n no final da lista encadeada e retorna true se for possivel e false caso contrario
bool empilhar_encadeada(lista_encadeada* lista_encadeada, type n);

//remove o ultimo elemento e armazena em elemento_retorno. Retorna true se foi possivel e false caso contrario. 
//No caso do retorno false o valor de elemento_retorno será 0 e a lista será reinicializada
bool desempilhar_encadeada(lista_encadeada* lista_encadeada, type* elemento_retorno);

//remove primeiro elemento e armazena em elemento_retorno. Retorna true se foi possivel e false caso contrario. 
//No caso do retorno false o valor de elemento_retorno será 0 e a lista será reinicializada
bool desenfileirar_encadeada(lista_encadeada* lista_encadeada, type* elemento_retorno);

//insere o elemento n na posicao pos e devolve true se foi possivel e false caso contrario
bool inserir_encadeado(lista_encadeada* lista_encadeada, type n, int pos);

//insere o elemento n na lista de forma a mante-la ordenada. Retorna true se foi possivel e false caso contrario
bool inserir_ordenado_encadeado(lista_encadeada* lista_encadeada, type n);

//devolve o no da posicao pos ou NULL caso nao haja
no_lista* acessar_encadeado(lista_encadeada lista_encadeada, int pos);

//devolve a posicao do k-esimo no que contem o dado n ou -1 caso nao exista
int localizar_encadeado(lista_encadeada lista_encadeada, type n, int k);

//junta ambas as listas e retorna true se foi possivel e false caso contrario
//ambas as listas serao identicas, não importando qual ira mexer a partir daqui
bool juntar_encadeado(lista_encadeada* lista_encadeada1, lista_encadeada* lista_encadeada2);

//altera o dado do no na posicao pos e retorna true se foi possivel ou false caso contrario
bool alterar_encadeado(lista_encadeada* lista_encadeada, int pos, type n);

//exibe os valores da lista encadaeada. Talvez seja necessario mudar o tipo de formatação no printf() dependendo do tipo dos dados
void print_lista_encadeada(lista_encadeada lista_encadeada);

//inicializa a arvore AVL
void init_arvore(arvore* arvore);

//insere os elementos e balanceia caso necessario
void inserir_arvore(arvore* arvore, no_arvore** raiz, type n);

//inicializa a hashtable
void init_hash(hash* hashtable);

//realica a funcao hash e devolve o indice codificado do dado n
int hash_func(type n);

//adiciona o dado n na tabela hash
bool adicionar_hash(hash hashtable, type n);

//acessa o dado n e devolve o no que o tem
no_lista* acessar_hash(hash hashtable, type n);

//remove o no que contem o dado n da tabela hash
void remover_hash(hash hashtable, type n);

#endif // !PROVA_H
