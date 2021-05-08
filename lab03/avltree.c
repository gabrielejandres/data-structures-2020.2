/*
  * Programa: Inserção de chaves em uma árvore AVL e impressão das chaves em pré-ordem na linguagem C
  * Autor: Gabriele Jandres Cavalcanti
  * Universidade Federal do Rio de Janeiro
  * Data de criação: maio de 2021
*/

#include <stdio.h>
#include <stdlib.h>

/* ********* ESTRUTURAS ********* */ 

/* Estrutura de um nó da árvore AVL */
typedef struct node {
  int key; // valor / chave de um nó
  int height; // altura do nó / subárvore
  struct node *left; // aponta para o nó esquerdo
  struct node *right; // aponta para o nó direito
} node;

/* ********* FUNÇÕES ********* */ 

/* Função para imprimir a árvore AVL em pré-ordem */
void printPreOrder(node *root) {
    if (root != NULL) {
      printf("%d\n", root->key);
      printPreOrder(root->left);
      printPreOrder(root->right);
    }
}

/* Função para criar um novo nó da árvore */
node* createNewNode(int value) {
    node* tmp = (node*) malloc(sizeof(node));

    if (tmp == NULL) {
        printf("Erro ao criar novo no. Falta memoria");
        exit(1);
    }

    tmp->key = value;

    // Inicialmente não há ninguém à esquerda nem à direita do nó 
    tmp->left = NULL;
    tmp->right = NULL;

    // Inicialmente o nó é uma folha, por isso sua altura inicial é 1
    tmp->height = 1;

    return tmp;
}

/* Função auxiliar para comparar dois inteiros e retornar o maior deles que será necessária para descobrir a altura da árvore */
int getMaxNumber(int num1, int num2) {
    return (num1 > num2) ? num1 : num2;
}

/* Função para determinar a altura de um nó */
int getHeight(node *n) {
    return (n == NULL) ?  0 : n->height;
}

/* Função para obter o fator de balanceamento de um nó */
int getBalanceFactor(node *n) {
    return (n == NULL) ? 0 : getHeight(n->left) - getHeight(n->right);
}

/* Função para realizar uma rotação simples para a direita e manter a condição balanceada da árvore AVL */
node* realizeRightRotation(node *n) {
    node *aux = n->left; // nó auxiliar recebe o filho à esquerda da antiga raiz
    node *tmp = aux->right; // nó auxiliar para preservar o valor do nó à direita da nova raiz

    aux->right = n; // nó à direita da nova raiz recebe a antiga raiz
    n->left = tmp; // nó à esquerda da antiga raiz recebe o antigo filho à direita da nova raiz
 
    // Após rotacionar, é necessário atualizar as alturas dos nós envolvidos na rotação
    n->height = getMaxNumber(getHeight(n->left), getHeight(n->right)) + 1; // altura da antiga raiz
    aux->height = getMaxNumber(getHeight(aux->left), getHeight(aux->right)) + 1; // altura da nova raiz
 
    return aux; // esse novo nó será a nova raiz
}

/* Função para realizar uma rotação simples para a esquerda e manter a condição balanceada da árvore AVL */
node* realizeLeftRotation(node *n) {
    node *aux = n->right; // nó auxiliar recebe o filho à direita da antiga raiz
    node *tmp = aux->left; // nó auxiliar para preservar o valor do nó à esquerda da nova raiz

    aux->left = n; // nó à esquerda da nova raiz recebe a antiga raiz
    n->right = tmp; // nó à direita da antiga raiz recebe o antigo filho à esquerda da nova raiz
 
    // Após rotacionar, é necessário atualizar as alturas dos nós envolvidos na rotação
    n->height = getMaxNumber(getHeight(n->left), getHeight(n->right)) + 1; // altura da antiga raiz
    aux->height = getMaxNumber(getHeight(aux->left), getHeight(aux->right)) + 1; // altura da nova raiz
 
    return aux; // esse novo nó será a nova raiz
}

/* Função para realizar uma rotação dupla à direita (rotação simples para a direita em seguida de rotação simples para a esquerda)
 e manter a condição balanceada da árvore AVL */
node* realizeRightLeftRotation(node *n) {
    // Realiza a rotação à direita
    n->right = realizeRightRotation(n->right);
    // Realiza rotação à esquerda
    return realizeLeftRotation(n);
}

/* Função para realizar uma rotação dupla à esquerda (rotação simples para a esquerda em seguida de rotação simples para a direita)
 e manter a condição balanceada da árvore AVL */
node* realizeLeftRightRotation(node *n) {
    // Realiza rotação à esquerda
    n->left =  realizeLeftRotation(n->left);
    // Realiza a rotação à direita
    return realizeRightRotation(n);
}

/* Função para inserir um elemento na árvore AVL */
node* insertIntoAVLTree(node *n, int value) {
    // Se a raiz é nula, vou simplesmente inserir o valor porque a árvore é vazia ou nó folha
    if (n == NULL) 
      return(createNewNode(value));
 
    // Se o valor que quero inserir for menor do que o valor da raiz, tenho que realizar uma inserção na subárvore da esquerda
    if (value < n->key)
      n->left  = insertIntoAVLTree(n->left, value);
    // Se o valor que quero inserir for menor do que o valor da raiz, tenho que realizar uma inserção na subárvore da direita
    else if (value > n->key)
      n->right = insertIntoAVLTree(n->right, value);
    // Não posso inserir duas vezes o mesmo valor, então retorno o próprio nó
    else
      return n;
 
    // Atualiza a altura do nó atual após a inserção
    n->height = 1 + getMaxNumber(getHeight(n->left), getHeight(n->right));
 
    // Obtém o fator de balanceamento nó após a inserção para verificar se está desbalanceado
    int balanceFactor = getBalanceFactor(n);
 
    // Quando o nó é inserido na subárvore esquerda da subárvore esquerda e a árvore se torna desbalanceada, precisamos realizar uma 
    // rotação simples para a direita 
    if (balanceFactor > 1 && value < n->left->key)
      return realizeRightRotation(n);
 
    // Quando o nó é inserido na subárvore direita da subárvore direita e a árvore se torna desbalanceada, precisamos realizar uma 
    // rotação simples para a esquerda 
    if (balanceFactor < -1 && value > n->right->key)
      return realizeLeftRotation(n);

    // Quando o nó é inserido na subárvore esquerda da subárvore direita e a árvore se torna desbalanceada, precisamos realizar uma 
    // rotação simples para a direita seguida de uma rotação simples para a esquerda
    if (balanceFactor < -1 && value < n->right->key)
      return realizeRightLeftRotation(n);
 
    // Quando o nó é inserido na subárvore direita da subárvore esquerda e a árvore se torna desbalanceada, precisamos realizar uma 
    // rotação simples para a esquerda seguida de uma rotação simples para a direita
    if (balanceFactor > 1 && value > n->left->key)
      return realizeLeftRightRotation(n);

    return n;
}

/* Função principal */
int main(int argc, char *argv[ ]){

    int num;
    node *root = NULL;

    // Leitura dos valores a serem inseridos na árvore
    while(scanf("%d", &num) == 1)
      root = insertIntoAVLTree(root, num);
    
    // Imprimir as chaves em pré-ordem
    printPreOrder(root);

    return 0;
}