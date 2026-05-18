#include <stdio.h>

#include "../include/parser.h"
#include "../include/evaluator.h"
#include "../include/cola.h"

int main() {

    Variable variables[MAX_VARIABLES];

    int totalVariables;

    char expresion[MAX_EXPR];

    cargarArchivo(
        "../input/caso1.txt",
        variables,
        &totalVariables,
        expresion
    );

    printf("Expresion infija:\n");
    printf("%s\n\n", expresion);

    Cola* postfija =
        infijaAPostfija(expresion);

    printf("Expresion postfija:\n");

    imprimirCola(postfija);

    float resultado =
        evaluarPostfija(
            postfija,
            variables,
            totalVariables
        );

    printf("\nResultado:\n");
    printf("%.2f\n", resultado);

    destruirCola(postfija);

    return 0;
}
