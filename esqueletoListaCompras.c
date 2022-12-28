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

#define EXIT 10  // valor fixo para a opção que finaliza a aplicação

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
     printf("\nMenu principal\n");
     // complete com as demais opcoes...

     printf("%d - Sair do programa",EXIT);
     printf("\nDigite a opcao: ");
     scanf("%d",&op);
     return op;
}

// Apresenta o segundo menu da aplicação e retorna a opção selecionada
int menu2()
{
    int op = 0;
    printf("Submenu - Gerenciar lista de compras\n");
    // complete com as demais opcoes...

    printf("%d Retornar para o menu principal",EXIT);
    printf("\nDigite a opcao: ");
    scanf("%d",&op); 
    return op;
}

// Permite o cadastro de um item (caso o produto ainda não exista) em uma lista de compas
void insert()
{
     printf("inserindo");
     return;
}

// Permite consultar se um item está em uma lista de compras
void query()
{
     printf("pesquisando");
     return;
}

// Permite a atualização da quantidade de um produto (caso exista) na lista de compras
void update()
{
     printf("atualizando");
     return;
}

// Listar todos os itens da lista de compras em ordem alfabética;
void list()
{
     printf("listando");
     return;
}

// Permite excluir um item de uma lista de compras
void delete()
{
     printf("deletando");
     return;
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

    opcao1 = 0;
    while (opcao1 != EXIT)
    {
          opcao1 = menu1();
               
          switch(opcao1)
          {
               case 1 : // gerenciar lista de compras A
                    opcao2 = 0;
                    while(opcao2 != EXIT){
                         printf("\n\n** Lista de Compras A **\n\n");
                         opcao2 = menu2();
                         switch(opcao2){ // operacoes sobre a arvore A
                              case 1 : 
                                   insert();
                                   break;
                              case 2 : 
                                   query();
                                   break;
                              case 3 : 
                                   update();
                                   break;
                              case 4 : 
                                   list();
                                   break;
                              case 5 : 
                                   delete();
                         }    
                    }
                    break;
               case 2 : // gerenciar lista de compras B
                    // idem ao caso 1, mas para a arvore B
               case 3 : // Visualizar itens duplicados
                    intersect();

          }
    }
    return 0;
}
