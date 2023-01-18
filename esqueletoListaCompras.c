/*
 Este é um esqueleto que deve ser utilizado como base para implementação do trabalho;
	- As funções não têm os parâmetros definidos; se necessário, estes devem ser incluídos; Os tipos de retorno podem ser alterados, se necessário;
 	- Devem ser respeitados os nomes atribuídos às funções e estruturas, porém, novas estruturas e funções podem ser criadas, caso julgue necessário;
	- Faça os includes necessários;
	- A organização das funções fica a critério do programador;
	- A indentação correta faz parte da nota;
	- Não são permitidas variáveis globais;
	- Caso seja detectado plágio, os grupos envolvidos receberão nota 0.
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define EXIT 10  // valor fixo para a opção que finaliza a aplicação
#define LIMPAR system("cls")
#define PAUSAR system("pause")


// ESTRUTURAS DE ARVORE
// Struct que representa um item de uma lista de compras armazenada em uma arvore binaria de busca
struct item {
	char nome[50];
	int quantidade;
    struct item  *esquerdo; 
	struct item  *direito;
};
typedef struct item Item;



// ESTRUTURAS DE LISTA
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



// FUNÇÕES DE LISTA
// ---------------------------------------------------------------------------------------------------------------------------------------------
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
// ---------------------------------------------------------------------------------------------------------------------------------------------------

// FUNÇÕES DO SISTEMA
// Apresenta o primeiro menu da aplicação e retorna a opção selecionada
int menu1()
{
     int op = 0;
     LIMPAR; 
     printf("Menu principal\n");
     printf("\t01 - Gerenciar lista A\n");
     printf("\t02 - Gerenciar lista B\n");
     printf("\t03 - Itens duplicados\n");

     printf("\t%d - Sair do programa\n",EXIT);
     printf("\n\nDigite a opcao: ");
     scanf("%d",&op);
     return op;
}

// Apresenta o segundo menu da aplicação e retorna a opção selecionada
int menu2()
{
     int op = 0;
     printf("Submenu - Gerenciar lista de compras\n");
	printf("\n01 - Inserir produto");
	printf("\n02 - Pesquisar produto");
	printf("\n03 - Atualizar produto");
	printf("\n04 - Listar produtos");
	printf("\n05 - Deletar produto");
     printf("\n%d - Retornar para o menu principal",EXIT);
     printf("\n\nDigite a opcao: ");
     scanf("%d",&op); 
     return op;
}

Item* min(Item* raiz) {
    if (raiz->esquerdo == NULL) return raiz;
    return min(raiz->esquerdo); 
}    

Item* create(char nome[50], int qtd)
{
    Item* new = malloc(sizeof(Item));
    strcpy(new->nome, nome);
    new->quantidade = qtd; 
    new->direito = NULL;
    new->esquerdo = NULL;
    return new; 
}

// Permite o cadastro de um item (caso o produto ainda não exista) em uma lista de compas
Item* insert(Item *raiz, Item *new)
{
     if (raiz == NULL) return new; 
     if (strcmp(raiz->nome, new->nome) == 1) raiz->esquerdo = insert(raiz->esquerdo, new);
     else raiz->direito = insert(raiz->direito, new);
       
     return raiz; 
}

// Permite consultar se um item está em uma lista de compras
Item* query(char name[50], Item* raiz)
{
    if (raiz == NULL) return NULL;
    if (strcmp(name, raiz->nome) == 0) return raiz; 

     Item *esq = query(name, raiz->esquerdo);
     if (esq != NULL) return esq; 
     return query(name, raiz->direito);     
}

// Permite a atualização da quantidade de um produto (caso exista) na lista de compras
// CONSERTAR 
void update(Item *produto, int newQtd)
{
    produto->quantidade = newQtd; 
}

// Listar todos os itens da lista de compras em ordem alfabética;
void list(Item* raiz)
{
     if (raiz == NULL) return; 
     list(raiz->esquerdo);
     printf("%s\t\t%d\n", raiz->nome, raiz->quantidade);
     list(raiz->direito);    
}

// Permite excluir um item de uma lista de compras
Item* delete(Item* raiz, char nome[50])
{
    if (raiz == NULL) return raiz; 

    // nenhum filho 
    if (strcmp(nome, raiz->nome) == -1) {
        raiz->esquerdo = delete(raiz->esquerdo, nome);
    }
    else if (strcmp(nome, raiz->nome) == 1){
        raiz->direito = delete(raiz->direito, nome); 
    } else {
        // Apenas um filho ou nenhum:
        if (raiz->esquerdo == NULL) return raiz->direito;
        if (raiz->direito == NULL) return raiz->esquerdo; 

        // dois filhos 
        Item* aux = min(raiz->direito); 
        strcpy(raiz->nome, aux->nome); 
        raiz->quantidade = aux->quantidade; 
        raiz->direito = delete(raiz->direito, aux->nome); 
    }
    return raiz; 
}

void intersect(Item* raizA, Item* raizB, Lista* produtos)
{
     if (raizA == NULL) return; 
     intersect(raizA->esquerdo, raizB, produtos); 
     if (query(raizA->nome, raizB) != NULL) push_back(produtos, createItem(raizA)); 
     intersect(raizA->direito, raizB, produtos); 
}    

// Programa principal
int main()
{
     int opcao1;
     int opcao2;
     Item *raizA = NULL;
     Item *raizB = NULL;

     char nome[50]; 
     int qtd; 
     int opt; 
     Item* aux; 

     Item* A = create("aproduto", 1);
     Item* B = create("bproduto", 1);
     Item* C = create("cproduto", 1);
     Item* D = create("dproduto", 1);
     Item* E = create("eproduto", 1);
     
     Item* F = create("fproduto", 1);
     Item* G = create("gproduto", 1);
     Item* H = create("hproduto", 1);
     Item* I = create("iproduto", 1);
     Item* J = create("jproduto", 1);

     raizA = insert(raizA, D);
     raizA = insert(raizA, B);
     raizA = insert(raizA, E);
     raizA = insert(raizA, A);
     raizA = insert(raizA, C);
     
     raizB = insert(raizB, H);
     raizB = insert(raizB, G);
     raizB = insert(raizB, J);
     raizB = insert(raizB, I);
     raizB = insert(raizB, F);

    opcao1 = 0;
    while (opcao1 != EXIT)
    {
          opcao1 = menu1();
               
          switch(opcao1)
          {
               case 1 : // gerenciar lista de compras A
                    opcao2 = 0;
                    while(opcao2 != EXIT){
	                    LIMPAR; 
                         printf("** Lista de Compras A **\n\n");
                         opcao2 = menu2();
                         switch(opcao2){ // operacoes sobre a arvore A
                              // CADASTRO DE PRODUTOS
                              case 1 : 
                                   printf("Nome: ");
                                   scanf("%s", nome); 
                                   aux = query(nome, raizA);
                                   if (aux == NULL) {
                                        printf("\nQuantidade: ");
                                        scanf("%d", &qtd);
                                        insert(raizA, create(nome, qtd)); 
                                        printf("\n\nProduto Cadastrado!\n\tNome: %s\n\tQtd: %d\n\n", nome, qtd); 
                                   }
                                   else 
                                   {
                                        printf("\nEste produto ja esta cadastrado!\n\n");
                                        printf("Deseja atualizar sua quantidade?\n[0] - Nao\n[1] - Sim\nOpcao: ");
                                        scanf("%d", &opt); 
                                        if (opt) goto updateA; 
                                        else printf("\nProcesso cancelado!\n\n");
                                   }
                                   PAUSAR;
                                   break;


                              // VERIFICAR SE PRODUTO EXISTE
                              case 2 : 
                                   printf("Nome: ");
                                   scanf("%s", nome); 
                                   aux = query(nome, raizA);
                                   if (aux == NULL) printf("\nProduto nao cadastrado!\n\n");
                                   else printf("\nProduto cadastrado!\n\tNome: %s\n\tQuantidade: %d\n\n", aux->nome, aux->quantidade);
                                   PAUSAR; 
                                   break;

                              // ATUALIZAR PRODUTO X
                              case 3 : 
                                   printf("Nome: ");
                                   scanf("%s", nome); 
                                   aux = query(nome, raizA);
                                   if (aux == NULL){
                                        printf("\nProduto nao cadastrado!\n\n");
                                   }
                                   else {
                                        updateA:
                                        printf("\nNova quantidade: ");
                                        scanf("%d", &qtd);
                                        update(aux, qtd);
                                        printf("\nProduto atualizado!\n\n");
                                   }
                                   PAUSAR;
                                   break;
                              
                              // LISTAR PRODUTOS 
                              case 4 : 
                                   printf("\n\n** Lista de Produtos **\n"); 
                                   printf("Nome\t\tQuantidade\n");
                                   list(raizA);
                                   printf("\n\n");
                                   PAUSAR; 
                                   break;
                              
                              // DELETAR PRODUTO 
                              case 5 : 
                                   printf("Nome: ");
                                   scanf("%s", nome); 
                                   aux = query(nome, raizA);
                                   if (aux == NULL){
                                        printf("\nProduto nao cadastrado!\n\n");
                                   }
                                   else {
                                        printf("\nProduto: %s\nQuantidade: %d\n\n", aux->nome, aux->quantidade);
                                        printf("Deseja excluir o produto?\n[0] - Nao\n[1] - Sim\nOpcao: ");
                                        scanf("%d", &opt); 
                                        if (opt) {
                                             delete(raizA, nome);
                                             printf("\nProduto deletado!\n\n");
                                        } 
                                        else printf("\nProduto nao deletado!\n\n");
                                   }
                                   PAUSAR;
                                   break;
                         }    
                    }
                    break;
               case 2 : // gerenciar lista de compras B
                    opcao2 = 0;
                    while(opcao2 != EXIT){
	                    LIMPAR; 
                         printf("** Lista de Compras B **\n\n");
                         opcao2 = menu2();
                         switch(opcao2){ // operacoes sobre a arvore B

                              // CADASTRO DE PRODUTOS
                              case 1 : 
                                   printf("Nome: ");
                                   scanf("%s", nome); 
                                   aux = query(nome, raizB);
                                   if (aux == NULL) {
                                        printf("\nQuantidade: ");
                                        scanf("%d", &qtd);
                                        insert(raizB, create(nome, qtd)); 
                                        printf("\n\nProduto Cadastrado!\n\tNome: %s\n\tQtd: %d\n\n", nome, qtd); 
                                   }
                                   else 
                                   {
                                        printf("\nEste produto ja esta cadastrado!\n\n");
                                        printf("Deseja atualizar sua quantidade?\n[0] - Nao\n[1] - Sim\nOpcao: ");
                                        scanf("%d", &opt); 
                                        if (opt) goto updateB; 
                                        else printf("\nProcesso cancelado!\n\n");
                                   }
                                   PAUSAR;
                                   break;


                              // VERIFICAR SE PRODUTO EXISTE
                              case 2 : 
                                   printf("Nome: ");
                                   scanf("%s", nome); 
                                   aux = query(nome, raizB);
                                   if (aux == NULL) printf("\nProduto nao cadastrado!\n\n");
                                   else printf("\nProduto cadastrado!\n\tNome: %s\n\tQuantidade: %d\n\n", aux->nome, aux->quantidade);
                                   PAUSAR; 
                                   break;

                              // ATUALIZAR PRODUTO X
                              case 3 : 
                                   printf("Nome: ");
                                   scanf("%s", nome); 
                                   aux = query(nome, raizB);
                                   if (aux == NULL){
                                        printf("\nProduto nao cadastrado!\n\n");
                                   }
                                   else {
                                        updateB:
                                        printf("\nNova quantidade: ");
                                        scanf("%d", &qtd);
                                        update(aux, qtd);
                                        printf("\nProduto atualizado!\n\n");
                                   }
                                   PAUSAR;
                                   break;
                              
                              // LISTAR PRODUTOS 
                              case 4 : 
                                   printf("\n\n** Lista de Produtos **\n"); 
                                   printf("Nome\t\tQuantidade\n");
                                   list(raizB);
                                   printf("\n\n");
                                   PAUSAR; 
                                   break;
                              
                              // DELETAR PRODUTO 
                              case 5 : 
                                   printf("Nome: ");
                                   scanf("%s", nome); 
                                   aux = query(nome, raizB);
                                   if (aux == NULL){
                                        printf("\nProduto nao cadastrado!\n\n");
                                   }
                                   else {
                                        printf("\nProduto: %s\nQuantidade: %d\n\n", aux->nome, aux->quantidade);
                                        printf("Deseja excluir o produto?\n[0] - Nao\n[1] - Sim\nOpcao: ");
                                        scanf("%d", &opt); 
                                        if (opt) {
                                             delete(raizB, nome);
                                             printf("\nProduto deletado!\n\n");
                                        } 
                                        else printf("\nProduto nao deletado!\n\n");
                                   }
                                   PAUSAR;
                                   break;
                         }    
                    }
                    break;
               case 3 : // Visualizar itens duplicados
                    LIMPAR;
                    printf("** Interseccao das listas A e B **"); 

                    Lista *produtos; 
                    produtos->primeiro = NULL; 
                    produtos->ultimo = NULL; 

                    intersect(raizA, raizB, produtos);

                    if (produtos->primeiro != NULL) print_list(produtos);
                    else printf("\nNao ha itens iguais nas listas!\n\n"); 

                    PAUSAR; 

          }
    }
    return 0;
}
