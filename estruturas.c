typedef struct struct_item
{
	unsigned codigo;
	char nome[30];
	float preco;
	float valorLance;
	char desc[60];
	float precoPago;
	long cpf_comprador;
} item;

typedef struct struct_fila
{
	unsigned int tamanho;
	item *vet;
	int final;
	int inicio;
} fila;

typedef struct struct_comprador
{
	char cpf[11];
	char nome[40];
	char fone[15];
} comprador;
