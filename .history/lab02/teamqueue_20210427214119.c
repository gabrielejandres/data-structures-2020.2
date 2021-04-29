/*
  * Programa: Implementação do problema "Team queue" na linguagem C
  * Autor: Gabriele Jandres Cavalcanti
  * Universidade Federal do Rio de Janeiro
  * Data de criação: abril de 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_ELEMENTS_OF_A_TEAM 1000

/* ********* ESTRUTURAS ********* */ 

/* Estrutura de um time */
typedef struct {
  int num_elements; // quantidade de elementos de um time
  int *elements; // array de elementos de um time
} Team;

/* Estrutura de um nó da lista encadeada */
typedef struct {
  int key; // valor
  int team_index; // índice do time ao qual pertence
  struct node *prev; // aponta para o nó anterior
  struct node *next; // aponta para o próximo nó
} node;

/* Estrutura da fila */
typedef struct {
    int num_of_teams; // número de times que existem na fila
    node *head; // cabeça da fila
    node *tail; // cauda da fila
    node **last_index_team; // vetor que vai armazenar o índice da última pessoa de um time na fila
} queue;

/* ********* FUNÇÕES ********* */ 

/* Função para criar um novo nó da lista encadeada */
node* newNode(int value, int team_index)
{
    node* tmp = (node*) malloc(sizeof(node));

    if (tmp == NULL) {
        printf("Erro ao criar novo no. Falta memoria");
        exit(1);
    }

    tmp->key = value;
    tmp->team_index = team_index;
    tmp->next = NULL;
    tmp->prev = NULL;

    return tmp;
}

/* Função para criar e inicializar uma fila vazia */
queue* createQueue(int num_of_teams) {
  queue *q = (queue*) malloc(sizeof(node));

  if (q == NULL) {
    printf("Erro ao inicializar fila. Falta memoria");
    exit(1);
  }

  q->num_of_teams = num_of_teams;
  q->head = NULL;
  q->tail = NULL;
  for (int i=0; i <= num_of_teams;  i++)
  {
      q->last_index_team[i] = NULL;
  }

  return q;
}

/* Função para adicionar um elemento na fila */
void enqueue(queue *q, int value, int team_index) {
  // Cria um novo nó da lista encadeada
  node *tmp = newNode(value, team_index);

  // Se a fila está vazia, o novo nó é a cabeça e cauda da fila
  if (q->tail == NULL) {
      q->head = q->tail = tmp;
      return;
  }

  // CRIAR A LÓGICA DE FURAR FILA AQUI!!!
  q->tail->next = tmp;
  q->tail = tmp;
}

/* Função para remover um elemento da fila */
void dequeue(queue *q) {
  // Se a fila tiver vazia, não tem o que remover
  if (q->head == NULL) return;
  
  // Remove o primeiro da fila e coloca o próximo como cabeça
  node *tmp = q->head;
  q->head = q->head->next;

  // Se a cabeça é nula, a cauda também (a fila está vazia nesse caso)
  if (q->head == NULL)
      q->tail = NULL;

  free(tmp);
}

/* Função principal */
int main(int argc, char *argv[ ]){

  int t;
  int scenario = 1;
  scanf("%d",&t);

  // Vou ler as entradas enquanto a quantidade de times for diferente de 0
  while(t != 0) {

    printf("Scenario #%d\n", scenario);
    // CRIAR A FILA AQUI!!!
    Team teams[t]; //array para armazenar as structs de times

    // Para cada um dos times, vou ler a quantidade de elementos e adicioná-los em um array
    for(int i = 0; i < t; i++) {
      int num_elements;
      scanf("%d",&num_elements);

      // Criando uma nova estrutura de times
      Team team;
      team.elements = (int) malloc(num_elements * sizeof(int));

      // Lendo os elementos de um time
      while(num_elements--){
        int element;
        scanf("%d",&element);
      }
    }
    
    scanf("%d",&t);
    printf("\n");
    scenario++;
  }

  return 0;
}