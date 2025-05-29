#include "prova.h"

void init_lista(lista* l) {
	l->qnt = 0;
	l->fim = 0;
	l->inicio = 0;
}

bool inserir(lista* l, type n, int pos) {
	if (lista_cheia(*l) || pos > l->qnt || pos < 0) return false;

	int i;
	for (i = l->qnt; i >= pos; i--) l->dados[i + 1] = l->dados[i];
	l->dados[i + 1] = n;

	l->qnt++;

	return true;
}

bool adicionar(lista* l, type n) {
	if (l->qnt >= TAM_LISTA) return false;

	l->dados[l->qnt++] = n;

	return true;
}

bool inserir_ordenado(lista* l, type n) {
	if (l->qnt >= TAM_LISTA) return false;

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
	return l.qnt >= TAM_LISTA;
}

bool enfileirar(lista* f, type n) {
	if (lista_cheia(*f)) return false;

	f->dados[f->fim] = n;

	f->fim = (f->fim + 1) % TAM_LISTA;

	f->qnt++;

	return true;
}

type desenfileirar(lista* f) {
	if (lista_vazia(*f)) return f->dados;

	f->inicio = (f->inicio + 1) % TAM_LISTA;

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

void heap_minimo(lista* l) {
	int atual = (l->qnt - 1) / 2;

	while (atual >= 0) {
		int esquerda = 2 * atual + 1;
		int direita = 2 * atual + 2;
		bool maior_esquerda = l->dados[atual] > l->dados[esquerda];
		bool maior_direita = direita < l->qnt && l->dados[atual] > l->dados[direita];
		
		int copia_atual = atual;
		while (maior_esquerda || maior_direita) {
			int troca;
			if (maior_esquerda && maior_direita) troca = l->dados[esquerda] < l->dados[direita] ? esquerda : direita;
			else if (maior_esquerda) troca = esquerda;
			else if (maior_direita) troca = direita;

			int aux = l->dados[copia_atual];
			l->dados[copia_atual] = l->dados[troca];
			l->dados[troca] = aux;

			copia_atual = troca;
			esquerda = 2 * copia_atual + 1;
			direita = 2 * copia_atual + 2;

			maior_esquerda = esquerda < l->qnt && l->dados[copia_atual] > l->dados[esquerda];
			maior_direita = direita < l->qnt && l->dados[copia_atual] > l->dados[direita];
		}
		atual--;
	}
}

void heap_maximo(lista* l) {
	int atual = (l->qnt - 1) / 2;

	while (atual >= 0) {
		int esquerda = 2 * atual + 1;
		int direita = 2 * atual + 2;

		bool menor_esquerda = l->dados[atual] < l->dados[esquerda];
		bool menor_direita = direita < l->qnt && l->dados[atual] < l->dados[direita];

		int copia_atual = atual;
		while (menor_esquerda || menor_direita) {
			int troca;
			if (menor_esquerda && menor_direita) troca = l->dados[esquerda] > l->dados[direita] ? esquerda : direita;
			else if (menor_esquerda) troca = esquerda;
			else if (menor_direita) troca = direita;

			int aux = l->dados[copia_atual];
			l->dados[copia_atual] = l->dados[troca];
			l->dados[troca] = aux;

			copia_atual = troca;
			esquerda = 2 * copia_atual + 1;
			direita = 2 * copia_atual + 2;

			menor_esquerda = esquerda < l->qnt && l->dados[copia_atual] < l->dados[esquerda];
			menor_direita = direita < l->qnt && l->dados[copia_atual] < l->dados[direita];
		}
		atual--;
	}
}

void print_sequencial(lista l) {
	for (int i = l.inicio; l.qnt; i++) {
		printf("%d ", l.dados[i % TAM_LISTA]);
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
	if (k < 0 || k > le->qnt) return false;
	
	no_lista* no_atual;

	if (k == le->qnt) return empilhar_encadeada(le, n);

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

	if (!no_anterior) le->inicio = novo_no;
	else no_anterior->prox = novo_no;

	le->qnt++;

	return true;
}

bool inserir_ordenado_encadeado(lista_encadeada* le, type n) {
	no_lista* no_atual = le->inicio;

	while (no_atual && no_atual->dado < n) no_atual = no_atual->prox;
	
	if (!no_atual) return empilhar_encadeada(le, n);

	no_lista* no_anterior = no_atual->ant;

	no_lista* novo_no = malloc(sizeof(no_lista));
	if (!novo_no) return false;

	novo_no->dado = n;
	novo_no->prox = no_atual;
	novo_no->ant = no_anterior;
	no_atual->ant = novo_no;

	if (!no_anterior) le->inicio = novo_no;
	else no_anterior->prox = novo_no;

	le->qnt++;

	return true;
}

no_lista* acessar_encadeado(lista_encadeada le, int i) {
	if (i < 0 || i > le.qnt - 1) return NULL;

	no_lista* no_atual;
	if (i < le.qnt / 2) {
		no_atual = le.inicio;
		for (int j = 0; j < i; j++) no_atual = no_atual->prox;
	}
	else {
		no_atual = le.fim;
		for (int j = le.qnt - 1; j > i; j--) no_atual = no_atual->ant;
	}

	return no_atual;
}

int localizar_encadeado(lista_encadeada le, type n, int k) {
	no_lista* no_atual = le.inicio;

	int ocorrencias = 1;
	for (int i = 0; i < le.qnt; i++) {
		if (no_atual->dado == n) {
			if (ocorrencias == k) return i;
			ocorrencias++;
		}
		no_atual = no_atual->prox;
	}

	return -1;
}

bool juntar_encadeado(lista_encadeada* le1, lista_encadeada* le2) {
	if (!le2->inicio || !le1->fim) return false;
	
	le1->fim->prox = le2->inicio;
	le2->inicio->ant = le1->fim;

	le1->fim = le2->fim;
	le2->inicio = le1->inicio;

	le1->qnt = le2->qnt = le1->qnt + le2->qnt;

	return true;
}

bool alterar_encadeado(lista_encadeada* le, int i, type n) {
	if (i < 0 || i > le->qnt - 1) return false;

	no_lista* no_atual;
	if (i < le->qnt / 2) {
		no_atual = le->inicio;
		for (int j = 0; j < i; j++) no_atual = no_atual->prox;
	}
	else {
		no_atual = le->fim;
		for (int j = le->qnt - 1; j > i; j--) no_atual = no_atual->ant;
	}

	no_atual->dado = n;

	return true;
}

void print_lista_encadeada(lista_encadeada le) {
	no_lista* no_atual = le.inicio;

	for (int i = 0; i < le.qnt; i++) {
		printf("%d ", no_atual->dado);
		no_atual = no_atual->prox;
	}
	printf("\n");
}

void init_arvore(arvore* a) {
	a->raiz = NULL;
	a->qnt = 0;
}

static void ajustar_altura_no(no_arvore* no_atual) {
	no_arvore* no_esquerdo = no_atual->esq;
	no_arvore* no_direito = no_atual->dir;

	if (no_esquerdo && no_direito) {
		no_atual->altura = (no_esquerdo->altura > no_direito->altura ? no_esquerdo->altura : no_direito->altura) + 1;
		no_atual->bal = no_direito->altura - no_esquerdo->altura;
	}
	else if (no_esquerdo) {
		no_atual->altura = no_esquerdo->altura + 1;
		no_atual->bal = -no_esquerdo->altura - 1;
	}
	else if (no_direito) {
		no_atual->altura = no_direito->altura + 1;
		no_atual->bal = no_direito->altura + 1;
	}
}

static void rotacao_esquerda(no_arvore** no_desbalanceado) {
	no_arvore* no_temp = (*no_desbalanceado)->dir->esq;
	no_arvore* no_direita = (*no_desbalanceado)->dir;

	no_direita->esq = (*no_desbalanceado);
	(*no_desbalanceado)->dir = no_temp;

	(*no_desbalanceado) = no_direita;

	ajustar_altura_no((*no_desbalanceado)->esq);
	ajustar_altura_no(*no_desbalanceado);
}

static void rotacao_direita(no_arvore** no_desbalanceado) {
	no_arvore* no_temp = (*no_desbalanceado)->esq->dir;
	no_arvore* no_esquerda = (*no_desbalanceado)->esq;

	no_esquerda->dir = (*no_desbalanceado);
	(*no_desbalanceado)->esq = no_temp;

	(*no_desbalanceado) = no_esquerda;

	ajustar_altura_no((*no_desbalanceado)->dir);
	ajustar_altura_no(*no_desbalanceado);
}

static void balancear_arvore(no_arvore** no_atual) {
	if ((*no_atual)->bal > 1) {
		if ((*no_atual)->dir->bal > 0) rotacao_esquerda(no_atual);
		else {
			rotacao_direita(&(*no_atual)->dir);
			rotacao_esquerda(no_atual);
		}
	}
	else {
		if ((*no_atual)->esq->bal < 1) rotacao_direita(no_atual);
		else {
			rotacao_esquerda(&(*no_atual)->esq);
			rotacao_direita(no_atual);
		}
	}
}

void inserir_arvore(arvore* a, no_arvore** no_atual, type n) {
	if (!*no_atual) {
		*no_atual = malloc(sizeof(no_arvore));
		(*no_atual)->dado = n;
		(*no_atual)->ocorrencias = 1;
		(*no_atual)->altura = (*no_atual)->bal = 0;
		(*no_atual)->esq = (*no_atual)->dir = NULL;
		a->qnt++;
		return;
	}

	if ((*no_atual)->dado > n) inserir_arvore(a, &(*no_atual)->esq, n);
	else if ((*no_atual)->dado < n) inserir_arvore(a, &(*no_atual)->dir, n);
	else {
		(*no_atual)->ocorrencias++;
		a->qnt++;
		return;
	}

	ajustar_altura_no(*no_atual);
	if ((*no_atual)->bal > 1 || (*no_atual)->bal < -1) balancear_arvore(no_atual);
}

void init_hash(hash h) {
	for (int i = 0; i < TAM_HASH; i++) h[i] = NULL;
}

int hash_func(type n) {
	type copia = n;
	int tam = 0;
	while (copia > 0) {
		copia /= 10;
		tam++;
	}

	return (n * tam) % TAM_HASH;
}

bool adicionar_hash(hash h, type n) {
	int indice_hash = hash_func(n);

	no_lista* novo_no = malloc(sizeof(no_lista));
	if (!novo_no) return false;
	novo_no->dado = n;
	novo_no->prox = h[indice_hash];
	novo_no->ant = NULL;
	
	if (novo_no->prox) novo_no->prox->ant = novo_no;
	h[indice_hash] = novo_no;

	return true;
}

no_lista* acessar_hash(hash h, type n) {
	int indice_hash = hash_func(n);

	no_lista* no_atual = h[indice_hash];
	while (no_atual && no_atual->dado != n) no_atual = no_atual->prox;

	return no_atual;
}

void remover_hash(hash h, type n) {
	int indice_hash = hash_func(n);

	no_lista** no_atual = &h[indice_hash];
	while ((*no_atual) && (*no_atual)->dado != n) no_atual = &(*no_atual)->prox;

	if (*no_atual) {
		no_lista* no_temp = *no_atual;
		*no_atual = (*no_atual)->prox;
		if (*no_atual) (*no_atual)->ant = no_temp->ant;
		free(no_temp);
	}
}
