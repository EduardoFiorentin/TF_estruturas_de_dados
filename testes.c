#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

struct item {
	char produto[50];
	int quantidade;
    struct item  *esquerdo; 
	struct item  *direito;
};
typedef struct item Item;

int query(char name[50], Item* raiz)
{
    if (raiz == NULL) return 0;
    if (strcmp(name, raiz->produto) == 0) return 1; 

    return (query(name, raiz->esquerdo) || query(name, raiz->direito));
}

void imprimePreOrdem(Item *raiz){
    if (raiz == NULL) return; 
    imprimePreOrdem(raiz->esquerdo);
    printf("%s|", raiz->produto);
    imprimePreOrdem(raiz->direito);    
}

Item* insert(Item *raiz, Item *new)
{
    if (raiz == NULL) return new; 
    if (strcmp(raiz->produto, new->produto) == 1) raiz->esquerdo = insert(raiz->esquerdo, new);
    else raiz->direito = insert(raiz->direito, new);
       
    return raiz; 
}

Item* create (char nome[50], int qtd)
{
    Item* new = malloc(sizeof(Item));
    strcpy(new->produto, nome);
    new->quantidade = qtd; 
    new->direito = NULL;
    new->esquerdo = NULL;
    // printf("%s %d", new->produto, new->quantidade); 
    return new; 
}

int main() 
{
    Item* raiz = NULL; 

    Item* A = create("aproduto", 1);
    Item* B = create("bproduto", 1);
    Item* C = create("cproduto", 1);
    Item* D = create("dproduto", 1);
    Item* E = create("eproduto", 1);


    raiz = insert(raiz, D);
    raiz = insert(raiz, B);
    raiz = insert(raiz, E);
    raiz = insert(raiz, A);
    raiz = insert(raiz, C);

    printf("\n\n%d\n\n", query("dproduto", raiz));

    // raiz = adicionaProduto(raiz, criaProduto("aproduto", 1));
    // raiz = adicionaProduto(raiz, criaProduto("bproduto", 1));
    // raiz = adicionaProduto(raiz, criaProduto("cproduto", 1));
    // raiz = adicionaProduto(raiz, criaProduto("dproduto", 1));
    // raiz = adicionaProduto(raiz, criaProduto("eproduto", 1));

    imprimePreOrdem(raiz);

    return 0;
}