/*
  * Programa: Implementação do problema 10583 Ubiquitous Religions do online judge usando union find com compressão de caminhos e união por rank
  * Autor: Gabriele Jandres Cavalcanti
  * Universidade Federal do Rio de Janeiro
  * Data de criação: junho de 2021
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBER_OF_STUDENTS 50000

// Array que armazenará os ranks de cada valor do conjunto
static int rank[MAX_NUMBER_OF_STUDENTS];

// Array que armazenará os pais/representantes de cada valor do conjunto
static int parent[MAX_NUMBER_OF_STUDENTS];

/* ********* FUNÇÕES ********* */ 

/* Função para criar um conjunto com a quantidade de nós/valores desejada */
void createSet(int nodes) {
    for(int i = 1; i <= nodes; i++) {
        // Inicialmente todos os ranks são 0 porque os subconjuntos são unitários
        rank[i] = 0;
        // No começo todos os subconjuntos são unitários, então o próprio nó é seu pai
        parent[i] = i; 
    }
}

/* Função para encontrar o representante/pai do subconjunto do valor usando compressão de caminhos */
int find(int value){
    // Se o valor passado não for o próprio representante do conjunto, procura por ele recursivamente
    if(value != parent[value]) {
      parent[value] = find(parent[value]);
    }

    return parent[value];
}

/* Função para unir dois conjuntos usando critério de rank */
void Union(int a, int b, int* religions) {
  // Encontra os representantes/pais dos valores passados
	int parent_a = find(a);
	int parent_b = find(b);

  int sameParent = parent_a == parent_b ? 1 : 0;

  // Dois nós vão ser unidos se estiverem em subconjuntos diferentes
	if(!sameParent){

    // O subconjunto com maior rank se torna o representante do subconjunto com o menor rank
    if(rank[parent_a] <= rank[parent_b]){
      parent[parent_a] = parent_b;
      
      // Se ambos os subconjuntos tiverem o mesmo rank, o representante de b passa a ser representante de a
      if(rank[parent_a] == rank[parent_b]) {
        rank[parent_b]++;
      }
    }
    else{
      parent[parent_b] = parent_a;
    }

    // Diminui a quantidade de subconjuntos quando são unidos
		(*religions)--;
  }
}

/* Função principal */
int main(int argc, char *argv[ ]){
    int nodes, edges, religions, node1, node2 = 0;
    int caseNumber = 1;

    // Leitura da quantidade total de estudantes e da quantidade de arestas/ligações entre estudantes
    while(scanf("%d %d", &nodes, &edges) && nodes && edges) {

      // Cria um conjunto com todos os nós unitários representando cada estudante
      createSet(nodes);

      // Inicializa a quantidade de subconjuntos como sendo o total de conjuntos unitários
      religions = nodes;

      // Enquanto existirem relações entre estudantes, une subconjuntos
      while(edges--){
        scanf("%d%d", &node1, &node2);
        Union((node1), (node2), &religions);
      }

      printf("Case %d: %d\n", caseNumber++, religions);
    }

    return 0;
}