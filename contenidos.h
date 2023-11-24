#ifndef CONTENIDOS_H_INCLUDED
#define CONTENIDOS_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "categorias.h"
#include "contenidoFavorito.h"

typedef struct {
   int idContenido;           // auto incremental
   char titulo[100];
   char descripcion[400];
   char categoria[30];
   int likes;
   int puntosPorCompartir;
   int activo;                // indica 1 o 0 si el contenido está activo
} stContenido;

typedef struct
{
    stContenido c;
    struct nodoListaContenido * sig;
} nodoListaContenido;

typedef struct
{
    stContenido c;
    struct nodoArbolContenido * izq;
    struct nodoArbolContenido * der;
} nodoArbolContenido ;

//void cargarArchivoContenido(char nombreArchivo[],stCategorias categorias[], int validosCategorias);
nodoArbolContenido* crearNodoArbol(stContenido nuevo);
nodoArbolContenido* insertarEnArbol(nodoArbolContenido* arbol, nodoArbolContenido* nuevo);
nodoArbolContenido * buscarContenidoPorId(nodoArbolContenido * arbol, int idContenido);
void mostrarContenidosPorCategorias(stContenido c, int categoriasUsuario[],int validosCat,stCategorias categorias[]);
void mostrarInOrden(nodoArbolContenido* arbol, int categoriasUsuario[],int validosCat, stCategorias categorias[]);
void mostrarPreOrden(nodoArbolContenido* arbol);
void mostrarPostOrden(nodoArbolContenido* arbol);
stContenido cargarContenido(stCategorias categorias[], int validosCategorias, nodoArbolContenido * arbol);
void deArbolToArchivo(nodoArbolContenido * arbol, char nombreArchivo[]);
void cargarArchivo(nodoArbolContenido * arbol, FILE * archi);
int contarCantidadPublicaciones(nodoArbolContenido * arbol);
void saltoDeLineaCada60Caracteres(const char* texto);
nodoArbolContenido * buscarContenidoPorTitulo(nodoArbolContenido* arbol, char tituloContenido[]);
void mostrarContenidoAdmin(stContenido contenido);
void mostrarInOrderAdmin (nodoArbolContenido * arbol);
nodoArbolContenido * subprogramaModificarContenidoAdmin(nodoArbolContenido * arbol);
nodoArbolContenido * borrarNodoArbol(nodoArbolContenido * arbol, int idContenido);
stContenido nodoMasIzq(nodoArbolContenido * arbol);
stContenido nodoMasDer(nodoArbolContenido * arbol);

void mostrarUncontenido(stContenido contenido);
///lista contenidos
nodoListaContenido * inicListaContenidos();
nodoListaContenido * crearNodoContenidoFavorito(stContenido contenido);
nodoListaContenido * agregarFinalLista(nodoListaContenido * lista,nodoListaContenido * nuevo);
void mostrarListaContenidoFavorito(nodoListaContenido * lista,int categoriasUsuario[], int validosCat, stCategorias categorias[]);
int dioLike(nodoListaContenido * lista,int idContenido);
int pasarListaToArchivo(nodoListaContenido * lista,FILE * archi,int cont,int idUsuario);
nodoListaContenido * actualizarListaFavoritosUsuario(nodoListaContenido * lista,nodoArbolContenido * arbol);


#endif // CONTENIDOS_H_INCLUDED
