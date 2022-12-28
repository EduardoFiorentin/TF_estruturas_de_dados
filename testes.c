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

void imprimePreOrdem(Item *raiz){
    if (raiz == NULL) return; 
    printf("%s|", raiz->produto);
    imprimePreOrdem(raiz->esquerdo);
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
    strcpy(nome, new->produto);
    new->quantidade = qtd; 
    new->direito = NULL;
    new->esquerdo = NULL;
    printf("%s %d", new->produto, new->quantidade); 
    return new; 
}

int main() 
{
    Item* raiz = NULL; 
    raiz = adicionaProduto(raiz, criaProduto("aproduto", 1));
    raiz = adicionaProduto(raiz, criaProduto("bproduto", 1));
    raiz = adicionaProduto(raiz, criaProduto("cproduto", 1));
    raiz = adicionaProduto(raiz, criaProduto("dproduto", 1));
    raiz = adicionaProduto(raiz, criaProduto("eproduto", 1));

    imprimePreOrdem(raiz);

    return 0;
}