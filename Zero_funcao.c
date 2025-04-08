#include <stdio.h>
#include <math.h>


double bissecao(double a, double b, double lim, int* iteracoes);
double secante(double x0, double x1, double limite, int* iteracoes);
double funcao(double x);

int main() {
    // --- Parâmetros de entrada ---
    //Letra A
    //double a = 0, b = 1, lim = 1e-10;
    //Letra B
    //double a = 0, b = 1, lim = 1e-10;
    //Letra C
    double a = 23, b = 26, lim = 1e-10;


    double x0 = 0, x1 = 1;

    // --- Contadores de iteração ---
    int qnt_interacao_bissecao = 0;
    int qnt_interacao_secante = 0;

    // --- Método da Bisseção ---
    double raiz_bissecao = bissecao(a, b, lim, &qnt_interacao_bissecao);
    double resp_bissecao[2] = {raiz_bissecao, -raiz_bissecao};

    printf("--------Método da Bisseção--------\n");
    printf("Refinamento e critério de parada: 1e-10\n");
    printf("Erro: 1.0E-10\n");
    printf("X1 ou a: %.15f\n", resp_bissecao[0]);
    printf("X2 ou b: %.15f\n", resp_bissecao[1]);
    printf("Número de iterações: %d\n", qnt_interacao_bissecao);
    printf("Valor de x (raiz encontrada): %.15f\n", raiz_bissecao);
    printf("f(x): %.15f\n", funcao(raiz_bissecao));

    // --- Método da Secante ---
    double raiz_secante = secante(x0, x1, lim, &qnt_interacao_secante);
    double resp_secante[2] = {raiz_secante, -raiz_secante};

    printf("\n--------Método da Secante--------\n");
    printf("Erro: 1.0E-10\n");
    printf("Intervalo inicial: (%f , %f)\n", x0, x1);
    printf("Raiz 1: %.15f\n", resp_secante[0]);
    printf("Raiz 2: %.15f\n", resp_secante[1]);
    printf("Número de iterações: %d\n", qnt_interacao_secante);
    printf("Valor de x (raiz encontrada): %.15f\n", raiz_secante);
    printf("f(x): %.15f\n", funcao(raiz_secante));

    // --- Checagem de existência de raiz ---
    if (funcao(x0) * funcao(x1) >= 0) {
        printf("Não tem raiz real no intervalo inicial.\n");
    } else {
        printf("Tem raiz real <- **********\n");
    }

    return 0;
}

// --- Função alvo ---
double funcao(double x) {
    // return pow(x, 5) - 2 * pow(x, 4) - 9 * pow(x, 3) + 22 * pow(x, 2) + 4 * x - 24;
    // return sqrt(x) - cos(x);
    return (sqrt(x) - 5) * exp(-x);
}

// --- Implementação do método da bisseção ---
double bissecao(double a, double b, double lim, int* iteracoes) {
    double x0 = a, x1 = b, meio, modulo;
    *iteracoes = 0;

    do {
        meio = (a + b) / 2.0;

        if (funcao(meio) * funcao(a) < 0) {
            b = meio;
        } else {
            a = meio;
        }

        x0 = x1;
        x1 = meio;
        modulo = fabs(x1 - x0);
        (*iteracoes)++;
    } while (modulo > lim);

    return x1;
}

// --- Implementação do método da secante ---
double secante(double x0, double x1, double limite, int* iteracoes) {
    double x2, erro_absoluto;
    *iteracoes = 0;
    erro_absoluto = fabs(x1 - x0);

    do {
        double f0 = funcao(x0);
        double f1 = funcao(x1);

        if (fabs(f1 - f0) < 1e-14) {
            printf("Divisão por valor muito pequeno evitada.\n");
            return x1;
        }

        x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
        x0 = x1;
        x1 = x2;

        erro_absoluto = fabs(x1 - x0);
        (*iteracoes)++;
    } while (erro_absoluto > limite);

    return x2;
}
