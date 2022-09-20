#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <queue>
using namespace std;

void atualizar(struct noBstAvl* no);
struct noBstAvl* balancear(struct noBstAvl* no);
struct noBstAvl* rebalancearEsqEsq(struct noBstAvl* no);
struct noBstAvl* rebalancearEsqDir(struct noBstAvl* no);
struct noBstAvl* rebalancearDirDir(struct noBstAvl* no);
struct noBstAvl* rebalancearDirEsq(struct noBstAvl* no);

struct avl {
    struct noBstAvl* raiz;
    int tam;
};

struct noBstAvl {
    int val;
    int altura;
    int balanco;
    struct noBstAvl* esq;
    struct noBstAvl* dir;
};

struct avl* alocarAvl() {
    struct avl* Avl = (struct avl*)malloc(sizeof(struct avl));

    Avl->raiz = NULL;
    Avl->tam = 0;

    return Avl;
}

struct noBstAvl* alocarNovoNo(int val) {
    struct noBstAvl* novoNo = (struct noBstAvl*)malloc(sizeof(struct noBstAvl));
    
    novoNo->val = val;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->altura = 0;
    novoNo->balanco = 0;
    
    return novoNo;
}

struct noBstAvl* rotacaoDireita(struct noBstAvl* arvore) {
    struct noBstAvl* esq = arvore->esq;
    arvore->esq = arvore->esq->dir;
    esq->dir = arvore;
    atualizar(arvore);
    atualizar(esq);
    return esq;
}

struct noBstAvl* rotacaoEsquerda(struct noBstAvl* arvore) {
    struct noBstAvl* dir = arvore->dir;
    arvore->dir = arvore->dir->esq;
    dir->esq = arvore;
    atualizar(arvore);
    atualizar(dir);
    return dir;
}

void inserirNo(struct noBstAvl** raiz, int val) {
    if (*raiz == NULL)
    {
        *raiz = alocarNovoNo(val);
    }
    else{
        if ((*raiz)->val > val){
                inserirNo(&((*raiz)->esq), val);
                
        }
        else{
            inserirNo(&((*raiz)->dir), val);
        }
        atualizar(*raiz);
        *raiz = balancear(*raiz);
    }
}

void inserir(struct avl* avl, int val) {
    inserirNo(&(avl)->raiz,val);
    avl->tam++;
}

void atualizar(struct noBstAvl* no) {
    int temp1, temp2, maximo;
    temp1 = (no->esq == NULL) ? -1 : no->esq->altura;
    temp2 = (no->dir == NULL) ? -1 : no->dir->altura;
    maximo = temp1 > temp2 ? temp1 : temp2;

    no->altura = 1 + maximo;
    no->balanco = temp2 - temp1;
}

struct noBstAvl* balancear(struct noBstAvl* no) {
    if(no == NULL){
        return no;
    }
    if (no->balanco == -2) {
        if (no->esq->balanco <= 0) {
            return (rebalancearEsqEsq(no));
        }
        else {
            return (rebalancearEsqDir(no));
        }
    }
    else if (no->balanco == +2) {
        if (no->dir->balanco >= 0) {
            return (rebalancearDirDir(no));
        }
        else {
            return (rebalancearDirEsq(no));
        }
    }
    return no;
}

struct noBstAvl* rebalancearEsqEsq(struct noBstAvl* no) {
    struct noBstAvl *novaRaiz = rotacaoDireita(no);

    return novaRaiz;
}

struct noBstAvl* rebalancearEsqDir(struct noBstAvl* no) {
    struct noBstAvl *novaRaiz = no;
    novaRaiz->esq = rotacaoEsquerda(novaRaiz->esq);
    novaRaiz = rotacaoDireita(novaRaiz);

    return novaRaiz;
}

struct noBstAvl* rebalancearDirDir(struct noBstAvl* no) {
    struct noBstAvl *novaRaiz = rotacaoEsquerda(no);

    return novaRaiz;
}

struct noBstAvl* rebalancearDirEsq(struct noBstAvl* no) {
    struct noBstAvl *novaRaiz = no;
    novaRaiz->dir = rotacaoDireita(novaRaiz->dir);
    novaRaiz = rotacaoEsquerda(novaRaiz);

    return novaRaiz;
}

int max(struct noBstAvl* raiz) {
    if(raiz == NULL){
        return NULL;
    }
    if(raiz->dir != NULL){
        return max(raiz->dir);
    }
    else{
        return raiz->val;
    }
}

int min(struct noBstAvl* raiz) {
    if(raiz == NULL){
        return NULL;
    }
    if(raiz->esq != NULL){
        return min(raiz->esq);
    }
    else{
        return raiz->val;
    }
}

struct noBstAvl* auxMin(struct noBstAvl* raiz) {
    while (raiz->esq != NULL) {
        raiz = raiz->esq;
    }
    return raiz;
}

struct noBstAvl* removerNo(struct noBstAvl* raiz, int val) {
    if (raiz == NULL) {
        return raiz;
    }
    else if (val < raiz->val) {
        raiz->esq = removerNo(raiz->esq, val);
    }
    else if (val > raiz->val) {
        raiz->dir = removerNo(raiz->dir, val);
    }
    else {
        atualizar(raiz);
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            raiz = NULL;
        }
        else if (raiz->esq == NULL) {
            struct noBstAvl* aux = raiz;
            raiz = raiz->dir;
            free(aux);
        }
        else if (raiz->dir == NULL) {
            struct noBstAvl* aux = raiz;
            raiz = raiz->esq;
            free(aux);
        }
        else {
            struct noBstAvl* aux = auxMin(raiz->dir);
            raiz->val = aux->val;
            raiz->dir = removerNo(raiz->dir, aux->val);
        }
    }
    return balancear(raiz);
}

void remover(struct avl* avl, int val) {
    if (removerNo(avl->raiz, val) != NULL) {
        avl->tam--;
    }
}

void imprimir(queue<struct noBstAvl*> nosImpressao);

void imprimir(struct noBstAvl* raiz) {
    queue<struct noBstAvl*> nosImpressao;
    nosImpressao.push(raiz);
    imprimir(nosImpressao);
}

void imprimir(queue<struct noBstAvl*> nosImpressao) {

    queue<struct noBstAvl*> nosImpressaoProxNivel;

    while (!nosImpressao.empty()) {
        struct noBstAvl* noImpressao = nosImpressao.front();
        if(noImpressao != NULL){
            if (noImpressao->esq != NULL) 
                nosImpressaoProxNivel.push(noImpressao->esq);
            else
                nosImpressaoProxNivel.push(NULL);
            if (noImpressao->dir != NULL) 
                nosImpressaoProxNivel.push(noImpressao->dir);
            else
                nosImpressaoProxNivel.push(NULL);
        }
        nosImpressao.pop();

        if (noImpressao != NULL) {
            cout << to_string(noImpressao->val) << " | ";
        }
        else {
            cout << "N | ";
        }
    }
    cout << endl << endl;
    if(!nosImpressaoProxNivel.empty())
        imprimir(nosImpressaoProxNivel);
} 
