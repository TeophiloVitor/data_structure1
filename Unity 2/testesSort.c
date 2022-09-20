#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

void swap(int* v, int i, int j){
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int particiona(int* v, int ini, int fim){
    int pIndex = ini;

    //a seguir parte do codigo que realiza a randomizacao
    //hora atual do sistema
    srand(time(NULL));
    //teremos uma posicao aleatoria entre inicio e fim
    int posAleatoria = ini+(rand()%(fim+1-ini));
    //realizamos o swap para que posAleatoria seja o fim
    swap(v, posAleatoria, fim);

    int pivo = v[fim];
    for(int i = ini; i < fim; i++){
        if(v[i] <= pivo){
            swap(v,i,pIndex);
            pIndex++;
        }
    }
    swap(v,pIndex,fim);
    return pIndex;
}

void quickSort(int* v, int ini, int fim){
    if(fim>ini){                        
        int indexPivo = particiona(v,ini,fim);
        quickSort(v,ini,indexPivo-1);
        quickSort(v,indexPivo+1,fim); 
    }
}

void imprimir(int* vetor, int tamanho) {
    printf("[");
    for(int i = 0; i <= tamanho - 1; i++){
        if(i == tamanho - 1){
            printf("%d] \n", vetor[i]);
        }else{
            printf("%d,", vetor[i]);
        }
    }
}

void gerarVetores(int tamanhoVetor, int* vetorAleatorio, int* vetorOrdenado, int* vetorDecrescente) {
    for (int i = 0; i < tamanhoVetor; i++) {
        vetorAleatorio[i] = rand() % INT_MAX;
        vetorOrdenado[i] = vetorAleatorio[i];
    }
    quickSort(vetorOrdenado,0,tamanhoVetor); //MUDAR
    int posicao = 0;
    for (int i = tamanhoVetor - 1; i >= 0; i--) {
        vetorDecrescente[posicao] = vetorOrdenado[i];
        posicao++;
    }
}

void executar(int* vetor, int quantidadeExec, int tamanhoVetor, double* tempExec) {
    clock_t t_inicial, t_final;
    int vetorAux[tamanhoVetor];

    for(int i = 0; i < tamanhoVetor; i++){
        vetorAux[i] = vetor[i];
    }

    for (int i = 0; i < quantidadeExec; i++) {
        t_inicial = clock();
        quickSort(vetor,0,tamanhoVetor); //MUDAR
        t_final = clock();
        tempExec[i] = (double) (t_final - t_inicial);

        for(int i = 0; i < tamanhoVetor; i++){
            vetor[i] = vetorAux[i];
        }
    }
}

double mediaTempo(double* tempExec, int quantidadeExec) {
    double somaTempo = 0.0;
    for (int i = 0; i < quantidadeExec; i++) {
        somaTempo += tempExec[i];
    }
    return somaTempo / quantidadeExec;
}

double medianaTempo(double* tempExec, int quantidadeExec) {
    if (quantidadeExec % 2 == 0) {
        int metade = quantidadeExec / 2;
        return (double) ((tempExec[metade - 1] + tempExec[metade]) / 2);
    } else {
        int posicao = (quantidadeExec + 1) / 2;
        return tempExec[posicao - 1];
    }
}

int main (){
    int tamanhoVetor = 10000;
    int quantidadeExec = 10;
    int vetorAleatorio[tamanhoVetor];
    int vetorOrdenado[tamanhoVetor];
    int vetorDecrescente[tamanhoVetor];
    double tempExec[quantidadeExec];
    srand(30);
    gerarVetores(tamanhoVetor, vetorAleatorio, vetorOrdenado, vetorDecrescente);
    executar(vetorOrdenado, quantidadeExec, tamanhoVetor, tempExec);
    printf("-----------------------------------------------------------------------------------------\n");
    printf("Tempo de execucao c/ vetor ordenado = %f s\n", (mediaTempo(tempExec, quantidadeExec)/100));
    printf("-----------------------------------------------------------------------------------------\n");
    executar(vetorAleatorio, quantidadeExec, tamanhoVetor, tempExec);
    printf("Tempo de execucao c/ vetor aleatorio = %f s\n", (mediaTempo(tempExec, quantidadeExec)/100));
    printf("-----------------------------------------------------------------------------------------\n");
    executar(vetorDecrescente, quantidadeExec, tamanhoVetor, tempExec);
    printf("Tempo de execucao c/ com vetor ordenado decrescente = %f s\n", (mediaTempo(tempExec, quantidadeExec)/100));
    printf("-----------------------------------------------------------------------------------------\n");
    return 0;
}