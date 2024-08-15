/* iaed24 - ist1109260 - project */


/**
 * Ficheiro principal da resolução do projeto que consiste na construção
 de um sistema de gestão de parques de estacionamento.
 * FICHEIRO: project.c
 * AUTOR: Ana Santos - 109260
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "project.h"

/** Funções auxiliares para ler e imprimir datas **/

/** 
 * Lê e armazena os dados na estrutura Data.
*/
Data leData(void) {
    Data d;
    scanf("%d-%d-%d %d:%d",&d.dia,&d.mes,&d.ano,&d.hora,&d.minutos);
    return d;
}

/** 
 * Imprime a estrutura Data .
 * PARAMETRO: d A data a ser imprimida.
*/
void mostraData(const Data *d) {
    printf("%02d-%02d-%04d %02d:%02d",d->dia,d->mes,d->ano,d->hora,d->minutos);
}

/** Funções auxiliares para tratar as datas **/

/** 
 * Calcula o número de dias de um determinado mês.
 * PARAMETRO: m O mês a ser verificado.
 * RETORNA: O número de dias de um determinado mês.
 */
int diames(int m) {
    if (m == 2)
        return 28;

    if (m <= 7) {
        if (m % 2 != 0)
            return 31;
        else
            return 30;
    } else {
        if (m % 2 == 0)
            return 31;
        else
            return 30;
    }
}

/**
 * Determina se a primeira Data é mais antiga do que a segunda.
 * PARAMETRO: d1 A data 1 
 * PARAMETRO: d2 A data 2
 * RETORNA: TRUE se a d1 for mais antiga que a d2, FALSE caso contrário.
 */
int maisAntiga(Data *d1, Data *d2) {
    if (d1->ano < d2->ano) return TRUE;
    if (d1->ano > d2->ano) return FALSE;
    if (d1->mes < d2->mes) return TRUE;
    if (d1->mes > d2->mes) return FALSE;
    if (d1->dia < d2->dia) return TRUE;
    if (d1->dia > d2->dia) return FALSE;
    if (d1->hora < d2->hora) return TRUE;
    if (d1->hora > d2->hora) return FALSE;
    if (d1->minutos < d2->minutos) return TRUE;
    if (d1->minutos > d2->minutos) return FALSE;
    return TRUE; // As datas são iguais
}

/** 
 * Determina se duas Datas são iguais (sem contar com a hora).
 * PARAMETRO: d1 A data 1
 * PARAMETRO: d2 A data 2 
 * RETORNA: TRUE se as datas forem iguais, FALSE caso contrário.
*/
int comparaDatas(Data *data1, Data *data2) {
    if (data1->dia == data2->dia && data1->mes == data2->mes && 
    data1->ano == data2->ano) {
        // As datas são iguais
        return TRUE;
    } else {
        // As datas são diferentes
        return FALSE;
    }
}

/**
 * Converte as datas para minutos com "base" na data 00-00-0000 00:00.
 * PARAMETRO: d A data
 * RETORNA: Os minutos correspondentes a uma data.
*/
int transformaMinutos(Data d) {
    int minutos, i = 1, counterDias = 0;
    while ( i < d.mes ) {
        int diasDoMes = diames(i);
        counterDias += diasDoMes;
        i++;
    }
    minutos = d.ano * MINUTOSANOS + (counterDias+d.dia-1) * 
    MINUTOSDIA + d.hora*MINUTOSHORA + d.minutos;

    return minutos;
}

/**
 * Calcula a diferença em minutos entre duas datas.
 * PARAMETRO: d1 A data 1
 * PARAMETRO: d2 A data 2
 * RETORNA: Os minutos de diferença entre duas datas.
 */
float acumulaMinutos(Data *d1, Data *d2) {
    float minutos;
    int minutosD1;
    int minutosD2;

    minutosD1 = transformaMinutos(*d1);
    minutosD2 = transformaMinutos(*d2);

    minutos = minutosD2 - minutosD1;
    return minutos;
}

/** Funções auxiliares para verificar parâmetros das datas **/

/**
 * Verifica se o dia e o mês da Data sao válidos.
 * PARAMETRO: data A data.
 * RETORNA: TRUE se o mês estiver dentro dos parâmetros, FALSE caso contrário.
 */
int verificaDiaMes(Data data) {
    int m = data.mes, d = data.dia;

    // Verifica se o mes é válido
    if (m < 1 || m > 12) {
        return FALSE;
    }

    // Verifica se o dia está dentro do intervalo correto para o mes
    if (d < 1 || (m == 2 && d > 28) || 
        ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) || d > 31) {
            return FALSE;
    }

    return TRUE;
}

/**
 * Verifica se a data é válida.
 * PARAMETRO: data A data.
 * RETORNA: TRUE se a data se estiver dentro dos parâmetros, 
   FALSE caso contrário.
 */
int verificaData(Data data) {
    if (!verificaDiaMes(data)) {
        return FALSE;
    }
    /** Verifica se a hora está no intervalo correto. */
    if (data.hora < 0 || data.hora > 23) {
        return FALSE;
    }
    /* Verifica se os minutos estão no intervalo correto. */
    if (data.minutos < 0 || data.minutos > 59) {
        return FALSE;
    }
    return TRUE;
}

/** Funções auxiliares para verificar os parâmetros das matrículas **/

/**
 * Verifica se uma letra é MAIÚSCULA e de A a Z.
 * PARAMETRO: c A letra.
 * RETORNA: TRUE caso a letra esteja dentro dos parâmetros, FALSE caso 
   contrário.
 */
int verificaLetra(char c) {
    if (c >= 'A' && c <= 'Z') {
        return TRUE;
    }
    return FALSE;
}

/**
 * Verifica se um dígito está entre 0 e 9.
 * PARAMETRO: c O dígito.
 * RETORNA: TRUE caso o dígito esteja dentro dos parâmetros, FALSE caso 
   contrário.
 */
int verificaDigito(char c) {
    if (c >= '0' && c <= '9') {
        return TRUE;
    }
    return FALSE;
}

/**
 * Verifica se um par de caracteres tem apenas letras ou apenas dígitos.
 * PARAMETRO: primeiro Primeiro char.
 * PARAMETRO: segundo Segundo char.
 * RETORNA: TRUE caso o par apenas tenha letra ou dígitos, FALSE caso contrário.
 */
