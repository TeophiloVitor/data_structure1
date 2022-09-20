#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedstack {
    struct no* topo;
    int qtdade;
};

struct linkedstack* inicializar() {
    struct linkedstack* pilha = (struct linkedstack*)malloc(sizeof(struct linkedstack));
    pilha->topo = NULL;
    pilha->qtdade = 0;

    return pilha;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo->prox = NULL;
    novoNo->val = valor;

    return novoNo;
}

//retornar true se a pilha for nula ou vazia
bool vazia(struct linkedstack* pilha) {
    if (pilha != NULL) {
        if (pilha->qtdade != 0) {
            return false;
        }
    }
    return true;
}

//se a pilha estiver nula, instancie a pilha
//por causa da possibilidade de instanciacao usamos struct linkedstack**
void empilhar(struct linkedstack** pilha, int valor) {
    struct linkedstack* ref;
    struct no* novoNo = alocarNovoNo(valor);
    if (*pilha == NULL) {
        *pilha = inicializar();
    }

    ref = *pilha;

    if (ref->topo != NULL) {
        novoNo->prox = ref->topo;
    }
    ref->topo = novoNo;
    ref->qtdade++;
}

//decrementar qtdade se a pilha nao estiver nula ou vazia
void desempilhar(struct linkedstack* pilha) {
    if (vazia(pilha) != true) {
        struct no* temp = pilha->topo;
        pilha->topo = pilha->topo->prox;
        free(temp);
        pilha->qtdade--;
    }
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int desempilharRetornando(struct linkedstack* pilha) {
    int retorno = vazia(pilha) == true ? INT_MIN : pilha->topo->val;
    desempilhar(pilha);
    return retorno;
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int topo(struct linkedstack* pilha) {
    if (vazia(pilha) == true) {
        return INT_MIN;
    }
    return pilha->topo->val;
}

void exibirPilha(struct linkedstack* pilha) {
    //usamos o aux para percorrer a lista
    if (!vazia(pilha)) {
        struct no* aux = pilha->topo;
        //navega partindo do topo ate chegar NULL
        printf("_\n");
        do {
            printf("%d\n", aux->val);
            aux = aux->prox;
        } while (aux != NULL);
        printf("_");
    }
    else {
        printf("A pilha esta vazia!");
    }
}