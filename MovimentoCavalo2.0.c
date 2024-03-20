/// CAVALO DE EULER
#include<stdio.h>
#define MAX 20
#include <locale.h> /// poder usar o set locale na função main

/// Função para imprimir o tabuleiro
void imprimir(int n, int M[MAX][MAX])
{
    int x, y;
    for (x = 0; x < n; x++) {
        for (y = 0; y < n; y++)
            printf(" %3d ", M[x][y]);
        printf("\n");
    }
}

/// Função recursiva para o passeio do cavalo
int passeio(int n, int x, int y, int pos, int M[MAX][MAX], int xMove[], int yMove[])
{
    int k, nextX, nextY;

    if (pos == n * n) return 1;    /// Se todas as posições foram preenchidas, retorna 1 (sucesso)

    /// Tenta todos os movimentos possíveis
    for (k = 0; k < 8; k++) {
        nextX = x + xMove[k];
        nextY = y + yMove[k];

        /// Verifica se o próximo movimento é válido
        if ((nextX >= 0) && (nextX < n) && (nextY >= 0) && (nextY < n) &&
            (M[nextX][nextY] == 0)) {
            M[nextX][nextY] = pos + 1;

            /// Chama recursivamente para o próximo movimento até encontrar um caminho ( ou não)
            if (passeio(n, nextX, nextY, pos + 1, M, xMove, yMove))
                return 1; /// Se encontrou um caminho, retorna 1 (sucesso)
            else
                M[nextX][nextY] = 0; /// Se não, desfaz o movimento
        }
    }
    return 0; /// Retorna 0 se nenhum caminho foi encontrado
}


int main()
{
    setlocale(LC_ALL, "Portuguese"); /// Definir a linguagem como portuguesa, e usar as regras e assentuação da lingua portuguesa ( ESTÉTICA kkkkk )

    int M[MAX][MAX], x, y, n, inicioX, inicioY;

    /// Movimentos possíveis do cavalo
    int xMove[8] = {2, 1, -1, -2, -2, -1,  1,  2};
    int yMove[8] = {1, 2,  2,  1, -1, -2, -2, -1};

    /// Solicita ao usuário o tamanho do tabuleiro, linha e coluna iniciais.

    printf("Informe o tamanho do tabuleiro desejado: ");/// como as possibilidades de movimento do cavalo sempre as mesma, o tamanho do tábuleiro pode ser qualquer um.
                                                            /// na teoria, pq quando coloco um tabuleiro maior que 8, o codigo não dá certo kkkkk.... mas com valores menores, sim.
                                                            /// Provavelmente o erro é nos movimentos possiveis do cavalo.
    scanf("%d", &n);
    printf("Informe a linha inicial desejada: ");
    scanf("%d", &inicioX);
    printf("Informe a coluna desejada: ");
    scanf("%d", &inicioY);

    /// Inicializa o tabuleiro com zeros
    for(x = 0; x < n; x++)
        for (y = 0; y < n; y++)
            M[x][y] = 0;

   /// Marca a posição inicial no tabuleiro
    M[inicioX - 1][inicioY - 1] = 1;

    /// Chama a função de passeio do cavalo e exibe o resultado
    if (passeio(n, inicioX - 1, inicioY - 1, 1, M, xMove, yMove) == 0)
        printf("Não é uma fórmula válida.\n");
    else
        imprimir(n, M);

    return 0;
}
