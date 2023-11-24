#ifndef CONTENIDOFAVORITO_H_INCLUDED
#define CONTENIDOFAVORITO_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int idFavorito;
    int idUsuario;
    int idContenido;

} stFavorito;

int leerArchivoContenidoFavorito(char nombreArchivo[], stFavorito contenidosFavoritos[], int validosContenidosFavoritos);
void cargarArchivoContenidoFavorito(char nombreArchivo[]);
void sacarContenidoFavorito(stFavorito favoritos[],int validosFavoritos,int idContenido,int idUsuario);
int insertarEnOrden(stFavorito favoritos[],int validosFavoritos, int idUsuario,int idContenido);


#endif // CONTENIDOFAVORITO_H_INCLUDED