int verificaPar(char primeiro, char segundo) {
    if ((verificaLetra(primeiro) && verificaLetra(segundo)) ||
        (verificaDigito(primeiro) && verificaDigito(segundo))) {
            return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * Verifica se a matricula tem o formato válido.
 * PARAMETRO: matricula A matrícula.
 * RETORNA: TRUE caso a matrícula esteja dentro dos parâmetros, FALSE caso 
   contrário.
 */
int verificaMatricula(char *matricula) {
    int len = strlen(matricula);
    int letra = FALSE; 
    int digito = FALSE; 

    /** Verifica cada par de caracteres */
    for (int i = 0; i < len; i += 3) {
        if (verificaPar(matricula[i], matricula[i+1])) {
            if (verificaLetra(matricula[i]) && verificaLetra(matricula[i+1])) {
                letra = TRUE;
            }
            else if (verificaDigito(matricula[i]) && 
                verificaDigito(matricula[i+1])) {
                digito = TRUE;
            }
        }
        else {
            return FALSE; 
        }
    } 
    return (letra && digito);
}

/** Funções auxiliares para tratar o input **/

/**
 * "Absorve" espaços.
 * RETORNA: TRUE se chegar ao fim de uma linha. FALSE caso contrário.
 */
int leEspacos() {
    int c;
    while ((c = getchar()) == ' ' || c == '\t');
    if (c == '\n')
        return TRUE;
    ungetc(c, stdin);
    return FALSE;
}

/**
 * "Absorve" espaços em branco até encontrar um char diferente.
 */
void saltaEspacos() {
    int c;
    while ((c = getchar()) == ' ' || c == '\t' || c == '\n');
    ungetc(c, stdin);
}

/** 
 * Lê um nome que recebe como parâmetro.
 * RETORNA: O nome lido como uma string. 
*/
char* leNome() {
    char *s, b[BUFSIZ];
    int i = 0, c;

    b[0] = getchar();
    if (b[0] != '"') {
        i = 1;
        while ((c = getchar()) != ' ' && c != '\t' && c != '\n')
            b[i++] = c;
        ungetc(c, stdin);
    }
    else {
        while((c = getchar()) != '"')
            b[i++] = c;
    }
    b[i++] = '\0';

    s = (char *) malloc(sizeof(char) * (strlen(b) + 1));
    strcpy(s, b);

    return s;
}

/**
 * Verifica se há mais input disponível após espaços em branco.
 * RETORNA: TRUE se existir mais input. FALSE caso contrário.
 */
int temMaisInput() {
    int c;
    /* Ignora espaços em branco */
    while ((c = getchar()) == ' ' || c == '\t') {
        continue;
    }
    if (c != '\n' && c != EOF) {
        ungetc(c, stdin); 
        return TRUE;
    }
    return FALSE; 
}


/** Funções para tratar todos os comandos da hashtable criada **/

/**
 * Função hash que converte strings em valor hash.
 * PARAMETRO: key A chave (matricula) a ser convertida.
 * PARAMETRO: M O tamanho da hashTable.
 * RETORNA: O valor hash.
 */
unsigned int hash(Key key, int M) {
    unsigned int valorH = 0;
    while (*key != '\0') {
        valorH = *key + 31 * valorH;
        key++;
    }
    return valorH % M;
}

/**
 * Inicializa a hashtable.
 * PARAMETRO: hashTable A hashtable a ser inicializada.
 */
void inicializaTable(HashTable *hashTable) {
    hashTable->size = 0;
    hashTable->capacity = INITIAL_SIZE;
    /** Aloca memória para a hashtable */
    hashTable->table = (Link*)malloc(sizeof(Link) * hashTable->capacity);
    /** Inicializa cada entrada da table como NULL */
    for (int i = 0; i < hashTable->capacity; i++)
        hashTable->table[i] = NULL;
}

/**
 * Liberta toda a memória associada à hashtable
 * PARAMETRO: hashTable  A hashtable a ser libertada.
 */
void freeHashTable(HashTable *hashTable) {
    for (int i = 0; i < hashTable->capacity; i++) {
        Link current = hashTable->table[i];
        /** Percorre a lista ligada na posição i. */
        while (current != NULL) {
            Link temp = current;
            current = current->next;

            /** Liberta a  memória dos dados contidos em temp->p. */
            free(temp->p->matricula);
            /** Liberta a memória de cada ParqueEDatas na lista ligada. */
            ParqueEDatas *parqueEDatas = temp->p->parqueEdatas;
            while (parqueEDatas != NULL) {
                ParqueEDatas *tempParqueEDatas = parqueEDatas;
                parqueEDatas = parqueEDatas->next;
                free(tempParqueEDatas->nomeParque);
                free(tempParqueEDatas);
            }
            /** Liberta a memória da MatriculaCarro. */
            free(temp->p);
            /** Liberta a memória do nó da lista. */
            free(temp);   
        }
    }
    /** Liberta a memória da hashTable. */
    free(hashTable->table);
    hashTable->capacity = 0;
    hashTable->size = 0;
}

/**
 * Insere um novo item2 na hashTable. 
 * Resolução de colisões por encadeamento.
 * PARAMETRO: hashTable A hashtable na qual queremos inserir o item.
 * PARAMETRO: k A chave associada ao item.
 * PARAMETRO: item O item a ser inserido na hashtable.
 */
void insertItem(HashTable *hashTable, Key k, Item2 item) {
    /** Calcula o índice hash para a key. */
    int h = hash(k, hashTable->capacity);
    /** Aloca memória para um novo nó da lista ligada. */
    Link newNode = (Link)malloc(sizeof(Node2));
    /** Insere o novo nó no início da lista ligada. */
    newNode->p = item;
    newNode->next = hashTable->table[h];
    hashTable->table[h] = newNode;
    /** Aumenta o tamanho da hashTable. */
    hashTable->size++;
}

/**
 * Encontra um item na hashTable com base na key.
 * PARAMETRO: hashTable A hashtable na qual queremo encontrar o item.
 * PARAMETRO: k A chave associada ao item que queremos encontrar.
 * RETORNA: Retorna um ponteiro para o item encontrado, NULL se a chave não for
   encontrada.
 */
MatriculaCarro *findItem(HashTable *hashTable, Key k) {
    int h = hash(k, hashTable->capacity);
    Link current = hashTable->table[h];
    while (current != NULL) {
        /** Verifica se a key do item2 é igual à chave procurada. */
        if (strcmp(key(current->p), k) == 0)
            return current->p;
        current = current->next;
    }
    /** Chave não encontrada. */
    return NULL;
}


/** PILHA PARA GUARDAR DATA ATUAL NO SISTEMA **/

/**
 * Inicializa pilha.
 */
void iniciaPilha() {
    topo = NULL; 
    }

/**
 * Dá "push" de um novo item no topo da pilha.
 * PARAMETRO: data A data cuja qual queremos introduzir no topo da pilha.
 */
void push(Item data) {
    struct node *novo;
    novo = (struct node *) malloc(sizeof(struct node));
    novo->item = data;
    novo->next = topo;
    topo = novo;
}

/**
 * Verifica se pilha está vazia.
 * RETORNA: TRUE caso esteja, FALSE caso contrário.
 */
int semData() {
    if(topo == NULL) return TRUE;
    return FALSE;
}

/**
 * Remove elemento do topo da pilha.
 */
void pop() {
    struct node *temp = topo;
    topo = topo->next;
    free(temp);
}

/**
 * Liberta toda a memória da pilha.
 */
void libertaPilha() {
    while (topo != NULL) {
        pop();
    }
}

/** Funções que ajudam a criar a estrutura de dados da hashtable **/

/**
 * Cria a estrutura MatriculaCarro que corresponde à estrutura da hashtable.
 * PARAMETRO: matricula A matricula do carro.
 * PARAMETRO: nomeParque O nome do parque.
 * PARAMETRO: dataEntrada A data de entrada do veículo no parque.
 * PARAMETRO: dataSaida A data de saida do veículo no parque.
 * RETORNA: Retorna um ponteiro para a estrutura MatriculaCarro criada. 
 */
MatriculaCarro *criarMatriculaCarro(char *matricula, char *nomeParque,
    Data dataEntrada, Data dataSaida) {

    MatriculaCarro *novaMatricula = (MatriculaCarro*)malloc(sizeof(MatriculaCarro));
    novaMatricula->matricula = strdup(matricula);
    
    novaMatricula->parqueEdatas = NULL;

    adicionarParqueEDatas(novaMatricula, nomeParque, dataEntrada, dataSaida);

    return novaMatricula;
}

/**
 * Adiciona as informações parquesEdatas da estrutura matriculaCarro.
 * PARAMETRO: matricula A estrutura MatriculaCarro na qual as informações serão 
   adicionadas.
 * PARAMETRO: nomeParque O nome do parque a ser adicionado.
 * PARAMETRO: dataEntrada A data de entrada no parque a ser adicionada.
 * PARAMETRO: dataSaida A data de saida no parque a ser adicionada.
 */
void adicionarParqueEDatas(MatriculaCarro *matricula, char *nomeParque, 
    Data dataEntrada, Data dataSaida) {
    
    /* Aloca memória para uma nova estrutura ParqueEDatas. */
    ParqueEDatas *novoParqueEDatas = (ParqueEDatas*)malloc(sizeof(ParqueEDatas));
    novoParqueEDatas->nomeParque = strdup(nomeParque);

    /* Cria os dados iniciais. */
    novoParqueEDatas->dataEntrada = dataEntrada;
    novoParqueEDatas->dataSaida = dataSaida;
    novoParqueEDatas->prev = NULL;
    novoParqueEDatas->next = NULL;

    /* Verifica se a lista de parques e datas está vazia. */
    if (matricula->parqueEdatas == NULL || 
        strcmp(nomeParque, matricula->parqueEdatas->nomeParque) < 0 ||
        (strcmp(nomeParque, matricula->parqueEdatas->nomeParque) == 0 
        && maisAntiga(&dataEntrada, &(matricula->parqueEdatas->dataEntrada)))){
        /* Insere o parque no início da lista. */
        inserirNoInicio(&(matricula->parqueEdatas), novoParqueEDatas);
        return;
    }

    /* Encontra a posição correta para inserir o novo parque. */
    ParqueEDatas *temporario = matricula->parqueEdatas;
    while (temporario->next != NULL && 
          (strcmp(nomeParque, temporario->next->nomeParque) > 0 || 
          (strcmp(nomeParque, temporario->next->nomeParque) == 0 
          && !maisAntiga(&dataEntrada, &(temporario->next->dataEntrada))))) {
        temporario = temporario->next;
    }
    /* Insere o novo parque na posição encontrada. */
    inserirDepois(temporario, novoParqueEDatas);

}

/**
 * Função para inserir um novo nó no início da lista.
 * PARAMETRO: head O ponteiro para o ponteiro para o início da lista.
 * PARAMETRO: novoParque O novo nó a ser inserido.
 */
void inserirNoInicio(ParqueEDatas **head, ParqueEDatas *novoParque) {
    novoParque->next = *head;
    if (*head != NULL) {
        (*head)->prev = novoParque;
    }
    *head = novoParque;
}

/**
 * Função para inserir um novo nó
 * PARAMETRO: prev O nó anterior ao novo nó a ser inserido.
 * PARAMETRO: novoParque O novo nó a ser inserido na lista.
 */
void inserirDepois(ParqueEDatas *prev, ParqueEDatas *novoParque) {
    novoParque->next = prev->next;
    if (prev->next != NULL) {
        prev->next->prev = novoParque;
    }
    prev->next = novoParque;
    novoParque->prev = prev;
}


/** Funções para tratar os comandos **/


/**
 * Função para tratar o comando p
 * PARAMETRO: head Ponteiro para o ponteiro da cabeça da lista ligada de 
   parques.
 */
void parques(Parque **head) {
    char *s;
    int fimLinha = leEspacos(), capacidade = 0;
    float valor15 = 0.0 , valor15apos1hora = 0.0 , valorMax = 0.0;
    Parque *aux;
    int quantidadeParques = contaParques(*head);

    if (fimLinha) {
        mostraParques(head);
        return;
    }
    
    s = leNome();
    aux = encontraParque(head, s);
    
    if (!fimLinha) {
        if (aux != NULL) {
            printf("%s: parking already exists.\n", s);
            free(s);
            return;
    }
    if (quantidadeParques >= MAX_PARQUES) {
        printf("too many parks.\n");
    }
    else {
        scanf("%d%f%f%f", &capacidade, &valor15, &valor15apos1hora, &valorMax);
        if (!verificaParametros(capacidade, valor15, valor15apos1hora, valorMax)) {
            free(s);
            return;
    }
        criaParque(head, s, capacidade, valor15, valor15apos1hora, valorMax);
    }
    }
    free(s);   
}

/**
 * Cria parque e adiciona o novo parque à lista ligada.
 * PARAMETRO: head Ponteiro para o ponteiro da cabeça da lista ligada de parques.
 * PARAMETRO: nomeParque O nome do novo parque a ser criado.
 * PARAMETRO: capacidade A capacidade do novo parque a ser criado.
 * PARAMETRO: valor_15 O valor X do novo parque a ser criado.
 * PARAMETRO: valor_15_apos_1hora O valor Y do novo parque a ser criado.
 * PARAMETRO: valor_MAX_diario O valor Z do novo parque a ser criado.
 */
void criaParque(Parque **head, char *nomeParque, int capacidade,
    float valor_15, float valor_15_apos_1hora, float valor_MAX_diario ) {
    /** Aloca espaço para o novo parque. */
    Parque *novoParque = (Parque *) malloc(sizeof(Parque));

    /** Aloca espaço para o nome do parque. */
    novoParque->nomeParque = (char *) malloc(sizeof(char) * (strlen(nomeParque) 
    + 1));
   
    /** Copia o nome do parque. */
    strcpy(novoParque->nomeParque, nomeParque);

    /** Define os valores iniciais. */
    novoParque->capacidade = capacidade;
    novoParque->valor_15 = valor_15;
    novoParque->valor_15_apos_1hora = valor_15_apos_1hora;
    novoParque->valor_MAX_diario = valor_MAX_diario;
    novoParque->lugares_disponiveis = capacidade;
    novoParque->dataFaturacao = NULL;

    novoParque->veiculos = NULL;
    novoParque->prev = NULL;
    novoParque->next = NULL;
    
    /** Adiciona o novo parque à lista. */
    inserirParque(head,novoParque);
}

/**
 * Insere um novo nó na lista ligada de Parques.
 * 
 * PARAMETRO: head Ponteiro para o ponteiro da lista ligada de parques.
 * PARAMETRO: novoParque O novo parque a ser inserido.
 */
void inserirParque(Parque **head, Parque *novoParque) {
    if (*head == NULL) {
        *head = novoParque;
    } else {
        Parque *temporario = *head;
        while (temporario->next != NULL) {
            temporario = temporario->next;
        }
        temporario->next = novoParque;
        novoParque->prev = temporario;
    }
}

/**
 * Encontra um parque específico na lista de parques.
 * PARAMETRO: head Ponteiro para o ponteiro da lista ligada de parques.
 * PARAMETRO: nomeParque O nome do parque a ser encontrado.
 * RETORNA: Um ponteiro para o parque encontrado, NULL caso não encontre nada.
 */
Parque* encontraParque(Parque **head, char *nomeParque) {
    Parque *atual = *head;
    while (atual != NULL) {
        if (strcmp(nomeParque, atual->nomeParque) == 0) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

/**
 * Conta o número de parques existentes na lista. 
 * PARAMETRO: head O ponteiro para o início da lista de parques.
 * RETORNA: O número de parques existentes na lista.
 */
int contaParques(Parque *head) {
    int count = 0;
    Parque *atual = head;

    while (atual != NULL) {
        count++;
        atual = atual->next;
    }
    return count;
}

/**
 * Verifica se os parâmetros o parque são válidos.
 * PARAMETRO: capacidade A capacidade do parque.
 * PARAMETRO: valor15 O valor X do parque.
 * PARAMETRO: valor15apos1 O valor Y do parque.
 * PARAMETRO: valorMAX O valor Z do parque.
 * RETORNA: TRUE caso se verifique, FALSE caso contrário.
 */
int verificaParametros(int capacidade, float valor15, float valor15apos1 ,
    float valorMAX) {
    
    if (capacidade <= 0) {
        printf("%d: invalid capacity.\n", capacidade);
        return 0;
    }
    else if (valor15 <= 0 || valor15apos1 <= 0 || valorMAX<= 0 || 
        valorMAX<valor15apos1 || valor15apos1<valor15) {
        
        printf("invalid cost.\n");
        return FALSE;
    }
    return TRUE;
}

/**
 * @brief Imprime informações do parque atual na lista.
 * PARAMETRO: parqueAtual O parque cujas informaçoes vão ser imprimidas.
 */
void parqueAtual(Parque *parqueAtual) {
    printf("%s %d", parqueAtual->nomeParque, parqueAtual->capacidade);
    int lugares = (parqueAtual->lugares_disponiveis);
    printf(" %d\n", lugares); // Adicionando nova linha no final
}

/**
 * Mostra todas as informações dos parques da lista.
 * PARAMETRO: head O ponteiro para o ponteiro da lista ligada de parques.
 */
void mostraParques(Parque **head) {
    Parque *atual;
    for (atual = *head; atual != NULL; atual = atual->next) {
        /* Chama a função parqueAtual para imprimir as informações respetivas.*/
        parqueAtual(atual);
    }
}



/**
 * Função para tratar o comando e
 * PARAMETRO: head Ponteiro para o ponteiro da lista ligada de parques.
 */
void entradaVeiculos(Parque **head) {
    char *s, *matricula; 
    Parque *encontraP;
    Veiculo *encontraV, *veiculoCorreto;
    Data dataEntrada;
    int fimLinha = leEspacos();

    s = leNome();
    saltaEspacos();
    matricula = leNome();
    encontraP = encontraParque(head, s);
    
    if (!fimLinha) {
        /* Verifica se o parque existe. */
        if (!verificarEntradaParque(encontraP, s, matricula)) {
            free(s);
            free(matricula);
            return;
        }

        /* Encontra se o veículo já está em algum parque.*/
        encontraV = encontraVeiculo(head, matricula);
        /* Encontra o veículo específico */
        veiculoCorreto = encontraVeiculoNoParque(encontraP, matricula);

        /* Se o veículo está num parque e não tem dataSaida significa 
        que ainda não saiu, logo não pode entrar. */
        if ((encontraV != NULL && encontraV->dataSaida == NULL) 
            || (veiculoCorreto != NULL && veiculoCorreto->dataSaida == NULL)) {
            printf("%s: invalid vehicle entry.\n", matricula);
            free(matricula);
            free(s);
            return;
        }  
    
        dataEntrada = leData();
        
        if(!verificaData(dataEntrada)) {
            printf("invalid date.\n");
            free(s);
            free(matricula);
            return;
        }
        /* Se o veículo está num parque mas tem data de saída pode entrar.
        DataSaida fica NULL e o número de lugares disponíveis diminui 1. */
        if ((veiculoCorreto != NULL && veiculoCorreto->dataSaida != NULL) ) {
            memcpy(veiculoCorreto->dataEntrada, &dataEntrada, sizeof(Data));
            veiculoCorreto->dataSaida = NULL;
            encontraP->lugares_disponiveis--;
            printf("%s %d\n", encontraP->nomeParque, 
            encontraP->lugares_disponiveis);
            free(s); 
            free(matricula);
            return;
    }
    /* Se o veiculo não está de todo em nenhum parque registamos 
    a sua entrada */
    registaEntradaVeiculo(encontraP, matricula, &dataEntrada);
    free(s);
    free(matricula); 
    }
}

/**
 * Verifica se é possível a entrada de um veículo no parque especificado.
 * PARAMETRO: parque O parque onde se pretende estacionar o veículo.
 * PARAMETRO: nomeParque O nome do parque.
 * PARAMETRO: matricula A matrícula do veículo.
 * RETORNA: TRUE se for possível a entrada do veículo no parque, FALSE 
   caso contrário.
 */
int verificarEntradaParque(Parque *parque, char *nomeParque, char *matricula) {
    if (parque == NULL) {
        printf("%s: no such parking.\n", nomeParque);
        return FALSE;
    }

    if (parque->lugares_disponiveis == 0) {
        printf("%s: parking is full.\n", nomeParque);
        return FALSE;
    }

    if (!verificaMatricula(matricula)) {
        printf("%s: invalid licence plate.\n", matricula);
        return FALSE;
    }

    return TRUE;
}

/**
 * Insere um novo veículo na lista ligada de veiculos de um parque.
 * PARAMETRO: parque O parque onde o veículo vai ser introduzido.
 * PARAMETRO: novoVeiculo O novo veículo a ser introduzido.
 */
void inserirVeiculoNoParque(Parque *parque, Veiculo *novoVeiculo) {
    if (parque->veiculos == NULL) {
        /* Se a lista de veículos do parque estiver vazia, insere o novo veículo. */
        parque->veiculos = novoVeiculo;
    } else {
        /* Caso contrário, percorre a lista de veículos até encontrar o último veículo */
        Veiculo *temporario = parque->veiculos;
        while (temporario->next != NULL) {
            temporario = temporario->next;
        }
        /* Adiciona o novo veículo após o último veículo na lista. */
        temporario->next = novoVeiculo;
        novoVeiculo->prev = temporario;
    }
}

/**
 * Encontra um veículo num parque específico. 
 * PARAMETRO: parque O parque onde se pretende encontrar o veículo.
 * PARAMETRO: matricula A matricula do veículo a ser encontrado.
 * RETORNA: Um ponteiro para o veículo encontrado, NULL caso não seja 
   encontrado.
 */
Veiculo* encontraVeiculoNoParque(Parque *parque, char *matricula) {
    Veiculo *atual = parque->veiculos;
    while (atual != NULL) {
        if (strcmp(matricula, atual->matricula) == 0) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

/**
 * Verifica se já existe um veiculo na lista de parques.
 * PARAMETRO: head Ponteiro para o ponteiro da lista ligada de parques.
 * PARAMETRO: matricula A matricula do veículo a ser encontrado.
 * RETORNA: Ponteiro para o veículo encontrado, NULL se o veículo não for 
   encontrado em nenhum parque.
 */
Veiculo* encontraVeiculo(Parque **head, char *matricula) {
    Parque *parqueAtual = *head;

    while (parqueAtual != NULL) {
        Veiculo *atual = parqueAtual->veiculos;
        while (atual != NULL) {
            if (strcmp(matricula, atual->matricula) == 0) {
                return atual;
            }
            atual = atual->next;
        }
        parqueAtual = parqueAtual->next;
    }
    return NULL;
}

/**
 * Cria e adiciona um novo veículo à lista ligada de veículos.
 * PARAMETRO: parque O parque onde o veículo vai ser introduzido.
 * PARAMETRO: matricula A matricula do veículo.
 * PARAMETRO: dataEntrada A data de entrada do veiculo.
 */
void criaVeiculo(Parque *parque, char *matricula, Data *dataEntrada ) {
    /* Aloca memória para o novo veículo */
    Veiculo *novoVeiculo = (Veiculo*) malloc (sizeof(Veiculo));

    /* Aloca memória e copia a informação da matrícula do veículo */
    novoVeiculo->matricula = (char *) malloc(sizeof(char) * (strlen(matricula) + 1));
    strcpy(novoVeiculo->matricula, matricula);

    /* Aloca memória e copia o nome do parque associado ao veículo */
    novoVeiculo->nomeParque = (char *) malloc(sizeof(char) * (strlen(parque->nomeParque) + 1)); // Aloca memória para o nome do parque
    strcpy(novoVeiculo->nomeParque, parque->nomeParque);

    /* Aloca memória para a data de entrada do veículo e copia os dados. */
    novoVeiculo->dataEntrada = (Data*) malloc(sizeof(Data));
    memcpy(novoVeiculo->dataEntrada, dataEntrada, sizeof(Data));

    /* Define a data de saida como NULL para indicar que o veículo está estacionado*/
    novoVeiculo->dataSaida = NULL;

    novoVeiculo->prev = NULL;
    novoVeiculo->next = NULL;
    
    inserirVeiculoNoParque(parque,novoVeiculo);
    parque->lugares_disponiveis--;
    }


/**
 * Regista a entrada de um veículo num parque. 
 * PARAMETRO: parque O parque onde o veículo vai ser introduzido.
 * PARAMETRO: matricula A matricula do veículo.
 * PARAMETRO: dataEntrada A data de entrada do veículo.
 */
void registaEntradaVeiculo(Parque *parque, char *matricula, Data *dataEntrada){
    if (!semData()) {
        Data dataTopo = topo->item;
        /* Verifica se a dataEntrada é válida e se é mais recente do que a data 
        do sistema. */
        if (verificaData(*dataEntrada) && maisAntiga(&dataTopo, dataEntrada)) {
            /* Dá push da dataEntrada para o sistema geral. */
            push(*dataEntrada);
            criaVeiculo(parque, matricula, dataEntrada); 
            printf("%s %d\n", parque->nomeParque, parque->lugares_disponiveis); 
            return;
        } else {
            printf("invalid date.\n"); 
            return;
        }
    } else {
        /* Se a pilha estiver vazia inicialmente, ele dá push logo. */
        push(*dataEntrada);
        criaVeiculo(parque, matricula, dataEntrada);
        printf("%s %d\n", parque->nomeParque, parque->lugares_disponiveis);
        return;
    }
}


/**
 * Função para tratar o comando s.
 * PARAMETRO: head Ponteiro para o ponteiro da lista ligada de parques.
 * PARAMETRO: hashTable Ponteiro para a hashtable.
 */
void comandoS(Parque **head, HashTable *hashTable) {
    char *s, *matricula, *nomeParque;
    Parque *encontraP;
    Veiculo *encontraV, *veiculoqueQUERO;
    Data dataSaida, *dataEntrada;
    int fimLinha=leEspacos();

    s=leNome();
    saltaEspacos();
    matricula = leNome();
    encontraP = encontraParque(head, s);

    if (!fimLinha) {
        if (encontraP == NULL) {
            printf("%s: no such parking.\n", s);
            free(s);
            free(matricula);
            return;
        }
        if (!verificaMatricula(matricula)) {
            printf("%s: invalid licence plate.\n",matricula);
            free(matricula);
            free(s);
            return;
            }
        /* Encontra o veículo na lista geral de veículos.*/
        encontraV = encontraVeiculo(head, matricula);
        /* Encontra o veículo no parque específico. */
        veiculoqueQUERO = encontraVeiculoNoParque(encontraP, matricula);
        /* Verifica se o veículo foi encontrado e se está no parque. 
        Imprime mensagem de erro caso não aconteça nenhuma das opções. */
        if (encontraV == NULL || veiculoqueQUERO == NULL ||
        (veiculoqueQUERO != NULL && veiculoqueQUERO->dataSaida != NULL)) {
            printf("%s: invalid vehicle exit.\n", matricula);
            free(s);
            free(matricula);
            return;
            }
            dataEntrada = veiculoqueQUERO->dataEntrada;
            dataSaida = leData();
            nomeParque = encontraP->nomeParque;
            /** Regista a saída do veículo */
            dataGeralnaSaida(encontraP, veiculoqueQUERO, dataEntrada, 
            &dataSaida);
            /** Procura pela matrícula do veículo na hashTable*/
            MatriculaCarro *encontraNaHash = findItem(hashTable, matricula);
            /** Se não encontrar , insere a matricula na hashTable. */
            if (encontraNaHash == NULL) {
                MatriculaCarro *novaMatricula = criarMatriculaCarro(matricula, 
                nomeParque, *dataEntrada, dataSaida);
                insertItem(hashTable, matricula, novaMatricula);
            } else {
                /** Caso contrário, adiciona o parqueEdatas à entrada 
                existente.*/
                adicionarParqueEDatas(encontraNaHash,nomeParque,*dataEntrada,
                dataSaida);
            }
            free(s);
            free(matricula);
    } 
} 

/**
 * Calcula o valor a pagar pelos minutos estacionado. 
 * PARAMETRO: minutinhos O tempo estacionado em minutos.
 * PARAMETRO: valor15 O valor X do parque.
 * PARAMETRO: valor15APOS1 O valor Y do parque.
 * PARAMETRO: diario O valor Z do parque.
 * RETORNA: O valor a ser pago pelo tempo estacionado.
 */
float valorPago(int minutinhos, float valor15, float valor15APOS1, float diario) {
    float blocosde24 = minutinhos / MINUTOSDIA;
    float blocosde15 = (minutinhos % MINUTOSDIA) / BLOCOS15;
    float restantes = (minutinhos % MINUTOSDIA) % BLOCOS15;
    float valorPago = 0;

    if (blocosde15 >= 4) {
        if (restantes > 0) {
        valorPago += valor15APOS1;
        } 
        valorPago += 4 * valor15 + (blocosde15 - 4) * valor15APOS1;
    } 
    else {
        if (restantes > 0) {
            valorPago += valor15;
        }
        valorPago += valor15 * blocosde15;
        }

    if (valorPago>diario) {
        valorPago=diario;
    }
    valorPago += blocosde24 * diario;
    return valorPago;
}

/**
 * Regista a saída de um veículo. Define a sua data de saida
   e aumenta o número de lugares 1
 * PARÂMETRO parque O parque onde o veículo está estacionado.
 * PARAMETRO: veiculo O veículo que está a sair do parque.
 * PARAMETRO: dataSaida A data de saída do veículo.
 */
void introduzSaida(Parque *parque, Veiculo *veiculo, Data *dataSaida) {
    veiculo->dataSaida = dataSaida;
    parque->lugares_disponiveis++;
}


/**
 * Lida com todo o processo de saída de um veículo.
 * PARAMETRO: parque O parque onde o veiculo está estacionado.
 * PARAMETRO: veiculo O veículo que vai sair do parque.
 * PARAMETRO: dataE A data de entrada do veículo.
 * PARAMETRO: dataS A data de saida do veículo.
 */
void dataGeralnaSaida(Parque *parque, Veiculo *veiculo, Data *dataE, 
    Data *dataS) {
    /*Obtém os valores X,Y e Z do parque. */
    float valor15 = parque->valor_15;
    float valor15APOS1 = parque->valor_15_apos_1hora;
    float valorMAX = parque->valor_MAX_diario;

    if (!semData()) {
        Data dataTopo = topo->item;
        if (verificaData(*dataS) && maisAntiga(&dataTopo, dataS)) {
            float minutosEstacionado = acumulaMinutos(dataE,dataS);
            float valor = valorPago(minutosEstacionado,valor15,valor15APOS1,valorMAX);
            push(*dataS);
            introduzSaida(parque, veiculo, dataS);
            /* Acrescenta o valor faturado ao total da faturacao do parque 
            nesta data específica (data de saída). */
            acrescentaValorFaturado(parque,dataS,valor);
            /* Adiciona o veículo à lista ligada de veículos que já saíram,
            juntamente com o valor pago na saída. */
            listaVeiculosSaida(parque,veiculo,*dataS,valor);
            printf("%s ", veiculo->matricula);
            mostraData(dataE);
            printf(" ");
            mostraData(dataS);
            printf(" %.2f\n", valor); 
            return;
        }  
        else {
            printf("invalid date.\n"); 
            return;
        }
    } else {
        printf("invalid date.\n"); 
        return;
    }
}



/**
 * Função para tratar o comando v.
 * PARAMETRO: head O ponteiro para a lista de parques.
 * PARAMETRO: hashTable O ponteiro para a hashtable.
 */
void comandoV(Parque **head, HashTable *hashTable) {
    char *matricula;
    Veiculo *encontreiVeiculo;
    int fimLinha=leEspacos();

    matricula = leNome();
    encontreiVeiculo = encontraVeiculo(head,matricula);
    if (!fimLinha) {
        if (!(verificaMatricula(matricula))) {
            printf("%s: invalid licence plate.\n",matricula);
            free(matricula);
            return;
        }
        if (encontreiVeiculo == NULL) {
            printf("%s: no entries found in any parking.\n",matricula);
            free(matricula);
            return;
        }
    
    /* Obtém a lista ligada de parques e datas associadas à matrícula.*/
    veiculosSemDataSaida(head,hashTable);
    MatriculaCarro *veiculo = findItem(hashTable, matricula);
    mostraParquesEDatas(&(veiculo->parqueEdatas));
    free(matricula);
    }
}

/**
 * Imprime as informações de entrada ou entrada e saída.
 * PARAMETRO: parqueAtual O ponteiro para a estrutura parques e datas.
 */
void parqueEdatasAtual(ParqueEDatas *parqueAtual) {
    /* Verifica se a data de saída é inválida (o veículo ainda não saiu). */
    if (parqueAtual->dataSaida.ano == -1) {
        printf("%s ", parqueAtual->nomeParque);
        mostraData(&(parqueAtual->dataEntrada));
        printf("\n");
        return;
    } else {
        printf("%s ", parqueAtual->nomeParque);
        mostraData(&(parqueAtual->dataEntrada));
        printf(" ");
        mostraData(&(parqueAtual->dataSaida));
        printf("\n");
    }
}

/**
 * Percorre a lista ligada de parques e datas.
 * PARAMETRO: head O ponteiro para o ponteiro da lista ligada de parques e datas.
 */
void mostraParquesEDatas(ParqueEDatas **head) {
    ParqueEDatas *atual;
    for (atual = *head; atual != NULL; atual = atual->next) {
        parqueEdatasAtual(atual);
    }
}

/**
 * Verifica se já existe uma entrada repetida para o mesmo parque e data de 
   entrada.
 * PARAMETRO: veiculo O ponteiro para a estrutura MatriculaCarro. 
 * PARAMETRO: nomeParque O nome do parque a verificar se já tem data repetida.
 * PARAMETRO: dataEntrada A data de entrada a verificar se já tem entrada repetida.
 * RETORNA: TRUE caso encontre, FALSE caso contrário.
 */
int existeEntradaRepetida(MatriculaCarro *veiculo, char *nomeParque, Data dataEntrada) {
    ParqueEDatas *parqueEDatas = veiculo->parqueEdatas;
    while (parqueEDatas != NULL) {
        if (strcmp(parqueEDatas->nomeParque, nomeParque) == 0 &&
            parqueEDatas->dataEntrada.dia == dataEntrada.dia &&
            parqueEDatas->dataEntrada.mes == dataEntrada.mes &&
            parqueEDatas->dataEntrada.ano == dataEntrada.ano &&
            parqueEDatas->dataSaida.dia == -1 &&
            parqueEDatas->dataSaida.mes == -1 &&
            parqueEDatas->dataSaida.ano == -1) {
            return TRUE; /** Entrada repetida encontrada */
        }
        parqueEDatas = parqueEDatas->next;
    }
    return FALSE; 
}

/**
 * Verifica veículos estacionados sem data de saída e mete-os na hashTable.
 * PARAMETRO: head O ponteiro para o ponteiro da lista ligada de parques.
 * PARAMETRO: hashTable O ponteiro para a hashtable que guarda as matrículas.
 */
void veiculosSemDataSaida(Parque **head, HashTable *hashTable) {
    Parque *parqueAtual = *head;
    char *matricula, *nomeParque;
    Data *dataEntrada, dataSaidaInvalida = {-1,-1,-1,-1,-1};

    while (parqueAtual != NULL) {
        nomeParque = parqueAtual->nomeParque;
        Veiculo *veiculoAtual = parqueAtual->veiculos;
        
        while (veiculoAtual != NULL) {
            /* Verifica se o veículo ainda não saiu (Data de saida nula). */
            if (veiculoAtual->dataSaida == NULL) {
            dataEntrada = veiculoAtual->dataEntrada;
            matricula = veiculoAtual->matricula;
            /* Verifica se a matrícula está na hashTable */
            MatriculaCarro *veiculo = findItem(hashTable, matricula);
            if (veiculo==NULL) {
                MatriculaCarro *novaMatricula = criarMatriculaCarro(matricula, 
                nomeParque, *dataEntrada, dataSaidaInvalida);
                /* Cria uma nova entrada para a matrícula com a 
                data de saída inválida. */
                insertItem(hashTable, matricula, novaMatricula);
            } else {
                /* Verifica a existência de entradas repetidas. */
                if (!existeEntradaRepetida(veiculo, nomeParque, *dataEntrada)){
                    adicionarParqueEDatas(veiculo,nomeParque,*dataEntrada,
                    dataSaidaInvalida);
                }
                }
            }
            veiculoAtual = veiculoAtual->next;
        }
            parqueAtual = parqueAtual->next;
        }
}



/**
 * Função para tratar o comando f.
 * 
 * PARAMETRO: head O ponteiro para o ponteiro da lista ligada de parques.
 */
void comandoF(Parque **head) {
    char *nomeParque;
    Data dataF, dataTopo = topo->item;
    int fimLinha = leEspacos(), existeParametro;
    Parque *encontraP;

    nomeParque = leNome();
    encontraP = encontraParque(head, nomeParque);
    if (encontraP == NULL) {
        printf("%s: no such parking.\n", nomeParque);
        free(nomeParque);
        return;
    }

    if (!fimLinha) {
        existeParametro = temMaisInput();
        /** Verifica se existe um segundo parâmetro */
        if (existeParametro) {
            scanf("%d-%d-%d",&dataF.dia,&dataF.mes,&dataF.ano);
            dataF.hora = 0;
            dataF.minutos = 0;
            if (!verificaDiaMes(dataF) || (maisAntigaEspecial(&dataTopo, &dataF))) {
                printf("invalid date.\n");
                free(nomeParque);
                return;
            }
            percorrerVeiculosSaidaPorData(encontraP, &dataF);
            free(nomeParque);
        } else {
            mostrarValorFaturadoPorDataSaida(encontraP);
            free(nomeParque);
        }
    }
}

/**
 * Adiciona um novo veículo à lista de veículos de saída do parque.
 * PARAMETRO: parque O parque onde o veículo está estacionado.
 * PARAMETRO: veiculo O veículo que está a sair do parque.
 * PARAMETRO: dataSaida A data de saída do veículo.
 * PARAMETRO: valorPago O valor pago pelo estacionamento.
 */
void listaVeiculosSaida(Parque *parque, Veiculo *veiculo, Data dataSaida, 
float valorPago) {
    /* Aloca espaço para um novo veículo de saída */
    VeiculoSaida *novoveiculo = (VeiculoSaida*)malloc(sizeof(VeiculoSaida));

    /* Aloca espaço e copia a matrícula do veículo de saída. */
    novoveiculo->matriculaS = (char *)malloc(sizeof(char) * (strlen(veiculo->matricula) + 1));
    strcpy(novoveiculo->matriculaS, veiculo->matricula);

    novoveiculo->dataSaida = dataSaida;
    novoveiculo->valorPago = valorPago;
    novoveiculo->prev = NULL;
    novoveiculo->next = NULL;

    if (parque->dataFaturacao != NULL) {
        DataFaturacao *atual = parque->dataFaturacao;
        while (atual != NULL) {
        /* Verifica se a data de faturação atual corresponde à data de saída
        do veículo. */
        if (comparaDatas(atual->dataF, &dataSaida)) {
            if (atual->veiculoSaida == NULL) {
                atual->veiculoSaida = novoveiculo;
            } else {
                VeiculoSaida *temp = atual->veiculoSaida;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = novoveiculo;
                novoveiculo->prev = temp;
            }
        }
        atual = atual->next;
    }
    }
}

/**
 * Adiciona OU atualiza o valor de faturação de cada data de saida.
 * PARAMETRO: parque O parque onde ocorre a faturação.
 * PARAMETRO: dataF A data de saída do veículo.
 * PARAMETRO: valorF O valor faturado nessa data.
 */
void acrescentaValorFaturado(Parque *parque, Data *dataF, float valorF) {
    /* Inicia a verificação a partir do primeiro nó da lista ligada de datas 
    de faturação. */
    DataFaturacao *atual = parque->dataFaturacao;

    if (atual == NULL) {
        /* Aloca memória para uma nova data de faturação inicial. */
        DataFaturacao *novaData = (DataFaturacao*)malloc(sizeof(DataFaturacao));
        novaData->dataF = (Data*)malloc(sizeof(Data));
        memcpy(novaData->dataF, dataF, sizeof(Data)); // Aloca memória para a data

        /* Define os valores iniciais */
        novaData->valorFaturado = valorF;
        novaData->veiculoSaida = NULL;
        novaData->prev = NULL;
        novaData->next = NULL;
        parque->dataFaturacao = novaData; 
        return;
    }
    while (atual != NULL) {
        /* Atualiza o valor faturado na data correta se a encontrar. */
        if (atual->dataF->dia == dataF->dia &&
            atual->dataF->mes == dataF->mes &&
            atual->dataF->ano == dataF->ano) {
            
            atual->valorFaturado += valorF;
            return;
        }
        atual = atual->next;
    }

    /* Se não encontrar nenhuma data igual, cria uma nova. */
    /* Aloca memória para uma nova. */
    DataFaturacao *novaData = (DataFaturacao*)malloc(sizeof(DataFaturacao));
    novaData->dataF = (Data*)malloc(sizeof(Data)); 
    memcpy(novaData->dataF, dataF, sizeof(Data)); 

    novaData->valorFaturado = valorF;
    novaData->veiculoSaida = NULL;
    novaData->prev = NULL;
    novaData->next = NULL;

    if (parque->dataFaturacao == NULL) {
        parque->dataFaturacao = novaData;
    } 
    else {
        DataFaturacao *temporario = parque->dataFaturacao;
        while (temporario->next != NULL) {
            temporario = temporario->next;
        }
        temporario->next = novaData;
        novaData->prev = temporario;
    }
}

/**
 * Percorre a lista de veiculos saida de cada data de faturação e imprime as 
   suas informações.
 * PARAMETRO: parque O parque onde ocorre a faturação.
 * PARAMETRO: data A data cuja qual queremos ver os veículos e as suas datas de 
   saída.
 */
void percorrerVeiculosSaidaPorData(Parque *parque, Data *data) {
    DataFaturacao *dataAtual = parque->dataFaturacao;

    /** Encontra a data correspondente na lista de datas de faturação. */
    while (dataAtual != NULL) {
        if (comparaDatas(dataAtual->dataF, data)) {
            /** Quando encontra a data correta percorre a lista de veiculos
            e imprime as suas informações. */
            VeiculoSaida *veiculoSaidaAtual = dataAtual->veiculoSaida;
            while (veiculoSaidaAtual != NULL) {
            printf("%s ", veiculoSaidaAtual->matriculaS);
            printf("%02d:%02d ", veiculoSaidaAtual->dataSaida.hora, 
            veiculoSaidaAtual->dataSaida.minutos);
            printf("%.2f\n", veiculoSaidaAtual->valorPago);
            veiculoSaidaAtual = veiculoSaidaAtual->next;
        }
        }
        dataAtual = dataAtual->next;
    }

}

/**
 * Percorre a lista de datas de faturação e imprime as suas informações. 
 * PARAMETRO: parque O ponteiro para o parque cujo qual queremos ver as informações
   de faturação por data de saída.
 */
void mostrarValorFaturadoPorDataSaida(Parque *parque) {
    DataFaturacao *atual = parque->dataFaturacao;
    
    while (atual != NULL) {
            printf("%02d-%02d-%04d",atual->dataF->dia,atual->dataF->mes,
            atual->dataF->ano);
            printf(" ");
            printf("%.2f\n", atual->valorFaturado);
            atual = atual->next;
        }
    }

/**
 * Verifica se duas datas são iguais com base apenas no ano, mes e dia.
 * 
 * PARAMETRO: d1 Ponteiro para a primeira data.
 * PARAMETRO: d2 Ponteiro para a segunda data.
 * RETORNA: TRUE se a primeira data for mais antiga, FALSE caso contrário.
 */
int maisAntigaEspecial(Data *d1, Data *d2) {
    if (d1->ano < d2->ano) return TRUE;
    if (d1->ano > d2->ano) return FALSE;
    if (d1->mes < d2->mes) return TRUE;
    if (d1->mes > d2->mes) return FALSE;
    if (d1->dia < d2->dia) return TRUE;
    if (d1->dia > d2->dia) return FALSE;
    return FALSE; // Datas são iguais
}


/**
 * Função para tratar o comando r.
 * PARAMETRO: head Ponteiro para o ponteiro da cabeça da lista ligada de parques.
 * PARAMETRO: hashtable Ponteiro para a hashtable.
 */
void comandoR(Parque **head, HashTable *hashtable) {
    char *nomeParque;
    Parque *encontraP;
    int fimLinha=leEspacos();
    nomeParque=leNome();

    if (!fimLinha) {
        encontraP = encontraParque(head,nomeParque);
        if (encontraP == NULL) {
            printf("%s: no such parking.\n", nomeParque);
            free(nomeParque);
            return;
        }
        removeParquedaListaLigada(head,nomeParque);
        removerParquePorNome(hashtable,nomeParque);
        imprimeListaPorNome(*head);
        free(nomeParque);
    }
}

/**
 * Remove um parque da lista ligada de parques.  
 * PARAMETRO: head Ponteiro para o ponteiro da cabeça da lista ligada de parques.
 * PARAMETRO: nomeParque Nome do parque a ser removido.
 */
void removeParquedaListaLigada(Parque **head, char *nomeParque) {
    Parque *atual = *head;
    Parque *anterior = NULL;

    while (atual != NULL) {
        /* Verifica se o nome do parque atual é igual ao nome do parque a ser
        removido. */
        if (strcmp(nomeParque, atual->nomeParque) == 0) {
            /* Verifica se o nó a ser removido corresponde à cabeça da lista.*/
            if (anterior == NULL) { 
                /* Atualiza a cabeça para apontar para o próximo nó.*/
                *head = atual->next;
            } else {
                anterior->next = atual->next;
            }
            libertaVeiculos(atual);
            libertaDataFaturacao(atual);
            free(atual->nomeParque); 
            free(atual); 
            return; 
        }
        /* Atualiza os ponteiros para avançar na lista. */
        anterior = atual;
        atual = atual->next;
    }
}

/**
 * Ordena um array de strings com BubbleSort.
 * PARAMETRO: nomes Array de strings a ser ordenado.
 * PARAMETRO: count Número de elementos no array.
 */
void ordenaStrings(char **nomes, int count) {
    int trocou = TRUE; /* Flag */
    /* Loop até não existir mais trocas a fazer. */
    while (trocou) {
        trocou = FALSE;
        for (int i = 0; i < count - 1; i++) {
            /* Compara duas strings adjacentes fazendo a troca caso seja 
            necessário. */
            if (strcmp(nomes[i], nomes[i + 1]) > 0) {
                char *temp = nomes[i];
                nomes[i] = nomes[i + 1];
                nomes[i + 1] = temp;
                trocou = TRUE;
            }
        }
    }
}

/**
 * Imprime os nomes dos parques da lista por ordem alfabética. 
 * PARAMETRO: head Ponteiro para o início da lista de parques.
 */
void imprimeListaPorNome(Parque *head) {
    Parque *atual = head;
    int count = 0;

    /** Conta o número de nós na lista */
    while (atual != NULL) {
        count++;
        atual = atual->next;
    }

    /** Aloca memória para um array de strings. */
    char **nomes = (char **)malloc(count * sizeof(char *));

    /** Renicia o ponteiro para percorrer a lista de novo. */
    atual = head;
    int i = 0;

    /** Copia os nomes dos parques. */
    while (atual != NULL) {
        nomes[i] = atual->nomeParque;
        i++;
        atual = atual->next;
    }
    /** Ordena os nomes dos parques por ordem alfabética. */
    ordenaStrings(nomes, count);
    
    /** Imprime os nomes dos parques ordenados. */
    for (i = 0; i < count; i++) {
        printf("%s\n", nomes[i]);
    }
    free(nomes);
}

/**
 * Remove os parques pedidos da hashtable.
 * PARAMETRO: hashTable Ponteiro para a hashtable.
 * PARAMETRO: nomeParque Nome do parque a ser removido.
 */
void removerParquePorNome(HashTable *hashTable, char *nomeParque) {
    /* Percorre todos os indíces da hashtable. */
    for (int i = 0; i < hashTable->capacity; i++) {
        Link indice = hashTable->table[i];
        /* Percorre todos os nós dos indíces. */
        while (indice != NULL) {
            /* Ponteiro para a estrutura MatriculaCarro. */
            MatriculaCarro *matricula = indice->p;
            /* Ponteiro para a lista ligada de ParquesEData da matrícula.*/
            ParqueEDatas *parqueAtual = matricula->parqueEdatas;
            /* Percorre todos os parquesEdata. */
            while (parqueAtual != NULL) {
                ParqueEDatas *proximoParque = parqueAtual->next;
                if (strcmp(parqueAtual->nomeParque, nomeParque) == 0) {
                    /* Remove o parque */
                    if (parqueAtual->prev != NULL)
                        parqueAtual->prev->next = parqueAtual->next;
                    else
                        matricula->parqueEdatas = proximoParque;
                    if (parqueAtual->next != NULL)
                        parqueAtual->next->prev = parqueAtual->prev;
                    /* Liberta a memória alocada para o nome do parque e
                    a sua estrutura. */
                    free(parqueAtual->nomeParque);
                    free(parqueAtual);
                }
                parqueAtual = proximoParque;
            }
            indice = indice->next;
        }
    }
}


/** Funções para libertar toda a memória alocada no fim do programa. **/

/**
 * Liberta a memória alocada para todos os parques e para os seus veículos e 
   datas de faturação. 
 * PARAMETRO: head Ponteiro para o primeiro nó da lista ligada de parques.
 */
void libertaParques(Parque *head) {
    Parque *atual = head;
    while (atual != NULL) {
        Parque *proximo = atual->next;
        libertaVeiculos(atual); // Liberta os veículos do parque atual
        libertaDataFaturacao(atual);
        free(atual->nomeParque);
        free(atual);
        atual = proximo;
    }
}

/**
 * Liberta a memória alocada para todos os veículos.
 * PARAMETRO: parque Ponteiro para o parque cujos veículos vão ser libertados.
 */
void libertaVeiculos(Parque *parque) {
    Veiculo *atual = parque->veiculos;
    while (atual != NULL) {
        Veiculo *proximo = atual->next;
        free(atual->matricula);
        free(atual->nomeParque);
        free(atual->dataEntrada);
        free(atual);
        atual = proximo;
    }
}

/**
 * Liberta a memória alocada para todas as datas de faturação
   dentro de cada parque e para os seus veículos de saída.
 * PARAMETRO: parque Ponteiro para o parque cujas datas de faturação vão ser
   libertadas.
 */
void libertaDataFaturacao(Parque *parque) {
    DataFaturacao *atual = parque->dataFaturacao;
    while (atual != NULL) {
        DataFaturacao *proximo = atual->next;
        free(atual->dataF);
        libertaVeiculosSaida(atual->veiculoSaida);
        free(atual);
        atual = proximo;
    }
}

/**
 * Liberta a memória alocada para todos os veiculosSaida.
 * PARAMETRO: veiculoSaida 
 */
void libertaVeiculosSaida(VeiculoSaida *veiculoSaida) {
    VeiculoSaida *atual = veiculoSaida;
    while (atual != NULL) {
        VeiculoSaida *proximo = atual->next;
        free(atual->matriculaS);
        free(atual);
        atual=proximo;
    }
}


/* Função MAIN */
int main() {
    int c; Parque *head = NULL; HashTable hashTable;
    inicializaTable(&hashTable);
    do {
        c = getchar();
        switch(c) {
            case 'p':
                parques(&head);
                break;
            case 'e':
                entradaVeiculos(&head);
                break;
            case 's':
                comandoS(&head, &hashTable);
                break; 
            case 'v':
                comandoV(&head, &hashTable);
                break;
            case 'r':
                comandoR(&head, &hashTable);
                break;
            case 'f':
                comandoF(&head);
                break;
        case 'q':
            libertaParques(head); freeHashTable(&hashTable); libertaPilha();
            break;
            default:
            /* Ignorar linhas em branco */
            if (c == ' ' || c == '\t' || c == '\n') break;
        }
    } while (c != 'q');
    return 0;
}

