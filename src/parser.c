#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"
#include "../include/pila.h"
#include "../include/cola.h"

void cargarArchivo(
    const char* nombreArchivo,
    Variable variables[],
    int* totalVariables,
    char expresion[]
) {
    FILE *arch = fopen(nombreArchivo, "r");
    if (arch == NULL) {
        printf("yo creo que no se va a poder %s.\n", nombreArchivo);
        return;
    }

    char linea[MAX_EXPR];
    *totalVariables = 0;

    while (fgets(linea, sizeof(linea), arch) != NULL) {
        int longitud = strlen(linea);
        if (longitud > 0 && linea[longitud - 1] == '\n') {
            linea[longitud - 1] = '\0';
        }

        if (strlen(linea) == 0) continue;
        
        int igual = 0;
        for (int i = 0; i < strlen(linea); i++) {
            if (linea[i] == '=') {
                igual = 1;
                break;
            }
        }

        if (igual == 1) {
            char *nombre = strtok(linea, " =");
            char *numtext = strtok(NULL, " =");

            variables[*totalVariables].nombre = nombre[0];
            variables[*totalVariables].valor = atof(numtext);
            *totalVariables = *totalVariables + 1;
        } else {
            strcpy(expresion, linea);
        }
    }

    fclose(arch);
}

int esOperador(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        return 1;
    }
    return 0;
}

int precedencia(char op) {
    if (op == '^') {
        return 3;
    } else if (op == '*' || op == '/') {
        return 2;
    } else if (op == '+' || op == '-') {
        return 1;
    }
    return 0; 
}

Cola* infijaAPostfija(char* expresion) {
    Cola *postfija = crearCola();
    Pila *pila = crearPila();

    int longitud = strlen(expresion);

    for (int i = 0; i < longitud; i++) {
        char actual = expresion[i];

        if (actual == ' ') {
            continue;
        }

        if ((actual >= 'a' && actual <= 'z') || (actual >= 'A' && actual <= 'Z')) {
            enqueue(postfija, &actual, sizeof(char));
        } 
        else if (actual == '(') {
            push(pila, &actual, sizeof(char));
        } 
        else if (actual == ')') {
            while (pilaVacia(pila) == 0 && peek(pila) != '(') {
                char op = pop(pila);
                enqueue(postfija, &op, sizeof(char));
            }
            if (pilaVacia(pila) == 0) {
                pop(pila); 
            }
        } 
        else if (esOperador(actual) == 1) {
            while (pilaVacia(pila) == 0 && peek(pila) != '(') {
                char tope = peek(pila);
                int ant = precedencia(actual);
                int precTope = precedencia(tope);
                
                int sacar = 0;
                
                if (actual != '^' && precTope >= ant) {
                    sacar = 1;
                } else if (actual == '^' && precTope > ant) {
                    sacar = 1;
                }

                if (sacar == 1) {
                    char op = pop(pila);
                    enqueue(postfija, &op, sizeof(char));
                } else {
                    break; 
                }
            }
            push(pila, &actual, sizeof(char));
        }
    }

    while (pilaVacia(pila) == 0) {
        char op = pop(pila);
        enqueue(postfija, &op, sizeof(char));
    }

    destruirPila(pila);
    return postfija;
}