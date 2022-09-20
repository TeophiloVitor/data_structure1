int* selectionSort(int* vetor, int tam){
	for(int i = 0; i < tam; i++){
		int menor = i;
		for(int j = i; j < tam; j++){
			if(vetor[j] < vetor[menor]){
				menor = j;
			}
		}
		int aux = vetor[i]; //swap
		vetor[i] = vetor[menor];
		vetor[menor] = aux;
	}
	return vetor;
}

int* insertionSort(int* vetor, int tam){
	for(int i = 1; i < tam; i++){
		for(int j = i; j > 0 && vetor[j] < vetor[j-1]; j--){
			int aux = vetor[j]; //swap
			vetor[j] = vetor[j-1];
			vetor[j-1] = aux;
		}
	}
	return vetor;
}

int* bubbleSort(int* vetor, int tam){
	for(int i = 0; i<tam-1; i++){
		for(int j = 0; j < tam-i-1; j++){
			if(vetor[j] > vetor[j+1]){
				int aux = vetor[j]; //swap
				vetor[j] = vetor[j+1];
				vetor[j+1] = aux;
			}
		}
	}
	return vetor;
}

void merge(int* v, int tamv, int* v1, int tamv1, int* v2, int tamv2){
    int indexv = 0;
    int indexv1 = 0;
    int indexv2 = 0;
    while(indexv1 < tamv1 && indexv2 < tamv2){
	int menor;
        if(v1[indexv1] <= v2[indexv2]){
            menor = v1[indexv1];
            indexv1++;
        } else{
            menor = v2[indexv2];
            indexv2++;
        }
	v[indexv] = menor;
        indexv++;
    }
    //ainda poderíamos ter elementos no vetor v1 que não foram copiados para v
    while(indexv1 < tamv1){
        v[indexv] = v1[indexv1];
        indexv++;
        indexv1++;
    }
    //ainda poderíamos ter elementos no vetor v2 que não foram copiados para V
    while(indexv2 < tamv2){
        v[indexv] = v2[indexv2];
        indexv++;
        indexv2++;
    }
}

void mergeSort(int* v, int tamv){
    if(tamv>1){
        //primeiro quebramos o vetor em 2 vetores menores
        int meio = tamv/2;
        
        int tamv1 = meio;
        int* v1 = (int*)malloc(tamv1*sizeof(int));
        for(int i = 0; i < meio; i++){
            v1[i] = v[i];
        }

        int tamv2 = tamv-meio;
        int* v2 = (int*)malloc(tamv2*sizeof(int));
        for(int i = meio; i < tamv; i++){
            v2[i-meio] = v[i];
        }

        mergeSort(v1,tamv1);
        mergeSort(v2,tamv2);
        merge(v,tamv,v1,tamv1,v2,tamv2);
        
        free(v1);
        free(v2);
    }
}

int* countingSort (int* v, int tamv){
    //Descobrindo o maior valor do vetor
    int maior = v[0];
    for (int i = 0; i < tamv; i++){
        if (v[i] > maior)
            maior = v[i];
    }
    //Definindo o tamanho do vetor de ocorrências
    int tamVocorrencias = maior;
    int* vOcorrencias = (int*)calloc(tamVocorrencias,sizeof(int));
    //Incrementando a quantidade de valores repetidos na respectiva
    //posição
    for (int i = 0; i < tamv;i++){
        vOcorrencias[v[i]]++;
    }
    //Armazena em ordem crescente a soma cumulativa do vetor de
    //Ocorrências
    for (int i = 1; i <= tamVocorrencias; i++){
        vOcorrencias[i] += vOcorrencias[i-1];
    }
    //Definição do vetor ordenado
    int* vOrdenado = (int*)malloc(tamVocorrencias*sizeof(int));
    //Colocando valores no vetor ordenado
    for (int i = tam-1; i >= 0; i--) {
    	vOrdenado[vOcorrencias[v[i]] - 1] = v[i];
    	vOcorrencias[v[i]]--;
    }
    //Alterando valores do vetor inicial desordenado com os valores
    //do vetor ordenado
    for (int i = 0; i < tam; i++) {
        v[i] = vOrdenado[i];
    }
    //retornando o vetor ordenado
    return v;
}

int particao_aleatoria(int* v, int menor, int maior) {
    srand(time(0));
    //retorna um valor aleatorio entre 0 e n-1
    int random = menor + rand() % (maior - menor);
    //Swap para trocar o valor do pivo aleatorio na variavel "menor"
    int aux = v[random];
    v[random] = v[menor];
    v[menor] = aux;
    //inicializacao do pivo
    int pivo = v[menor];
    int i = menor - 1, j = maior + 1;
    //particionamento, apos inicializacao do pivo
    while (1) {
 
        do {
            i++;
        } while (v[i] < pivo);
 
        do {
            j--;
        } while (v[j] > pivo);
        //
        if (i >= j){
            return j;
        }
        //troca de valores
        int aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
}

int* quickSort(int* v, int menor, int maior){
    if (menor < maior) {
        int pi = particao_aleatoria(v, menor, maior);
 
        quickSort(v, menor, pi);
        quickSort(v, pi + 1, maior);
    }
    return v;
}	