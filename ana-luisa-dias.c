#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define QTD_ESTADOS 27
// IDE utilizada: VSCode GCC version 7.3.0 (Ubuntu 7.3.0-27 ubuntu1~18.04) 

typedef struct Cidade *TipoApontadorC;
typedef struct Estado *TipoApontadorE;
typedef struct nomeEstado{char nome[50];} Nome;

Nome nomesEstados[QTD_ESTADOS] = {"acre", "alagoas", "amapa", "amazonas", "bahia", "ceara", "distrito federal", "espirito santo", "goias", "maranhao", "mato grosso", "mato grosso do sul", "minas gerais", "para", "paraiba", "parana", "pernambuco", "piaui", "rio de janeiro", "rio grande do norte", "rio grande do sul", "rondonia", "roraima", "santa catarina", "sao paulo", "sergipe", "tocantins"};

typedef struct Cidade{
	int familiaCBolsa;
	float idh;
	int populacao;
	Nome nome;
	TipoApontadorC prox;
} Cidade;

typedef struct Estado{
	int familiaCBolsa;
	float idh;
	int populacao;
	Nome nome;
	int qtdCidades;
	TipoApontadorC topo;
	Cidade melhor, pior;
} Estado;

void imprimeEstado(Estado e){
	printf(" estado: %s\n número de municípios: %d\n população:%d\n idh:%.3f\n familias com bolsa familia:%d \n\n",
				 e.nome.nome, e.qtdCidades, e.populacao, e.idh / e.qtdCidades, e.familiaCBolsa);
}

void imprimeCidade(Cidade c, Nome estado){
	printf("nome: %s\nestado: %s\npopulação:%d\nidh:%.3f\nfamilias bolsa familia:%d\n\n",
				 c.nome.nome, estado.nome, c.populacao, c.idh, c.familiaCBolsa);
}

void inicializarEstado(TipoApontadorE estado, Nome nome)
{
	//A atribuição do NULL gerava um erro do tipo void*
	Cidade vazia;
	vazia.idh = 0;
	vazia.familiaCBolsa = 0;
	vazia.populacao = 0;

	estado->melhor =  vazia;
	estado->pior = vazia;
	estado->topo = NULL;
	estado->nome = nome;
	estado->familiaCBolsa = 0;
	estado->idh = 0;
	estado->populacao = 0;
	estado->qtdCidades = 0;
}

int posicaoEstado(char nome[40])
{
	int i = 0;
	for (i = 0; i < QTD_ESTADOS; i++){
		if (strcmp(nome, nomesEstados[i].nome) == 0){
			return i;
		}
	}
	return -1;
}

void inserirCidade(Cidade cidade, TipoApontadorE estado){
	TipoApontadorC aux;
	aux = (TipoApontadorC)malloc(sizeof(Cidade));
	aux->familiaCBolsa = cidade.familiaCBolsa;
	aux->idh = cidade.idh;
	aux->populacao = cidade.populacao;

	if (estado->topo == NULL){
		estado->topo = aux;
			estado->melhor = cidade;
			estado->pior = cidade;
		
	}else {
		aux->prox = estado->topo;
		estado->topo = aux;
		if (aux->idh > estado->melhor.idh){
			estado->melhor = cidade;
		} else if (aux->idh < estado->pior.idh)	{
			estado->pior = cidade;
		}
	}

	estado->familiaCBolsa += cidade.familiaCBolsa;
	estado->populacao += cidade.populacao;
	estado->idh += cidade.idh;
	estado->qtdCidades++;
}

void ordenaEstadosPorIDH(Estado e[]){
	int k, j, i;
	Estado aux;
//ordenando os estados utilizando bubble sort 
	for (k = 1; k < QTD_ESTADOS; k++){
		for (j = 0; j < QTD_ESTADOS - 1; j++)	{
			float idhcurrent = e[j].idh / e[j].qtdCidades;
			float idhnext = e[j + 1].idh / e[j + 1].qtdCidades;

			if (idhcurrent < idhnext){
				aux = e[j];
				e[j] = e[j + 1];
				e[j + 1] = aux;
			}
		}
	}
	for (int x = 0; x < QTD_ESTADOS; x++){
		imprimeEstado(e[x]);
	}
	
}

void ordenaMaiorCidade(Cidade c[],Nome ne[]){
	int k, j, i,n= QTD_ESTADOS;
	Cidade aux;
	Nome nome;
	//ordenando as melhores cidades utilizando bubble sort 
	for (k = 1; k < n; k++){
		for (j = 0; j < n - 1; j++)	{ 
				if (c[j].idh < c[j + 1].idh)	{
				aux = c[j];
				nome = ne[j];
				c[j] = c[j + 1];
				ne[j] = ne[j+1];
				c[j + 1] = aux;
				ne[j+1] = nome;
			}
		}
	}
	for (int i = 0; i < 10; i++){
		imprimeCidade(c[i],ne[i]);
	}
	
}

