#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Estrutura nodos arvore binaria
struct item {
	char nome[50];
	int quantidade;
    struct item  *esquerdo; 
	struct item  *direito;
};
typedef struct item Item;

Item* create(char nome[50], int qtd)
{
    Item* new = malloc(sizeof(Item));
    strcpy(new->nome, nome);
    new->quantidade = qtd; 
    new->direito = NULL;
    new->esquerdo = NULL;
    return new; 
}

// ---------------------------------------------------------------------------------------------------------

// estrutura do nodo (item de uma lista de compras)
struct itemList {
  Item *node; 
  struct itemList *proximo;
}; 
typedef struct itemList ItemList;

//estrutura da lista
struct lista {
  ItemList *primeiro;
  ItemList *ultimo;
};
typedef struct lista Lista;

ItemList* createItem(Item* node) {
    ItemList* aux = malloc(sizeof(ItemList));
    aux->node = node;
    aux->proximo = NULL;  
    return aux; 
}

// adicionar no final da lista 
void push_back(Lista *lista, ItemList* new)
{
    // colocar primeiro elemento da lista 
    if (lista->primeiro == NULL) 
    {
        new->proximo = NULL; 
        lista->primeiro = new;
        lista->ultimo = new; 
        return;
    }

    // inserir no final da lista
    else 
    {
        lista->ultimo->proximo = new;
        lista->ultimo = new; 
    }
}

void print_list(Lista *lista) 
{
    ItemList *aux_print; 

    printf("\nLista de frente pra tras:\n");
    for (aux_print = lista->primeiro; aux_print != NULL; aux_print = aux_print->proximo) 
    {
        printf("Nome: %s, Quantidade: %d\n", aux_print->node->nome, aux_print->node->quantidade);
    }
    printf("\n");

}

void free_list(Lista *lista) {
    ItemList *aux = lista->primeiro; 
    ItemList *aux_clear; 

    while (aux != NULL) 
    {
        aux_clear = aux;
        aux = aux->proximo;
        free(aux_clear);
    }
    lista->primeiro = NULL; 
    return; 
}


int main() {
    Lista produtos; 
    produtos.primeiro = NULL; 
    produtos.ultimo = NULL; 

    Item* A = create("aproduto", 1);
    Item* B = create("bproduto", 1);
    Item* C = create("cproduto", 1);
    Item* D = create("dproduto", 1);
    Item* E = create("eproduto", 1);

    push_back(&produtos, createItem(A));
    push_back(&produtos, createItem(B));
    push_back(&produtos, createItem(C));
    push_back(&produtos, createItem(D));
    push_back(&produtos, createItem(E));

    print_list(&produtos); 

    free_list(&produtos); 

    printf("\n\n%d\n\n", (produtos.primeiro == NULL));

    return 0; 
}