#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/cola.h"
 
Cola* crearCola() {
    Cola *c = (Cola *)malloc(sizeof(Cola));
    if (c == NULL) {
        printf("Error: sin memoria para crear cola.\n");
        return NULL;
    }
    c->frente = NULL;
    c->final = NULL;
    return c;
}

// Asigna memoria al puntero de la cola c
 
int colaVacia(Cola *c) {
    return c->frente == NULL;
}

// Revisa si el frente de la pila apunta a NULL
 
void enqueue(Cola *c, void *dato, size_t size) {
    NodoCola *nuevo = (NodoCola *)malloc(sizeof(NodoCola));
    if (nuevo == NULL) {
        printf("Error: sin memoria para enqueue.\n");
        return;
    }
    nuevo->dato = malloc(size);
    if (nuevo->dato == NULL) {
        printf("Error: sin memoria para dato en enqueue.\n");
        return;
    }
    memcpy(nuevo->dato, dato, size);
    nuevo->siguiente = NULL;
 
    if (colaVacia(c)) {
        c->frente = nuevo;
        c->final = nuevo;
    } else {
        c->final->siguiente = nuevo;
        c->final = nuevo;
    }
}
 
char dequeue(Cola *c) {
    if (colaVacia(c)) {
        printf("Error: dequeue en cola vacia.\n");
        return '\0';
    }
    NodoCola *temp = c->frente;
    c->frente = temp->siguiente;
    if (c->frente == NULL)
        c->final = NULL;
 
    char dato = *((char *)temp->dato);
    free(temp->dato);
    free(temp);
    return dato;
}
 
void imprimirCola(Cola *c) {
    NodoCola *actual = c->frente;
    while (actual != NULL) {
        printf("%c", *((char *)actual->dato));
        if (actual->siguiente != NULL)
            printf(" ");
        actual = actual->siguiente;
    }
    printf("\n");
}
 
void destruirCola(Cola *c) {
    while (!colaVacia(c)) {
        NodoCola *temp = c->frente;
        c->frente = temp->siguiente;
        free(temp->dato);
        free(temp);
    }
    free(c);
}
