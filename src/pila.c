#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/pila.h"

Pila* crearPila() {
    Pila *p = (Pila *)malloc(sizeof(Pila));
    if (p == NULL) {
        printf("Error: sin memoria para crear pila.\n");
        return NULL;
    }
    p->tope = NULL;
    return p;
}

// Se reserva memoria para el TDA "pila" y se verifica que no este vacia, si no lo esta, se asigna NULL al tope

int pilaVacia(Pila *p) {
    return p->tope == NULL;
}

void push(Pila *p, void *dato, size_t size) {
    NodoPila *nuevo = (NodoPila *)malloc(sizeof(NodoPila));
    if (nuevo == NULL) {
        printf("Error: sin memoria para push.\n");
        return;
    }
    nuevo->dato = malloc(size);
    if (nuevo->dato == NULL) {
        printf("Error: sin memoria para dato en push.\n");
        return;
    }
    memcpy(nuevo->dato, dato, size);
    nuevo->siguiente = p->tope;
    p->tope = nuevo;
}

// Ingresa un nuevo elemento en la cima de la pila

char pop(Pila *p) {
    if (pilaVacia(p)) {
        printf("Error: pop en pila vacia.\n");
        return '\0';
    }
    NodoPila *temp = p->tope;
    p->tope = temp->siguiente;
    char dato = *((char *)temp->dato);
    free(temp->dato);
    free(temp);
    return dato;
}

char peek(Pila *p) {
    if (pilaVacia(p)) return '\0';
    return *((char *)p->tope->dato);
}
 
void destruirPila(Pila *p) {
    while (!pilaVacia(p)) {
        NodoPila *temp = p->tope;
        p->tope = temp->siguiente;
        free(temp->dato);
        free(temp);
    }
    free(p);
}
