/*
  * Programa: Algoritmos de ordenação na linguagem C
  * Autor: Gabriele Jandres Cavalcanti
  * Universidade Federal do Rio de Janeiro
  * Data de criação: abril de 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 8

/* Aumenta o tamanho alocado para o vetor, quando necessário */
void overflow(int *vet[], int *size) {
  int *tmp;
  tmp = (int *) malloc(2 * sizeof(int) * (*size));

  if(!tmp){
    printf("Erro ao alocar memoria. \n");
    exit(1);
  }

  for(int i = 0; i < (*size); i++) {
    tmp[i] = (*vet)[i];
  }

  (*size) = (*size) * 2;
  free((*vet));
  (*vet) = tmp;
}

/* Troca duas posições no vetor */
void swap(int vet[], int i, int j) {
  int tmp = vet[i];
  vet[i] = vet[j];
  vet[j] = tmp; 
}

/* Ordenação quadrática */
void selectionSort(int vet[], int size) {
  for(int i = 0; i < size - 1; i++) {
    for(int j = i + 1; j < size; j++) {
      if(vet[i] > vet[j]) {
        swap(vet, i, j);
      }
    }
  }
}

/* Função auxiliar à ordenação Merge Sort para juntar dois "conjuntos" */
void merge(int vet[], int first, int middle, int last) {
  int i, j, pos, size;
  int *tmp;

  i = first;
  j = middle;
  pos = 0;
  size = last - first;

  tmp = (int *) malloc(sizeof(int) * size);

  while(i < middle && j < last) {
    if (vet[i] <= vet[j]){
      tmp[pos++] = vet[i++];
    } 
    else {
      tmp[pos++] = vet[j++];
    }
  }

  // caso ainda haja elementos na primeira metade
  while (i < middle) {
    tmp[pos++] = vet[i++];
  }

  // caso ainda haja elementos na segunda metade
  while (j < last) {
    tmp[pos++] = vet[j++];
  }

  // os elementos vão de volta para o vetor original
  for(pos = 0; pos < size; pos++) {
    vet[first + pos] = tmp[pos];
  }
  
  free(tmp);
}

/* Algoritmo de ordenação Merge Sort */
void mergeSort(int vet[], int first, int last) {
  int middle;

  if(last - first > 1) {
    middle = (first + last)/2;
    mergeSort(vet, first, middle);
    mergeSort(vet, middle, last);
    merge(vet, first, middle, last);
  } 
}

/* Função auxiliar à ordenação Quick Sort para posicionar todos elementos menores do que o pivô à sua esquerda */
int partition(int vet[], int first, int last){
  int i, j, pivot;
  i = first;
  j = last - 1;
  pivot = vet[first];

  while (i < j) {
    while (i < last && vet[i] <= pivot) {
      i++;
    }
    while (j > first && vet[j] > pivot) {
      j--;
    }
    if (i < j) {
      swap(vet, i, j);
    }
  }

  vet[first] = vet[j];
  vet[j] = pivot;
  return j;
}

/* Algoritmo de ordenação Quick Sort */
void quickSort(int vet[], int first, int last) {
  int pivot; 

  if (last - first < 1) {
    return;
  }

  pivot = partition(vet, first, last);

  quickSort(vet, first, pivot);
  quickSort(vet, pivot + 1, last);
}

/* Função principal */
int main(int argc, char *argv[ ]){
  int size = SIZE;
  int *vet;
  int num;
  int pos = 0;

  // alocação do tamanho inicial do vetor
  vet = (int *) malloc(sizeof(int) * size);

  if(!vet){
    printf("Erro ao alocar memoria. \n");
    return 1;
  }

  // leitura dos valores da entrada para armazenar no vetor
  while(scanf("%d", &num) == 1) {
    if(pos + 1 == size) {
      overflow(&vet, &size);
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