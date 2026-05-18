#include <stdio.h>
#include <stdlib.h>

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
        else if (actual == '+' || actual == '-' || actual == '*' || actual == '/' || actual == '^') {
            
            float b = 0.0; 
            if (pilaVacia(pilaNum) == 0) {
                b = *((float*)pilaNum->tope->dato);  
                pop(pilaNum);
            }

            float a = 0.0; 
            if (pilaVacia(pilaNum) == 0) {
                a = *((float*)pilaNum->tope->dato);  // bien
                pop(pilaNum); 
            }

            float res = 0.0; 
            
            switch (actual) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/':
                    if (b == 0.0) {
                        printf("Como vas a dividir entre 0??? :c.\n");
                        destruirPila(pilaNum);
                        return 0.0;
                    }
                    res = a / b;
                    break;
                case '^': 
                    res = 1;
                    for (int i = 0; i < (int)b; i++)
                        res *= a;
                    break;

            }

            push(pilaNum, &res, sizeof(float));
        }
    }

    float fin = 0.0;
    if (pilaVacia(pilaNum) == 0) {
        fin = *((float*)pilaNum->tope->dato);  
        pop(pilaNum);
    } else {
        printf("Error: expresion vacia o invalida.\n");
    }

    destruirPila(pilaNum);
    return fin;
}
