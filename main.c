/*
 * Sistema de Leilão
 *
 * Programa escrito por Wesley Viana *
 * E-Mail: viana.wesley@gmail.com
 * Twitter: @wviana
 * Telefone: 064-9231-8069
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.c"


void mostraTitulo();
int menu();
void limparTela();
void gotoxy(int x, int y);

void formularioItem(fila *f);
void initFila(fila *f);
void aumentaFila(fila *f);
void addItem(fila *f, item i);
void listarItens(fila *f);
void apagarItem(fila *f);
void telaFinal();
void iniciar(fila *f);
int filaVazia(fila *f);
comprador cadastraComprador();


int main(int argc, char **argv)
{
	printf("\033[40m\033[37m");

	fila items;

	initFila(&items);


	while(1)
	{

		limparTela();
		mostraTitulo();
		switch(menu())
		{
			case 5:
				telaFinal();
				return 0;
				break;

			case 1:
				formularioItem(&items);
				getchar();
				break;

			case 2:
				listarItens(&items);
				break;

			case 3:
				apagarItem(&items);
				break;

			case 4:
				iniciar(&items);
				break;



		}
	}

	return 0;
}

void iniciar(fila *f)
{
	char escolha = '\0';
	FILE *venda = NULL;
	char narquivo[40];
	float precoAtual = 0.0;
	comprador comp_temp;
	int i = 0;
	char gedit[50];



	gotoxy(7,0);

	if(filaVazia(f))
	{
		printf("  +-------------------------------------------------------------------------+\n");
		printf("  |               ATENÇÃO NENHUM CADASTRADO FOI ENCONTRADO                  |\n");
		printf("  +-------------------------------------------------------------------------+\n");
		getchar();
		return;
	}

	printf("  +-------------------------------------------------------------------------+\n");
	printf("  | ITEM SENDO LEILOADO:                                                    |\n");
	printf("  +-------------------------------------------------------------------------+\n");
	printf("  | PRECO INICIAL:                      | PRECO ATUAL:                      |\n");
	printf("  +-------------------------------------------------------------------------+\n");
	printf("  |   L-Lance   |  C - Cancelar  |  V-Vendido  | ::                         |\n");
	printf("  +-------------------------------------------------------------------------+\n");



	gotoxy(8,25);
	printf("%05d %s",f->vet[f->inicio].codigo,f->vet[f->inicio].nome);

	gotoxy(10,21);
	printf("R$ %-11.2f",f->vet[f->inicio].preco);


	precoAtual = f->vet[f->inicio].preco;

	for(;;){
		gotoxy(10,56);
		printf("R$ %-11.2f",precoAtual);

		setbuf(stdin,NULL);
		gotoxy(12,52);
		// scanf("%[LlCcVv]c", &escolha);
		escolha = getchar();
		setbuf(stdin,NULL);

		if(escolha=='L'||escolha=='l')
		{
            precoAtual += f->vet[f->inicio].valorLance; 
		}
		else if(escolha=='C'||escolha=='c')
		{
			return;
		}
		else if(escolha=='V'||escolha=='v')
		{
			setbuf(stdin,NULL);
			comp_temp = cadastraComprador();
			f->vet[f->inicio].precoPago = precoAtual;

			strcpy(narquivo,"Compra ");
			strcat(narquivo,comp_temp.nome);
			strcat(narquivo," ");
			strcat(narquivo,f->vet[f->inicio].nome);
			strcat(narquivo,".txt");

			venda = fopen(narquivo,"w");

			fprintf(venda,"################################################################################\n");
			fprintf(venda,"##  ||    | ____|  | |  ||     | /_\\ |  |  _  |                       SISTEMA ##\n");
			fprintf(venda,"##  ||__  | __|    | |  ||__   |  _  |  | |_| |                         DE    ##\n");
			fprintf(venda,"##  |___| |_____|  | |  |___|  |_| |_|  |_____|                       LEILAO  ##\n");
			fprintf(venda,"################################################################################\n\n");

			fprintf(venda,"=================================  ITEM  =====================================\n");
			fprintf(venda,"CODIGO: %d\n",f->vet[f->inicio].codigo);
			fprintf(venda,"NOME: %s\n",f->vet[f->inicio].nome);
			fprintf(venda,"\t%s\n\n",f->vet[f->inicio].desc);
			fprintf(venda,"VALOR INICIAL: R$ %.2f\n",f->vet[f->inicio].preco);
			fprintf(venda,"VALOR DE CADA LANCE: R$ %.2f\n",f->vet[f->inicio].valorLance);
			fprintf(venda,"VALOR PAGO: R$ %.2f\n",f->vet[f->inicio].precoPago);
			fprintf(venda,"LANCES DADOS: %.0f\n",(f->vet[f->inicio].precoPago-f->vet[f->inicio].preco)/(float)f->vet[f->inicio].valorLance);


			fprintf(venda,"================================ COMPRADOR ===================================\n");
			fprintf(venda,"CPF: %13s\n",comp_temp.cpf);
			fprintf(venda,"NOME: %s\n",comp_temp.nome);
			fprintf(venda,"TELEFONE: %s\n",comp_temp.fone);
			fprintf(venda,"\n\n______________________________\t\t\t______________________________\nAssinatura do Vendedor\t\t\t\tAssinatura do Comprador\n");

			fclose(venda);

			//retira o item da fila
			for(i=0;i<f->final;i++)
			{
				f->vet[i] = f->vet[i+1];
			}
			f->final--;

			gotoxy(14,0);
			printf("+--------------------------------------------------------------------+\n");
			printf("| Deseja imprimir o contrato (S-Sim/N-Não):                          |\n");
			printf("+--------------------------------------------------------------------+\n");

			gotoxy(15,46);
			scanf("%[SsNn]c",&escolha);
			setbuf(stdin,NULL);

			strcpy(gedit,"gedit \"");
			strcat(gedit,narquivo);
			strcat(gedit,"\"");

			if(escolha=='s'||escolha=='S')
				system(gedit);


			return;
		}



	}

}

comprador cadastraComprador()
{
	comprador temp;
	char confir;

	for(;;){
		gotoxy(7,0);
		printf("   +------------------------------------------------------------------------+\n");
		printf("   | CPF:                                                                   |\n");
		printf("   | NOME:                                                                  |\n");
		printf("   | Telefone:                                                              |\n");
		printf("   +------------------------------------------------------------------------+\n");
		printf("   | Confirmar (S-Sim // N-Não):                                            |\n");
		printf("   +------------------------------------------------------------------------+\n");
		printf("                                                                             \n");
		printf("                                                                             \n");

		setbuf(stdin,NULL);

		gotoxy(8,11);
		scanf("%11[^\n]s", temp.cpf);
		setbuf(stdin,NULL);

		gotoxy(9,12);
		scanf("%[^\n]s", temp.nome);
		setbuf(stdin,NULL);

		gotoxy(10,16);
		scanf("%15[^\n]s", temp.fone);
		setbuf(stdin,NULL);

		gotoxy(12,34);
		scanf("%[SNsn]c",&confir);
		setbuf(stdin,NULL);

		if(confir=='s'||confir=='S')
			break;
	}

	return temp;

}



int filaVazia(fila *f)
{
	if(f->final<f->inicio)
		return 1;
	return 0;
}

void telaFinal()
{
	limparTela();
	gotoxy(0,0);
	printf("\t\t\t\tSOBRE O AUTOR\n\n");
	printf("Programa escrito por: \tWesley Viana\n");
	printf("E-Mail: \t\tviana.wesley@gmail.com\n");
	printf("Twitter: \t\t@wviana\n");
	printf("Fone: \t\t\t064-9231-8069\n\n\n");

	printf("        _____________  \n");
	printf("  /\\   /             \\ \n");
	printf(" /  \\  |  #   _   #  | \n");
	printf("  ||   |  #  | |  #  | \n");
	printf("============================================== \n");

	getchar();
}

void initFila(fila *f)
{
	f->tamanho = 10;
	f->vet = (item*) malloc(f->tamanho*sizeof(item));
	f->final = -1;
	f->inicio= 0;

}

void gotoxy(int x, int y)
{
	printf("\033[%d;%dH",x,y);
}

void limparTela()
{
	printf("\033[2J");
}



void aumentaFila(fila *f)
{
	f->tamanho+=10;
	f->vet = realloc(f,f->tamanho*sizeof(item));

}

void addItem(fila *f, item i)
{
	if(f->final==9)
		aumentaFila(f);
	f->vet[++f->final]=i;
}

void listarItens(fila *f)
{
	int i;

	gotoxy(7,0);
	printf("+-------+-------------+-----------+--------------------------------------------+\n");
	printf("|  COD  |    PRECO    |   LANCE   |                DESCRIÇÃO                   |\n");
	printf("+-------+-------------+-----------+--------------------------------------------+\n");
	for(i=0;i<=f->final;i++)
	{
		printf("| %05d | %-11.2f | %-9.2f | %-42s |\n",f->vet[i].codigo,f->vet[i].preco,f->vet[i].valorLance,f->vet[i].desc);
	}
	printf("+-------+-------------+-----------+--------------------------------------------+\n");
	getchar();
}

void apagarItem(fila *f)
{
	int i;
	unsigned codigoBusca;
	char confirmar;

	gotoxy(7,0);
	printf("  +-------------------------------------------------------------------------+\n");
	printf("  | Codigo do item a ser apagado:                                           |\n");
	printf("  +-------------------------------------------------------------------------+\n\n");

	gotoxy(8,35);
	scanf("%d",&codigoBusca);
	setbuf(stdin,NULL);

	for(i=0;f->vet[i].codigo!=codigoBusca;i++)
	{
		if(i>f->final)
		{
			gotoxy(11,0);
			printf("  +-------------------------------------------------------------------------+\n");
			printf("  |                  ITEM NÃO ENCONTRADO                                    |\n");
			printf("  +-------------------------------------------------------------------------+\n");
			getchar();
			return;
		}
	}


	gotoxy(11,0);
	printf("+------------------------------------------------------------------------------+\n");
	printf("|                            ITEM A SER APAGADO                                |\n");
	printf("+-------+-------------+-----------+--------------------------------------------+\n");
	printf("|  COD  |    PRECO    |   LANCE   |                DESCRIÇÃO                   |\n");
	printf("+-------+-------------+-----------+--------------------------------------------+\n");
	printf("| %05d | %-11.2f | %-9.2f | %-42s |\n",f->vet[i].codigo,f->vet[i].preco,f->vet[i].valorLance,f->vet[i].desc);
	printf("+-------+-------------+-----------+--------------------------------------------+\n");
	printf("| CONFIRMAR EXCLUSÃO DESTE ITEM (S-SIM / N-NÃO):                               |\n");
	printf("+------------------------------------------------------------------------------+\n");

	gotoxy(18,50);
	scanf("%c",&confirmar);
	setbuf(stdin,NULL);

	if(confirmar=='S'||confirmar=='s')
	{
		for(;i<f->final;i++)
		{
			f->vet[i]=f->vet[i+1];
		}
		f->final--;
	}

}

void formularioItem(fila *f)
{
	item i;
	char escolha;

	for(;;)
	{
		gotoxy(7,0);
		printf("   +------------------------------------------------------------------------+\n");
		printf("   |                           CADASTRO DE ITEM                             |\n");
		printf("   +------------------------------------------------------------------------+\n");
		printf("   | Nome:                              | Preco Inicial:                    |\n");
		printf("   | Valor de Lances:                   | Codigo Gerado:                    |\n");
		printf("   +------------------------------------------------------------------------+\n");
		printf("   | Descrição:                                                             |\n");
		printf("   +------------------------------------------------------------------------+\n");
		printf("   |    A - Aceitar         |     N - Negar     |                           |\n");
		printf("   +------------------------------------------------------------------------+\n");

		gotoxy(10,12);
		scanf("%20[^\n]s",i.nome);
		setbuf(stdin,NULL);

		gotoxy(10,58);
		scanf("%f",&i.preco);
		setbuf(stdin,NULL);

		gotoxy(11,23);
		scanf("%f",&i.valorLance);
		setbuf(stdin,NULL);

		gotoxy(13,17);
		scanf("%59[^\n]s",i.desc);
		setbuf(stdin,NULL);

		if(f->final==-1)
			i.codigo = 1;
		else
			i.codigo = f->vet[f->final].codigo+1;


		gotoxy(11,58);
		printf("%05d",i.codigo);

		gotoxy(15,65);
		scanf("%c",&escolha);
		setbuf(stdin,NULL);

		if(escolha=='A'||escolha=='a')
		{
			addItem(f,i);
			return;
		}
		else if(escolha=='N'||escolha=='n')
		{
			return;
		}

	}

}

int menu()
{
	int escolha;
	gotoxy(20,0);
	printf("================================================================================\n");
	printf("|| 1-Adicionar Item | 2-Listar Itens | 3-Apagar Itens |  4-Iniciar  |  5-Sair ||\n");
	printf("================================================================================\n");
	printf(":: ");
	scanf("%d",&escolha);
	setbuf(stdin,NULL);
	return escolha;
}

void mostraTitulo()
{
	gotoxy(0,0);
	printf("################################################################################\n");
	printf("##  ||    | ____|  | |  ||     | /_\\ |  |  _  |                       SISTEMA ##\n");
	printf("##  ||__  | __|    | |  ||__   |  _  |  | |_| |                         DE    ##\n");
	printf("##  |___| |_____|  | |  |___|  |_| |_|  |_____|                       LEILAO  ##\n");
	printf("################################################################################\n\n");
}
