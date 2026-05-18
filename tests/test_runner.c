/*
=========================================================
TEST RUNNER — PROYECTO INFIJA A POSTFIJA
=========================================================

Objetivos:
- Verificar implementación de pila
- Verificar implementación de cola
- Verificar precedencia
- Verificar conversión infija → postfija
- Verificar evaluación postfija
- Verificar manejo de paréntesis
- Verificar potencia
- Verificar expresiones complejas
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/pila.h"
#include "../include/cola.h"
#include "../include/parser.h"
#include "../include/evaluator.h"

#define EPSILON 0.0001

int total = 0;
int passed = 0;

/* ===================================================== */
/* ASSERTS */
/* ===================================================== */

void assertTrue(
    int condition,
    const char* test
) {

    total++;

    if (condition) {

        printf("[OK] %s\n", test);

        passed++;

    } else {

        printf("[ERROR] %s\n", test);
    }
}

void assertFloat(
    float obtained,
    float expected,
    const char* test
) {

    total++;

    if (fabs(obtained - expected) < EPSILON) {

        printf("[OK] %s\n", test);

        passed++;

    } else {

        printf("[ERROR] %s\n", test);

        printf("Esperado: %.2f\n", expected);
        printf("Obtenido: %.2f\n", obtained);
    }
}

void assertString(
    const char* obtained,
    const char* expected,
    const char* test
) {

    total++;

    if (strcmp(obtained, expected) == 0) {

        printf("[OK] %s\n", test);

        passed++;

    } else {

        printf("[ERROR] %s\n", test);

        printf("Esperado: %s\n", expected);
        printf("Obtenido: %s\n", obtained);
    }
}

/* ===================================================== */
/* UTILIDADES */
/* ===================================================== */

void colaToString(
    Cola* c,
    char* buffer
) {

    buffer[0] = '\0';

    NodoCola* actual = c->frente;

    while (actual != NULL) {

        char temp[4];

        sprintf(temp, "%c ", actual->dato);

        strcat(buffer, temp);

        actual = actual->siguiente;
    }

    int len = strlen(buffer);

    if (len > 0) {
        buffer[len - 1] = '\0';
    }
}

/* ===================================================== */
/* PRUEBAS PILA */
/* ===================================================== */

void testCrearPila() {

    Pila* p = crearPila();

    assertTrue(
        p != NULL,
        "Crear pila"
    );

    assertTrue(
        pilaVacia(p),
        "Pila inicialmente vacia"
    );

    destruirPila(p);
}

void testPushPop() {

    Pila* p = crearPila();

    push(p, 'a');
    push(p, 'b');

    char c1 = pop(p);
    char c2 = pop(p);

    assertTrue(
        c1 == 'b' && c2 == 'a',
        "Push y Pop"
    );

    destruirPila(p);
}

void testPeek() {

    Pila* p = crearPila();

    push(p, '+');

    assertTrue(
        peek(p) == '+',
        "Peek"
    );

    destruirPila(p);
}

/* ===================================================== */
/* PRUEBAS COLA */
/* ===================================================== */

void testCrearCola() {

    Cola* c = crearCola();

    assertTrue(
        c != NULL,
        "Crear cola"
    );

    assertTrue(
        colaVacia(c),
        "Cola inicialmente vacia"
    );

    destruirCola(c);
}

void testEnqueueDequeue() {

    Cola* c = crearCola();

    enqueue(c, 'a');
    enqueue(c, 'b');

    char c1 = dequeue(c);
    char c2 = dequeue(c);

    assertTrue(
        c1 == 'a' && c2 == 'b',
        "Enqueue y Dequeue"
    );

    destruirCola(c);
}

/* ===================================================== */
/* PRUEBAS PRECEDENCIA */
/* ===================================================== */

void testPrecedencia() {

    int ok =
        precedencia('^') > precedencia('*')
        &&
        precedencia('*') > precedencia('+');

    assertTrue(
        ok,
        "Precedencia de operadores"
    );
}

/* ===================================================== */
/* PRUEBAS CONVERSION */
/* ===================================================== */

void testConversionSimple() {

    Cola* c =
        infijaAPostfija("a+b");

    char buffer[256];

    colaToString(c, buffer);

    assertString(
        buffer,
        "a b +",
        "Conversion simple"
    );

    destruirCola(c);
}

void testPrecedenciaMultiplicacion() {

    Cola* c =
        infijaAPostfija("a+b*c");

    char buffer[256];

    colaToString(c, buffer);

    assertString(
        buffer,
        "a b c * +",
        "Precedencia multiplicacion"
    );

    destruirCola(c);
}

void testParentesis() {

    Cola* c =
        infijaAPostfija("(a+b)*c");

    char buffer[256];

    colaToString(c, buffer);

    assertString(
        buffer,
        "a b + c *",
        "Parentesis"
    );

    destruirCola(c);
}

