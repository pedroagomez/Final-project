#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include "categorias.h"
#include "contenidos.h"
#include "contenidoFavorito.h"
#include "mensajeria.h"
#include "estilos.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
    int idUsuario;                 // auto incremental
    char nombre[30];
    char apellido[30];
    char userName[20];
    char password[20];
    char mail[30];
    char genero;
    int puntaje;
    int nivel;
    int cat[20];
    int validosCat;
    int rol;                     // 1: es admin - 0: es comun
    int activo;                 // indica 1 o 0 si el usuario está activo
} stUsuario;

typedef struct
{
    stUsuario usuario;
    nodoListaContenido * listaDeContenidosFavoritos;
    nodoMensaje* mensajesLista;
    //nodolista mensajes
} stCelda;


///FUNCIONES DE ARREGLO DE USUARIO!!
int buscarPosicionCelda(stCelda arreglo[],int validos,int idUsuario);
int agregarUsuario(stCelda arreglo[],int validos,int dim, stUsuario nuevo);
int alta(stCelda arreglo[],int validos,int dim,stUsuario usuario);
int menuIniciarSesion(stCelda arreglo[], int validosCelda);
int deArchivoToADL(stCelda arreglo[],int validos,int dim, char nombreArchivo[],nodoArbolContenido * arbol,stFavorito favoritos[],int validosFavoritos);
void subprogramaBuscarUsuarioPorId(stCelda arregloUsuario[],int validosUsuarios,stCategorias categorias[]);

///FUNCIONES USUARIO ALTA,BAJA,MODIFICACION DE DATOS
int validacionMail(char mail[]);
void modificarPerfilUsuario(stCelda arreglo[],int validosCelda, int pos);
int logear(stCelda arreglo[],int validos, char nombreUsuario[], char password[]);
int validarPassword(char contrasenia[]);
int verificarExistenciaMail(stCelda arreglo[],int validosCelda, char mail[]);
int verificarExistenciaUsuario(stCelda arreglo[],int validosCelda, char userName[]);
int buscarUsuarioPorNombre(stCelda arreglo[], int validosCelda,char nombre[]);
stUsuario modificarContrasenia(stUsuario usuario);
stUsuario carga(stCategorias categorias[], int validosCategorias,stCelda arreglo[],int validosCelda);
void mostrarUsuario(stUsuario usuario, stCategorias categorias[]);
void mostrarTodosUsuario(stCelda arregloUsuarios[],int validosUsuario,stCategorias categorias[], int validosCategorias);
void mostrarUsuarioAdmin(stUsuario usuario, stCategorias categorias[]);
void darmeBajaUsuario(stCelda arreglo[],int pos);
void cargarListasFavoritos(stCelda arregloUsuarios[],int validosCelda,nodoArbolContenido * arbol,stFavorito favoritos[],int validosFavoritos);
void subprogramaBuscarContenido(nodoArbolContenido ** arbol,stCelda arregloUsuario[],int pos,int validosUsuario);
void deListaFavoritosToArchivo(stCelda arregloUsuarios[],int validosUsuarios,char nombreArchivo[]);
void cargarListaMensajes(stCelda arregloUsuario[],int validosUsuario,stMensajeria arregloMensajes[], int validosMensajes);
void sumarPuntosPorCrearContenido(stCelda arregloUsuarios[],int pos);
void actualizarListaFavoritos(stCelda arregloUsuarios[],int validosUsusarios,nodoArbolContenido * arbol);




void mostrarMensajeActualizo(stCelda arregloUsuario[], int validosUsuarios,int pos,nodoArbolContenido* arbol);
void mostrarMensajesLeidos(stCelda arregloUsuario[],int pos,int validosUsuarios,nodoArbolContenido* arbol);
void mostrarMensajesNoLeidos(stCelda arregloUsuario[],int pos, int validosUsuarios, nodoArbolContenido* arbol);
void deListaMensajeToArchivo(stCelda arregloUsuarios[],int validosUsuarios,char nombreArchivo[]);
//int pesoArchivo(char nombreArchivo[], char structura[]);

#endif // USUARIO_H_INCLUDED
