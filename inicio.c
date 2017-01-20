void iniciar(fila *f)
{
	char escolha;
	FILE *venda;
	FILE *relatorio;
	char narquivo[40];
	float precoAtual;
	comprador comp_temp;
	int i;
	
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
		scanf("%c",&escolha);
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
			comp_temp = cadastraComprador();
			
			
			
			//retira o item da fila
			for(i=0;i<f->final;i++)
			{
				f->vet[i] = f->vet[i+1];
			}
			f->final--;
			return;
		}

		
	
	}
	
};

comprador cadastraComprador()
{
	comprador temp;
	char confir;
	
	do{
		gotoxy(7,0);
		printf("  +------------------------------------------------------------------------+\n");
		printf("  | Nome:                                                                  |\n");
		printf("  | CPF:                                                                   |\n");
		printf("  | Telefone:                                                              |\n");
		printf("  +------------------------------------------------------------------------+\n");
		printf("  | Confirmar (S-Sim // N-Não):                                              \n");
		printf("  +------------------------------------------------------------------------+\n");
		printf("                                                                            \n");
		printf("                                                                            \n");
		
		gotoxy(9,11);
		scanf("%40[^\n]s",temp.nome);
		setbuf(stdin,NULL);
		
		gotoxy(10,10);
		scanf("%d",&temp.cpf);
		setbuf(stdin,NULL);
		
		gotoxy(11,15);
		scanf("%15[^\n]s",temp.fone);
		setbuf(stdin,NULL);
		
		gotoxy(13,30);
		scanf("%[SNsn]c",&confir);
		setbuf(stdin,NULL);
	}while(confir!='S'||confir!='s');
	
	return temp;
	
};
