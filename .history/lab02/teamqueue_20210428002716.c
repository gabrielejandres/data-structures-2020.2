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

/* Estrutura de um nó da lista encadeada */
typedef struct node{
  int key; // valor
  int team_index; // índice do time ao qual pertence
  struct node *prev; // aponta para o nó anterior
  struct node *next; // aponta para o próximo nó
} node;

/* Estrutura de um time */
typedef struct team {
  int num_elements; // quantidade de elementos de um time
  int *elements; // array de elementos de um time
  node *last_index_queue; // endereço do último membro do time na fila
} Team;

/* Estrutura da fila */
typedef struct queue {
    int num_of_teams; // número de times que existem na fila
    node *head; // primeiro nó da fila
    node *tail; // último nó da fila
    // node **last_index_team; vetor que vai armazenar o índice da última pessoa de um time na fila
} queue;

/* ********* FUNÇÕES ********* */ 

int searchTeam(int element, Team *teams, int num_teams) {
    for(int i = 0; i < num_teams; i++) {
      printf("Time %d", i+1);
      printf("%d ", teams[i].num_elements);
      for(int j = 0; j < teams[i].num_elements; j++){
        printf("%d ", teams[i].elements[j]);
      }
      printf("\n");
    }
}

/* Função para criar um novo nó da lista encadeada */
struct node* newNode(int value, int team_index)
{
    struct node* tmp = (struct node*) malloc(sizeof(struct node));

    if (tmp == NULL) {
        printf("Erro ao criar novo no. Falta memoria");
        exit(1);
    }

    tmp->key = value;
    //tmp->team_index = team_index;
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
  // for (int i=0; i <= num_of_teams;  i++)
  // {
  //     q->last_index_team[i] = NULL;
  // }

  return q;
}

/* Função para adicionar um elemento na fila */
void enqueue(queue *q, int value, int team_index) { //, int team_index
  // Cria um novo nó da lista encadeada
  node *tmp = newNode(value, team_index); //, team_index

  // Se a fila está vazia, o novo nó é a cabeça e cauda da fila
  if (q->tail == NULL) {
      q->head = q->tail = tmp;
      return;
  }

  // CRIAR A LÓGICA DE FURAR FILA AQUI!!!
  q->tail->next = tmp;
  q->tail = tmp;

  printf("%d \n", *(q->head));
  printf("%d", *(q->tail));
}

/* Função para remover um elemento da fila */
int dequeue(queue *q) {
  // Se a fila tiver vazia, não tem o que remover
  if (q->head == NULL) exit(1);
  
  // Remove o primeiro da fila e coloca o próximo como cabeça
  node *tmp = q->head;
  q->head = q->head->next;

  // Se a cabeça é nula, a cauda também (a fila está vazia nesse caso)
  if (q->head == NULL)
      q->tail = NULL;

  int element = tmp->key;
  free(tmp);
  return element;
  // TENHO QUE ATUALIZAR A STRUCT DE TIMES COM O ULTIMO INDICE QUANDO REMOVER
}

/* Função principal */
int main(int argc, char *argv[ ]){

  int t;
  int scenario = 1;
  scanf("%d",&t);

  // Vou ler as entradas enquanto a quantidade de times for diferente de 0
  while(t != 0) {

    printf("Scenario #%d\n", scenario);

    // Para cada leva de entrada de times, vou criar uma fila diferente
    queue *teamQueue = createQueue(t);

    Team teams[t]; // array para armazenar as structs de times
    char command[10]; // string para armazenar os comandos de ação para a fila

    // Para cada um dos times, vou ler a quantidade de elementos e adicioná-los em um array
    for(int i = 0; i < t; i++) {
      int num_elements;
      scanf("%d",&num_elements);

      // Criando uma nova estrutura de times
      Team team;
      team.num_elements = num_elements;
      team.elements = (int*) malloc(num_elements * sizeof(int));
      team.last_index_queue = NULL; // ainda não há ninguém na fila

      // Lendo os elementos de um time
      for(int j = 0; j < num_elements; j++){
        int element;
        scanf("%d",&element);
        team.elements[j] = element;
      }

      // Adicionando o novo time lido ao array de times
      teams[i] = team;
    }

    /* **** TESTE **** */
    // for(int i = 0; i < t; i++) {
    //   printf("Time %d", i+1);
    //   printf("%d ", teams[i].num_elements);
    //   for(int j = 0; j < teams[i].num_elements; j++){
    //     printf("%d ", teams[i].elements[j]);
    //   }
    //   printf("\n");
    // }

    // Leitura do comando de ação
    getchar();
    scanf("%s",command);

    while(strcmp(command,"STOP") != 0){
      if(strcmp(command,"ENQUEUE") == 0){
        int element;
        scanf("%d",&element);
        int team_index = searchTeam(element, teams, t);
        enqueue(teamQueue, element, team_index);
        //printf("enqueue %d", element);
      } 
      else{
        // int id = dequeue(teamQueue);
        printf("dequeue");
      }
      scanf("%s",command);
    }

    scanf("%d",&t);
    printf("\n");
    scenario++;
    free(teamQueue);
  }

  return 0;
}