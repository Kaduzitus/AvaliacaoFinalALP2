#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX 50

int ID = 1; /// define o valor inicial do ID sendo 1

                            /// define a estrutura do livro
typedef struct Livro {
    int Id;
    char Titulo[MAX];
    char Autor[MAX];
    int Edicao;
    char Editora[MAX];
    int ano;
    int reserva; /// se o livro estiver reservado o valor ser� 1 e livre ser� 0
} Livro;

/// defini��o da estrutura da lista
typedef struct Elemento {
    Livro livro;
    struct Elemento *proximo;
} Elemento;

Elemento *listadelivros = NULL; /// Lista dos livros cadastrados

/// Prototipo das fun��es do menu da biblioteca.
void cadastrar();
void imprimir();
void excluir(int id);
void reservar(int id);
void liberar(int id);
void salvarEmArquivo();
void carregarDeArquivo();

int main() {
    int op, n;
    setlocale(LC_ALL, "Portuguese"); /// localizar a biblioteca com as regras de linguages da lingua portuguesa ( deixa o programa mais bonito sem os erros quando utiliza acentos )

    carregarDeArquivo();

    do { /// Menu com as op��es de escolha da biblioteca.

        printf("\nESCOLHA UMA OP��O:\n");
        printf("1 - Cadastrar Livro\n");
        printf("2 - Imprimir lista de livros\n");
        printf("3 - Excluir Livro\n");
        printf("4 - Reservar Livro\n");
        printf("5 - Liberar Livro\n");
        printf("0 - Sair\n");
        scanf("%d", &op);

        switch (op) {
            case 1:
                cadastrar();
                break;
            case 2:
                imprimir();
                break;
            case 3:
                printf("Digite o id do livro a ser exclu�do: ");
                scanf("%d", &n);
                excluir(n);
                break;
            case 4:
                printf("Digite o id do livro a ser reservado: ");
                scanf("%d", &n);
                reservar(n);
                break;
            case 5:
                printf("Digite o id do livro a ser liberado: ");
                scanf("%d", &n);
                liberar(n);
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Op��o inv�lida, digite um n�mero entre 0 e 5.\n"); /// caso digitem n�meros al�m de 0 a 5
        }
    } while (op != 0);

    salvarEmArquivo();

    return 0;
}
/// Fun��o que cadastra um livro novo

void cadastrar() {
    Elemento *newElemento = (Elemento *)malloc(sizeof(Elemento));

    if (newElemento == NULL) {
        printf("Erro ao alocar mem�ria.\n");
        exit(EXIT_FAILURE);
    }

    newElemento->proximo = listadelivros;
    listadelivros = newElemento;

    newElemento->livro.Id = ID++;  /// soma +1 ao ID de um novo livro
    printf("Digite o T�tulo do livro: ");
    scanf(" %[^\n]", newElemento->livro.Titulo);
    printf("Digite o Autor do livro: ");
    scanf(" %[^\n]", newElemento->livro.Autor);
    printf("Digite a Edi��o do livro: ");
    scanf("%d", &newElemento->livro.Edicao);
    printf("Digite a Editora do livro: ");
    scanf(" %[^\n]", newElemento->livro.Editora);
    printf("Digite o ano do livro: ");
    scanf("%d", &newElemento->livro.ano);

    newElemento->livro.reserva = 0;  /// Inicializa como n�o reservado
}
/// Fun��o para imprimir a lista de livros

void imprimir() {
    printf("\nLista de Livros:\n");

    Elemento *temp = listadelivros;

    while (temp != NULL) {
        Livro livro = temp->livro;

        printf("\nID: %d\n", livro.Id);
        printf("T�tulo: %s\n", livro.Titulo);
        printf("Autor: %s\n", livro.Autor);
        printf("Edi��o: %d\n", livro.Edicao);
        printf("Editora: %s\n", livro.Editora);
        printf("Ano: %d\n", livro.ano);

        if (livro.reserva == 1)
            printf("Livro Reservado.\n");
        else
            printf("Livro Liberado.\n");

        temp = temp->proximo;
    }
}
/// Fun��o para excluir um livro da lista

void excluir(int id) {
    Elemento *atual = listadelivros;
    Elemento *anterior = NULL;

    while (atual != NULL && atual->livro.Id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Livro n�o encontrado.\n");
        return;
    }

    if (anterior == NULL) {
        /// Remover o livro anterior
        listadelivros = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Livro exclu�do com sucesso.\n");
}
/// Fun��o que reserva um livro
void reservar(int id) {
    Elemento *temp = listadelivros;

    while (temp != NULL && temp->livro.Id != id) {
        temp = temp->proximo;
    }

    if (temp == NULL) {
        printf("Livro n�o encontrado.\n");
        return;
    }

    temp->livro.reserva = 1;
    printf("Livro reservado com sucesso.\n");
}
/// Fun��o que libera um livro que foi reservado
void liberar(int id) {
    Elemento *temp = listadelivros;

    while (temp != NULL && temp->livro.Id != id) {
        temp = temp->proximo;
    }

    if (temp == NULL) {
        printf("Livro n�o encontrado.\n");
        return;
    }

    temp->livro.reserva = 0;
    printf("Livro liberado com sucesso.\n");
}
/// Fun��o para salvar os dados em um arquivo TXT, para que a lista de livros fique salva ap�s o programa fechar

void salvarEmArquivo() {
    FILE *arquivo = fopen("livros.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(EXIT_FAILURE);
    }

    Elemento *temp = listadelivros;

    while (temp != NULL) {
        fprintf(arquivo, "%d\n%s\n%s\n%d\n%s\n%d\n%d\n",
                temp->livro.Id, temp->livro.Titulo, temp->livro.Autor,
                temp->livro.Edicao, temp->livro.Editora, temp->livro.ano,
                temp->livro.reserva);

        temp = temp->proximo;
    }

    fclose(arquivo);
}
/// Fun��o para que o arquivo TXT que tem a lista, seja aberto sempre que o programa seja inciado
void carregarDeArquivo() {
    FILE *arquivo = fopen("livros.txt", "r");

    if (arquivo == NULL) {
        printf("Arquivo de dados n�o encontrado. Iniciando com lista vazia.\n");
        return;
    }

    int maxID = 0;  /// Vari�vel para armazenar o maior ID existente

    while (1) {
        Elemento *newElemento = (Elemento *)malloc(sizeof(Elemento));

        if (newElemento == NULL) {
            printf("Erro ao alocar mem�ria.\n");
            exit(EXIT_FAILURE);
        }

        int result = fscanf(arquivo, "%d", &newElemento->livro.Id);
        if (result != 1) {
            free(newElemento);
            break;
        }

        if (newElemento->livro.Id > maxID) {
            maxID = newElemento->livro.Id;
        }

        fscanf(arquivo, " %[^\n]", newElemento->livro.Titulo);
        fscanf(arquivo, " %[^\n]", newElemento->livro.Autor);
        fscanf(arquivo, "%d", &newElemento->livro.Edicao);
        fscanf(arquivo, " %[^\n]", newElemento->livro.Editora);
        fscanf(arquivo, "%d", &newElemento->livro.ano);
        fscanf(arquivo, "%d", &newElemento->livro.reserva);

        newElemento->proximo = listadelivros;
        listadelivros = newElemento;
    }

    ID = maxID + 1;  /// Define o pr�ximo ID a ser usado

    fclose(arquivo);
}
