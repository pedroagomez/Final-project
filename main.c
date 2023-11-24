#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contenidoFavorito.h"
#include "contenidos.h"
#include "usuario.h"
#include "mensajeria.h"
#include "categorias.h"


int main()
{
    stCategorias categorias[10]; int validosCategorias=0, validosArregloUsuarios=0, usuarioLogueado, validosFavoritos=0;
    stCelda arregloUsuarios[25];
    stFavorito arregloFavoritos[50];
    char nombreArchivoUsuarios[20], nombreArchivoFavoritos[20], opcionMenuPrincipal,opcionMenuUsuario,opcionPerfilUsuario,opcionMenuContenido,opcionAdminUsuarios,opcionAdminContenido;
    strcpy(nombreArchivoUsuarios,"usuarios.bin");
    strcpy(nombreArchivoFavoritos,"favoritos.bin");


    ///PARA PROBAR LAS PUBLICACIONES
    stContenido arreglo[50];
    nodoArbolContenido * arbol=inicArbol();
    char nombreArchivoContenido[20];
    strcpy(nombreArchivoContenido,"contenido.bin");
    int validos,i=0;


    ///levanta las categorias las cuales van a pasar a las funciones!
    //cargarCategorias();
    validosCategorias = pasarCategoriasToArray(categorias);
    ///MOSTRAR CATEGORIAS
    //mostrarTodasCategorias(categorias,validosCategorias);

    ///CARGA CONTENIDOS FAVORITOS
    //cargarArchivoContenidoFavorito(nombreArchivoFavoritos);

    ///LEVANTA LOS CONTENIDOS EN UN ARREGLO
    validos = deArchivoAarregloDeContenido(arreglo,50,nombreArchivoContenido);

    ///PASA LO DEL ARREGLO A UN ARBOL HACIENDOLO DE MANERA DE DIVISION DE ARREGLO
    arbol=arregloToArbolBalanceado(arreglo,0,validos-1,arbol);
    //mostrarPreOrden(arbol);
    //system("pause");

    ///MUESTRA LO QUE HAY EN EL ARBOL, SI O SI TIENE QUE ESTAR LOGUEADO EL USUARIO PARA USAR EL FILTRO DE CATEGORIAS
    //mostrarInOrden(arbol,arregloUsuarios[usuarioLogueado].usuario.cat,arregloUsuarios[usuarioLogueado].usuario.validosCat,categorias);


    ///LEVANTA LOS CONTENIDOS FAVORITOS EN EL SISTEMA
    validosFavoritos = leerArchivoContenidoFavorito(nombreArchivoFavoritos,arregloFavoritos,validosFavoritos);


    ///LEVANTA LOS USUARIO EN ARREGLO DE USUARIO
    validosArregloUsuarios = deArchivoToADL(arregloUsuarios,validosArregloUsuarios,50,nombreArchivoUsuarios,arbol,arregloFavoritos,validosFavoritos);
    cargarListasFavoritos(arregloUsuarios,validosArregloUsuarios,arbol,arregloFavoritos,validosFavoritos);
    /*for (int i=0; i<validosArregloUsuarios; i++){
        mostrarUsuario(arregloUsuarios[i].usuario,categorias);
    }*/


    /*for (int i=0; i<validosFavoritos;i++){

        printf("Id usuario: %d\n",arregloFavoritos[i].idUsuario);
        printf("Id contenido: %d\n",arregloFavoritos[i].idContenido);
        printf("Id favorito: %d\n",arregloFavoritos[i].idFavorito);
    }*/
    //mostrarPreOrden(arbol);

    ///CARGA UN USUARIO
    //carga(categorias,validosCategorias,arregloUsuarios,validosCategorias);///para cargar usuario

    ///FUNCION LOGUEA UN USUARIO Y MUESTRA EL USUARIO
    //usuarioLogueado = menuIniciarSesion(arregloUsuarios,validosArregloUsuarios);
    //mostrarUsuario(arregloUsuarios[usuarioLogueado].usuario,categorias);
    //mostrarUsuario(arregloUsuarios[usuarioLogueado].usuario,categorias);

    //system("cls");

    ///CARGA EL ARREGLO DE USUARIOS
    //validosArregloUsuarios = alta(arregloUsuarios,validosArregloUsuarios,10,carga(categorias,validosCategorias,arregloUsuarios,validosArregloUsuarios));

    ///SOBREESCRIBE TODOS LOS CAMBIOS QUE HUBIERON EN LA SESION
    //deADLtoArchivo(arregloUsuarios,validosArregloUsuarios,nombreArchivoUsuarios);




    /*while (i<5){
        arbol = insertarEnArbol(arbol,crearNodoArbol(cargarContenido(categorias,validosCategorias,arbol)));
        i++;
    }*/
    ///SOLO PARA PRUEBA
    //mostrarUsuario(arregloUsuarios[usuarioLogueado].usuario,categorias);

    ///PERSISTE LOS CONTENIDOS EN EL ARCHIVO
    //deArbolToArchivo(arbol,nombreArchivoContenido);
    //mostrarPreOrden(arbol);
    //system("pause");

    ///PRUEBA
    //arregloUsuarios[0].usuario.rol=1;



    int validosMensajes=0;
    stMensajeria arregloMensajes[20];
    char nombreArchivoMensaje[20];
    strcpy(nombreArchivoMensaje,"mensaje.bin");
    validosMensajes=leerMensajeArchivo(nombreArchivoMensaje,arregloMensajes,validosMensajes);
    cargarListaMensajes(arregloUsuarios,validosArregloUsuarios,arregloMensajes,validosMensajes);

    //system("pause");

    do{
        system("cls");
        bienvenidoAlSistema();
        opcionMenuPrincipal = getch();
        switch (opcionMenuPrincipal){
        case '1':
            usuarioLogueado = menuIniciarSesion(arregloUsuarios,validosArregloUsuarios);
            if (usuarioLogueado!=-1 && !arregloUsuarios[usuarioLogueado].usuario.rol){
                actualizarListaFavoritos(arregloUsuarios,validosArregloUsuarios,arbol);
                do{
                    barra();
                    muroUsuario();
                    mostrarInOrden(arbol,arregloUsuarios[usuarioLogueado].usuario.cat,arregloUsuarios[usuarioLogueado].usuario.validosCat,categorias);
                    irArriba();
                    opcionMenuUsuario=getch();
                    switch(opcionMenuUsuario){
                    case '1':
                        do{
                            vistaPerfil();
                            mostrarUsuario(arregloUsuarios[usuarioLogueado].usuario,categorias);
                            irArriba();
                            opcionPerfilUsuario = getch();
                            switch(opcionPerfilUsuario){
                            ///CASO MODIFICAR PERFIL!
                            case '1':
                                modificarPerfilUsuario(arregloUsuarios,validosArregloUsuarios,usuarioLogueado);
                                break;
                            ///CASO DARME DE BAJA
                            case '3':
                                darmeBajaUsuario(arregloUsuarios,usuarioLogueado);
                                if (!arregloUsuarios[usuarioLogueado].usuario.activo){
                                    opcionPerfilUsuario='2';
                                    opcionMenuUsuario=27;
                                }
                                break;
                            default:
                                break;
                            }
                        }while(opcionPerfilUsuario!='2');
                        break;
                    case '2':
                        ///MENU DE CONTENIDOS
                        do{
                            vistaContenidoUsuario();
                            irArriba();
                            opcionMenuContenido=getch();
                            switch(opcionMenuContenido){
                            ///BUSCAR CONTENIDO
                            case '1':
                                    subprogramaBuscarContenido(&arbol,arregloUsuarios,usuarioLogueado,validosArregloUsuarios);
                                break;
                            ///MIS CONTENIDOS FAVORITOS
                            case '2':
                                system("cls");
                                mostrarListaContenidoFavorito(arregloUsuarios[usuarioLogueado].listaDeContenidosFavoritos,arregloUsuarios[usuarioLogueado].usuario.cat,arregloUsuarios[usuarioLogueado].usuario.validosCat,categorias);
                                printf("\t\t\t");
                                system("pause");
                                break;
                            ///CREAR CONTENIDO
                            case '3':
                                vistaCargarContenido();
                                arbol = insertarEnArbol(arbol,crearNodoArbol(cargarContenido(categorias,validosCategorias,arbol)));
                                sumarPuntosPorCrearContenido(arregloUsuarios,usuarioLogueado);
                                break;
                            default:
                                break;
                            }
                        }while(opcionMenuContenido!='4');

                        break;
                    ///MENU MENSAJES
                    case '3':
                            system("cls");
                            char opcionMenuMensajeUsuario;
                            do
                            {
                                menuMensajeUsuario(contarMensajesNoLeidos(arregloUsuarios[usuarioLogueado].mensajesLista));
                                opcionMenuMensajeUsuario=getch();
                                switch(opcionMenuMensajeUsuario)
                                {
                                case '1':
                                    mostrarMensajesNoLeidos(arregloUsuarios,usuarioLogueado,validosArregloUsuarios,arbol);
                                    break;
                                case '2':
                                    mostrarMensajesLeidos(arregloUsuarios,usuarioLogueado,validosArregloUsuarios,arbol);
                                    system("pause");
                                    break;
                                default:
                                    break;
                                }
                            }while(opcionMenuMensajeUsuario!='3');
                        break;
                    }
                }while(opcionMenuUsuario!=27);

            } else if (usuarioLogueado!=-1 && arregloUsuarios[usuarioLogueado].usuario.rol){
                    do{
                        barra();
                        muroAdmin();
                        opcionMenuUsuario=getch();
                        switch(opcionMenuUsuario){
                        case '1':
                            do{
                                vistaAdminUsuarios();
                                mostrarTodosUsuario(arregloUsuarios,validosArregloUsuarios,categorias,validosCategorias);
                                irArriba();
                                opcionAdminUsuarios = getch();
                                switch(opcionAdminUsuarios){
                                ///CASO BUSCAR USARIO POR ID!
                                case '1':
                                    system("cls");
                                    subprogramaBuscarUsuarioPorId(arregloUsuarios,validosArregloUsuarios,categorias);
                                break;
                            default:
                                break;
                            }
                        }while(opcionAdminUsuarios!='3');
                        break;
                    case '2':
                        ///MENU DE CONTENIDOS
                        do{
                            vistaContenidoAdmin();
                            mostrarInOrderAdmin(arbol);
                            irArriba();
                            opcionAdminContenido=getch();
                            switch(opcionAdminContenido){
                            ///BUSCAR CONTENIDO
                            case '1':
                                arbol = subprogramaModificarContenidoAdmin(arbol);

                            break;
                            default:
                                break;
                            }
                        }while(opcionAdminContenido!='3');

                        break;
                    }
                }while(opcionMenuUsuario!=27);
            }
            printf("\n\t\t\t\t\tSera redirigido al menu principal\n");
            Sleep(1000);
            break;
        case '2':
            registro();
            validosArregloUsuarios = alta(arregloUsuarios,validosArregloUsuarios,20,carga(categorias,validosCategorias,arregloUsuarios,validosArregloUsuarios));
            registroExitoso();
            break;
        }
    }while (opcionMenuPrincipal!=27);

    ///cuando termine de probar la linea de borrar nodo definitivamente desde vista admin
    ///ir a contenido.c -> linea 379 y comentarla!
    ///luego descomentar la linea 270 para que persista el arbol!
    deADLtoArchivo(arregloUsuarios,validosArregloUsuarios,nombreArchivoUsuarios);
    //deArbolToArchivo(arbol,nombreArchivoContenido);
    deListaFavoritosToArchivo(arregloUsuarios,validosArregloUsuarios,nombreArchivoFavoritos);
    deListaMensajeToArchivo(arregloUsuarios,validosArregloUsuarios,nombreArchivoMensaje);
    return 0;
}


