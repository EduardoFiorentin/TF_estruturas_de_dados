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

    int esq = query(name, raiz->esquerdo);
    int dir = query(name, raiz->direito);

    return (esq || dir);
}

void imprimePreOrdem(Item *raiz){
    if (raiz == NULL) return; 
    imprimePreOrdem(raiz->esquerdo);
    printf("%s|", raiz->produto);
    imprimePreOrdem(raiz->direito);    
}

Item* adicionaProduto(Item *raiz, Item *new)
{
    if (raiz == NULL) return new; 
    if (strcmp(raiz->produto, new->produto) == 1) raiz->esquerdo = adicionaProduto(raiz->esquerdo, new);
    else raiz->direito = adicionaProduto(raiz->direito, new);
       
    return raiz; 
}

Item* criaProduto (char nome[50], int qtd)
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

    Item* A = criaProduto("aproduto", 1);
    Item* B = criaProduto("bproduto", 1);
    Item* C = criaProduto("cproduto", 1);
    Item* D = criaProduto("dproduto", 1);
    Item* E = criaProduto("eproduto", 1);


    raiz = adicionaProduto(raiz, D);
    raiz = adicionaProduto(raiz, B);
    raiz = adicionaProduto(raiz, E);
    raiz = adicionaProduto(raiz, A);
    raiz = adicionaProduto(raiz, C);

    printf("\n\n%d\n\n", query("fproduto", raiz));

    // raiz = adicionaProduto(raiz, criaProduto("aproduto", 1));
    // raiz = adicionaProduto(raiz, criaProduto("bproduto", 1));
    // raiz = adicionaProduto(raiz, criaProduto("cproduto", 1));
    // raiz = adicionaProduto(raiz, criaProduto("dproduto", 1));
    // raiz = adicionaProduto(raiz, criaProduto("eproduto", 1));

    imprimePreOrdem(raiz);

    return 0;
}