#include <stdio.h>
#include <stdlib.h>

struct arraylist {
    int* vetor;
    int qtdade;//quantidade de elementos ja adicionados na lista
    int capacidade;//capacidade do arraylist
};

struct arraylist* inicializar(int capacidade) {
    //aloco memoria para o struct lista
    struct arraylist* lista = (struct arraylist*)malloc(sizeof(struct arraylist));
    //alocamos memoria para o endereco inical do arraylist (calloc inicializa todos os elementos com 0)
    lista->vetor = (int*)calloc(capacidade, sizeof(int));
    lista->qtdade = 0;//a quantidade de elementos ja adicionados na lista eh igual a 0
    lista->capacidade = capacidade;
    return lista;
}

int obterElementoEmPosicao(struct arraylist* lista, int posicao) {
    /*Para obter um elemento, eu preciso verificar se essa posicao solicitada existe, e tambem
    * se essa posicao eh menor do que a quantidade de elemetnos inseridos*/
    if (posicao >= 0 && posicao < lista->qtdade) {
        return lista->vetor[posicao];
    }
}

void duplicarCapacidade(struct arraylist* lista) {
    //aumento o tamanho de bloco de memoria alocado, e se necessario, realoco ele para outro lugar.
    lista->vetor = (int*)realloc(lista->vetor, 2 * lista->capacidade * sizeof(int));
    //duplico a capacidade do arraylist
    lista->capacidade = 2 * (lista->capacidade);
}

void inserirElementoNoFim(struct arraylist* lista, int valor) {
    /*antes de inserir um elemento no fim da lista, eu preciso verificar se o indice do arraylist eh o utlimo, e caso seja, 
    * eu so consigo inserir um novo elemento se eu aumentar o tamanho do arraylist*/
    if (lista->qtdade == lista->capacidade) {
        duplicarCapacidade(lista);
    }
    lista->vetor[lista->qtdade] = valor;
    lista->qtdade++;//ao final da insercao, eu tenho que atualizar a quantidade de elementos adicionados no arraylist
}

void inserirElementoEmPosicao(struct arraylist* lista, int valor, int posicao) {
    /*preciso verificar se a posicao que eu quero inserir o elemento eh valida, ou seja, se eh positiva e 
    * se ela eh menor do que a quantidade de elementos adicionados (caso contrario, eu estaria inserindo um elemento no fim do arraylist)*/
    if (posicao>=0 && posicao<=lista->qtdade) {
        /*se a quantidade de elementos adicionados for igual a capacidade do arraylist, eu preciso duplicar o tamanho da lista,
        pois so assim caberia um novo elemento*/
        if (lista->qtdade == lista->capacidade) {
            duplicarCapacidade(lista);
        }

        /* Suponha que o arraylist seja esse: 5 3 9, e eu quero inserir 1 na posicao 0, entao primeiramente eu preciso mover todos 
        * os elementos da posicao 0 em diante para a direita, e so depois eu insiro o elemento na posicao 0:
        5 3 9 _ _ _ qtdade = 3, i = 3
        5 3 _ 9 _ _ i = 3
        5 _ 3 9 _ _ i = 2
        _ 5 3 9 _ _ i = 1
        1 5 3 9 _ _
        */
        for (int i = lista->qtdade; i > posicao; i--) { //movo os elementos para a direita
            lista->vetor[i] = lista->vetor[i - 1];
        }
        lista->vetor[posicao] = valor; //insiro o elemento na posicao dada
        lista->qtdade++;//atualizo a quantidade de elementos inseridos
    }
}

void atualizarElemento(struct arraylist* lista, int valor, int posicao) {
    if (posicao>=0 && posicao<lista->qtdade) { //verifico se a posicao de atualizacao eh valida
        lista->vetor[posicao] = valor;
    }
}

int getTamanho(struct arraylist* lista) {
    return lista->qtdade;
}

void removerElementoNoFim(struct arraylist* lista) {
    lista->capacidade--;
    lista->qtdade--;
}

void removerElementoEmPosicao(struct arraylist* lista, int posicao) {
    if (posicao>=0 && posicao<lista->qtdade) { //verifico se a posicao de remocao eh valida
        /* 9 6 8 7 -> posicao 0
        * 6 6 8 7 -> posicao 1
        * 6 8 8 7 -> posicao 2
        * 6 8 7 7
        * 6 8 7
        */
        while (posicao<(lista->qtdade-1)) {
            lista->vetor[posicao] = lista->vetor[posicao+1];
            posicao++;
        }
        lista->qtdade--;
    }
}

//Algoritmo de busca binaria com custo Log(N) na base 2
int buscaBin(int* vetor , int inicio , int fim, int valor){
    int meio = (fim + inicio)/2;//Pega o elemento do meio
    if(valor == vetor[meio]){ //Verificamos se o valor do vetor do meio eh igual ao valor procurado
        return meio;
    }
    else if(valor > vetor[meio]){ //Se o valor procurado eh maior que o do meio do vetor
        return buscaBin(vetor,meio + 1,fim,valor); //Fazemos uma nova busca mas com o valor do inicio da busca sendo o meio+1, ja que meio foi comparado antes
    }
    else if(valor < vetor[meio]){ //Se o valor procurado eh menor que o do meio do vetor
        return buscaBin(vetor,inicio,meio - 1,valor);//Fazemos uma nova busca mas com o valor do fim da busca sendo o meio-1, ja que meio foi comparado antes
    }
    return -1; //Caso o valor buscado nao exista no vetor, retornamos uma posicao erro como -1
}

//Funcao que retorna a posicao que o nosso valor tem ou deveria ter no nosso vetor ordenado
int posOrdenadoBin(int* vetor , int inicio , int fim , int valor ){
    int meio = (fim + inicio)/2;
    if(valor == vetor[meio]){
        return meio;
    }
    else if(valor > vetor[meio]){
        return buscaBin(vetor,meio + 1,fim,valor);
    }
    else if(valor < vetor[meio]){
        return buscaBin(vetor,inicio,meio - 1,valor);
    }
    return fim; //caso o valor nao exista no vetor, retornamos o valor fim, que substituindo ele pelo nosso valor, ainda continuara ordenado
}

void inserirElementoEmListaOrdenada(struct arraylist* lista, int valor){
    int posicao = posOrdenadoBin(lista->vetor , 0 , lista->qtdade , valor);
    //A posicao que o nosso valor deve assumir no vetor ordenado
    inserirElementoEmPosicao(lista , valor , posicao); //inserindo nosso valor na posicao
}

void exibirLista(struct arraylist* lista) {
    printf("[");
    for (int i = 0; i < lista->qtdade; i++) {
        printf("%d", lista->vetor[i]);
        if (i < lista->qtdade - 1) {
            printf(", ");
        }
    }
    printf("]");
}