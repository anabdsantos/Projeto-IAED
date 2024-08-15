/* iaed-24 - ist109260 - project*/


/*
* Ficheiro: project.h
* Ana Santos - 109260
*/

#ifndef PROJECT_H
#define PROJECT_H
/** O número máximo de parques de estacionamento. */
#define MAX_PARQUES 20

/** Flags */
#define TRUE 1
#define FALSE 0 

/** Tamanho máximo que um nomeParque pode ter.*/
#define BUFSIZ 8192

/** Número de minutos num dia e num ano. */
#define MINUTOSDIA 1440
#define MINUTOSANOS 525600
#define MINUTOSHORA 60

/** Número de minutos num quarto de hora.*/
#define BLOCOS15 15

/** Tamanho inicial da hashtable */
#define INITIAL_SIZE 211


/* Definição da estrutura data */
typedef struct
{
    int dia, mes, ano;
    int hora, minutos;
} Data;

/* Definição da estrutura VeiculoSaida */
typedef struct VeiculoSaida {
    char *matriculaS;
    Data dataSaida;
    float valorPago;
    struct VeiculoSaida *prev, *next;

} VeiculoSaida;

/* Definição da estrutura DataFaturação */
typedef struct DataFaturacao {
    Data *dataF;
    float valorFaturado;
    VeiculoSaida *veiculoSaida;
    struct DataFaturacao *prev, *next;
} DataFaturacao;

/* Definição da estrutura Veiculo. */
typedef struct Veiculo {
    char *matricula;
    char *nomeParque;
    Data *dataEntrada;
    Data *dataSaida;
    struct Veiculo *prev, *next;
} Veiculo;

/* Definição da estrutura Parque. */
typedef struct Parque {
    char *nomeParque;
    int capacidade;
    float valor_15;
    float valor_15_apos_1hora;
    float valor_MAX_diario;
    int lugares_disponiveis;
    Veiculo *veiculos; 
    DataFaturacao *dataFaturacao;
    struct Parque *prev, *next;
} Parque;


/* Definição da estrutura Data Item */
typedef Data Item;

/* Definição da estrutura node numa lista ligada */
struct node {
    Item item;
    struct node *next;
};

/* Ponteiro para o topo da pilha */
static struct node *topo;

/* Definição da estrutura ParqueEDatas */
typedef struct ParqueEDatas {
    char *nomeParque;
    Data dataEntrada;
    Data dataSaida;
    struct ParqueEDatas *prev, *next;
} ParqueEDatas;

/* Definição da estrutura MatriculaCarro */
typedef struct matriculaCarro {
    char *matricula;
    ParqueEDatas *parqueEdatas;
} MatriculaCarro;

/* Definição da estrutura Node2 numa lista ligada */
typedef struct node2 {
    MatriculaCarro *p;
    struct node2 *next;
} Node2; 

/* Define um ponteiro para uma estrutura Node2 */
typedef Node2* Link; 

/* Define um ponteiro para uma estrutura MatriculaCarro */
typedef MatriculaCarro* Item2;

/* Define o tipo de chave da hash */
typedef char* Key; 
/* Função para extrair a key de um Item2*/
#define key(a) (a->matricula)

/* Definição da estrutura HashTable */
typedef struct {
    Link *table;
    int size; /* Tamanho atual da tabela */
    int capacity; /* Capacidade máxima da tabela */
} HashTable;


/*Funções que tratam a hashtable*/
unsigned int hash(Key k, int M);
void inicializaTable(HashTable *hashTable);
void freeHashTable(HashTable *hashTable);
void insertItem(HashTable *hashTable, Key k, Item2 item);
MatriculaCarro *findItem(HashTable *hashTable, Key k);

/* Funções que ajudam a criar a estrutura de dados da hashtable */
void inserirNoInicio(ParqueEDatas **head, ParqueEDatas *novoParque);
void inserirDepois(ParqueEDatas *prev, ParqueEDatas *novoParque);
void adicionarParqueEDatas(MatriculaCarro *matricula, char *nomeParque, 
Data dataEntrada, Data dataSaida);
MatriculaCarro *criarMatriculaCarro(char *matricula, char *nomeParque,
Data dataEntrada, Data dataSaida);

/*Funções Pilha*/
void iniciaPilha(void);
void push(Item data);
int semData();
void pop();
void libertaPilha();

/* Funções para tratar o comando p */
void criaParque(Parque **head, char *nomeParque, int capacidade,
float valor_15, float valor_15_apos_1hora, float valor_MAX_diario);
Parque* encontraParque(Parque **head, char *nomeParque);
void inserirParque(Parque **head, Parque *novoParque);
int contaParques(Parque *head);
int verificaParametros(int capacidade, float valor15, float valor15apos1 ,
float valorMAX);
void parqueAtual(Parque *parqueAtual);
void mostraParques(Parque **head);
void parques(Parque **head);

/* Funções para tratar o comando e */
int verificaMatricula(char *matricula);
void inserirVeiculoNoParque(Parque *parque, Veiculo *novoVeiculo);
Veiculo* encontraVeiculoNoParque(Parque *parque, char *matricula);
Veiculo* encontraVeiculo(Parque **head, char *matricula);
void criaVeiculo(Parque *parque, char *matricula, Data *dataEntrada );
void registaEntradaVeiculo(Parque *parque, char *matricula, Data *dataEntrada);
int verificarEntradaParque(Parque *parque, char *nomeParque, char *matricula);
void entradaVeiculos(Parque **head);

/* Funções para tratar o comando s. */
float valorPago(int minutinhos, float valor15, float valor15APOS1, 
float diario);
void introduzSaida(Parque *parque, Veiculo *veiculo, Data *dataSaida);
void dataGeralnaSaida(Parque *parque, Veiculo *veiculo, Data *dataE, 
Data *dataS);
void comandoS(Parque **head, HashTable *hashTable);

/* Funções para tratar o comando v. */
void parqueEdatasAtual(ParqueEDatas *parqueAtual);
void mostraParquesEDatas(ParqueEDatas **head);
int existeEntradaRepetida(MatriculaCarro *veiculo, char *nomeParque, 
Data dataEntrada);
void veiculosSemDataSaida(Parque **head, HashTable *hashTable);
void comandoV(Parque **head, HashTable *hashTable);

/* Funções para tratar o comando f. */
void acrescentaValorFaturado(Parque *parque, Data *dataF, float valorF);
void listaVeiculosSaida(Parque *parque, Veiculo *veiculo, Data dataSaida, 
float valorPago);
void percorrerVeiculosSaidaPorData(Parque *parque, Data *data);
void mostrarValorFaturadoPorDataSaida(Parque *parque);
int maisAntigaEspecial(Data *d1, Data *d2);
void comandoF(Parque **head);

/* Funções para tratar o comando r. */
void removeParquedaListaLigada(Parque **head, char *nomeParque);
void ordenaStrings(char **nomes, int count);
void imprimeListaPorNome(Parque *head);
void removerParquePorNome(HashTable *hashTable, char *nomeParque);
void comandoR(Parque **head, HashTable *hashtable);

/* Funções que apagam sistema */
void libertaParques(Parque *head);
void libertaVeiculosSaida(VeiculoSaida *veiculoSaida);
void libertaDataFaturacao(Parque *parque);
void libertaVeiculos(Parque *parque);


#endif

