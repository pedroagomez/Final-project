#include "mensajeria.h"



stMensajeria crearMensaje(int idReceptor, int idEmisor, int idContenido)
{
    stMensajeria mensaje;
    mensaje.idUsuarioReceptor=idReceptor;
    mensaje.idUsuarioEmisor=idEmisor;
    mensaje.idContenidoEnviado=idContenido;


    printf("\t\t\t\nEscriba el mensaje: ");
    fflush(stdin);
    gets(mensaje.mensaje);

    mensaje.leido=0;

    return mensaje;
}


void mostrarMensaje(stMensajeria mensaje,char nombreEmisor[])
{
    printf("\n\n\t\tMensaje de :%s\n",nombreEmisor);
    printf("\t\tMensaje:%s\n",mensaje.mensaje);

}

int leerMensajeArchivo(char nombreArchivo[],stMensajeria arreglo[],int validos)
{
    stMensajeria aux;
    FILE* archi=fopen(nombreArchivo,"rb");
    if(archi)
    {
        while(fread(&arreglo[validos],sizeof(stMensajeria),1,archi)>0)
        {
            validos++;
        }
        fclose(archi);
    }
    return validos;
}

nodoMensaje* inicListaMensaje()
{
    return NULL;
}

nodoMensaje* crearNodoMensaje(stMensajeria nuevo)
{
    nodoMensaje* lista=(nodoMensaje*)malloc(sizeof(nodoMensaje));
    lista->mensaje=nuevo;
    lista->siguiente=NULL;
    return lista;
}

nodoMensaje* agregarAlFinalMensaje(nodoMensaje* lista, nodoMensaje* nuevo)
{
    nodoMensaje* seguidora=lista;
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        while(seguidora->siguiente!=NULL)
        {
            seguidora=seguidora->siguiente;

        }
        seguidora->siguiente=nuevo;
    }

    return lista;
}


void pasarListaMensajeToArchivo(nodoMensaje * lista, FILE * archi)
{
    stMensajeria dato;
    while (lista){

        dato = lista->mensaje;
        fwrite(&dato,sizeof(stMensajeria),1,archi);
        lista = lista->siguiente;
    }

}

int contarMensajesNoLeidos(nodoMensaje * lista){

    int cont=0;

    while (lista){
        if (!lista->mensaje.leido)
            cont++;
        lista=lista->siguiente;
    }
    return cont;
}
