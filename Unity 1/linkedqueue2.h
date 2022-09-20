#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct no {
    int val;
    struct no* prox;
};


struct linkedqueue {
    struct no* frente;
    struct no* tras;
    int qtdade;
};

struct linkedqueue* inicializar() {
    struct linkedqueue* fila = (struct linkedqueue*)malloc(sizeof(struct linkedqueue));
    fila->frente = NULL;
    fila->tras = NULL;
    fila->qtdade = 0;

    return fila;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo->prox = NULL;
    novoNo->val = valor;

    return novoNo;
}

bool vazia(struct linkedqueue* fila) {
    if (fila != NULL) {
        if (fila->qtdade != 0 && fila->frente != NULL) {
            return false;
        }
    }
    return true;
}

//se a fila estiver nula, instancie a fila
//por causa da possibilidade de instanciacao usamos struct linkedqueue**
void enfileirar(struct linkedqueue** fila, int val) {
    struct linkedqueue* ref;
    struct no* novoNo = alocarNovoNo(val);
    if (*fila == NULL) {
        *fila = inicializar();
    }

    ref = *fila;
    if (ref->frente != NULL) {
        ref->tras->prox = novoNo;
    }
    else {
        ref->frente = novoNo;
    }

    ref->tras = novoNo;
    ref->qtdade++;
}

//retorne a constante INT_MIN se a fila for nula ou vazia
//lembrem de desalocar o no removido (free)
int desenfileirar(struct linkedqueue* fila) {
    if (vazia(fila) == true) {
        return INT_MIN;
    }

    int retorno = fila->frente->val;
    struct no* aux = fila->frente;
    fila->frente = fila->frente->prox;
    fila->qtdade--;
    free(aux);
    return retorno;
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int frente(struct linkedqueue* fila) {
    if (vazia(fila)) {
        return INT_MIN;
    }
    return fila->frente->val;
}