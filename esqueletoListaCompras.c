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

// Struct que representa um item de uma lista de compras armazenada em uma arvore binaria de busca
struct item {
	char produto[50];
	int quantidade;
    struct item  *esquerdo; 
	struct item  *direito;
};
typedef struct item Item;

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
	printf("\n01- Inserir produto");
	printf("\n02- Pesquisar produto");
	printf("\n03- Atualizar produto");
	printf("\n04- Listar produtos");
	printf("\n05- Deletar produto");
     printf("\n%d Retornar para o menu principal",EXIT);
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
    strcpy(new->produto, nome);
    new->quantidade = qtd; 
    new->direito = NULL;
    new->esquerdo = NULL;
    return new; 
}

// Permite o cadastro de um item (caso o produto ainda não exista) em uma lista de compas
Item* insert(Item *raiz, Item *new)
{
     if (raiz == NULL) return new; 
     if (strcmp(raiz->produto, new->produto) == 1) raiz->esquerdo = insert(raiz->esquerdo, new);
     else raiz->direito = insert(raiz->direito, new);
       
     return raiz; 
}

// Permite consultar se um item está em uma lista de compras
Item* query(char name[50], Item* raiz)
{
    if (raiz == NULL) return NULL;
    if (strcmp(name, raiz->produto) == 0) return raiz; 

     Item *esq = query(name, raiz->esquerdo);
     if (esq != NULL) return esq; 
     return query(name, raiz->direito);     
}

// Permite a atualização da quantidade de um produto (caso exista) na lista de compras
// CONSERTAR 
int update(Item *raiz, char nome, int newQtd)
{
     Item* aux = query(nome, raiz);
     if (aux == NULL) return 0; 
     aux->quantidade = newQtd; 
     return 1; 
}

// Listar todos os itens da lista de compras em ordem alfabética;
void list(Item* raiz)
{
     if (raiz == NULL) return; 
     list(raiz->esquerdo);
     printf("%s\t\t%d\n", raiz->produto, raiz->quantidade);
     list(raiz->direito);    
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

void intersect()
{
     printf("interseccao");
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

     raizA = insert(raizA, D);
     raizA = insert(raizA, B);
     raizA = insert(raizA, E);
     raizA = insert(raizA, A);
     raizA = insert(raizA, C);

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
                                   if (query(nome, raizA) == NULL) {
                                        printf("\nQuantidade: ");
                                        scanf("%d", &qtd);
                                        insert(raizA, create(nome, qtd)); 
                                        printf("\n\nProduto Cadastrado!\n\tNome: %s\n\tQtd: %d\n\n", nome, qtd); 
                                   } else printf("\nProduto ja existe!\n\n");
                                   PAUSAR;
                                   break;


                              // VERIFICAR SE PRODUTO EXISTE
                              case 2 : 
                                   printf("Nome: ");
                                   scanf("%s", nome); 
                                   if (query(nome, raizA) == NULL) printf("\nProduto nao cadastrado!\n\n");
                                   else printf("\nProduto cadastrado!\n\n");
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
                                        printf("\nNova quantidade: ");
                                        scanf("%d", &qtd);
                                        // update(raizA, nome, qtd);
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
                                        printf("\nProduto: %s\nQuantidade: %d\n\n", aux->produto, aux->quantidade);
                                        printf("Deseja excluir o produto?\n[0] - Nao\n[1] - Sim\nOpcao: ");
                                        scanf("%d", &opt); 
                                        if (opt) {
                                             delete(raizA, nome);
                                             printf("\nProduto deletado!\n\n");
                                        } 
                                        else printf("\nProduto não deletado!\n\n");
                                   }
                                   PAUSAR;
                                   break;
                         }    
                    }
                    break;
               case 2 : // gerenciar lista de compras B
                    // identico ao caso 1, mas para a arvore B
               case 3 : // Visualizar itens duplicados
                    intersect();

          }
    }
    return 0;
}
