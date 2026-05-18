#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/evaluator.h"
#include "../include/pila.h"
#include "../include/cola.h"

float obtenerValorVariable(
    Variable variables[],
    int total,
    char nombre
) {
    for (int i = 0; i < total; i++) {
        if (variables[i].nombre == nombre) {
            return variables[i].valor;
        }
    }
    printf("Error mi chav@ la variable '%c' no esta definida.\n", nombre);
    return 0.0;
}

float evaluarPostfija(
    Cola* postfija,
    Variable variables[],
    int totalVariables
) {
    Pila* pilaNum = crearPila();

    while (colaVacia(postfija) == 0) {
        char actual = dequeue(postfija);

        if ((actual >= 'a' && actual <= 'z') || (actual >= 'A' && actual <= 'Z')) {
            float valor = obtenerValorVariable(variables, totalVariables, actual);
            push(pilaNum, &valor, sizeof(float));
        } 
