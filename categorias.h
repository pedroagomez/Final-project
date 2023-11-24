#ifndef CATEGORIAS_H_INCLUDED
#define CATEGORIAS_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
typedef struct{
    int idCategoria;
    char categoria[20];
} stCategorias;

void cargarCategorias();
void mostrarTodasCategorias(stCategorias categorias[], int validosCategorias);
void mostrarCategoria(stCategorias categorias[], int idCategoria);
int pasarCategoriasToArray(stCategorias categorias[]);
#endif // CATEGORIAS_H_INCLUDED
