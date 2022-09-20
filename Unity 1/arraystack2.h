#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct arraystack {
    int* elementos;
    int tamanho;    //tam do array
    int qtdade;     //qtdade de elementos no array
};

struct arraystack* inicializar(int tamArray) {
    struct arraystack* pilha = (struct arraystack*)malloc(sizeof(struct arraystack));
    pilha->elementos = (int*)calloc(tamArray, sizeof(int));
    pilha->qtdade = 0;
    pilha->tamanho = tamArray;

    return pilha;
}

void duplicarCapacidade(struct arraystack* pilha) {
    pilha->elementos = (int*)realloc(pilha->elementos, 2 * pilha->tamanho * sizeof(int));
    pilha->tamanho *= 2;
}

//se a pilha estiver nula, instancie a pilha com tamanho 10
//por causa da possibilidade de instanciacao usamos struct arraystack**
//se a pilha encher, duplique a capacidade do array
void empilhar(struct arraystack** pilha, int valor) {
    struct arraystack* ref;
    if (*pilha != NULL) {
        ref = *pilha;
        if (ref->tamanho == ref->qtdade) {
            duplicarCapacidade(*pilha);
        }
    }
    else {
        *pilha = inicializar(10);
        ref = *pilha;
    }
    ref->elementos[ref->qtdade] = valor;
    ref->qtdade++;
}

//retornar true se a pilha for nula ou vazia
bool vazia(struct arraystack* pilha) {
    if ( pilha != NULL) {
        if (pilha->qtdade != 0) {
            return false;
        }
    }
    return true;
}

//decrementar qtdade se a pilha nao estiver nula ou vazia
void desempilhar(struct arraystack* pilha) {
    if (vazia(pilha) != true) {
        pilha->qtdade--;
    }
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int desempilharRetornando(struct arraystack* pilha) {
    if (vazia(pilha) != true) {
        pilha->qtdade--;
        return pilha->elementos[pilha->qtdade];
    }
    return INT_MIN;
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int topo(struct arraystack* pilha) {
    if (vazia(pilha) == true) {
        return INT_MIN;
    }
    return pilha->elementos[pilha->qtdade - 1];
}

void imprimir(struct arraystack* pilha) {
    printf("_\n");
    for (int i = pilha->qtdade - 1; i >= 0; i--) {
        printf("%d\n", pilha->elementos[i]);
    }
    printf("_\n\n");
}
