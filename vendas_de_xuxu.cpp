#include <stdio.h>
#include <stdlib.h>


typedef struct noitem
{
   int info;     
   struct noitem *prox; 
}no;

typedef struct
{
    no *topo;
}pilha;

typedef struct
{
    no *inicio, *fim;
}fila;

no *NovoNo(int info);
pilha *InicializandoPilha();
void empilha(pilha *p, int dados);
int desempilha(pilha *p);


fila *InicializandoFila();
void empilhaFila(fila *q, int dado);
int desempilhaFila(fila *q);
int filavazia(fila *q);

void imprimeAptasVendas(pilha *p);
int imprimeVendas(pilha *p);
void imprimeAvariadas(fila *q);
void imprimeConserto(fila *q);
void imprimeAvaria(fila *q);

int main()
{
    pilha *Aptasvendas = InicializandoPilha();
    pilha *Vendas = InicializandoPilha();
    fila *Avaria = InicializandoFila();

    int op, repetir=1, NumCaixa, caixa;

    scanf("%d", &NumCaixa);
    for (int i = 0; i < NumCaixa; i++)
    {   
        scanf("%d", &caixa);
        empilha(Aptasvendas, caixa);
    }
    


    while (repetir)
    {
        scanf("%d", &op);
        switch (op)
        {
        case 0:
            empilha(Vendas, desempilha(Aptasvendas));
            printf("a caixa %d foi enviada para venda\n", imprimeVendas(Vendas));
            break;
        case -1:
            imprimeConserto(Avaria);
            empilha(Aptasvendas, desempilhaFila(Avaria));
            break;
        case -2:
            imprimeAptasVendas(Aptasvendas);
            break;
        case -3:
            imprimeAvariadas(Avaria);
            break;
        default:
            empilhaFila(Avaria, desempilha(Vendas));
            imprimeAvaria(Avaria);
            break;
        }
    }





    return 0;
}

pilha *InicializandoPilha()
{
    pilha *p = (pilha *)malloc(sizeof(pilha));
    p->topo = NULL;
    return p;
}

no *NovoNo(int info)
{
    no *n = (no *)malloc(sizeof(no));
    n->info = info;
    n->prox = NULL;
    return n;
}
void empilha(pilha *p, int dados)
{
    no *n = NovoNo(dados);
    n->prox = p->topo;
    p->topo = n;
}

int desempilha(pilha *p)
{
    int aux;
    no *n;
    n = p->topo;
    aux = n->info;
    p->topo = n->prox;
    free(n);
    
    return aux; 
}

void imprimeAptasVendas(pilha *p)
{
    no *n = p->topo;
    printf("APTAS PARA VENDAS\n");
    while (n != NULL)
    {
        printf(" %d\n", n->info);
        n = n->prox;
    }
  
    
}

fila *InicializandoFila()
{
    fila *q = (fila *)malloc(sizeof(fila));
    q->inicio = NULL;
    q->fim = NULL;

}

void empilhaFila(fila *q, int dado)
{
    no *n = NovoNo(dado);
    if(filavazia(q)){
        q->inicio = n;
        q->fim = n;
    }else{
       q->fim->prox = n;
       q->fim = n;    
    }
    
}
int desempilhaFila(fila *q)
{ 
    no *n;  
    int aux;
    if(filavazia(q))
    {
        printf("fila vazia\n");
        return -1;
    }
    
    n = q->inicio;
    aux = n->info;
    q->inicio = n->prox;
    if(q->inicio == NULL){
        q->fim = NULL;
    }
    free(n);

    return aux;
}

int imprimeVendas(pilha *p)
{
    return p->topo->info;
}

void imprimeAvaria(fila *q)
{
    printf("caixa foi %d avariada\n", q->fim->info);
}

void imprimeConserto(fila *q)
{
    printf("caixa foi %d consertada\n", q->inicio->info);
}

void imprimeAvariadas(fila *q)
{ 
    no *n;
    n= q->inicio;
    printf("AVARIAS\n");
    while(n != NULL)
        {
            printf("%d\n", n->info);
            n = n->prox;
        }
}
int filavazia(fila *q)
{
    return q->inicio == NULL;
}