/**MANEJO USUARIO, ENTRAR EL SISTEMA, MOSTRARLE LAS CATEGORIAS DE SU INTERES,
    PARTE DEL MENU: PERFIL  MENU CONTENIDO    MENSAJES

    PERFIL-> MODIFICACION DE DATOS YA ESTA EL SUBPROGRAMA, DARME DE BAJA.

    MENU CONTENIDO-> BUSCAR CONTENIDO, MIS FAVORITOS, CREAR CONTENIDO
    BUSCAR CONTENIDO->DAR LIKE  AGREGAR FAVORITOS
    .

    MENSAJES-> VER MENSAJES NO LEIDOS, VER MENSAJES LEIDOS
    SEA EL CASO MOSTRAR PUBLICACION



    ADMIN -> VER TODAS PUBLICACIONES, VER TODOS USUARIOS

    VER TODAS PUBLICACIONES->ALTA,BAJA.
    VER TODOS USUARIOS-> ALTA, BAJA


    favoritos.bin--> id->ususario
                     id->contenido

     celda[usua].listadefavoritos


     CUANDO SE AGREGA UN FAVORITO AL ARREGLO DE FAVORITOS EN MEMORIA
     HAY QUE UBICARLO POR INSERCION!



     BUSCACONTENIDO->BUSCA CONTENIDO AL ARBOL->MODIFICAR EL ARBOL

     ARBOL = BUSCARCONTENIDO(ARBOL.....);


     favoritos = [1,1,0] [2,1,3] [3,2,3] [4,2,4] [5,4,1]++;




    */



