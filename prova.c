#include "prova.h"

void init_lista(lista* l) {
	l->qnt = 0;
	l->fim = 0;
	l->inicio = 0;
}

bool inserir(lista* l, type n, int pos) {
	if (l->qnt >= TAM_MAX || pos > l->qnt) return false;

	int i;
	for (i = l->qnt; i >= pos; i--) l->dados[i + 1] = l->dados[i];
	l->dados[i + 1] = n;

	l->qnt++;

	return true;
}

bool adicionar(lista* l, type n) {
	if (l->qnt >= TAM_MAX) return false;

	l->dados[l->qnt++] = n;

	return true;
}

bool inserir_ordenado(lista* l, type n) {
	if (l->qnt >= TAM_MAX) return false;

	int i;
	for (i = l->qnt - 1; n <= l->dados[i]; i--) l->dados[i + 1] = l->dados[i];

	l->dados[i + 1] = n;

	l->qnt++;

	return true;
}

bool remover(lista* l, int pos, type* n) {
	if (l->qnt <= 0 || pos >= l->qnt) return false;

	*n = l->dados[pos];

	for (int i = pos; i < l->qnt; i++) l->dados[i] = l->dados[i + 1];

	l->qnt--;

	return true;
}

type acessar_n(lista l, int pos) {
	if (pos < 0 || pos >= l.qnt) return -1;

	return l.dados[pos];
}

bool alterar(lista* l, type n, int pos) {
	if (pos < 0 || pos >= l->qnt) return false;

	l->dados[pos] = n;

	return true;
}

bool juntar(lista l1, lista l2, lista* l3) {
	if (sizeof(l3->dados) < (l1.qnt * sizeof(l1.dados[0]) + l2.qnt * sizeof(l2.dados[0]))) return false;

	int j = 0;

	for (int i = 0; i < l1.qnt; i++) l3->dados[j++] = l1.dados[i];
	for (int i = 0; i < l2.qnt; i++) l3->dados[j++] = l2.dados[i];

	l3->qnt = l1.qnt + l2.qnt;

	return true;
}

bool juntar_ordenado(lista l1, lista l2, lista* l3) {
	if (sizeof(l3->dados) < (l1.qnt * sizeof(l1.dados[0]) + l2.qnt * sizeof(l2.dados[0]))) return false;

	int i, j, k;
	i = j = k = 0;

	while (i < l1.qnt && j < l2.qnt) {
		if (l1.dados[i] < l2.dados[j]) l3->dados[k++] = l1.dados[i++];
		else l3->dados[k++] = l2.dados[j++];
	}

	while (i < l1.qnt) l3->dados[k++] = l1.dados[i++];
	while (j < l2.qnt) l3->dados[k++] = l2.dados[j++];

	l3->qnt = l1.qnt + l2.qnt;

	return true;
}

int localizar(lista l, type n, int k) {
	if (k > 0 && k <= l.qnt) {
		int num_ocorrencia = 1;
		for (int i = 0; i < l.qnt; i++) {
			if (l.dados[i] == n) {
				if (num_ocorrencia == k) return i;
				num_ocorrencia++;
			}
		}
	}

	return -1;
}

bool empilhar(lista* p, type n) {
	if (lista_cheia(*p)) return false;

	p->dados[p->fim++] = n;

	p->qnt++;

	return true;
}

type desempilhar(lista* p) {
	if (lista_vazia(*p)) return p->dados;

	p->qnt--;

	return p->dados[--p->fim];

}

bool lista_vazia(lista l) {
	return l.qnt <= 0;
}

bool lista_cheia(lista l) {
	return l.qnt >= TAM_MAX;
}

bool enfileirar(lista* f, type n) {
	if (lista_cheia(*f)) return false;

	f->dados[f->fim] = n;

	f->fim = (f->fim + 1) % TAM_MAX;

	f->qnt++;

	return true;
}

type desenfileirar(lista* f) {
	if (lista_vazia(*f)) return f->dados;

	f->inicio = (f->inicio + 1) % TAM_MAX;

	f->qnt--;
	
	return f->dados[f->inicio - 1];
}

type acessar_primeiro(lista f) {
	if (lista_vazia(f)) return f.dados;

	return f.dados[f.inicio];
}

type acessar_ultimo(lista f) {
	if (lista_vazia(f)) return f.dados;

	return f.dados[f.fim - 1];
}

void print_sequencial(lista l) {
	for (int i = l.inicio; l.qnt; i++) {
		printf("%d ", l.dados[i % TAM_MAX]);
		l.qnt--;
	}
	printf("\n");
}

void init_lista_encadeada(lista_encadeada* le) {
	le->inicio = le->fim = NULL;
	le->qnt = 0;
}

bool empilhar_encadeada(lista_encadeada* le, type n) {
	no_lista* novo_no = malloc(sizeof(no_lista));
	if (!novo_no) return false;
	novo_no->dado = n;
	novo_no->prox = NULL;
	novo_no->ant = le->fim;

	if (!le->inicio) le->inicio = novo_no;
	else le->fim->prox = novo_no;

	le->fim = novo_no;
	le->qnt++;

	return true;
}

bool desempilhar_encadeada(lista_encadeada* le, type* t) {
	if (!le->fim) {
		init_lista_encadeada(le);
		*t = 0;
		return false;
	}
	no_lista* no_temp = le->fim;
	*t = no_temp->dado;


	if (!no_temp->ant) le->inicio = le->fim = NULL;
	else {
		le->fim = no_temp->ant;
		le->fim->prox = NULL;
	}
	free(no_temp);

	le->qnt--;

	return false;
}

bool desenfileirar_encadeada(lista_encadeada* le, type* t) {
	if (!le->inicio) {
		init_lista_encadeada(le);
		*t = 0;
		return false;
	}

	no_lista* no_atual = le->inicio;
	*t = no_atual->dado;


	if (!no_atual->prox) le->inicio = le->fim = NULL;
	else {
		le->inicio = no_atual->prox;
		le->inicio->ant = NULL;
	}
	free(no_atual);

	le->qnt--;

	return true;
}

bool inserir_encadeado(lista_encadeada* le, type n, int k) {
	if (k < 0 || k > le->qnt - 1) return false;
	
	no_lista* no_atual;

	if (k < le->qnt / 2) {
		no_atual = le->inicio;
		for (int i = 0; i < k; i++) no_atual = no_atual->prox;
	}
	else {
		no_atual = le->fim;
		for (int i = le->qnt - 1; i > k; i--) no_atual = no_atual->ant;
	}

	no_lista* no_anterior = no_atual->ant;
	no_lista* novo_no = malloc(sizeof(no_lista));
	if (!novo_no) return false;
	novo_no->dado = n;
	novo_no->prox = no_atual;
	novo_no->ant = no_anterior;
	no_atual->ant = novo_no;
	no_anterior->prox = novo_no;

	le->qnt++;

	return true;
}
