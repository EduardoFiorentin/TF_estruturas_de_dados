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

Item* query(char name[50], Item* raiz)
{
    if (raiz == NULL) return NULL;
    if (strcmp(name, raiz->produto) == 0) return raiz; 

    Item *esq = query(name, raiz->esquerdo);
    if (esq != NULL) return esq; 
    return query(name, raiz->direito);     
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

Item* min(Item* raiz) {
    if (raiz->esquerdo == NULL) return raiz;
    return min(raiz->esquerdo); 
}

// Permite excluir um item de uma lista de compras
Item* delete(Item* raiz, char nome[50])
{
    if (raiz == NULL) return raiz; 

    // nenhum filho 
    if (strcmp(nome, raiz->produto) == -1) {
        raiz->esquerdo = delete(raiz->esquerdo, nome);
    }
    else if (strcmp(nome, raiz->produto) == 1){
        raiz->direito = delete(raiz->direito, nome); 
    } else {
        // Apenas um filho ou nenhum:
        if (raiz->esquerdo == NULL) return raiz->direito;
        if (raiz->direito == NULL) return raiz->esquerdo; 

        // dois filhos 
        Item* aux = min(raiz->direito); 
        strcpy(raiz->produto, aux->produto); 
        raiz->quantidade = aux->quantidade; 
        raiz->direito = delete(raiz->direito, aux->produto); 
    }
    return raiz; 
}


Item* create (char nome[50], int qtd)
{
    Item* new = malloc(sizeof(Item));
    strcpy(new->produto, nome);
    new->quantidade = qtd; 
    new->direito = NULL;
    new->esquerdo = NULL;
    return new; 
}

// int update(Item *raiz, char nome, int newQtd)
// {
//     printf("\nquery\n"); 
//     Item *aux = query(nome, raiz);
//     if (aux == NULL) return 0; 
//     printf("\nQtd: %d", aux->quantidade);
//     return 1; 
// }

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


    // printf("\n\n%d\n\n", (query(nome, raiz)->quantidade));
    // printf("\n\n%d\n\n", (query(nome, raiz)->quantidade));

    // raiz = adicionaProduto(raiz, criaProduto("aproduto", 1));
    // raiz = adicionaProduto(raiz, criaProduto("bproduto", 1));
    // raiz = adicionaProduto(raiz, criaProduto("cproduto", 1));
    // raiz = adicionaProduto(raiz, criaProduto("dproduto", 1));
    // raiz = adicionaProduto(raiz, criaProduto("eproduto", 1));
    char nome[50] = "aproduto";

    imprimePreOrdem(raiz);

    // printf("update");
    // int updat = update(raiz, nome, 5);
    // Item* aux = query(nome, raiz);
    // printf("\n\nSSK: %s %d\n\n", aux->produto, aux->quantidade);

    // int upd = update(raiz, nome, 5);
    delete(raiz, nome);
    printf("\n");


    imprimePreOrdem(raiz);

    // printf("\n%d\n", strcmp("A", "B")); 
    // printf("%s", min(raiz)->produto); 
    // strcmp("A", "B") : -1
    
    return 0;
}