void testExpresionCompleja() {

    Cola* c =
        infijaAPostfija("a+b*(c-d)/e");

    char buffer[256];

    colaToString(c, buffer);

    assertString(
        buffer,
        "a b c d - * e / +",
        "Expresion compleja"
    );

    destruirCola(c);
}

void testPotencia() {

    Cola* c =
        infijaAPostfija("a^b^c");

    char buffer[256];

    colaToString(c, buffer);

    assertString(
        buffer,
        "a b c ^ ^",
        "Potencia asociativa"
    );

    destruirCola(c);
}

/* ===================================================== */
/* PRUEBAS EVALUACION */
/* ===================================================== */

void testEvaluacionSimple() {

    Variable vars[2];

    vars[0].nombre = 'a';
    vars[0].valor = 5;

    vars[1].nombre = 'b';
    vars[1].valor = 3;

    Cola* c =
        infijaAPostfija("a+b");

    float res =
        evaluarPostfija(c, vars, 2);

    assertFloat(
        res,
        8,
        "Evaluacion simple"
    );

    destruirCola(c);
}

void testEvaluacionMultiplicacion() {

    Variable vars[3];

    vars[0].nombre = 'a';
    vars[0].valor = 2;

    vars[1].nombre = 'b';
    vars[1].valor = 3;

    vars[2].nombre = 'c';
    vars[2].valor = 4;

    Cola* c =
        infijaAPostfija("a+b*c");

    float res =
        evaluarPostfija(c, vars, 3);

    assertFloat(
        res,
        14,
        "Evaluacion multiplicacion"
    );

    destruirCola(c);
}

void testEvaluacionParentesis() {

    Variable vars[3];

    vars[0].nombre = 'a';
    vars[0].valor = 5;

    vars[1].nombre = 'b';
    vars[1].valor = 1;

    vars[2].nombre = 'c';
    vars[2].valor = 2;

    Cola* c =
        infijaAPostfija("(a+b)*c");

    float res =
        evaluarPostfija(c, vars, 3);

    assertFloat(
        res,
        12,
        "Evaluacion parentesis"
    );

    destruirCola(c);
}

void testEvaluacionPotencia() {

    Variable vars[3];

    vars[0].nombre = 'a';
    vars[0].valor = 2;

    vars[1].nombre = 'b';
    vars[1].valor = 3;

    vars[2].nombre = 'c';
    vars[2].valor = 2;

    Cola* c =
        infijaAPostfija("a^b^c");

    float res =
        evaluarPostfija(c, vars, 3);

    assertFloat(
        res,
        512,
        "Evaluacion potencia"
    );

    destruirCola(c);
}

void testEvaluacionCompleja() {

    Variable vars[5];

    vars[0].nombre = 'a';
    vars[0].valor = 10;

    vars[1].nombre = 'b';
    vars[1].valor = 2;

    vars[2].nombre = 'c';
    vars[2].valor = 8;

    vars[3].nombre = 'd';
    vars[3].valor = 4;

    vars[4].nombre = 'e';
    vars[4].valor = 2;

    Cola* c =
        infijaAPostfija("a+b*(c-d)/e");

    float res =
        evaluarPostfija(c, vars, 5);

    assertFloat(
        res,
        14,
        "Evaluacion compleja"
    );

    destruirCola(c);
}

/* ===================================================== */
/* PRUEBAS DE ARCHIVO */
/* ===================================================== */

void testLecturaArchivo() {

    Variable vars[MAX_VARIABLES];

    int totalVars;

    char expr[MAX_EXPR];

    cargarArchivo(
        "input/caso1.txt",
        vars,
        &totalVars,
        expr
    );

    int ok =
        totalVars == 3
        &&
        strcmp(expr, "(a+b)*c") == 0;

    assertTrue(
        ok,
        "Lectura de archivo"
    );
}

/* ===================================================== */
/* MAIN */
/* ===================================================== */

int main() {

    printf("====================================\n");
    printf("AUTOGRADING INFIJA A POSTFIJA\n");
    printf("====================================\n\n");

    testCrearPila();
    testPushPop();
    testPeek();

    testCrearCola();
    testEnqueueDequeue();

    testPrecedencia();

    testConversionSimple();
    testPrecedenciaMultiplicacion();
    testParentesis();
    testExpresionCompleja();
    testPotencia();

    testEvaluacionSimple();
    testEvaluacionMultiplicacion();
    testEvaluacionParentesis();
    testEvaluacionPotencia();
    testEvaluacionCompleja();

    testLecturaArchivo();

    printf("\n====================================\n");
    printf("RESULTADO FINAL\n");
    printf("====================================\n");

    printf(
        "Pruebas superadas: %d/%d\n",
        passed,
        total
    );

    if (passed != total) {
        return 1;
    }

    return 0;
}
