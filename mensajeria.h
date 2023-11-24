#ifndef MENSAJERIA_H_INCLUDED
#define MENSAJERIA_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>

typedef struct {
   int idUsuarioEmisor;
   int idUsuarioReceptor;
   int idContenidoEnviado;
   char mensaje[300];
   int leido;                      // 1:si 0:no
} stMensajeria;

/** nodo mensaje
    stmensajeria;
    nodoMensaje * siguiente;
*/

typedef struct
{
    stMensajeria mensaje;
    struct nodoMensaje* siguiente;
}nodoMensaje;


int leerMensajeArchivo(char nombreArchivo[],stMensajeria arreglo[],int validos);
void cargarArchivoMensaje(char nombreArchivo[]);
void mostrarMensaje(stMensajeria mensaje,char nombreEmisor[]);
stMensajeria crearMensaje(int idReceptor, int idEmisor, int idContenido);
void pasarListaMensajeToArchivo(nodoMensaje * lista, FILE * archi);
int contarMensajesNoLeidos(nodoMensaje * lista);

#endif // MENSAJERIA_H_INCLUDED
