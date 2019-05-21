# Trabalho Prático de Estrutura de Dados #
**As  seguintes  características das cidades  serão consideradas:  nome  (string);  estado (string); população(inteiro);  IDH (float); nº médio de famílias beneficiadas pelo bolsa família (inteiro).
O programa deve manter uma lista implementada com apontadores na qual cada elemento da lista devearmazenar um estado e seus respectivos dados. Cada estado terá também uma lista de cidades pertencentes a este estado com seus respectivos dados**

 ## Structs ##

1. `typedef struct Cidade *TipoApontadorC;`
2. `typedef struct Estado *TipoApontadorE;`
3. `typedef struct nomeEstado{char nome[50];} Nome;` 
4. `typedef struct Cidade{
	int familiaCBolsa;
	float idh;
	int populacao;
	Nome nome;
	TipoApontadorC prox;
} Cidade;`
5. `typedef struct Estado{
	int familiaCBolsa;
	float idh;
	int populacao;
	Nome nome;
	int qtdCidades;
	TipoApontadorC topo;
	Cidade melhor, pior;
} Estado;`


 ## Funções ##
 1. `void imprimeEstado(Estado e)`
 2. `imprimeCidade(Cidade c, Nome estado)` 
 3. `void inicializarEstado(TipoApontadorE estado, Nome nome)`
 4. `int posicaoEstado(char nome[40])`
 5. `void inserirCidade(Cidade cidade, TipoApontadorE estado)`
 6. `void ordenaEstadosPorIDH(Estado e[])`
 7. `void ordenaMaiorCidade(Cidade c[],Nome ne[])`
 8. `void ordenaPiorCidade(Cidade c[],Nome ne[])`
 9. `dadosDeUmEstado(Estado e[], Nome nome)`
 10. `dadosDeUmaCidade(Estado e[], Nome nome)`
 11. `void selecionaOp(char op, Estado e[])`