void ordenaPiorCidade(Cidade c[],Nome ne[]){
	int k, j, i,n= QTD_ESTADOS;
	Cidade aux;
	Nome nome;
	//ordenando as piores cidades utilizando bubble sort 
	for (k = 1; k < n; k++){
		for (j = 0; j < n - 1; j++)	{ 
				if (c[j].idh > c[j + 1].idh)	{
				aux = c[j];
				nome = ne[j];
				c[j] = c[j + 1];
				ne[j] = ne[j+1];
				c[j + 1] = aux;
				ne[j+1] = nome;
			}
		}
	}
	for (int i = 0; i < 10; i++){
		imprimeCidade(c[i],ne[i]);
	}
	
}

void dadosDeUmEstado(Estado e[], Nome nome){
	imprimeEstado(e[posicaoEstado(nome.nome)]);
}

void dadosDeUmaCidade(Estado e[], Nome nome){
	char buf[1000];
	int count = 0;
	int found = 0;
	FILE *file = fopen("data.csv", "r");
	/*como as cidades estão organizadas em ordem alfabética
	o arquivo é lido novamente até encontrar todas as ocorrências daquela cidade (e/ou mudar de letra) 
	similiar a estrutura de "desempilha" da atividade de pilhas*/

	while (fgets(buf, sizeof(buf), file)){
		Cidade c;
		Nome nEstado;
		sscanf(buf, "%60[^;];%40[^;];%d;%f;%d", c.nome.nome, nEstado.nome, &c.populacao, &c.idh, &c.familiaCBolsa);
		if (strcmp(nome.nome, c.nome.nome) == 0){
			imprimeCidade(c, nEstado);
			found++;
		}
		else if (found > 0 && nome.nome[0] != c.nome.nome[0]){
			break;
		}
	}
	fclose(file);
}

void selecionaOp(char op, Estado e[])
{
	Nome nome;
	Cidade c[QTD_ESTADOS];
	Cidade cm[QTD_ESTADOS];
	Nome estadoMaior[QTD_ESTADOS];
	Nome estadoPior[QTD_ESTADOS];
	
	switch (op)	{
	case 'e':
	//questão 2 dados de um estado
		gets(nome.nome);
		dadosDeUmEstado(e, nome);
		break;
	
	case 'z':
	//questão 4 IDH versus Bolsa Família – Piores cidades
		for(int x=0;x<QTD_ESTADOS;x++){
			cm[x] = e[x].pior;
			estadoPior[x] = e[x].nome;
		}
		ordenaPiorCidade(cm,estadoPior);
		break;

	case 'c':
	//questão 1 dados de uma cidade
		gets(nome.nome);
		dadosDeUmaCidade(e, nome);
		break;
	
	case 'a':
	//questão 3 IDH versus Bolsa Família – Melhores cidades
		for(int x=0;x<QTD_ESTADOS;x++){
			c[x] = e[x].melhor;
			estadoMaior[x] = e[x].nome;
		}
		ordenaMaiorCidade(c,estadoMaior);	
		break;

	case 't':
	//questão 5 Ranking dos estados ordenado pelos maiores IDH
		ordenaEstadosPorIDH(e);
		break;
	default:
		printf("");
	}
}


int main(){
	int i = 0;
	Estado estados[QTD_ESTADOS];
	char nome[20];
	int count = 0;
	char buf[1000];
	char op;

	for (i = 0; i < QTD_ESTADOS; i++){	inicializarEstado(&estados[i], nomesEstados[i]);	}
	
	//lendo o arquivo
	FILE *file = fopen("data.csv", "r");
	while (fgets(buf, sizeof(buf), file))
	{
		Cidade c;
		Nome nEstado;
		sscanf(buf, "%60[^;];%40[^;];%d;%f;%d", c.nome.nome, nEstado.nome, &c.populacao, &c.idh, &c.familiaCBolsa);
		if (count > 0 && posicaoEstado(nEstado.nome) != -1){
			inserirCidade(c, &estados[posicaoEstado(nEstado.nome)]);
		}
		count++;
	}
	//fim da leitura do arquivo

	fclose(file);
	scanf("%c", &op);
	//lendo opção 
	setbuf(stdin, NULL);
	//retirando buf do teclado para permitir a leitura dentro do próximo método 
	selecionaOp(op, estados);

	return 0;
}
