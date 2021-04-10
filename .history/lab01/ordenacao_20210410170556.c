/*
  * Programa: Algoritmos de ordenação na linguagem C
  * Autor: Gabriele Jandres Cavalcanti
  * Universidade Federal do Rio de Janeiro
  * Data de criação: abril de 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 8

/* Aumenta o tamanho alocado para o vetor, quando necessário */
void overflow(int *vet[], int *tam) {
  int *tmp;
  tmp = (int *) malloc(2 * sizeof(int) * (*tam));

  if(!tmp){
    printf("Erro ao alocar memoria. \n");
    exit(1);
  }

  for(int i = 0; i < (*tam); i++) {
    tmp[i] = (*vet)[i];
  }

  (*tam) = (*tam) * 2;
  free((*vet));
  (*vet) = tmp;
}

/* Troca duas posições no vetor */
void troca(int vet[], int i, int j) {
  int tmp = vet[i];
  vet[i] = vet[j];
  vet[j] = tmp; 
}

/* Ordenação quadrática */
void selectionSort(int vet[], int tam) {
  for(int i = 0; i < tam - 1; i++) {
    for(int j = i + 1; j < tam; j++) {
      if(vet[i] > vet[j]) {
        troca(vet, i, j);
      }
    }
  }
}

/* Função auxiliar à ordenação Merge Sort para juntar dois "conjuntos" */
void merge(int vet[], int inicio, int meio, int fim) {
  int i, j, pos, tam;
  int *tmp;

  i = inicio;
  j = meio;
  pos = 0;
  tam = fim - inicio;

  tmp = (int *) malloc(sizeof(int) * tam);

  while(i < meio && j < fim) {
    if (vet[i] <= vet[j]){
      tmp[pos++] = vet[i++];
    } 
    else {
      tmp[pos++] = vet[j++];
    }
  }

  // caso ainda haja elementos na primeira metade
  while (i < meio) {
    tmp[pos++] = vet[i++];
  }

  // caso ainda haja elementos na segunda metade
  while (j < fim) {
    tmp[pos++] = vet[j++];
  }

  // os elementos vão de volta para o vetor original
  for(pos = 0; pos < tam; pos++) {
    vet[inicio + pos] = tmp[pos];
  }
  
  free(tmp);
}

/* Algoritmo de ordenação Merge Sort */
void mergeSort(int vet[], int inicio, int fim) {
  int meio;

  if(fim - inicio > 1) {
    meio = (inicio + fim)/2;
    mergeSort(vet, inicio, meio);
    mergeSort(vet, meio, fim);
    merge(vet, inicio, meio, fim);
  } 
}

/* Função auxiliar à ordenação Quick Sort para posicionar todos elementos menores do que o pivô à sua esquerda */
int particiona(int vet[], int inicio, int fim){
  int i, j, pivot;
  i = inicio;
  j = fim - 1;
  pivot = vet[inicio];

  while (i < j) {
    while (i < fim && vet[i] <= pivot) {
      i++;
    }
    while (j > inicio && vet[j] > pivot) {
      j--;
    }
    if (i < j) {
      troca(vet, i, j);
    }
  }

  vet[inicio] = vet[j];
  vet[j] = pivot;
  return j;
}

/* Algoritmo de ordenação Quick Sort */
void quickSort(int vet[], int inicio, int fim) {
  int pivot; 

  if (fim - inicio < 1) {
    return;
  }

  pivot = particiona(vet, inicio, fim);

  quickSort(vet, inicio, pivot);
  quickSort(vet, pivot + 1, fim);
}

/* Função principal */
int main(int argc, char *argv[ ]){
  int tam = TAM;
  int *vet;
  int num;
  int pos = 0;

  // alocação do tamanho inicial do vetor
  vet = (int *) malloc(sizeof(int) * tam);

  if(!vet){
    printf("Erro ao alocar memoria. \n");
    return 1;
  }

  // leitura dos valores da entrada para armazenar no vetor
  while(scanf("%d", &num) == 1) {
    if(pos + 1 == tam) {
      overflow(&vet, &tam);
    }
    vet[pos++] = num;
  } 

  // testa se foram ou não passados argumentos na linha de comando
  if(argc == 1) {
    selectionSort(vet, pos);
    // printf("Ordenando usando Selection Sort: \n");
  } 
  else {
    if(strcmp(argv[1], "-m") == 0) {
      mergeSort(vet, 0, pos);
      // printf("Ordenando usando Merge Sort: \n");
    } 
    else if(strcmp(argv[1], "-q") == 0) {
      quickSort(vet, 0, pos);
      // printf("Ordenando usando Quick Sort: \n");
    }
  }

  // imprime o vetor ordenado
  for(int i = 0; i < pos; i++) {
    printf("%d\n", vet[i]);
  }

  return 0;
}