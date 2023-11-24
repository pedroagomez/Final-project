#include "contenidoFavorito.h"

int leerArchivoContenidoFavorito(char nombreArchivo[], stFavorito contenidosFavoritos[], int validosContenidosFavoritos){

    FILE * archi = fopen(nombreArchivo,"rb");

    if (archi){
        while (fread(&contenidosFavoritos[validosContenidosFavoritos],sizeof(stFavorito),1,archi)){
            validosContenidosFavoritos++;
        }   ///[1,1,3] [2,1,4] [3,1,5] [4,2,6]
    }
    fclose(archi);
    return validosContenidosFavoritos;
}

void cargarArchivoContenidoFavorito(char nombreArchivo[]){

    FILE * archi = fopen(nombreArchivo,"wb");
    stFavorito aux;
    for (int i=0; i<3;i++){
        printf("Id usuario: ");
        scanf("%d",&aux.idUsuario);
        printf("Id contenido: ");
        scanf("%d",&aux.idContenido);
        aux.idFavorito = i+1;
        fwrite(&aux,sizeof(stFavorito),1,archi);
    }
    fclose(archi);
}



/*void sacarContenidoFavorito(stFavorito favoritos[],int validosFavoritos,int idContenido,int idUsuario){
    int i=0,flag=0;
    while(flag==0 && i<validosFavoritos){
        if(favoritos[i].idContenido == idContenido && favoritos[i].idUsuario==idUsuario){
            favoritos[i].idContenido = 0;
            flag = 1;
        }
        i++;
    }
}

int insertarEnOrden(stFavorito favoritos[],int validosFavoritos, int idUsuario,int idContenido){
    int i =validosFavoritos-1;

    while(i > 0 && idUsuario != favoritos[i].idUsuario && idContenido > favoritos[i].idContenido)
    {
        favoritos[i+1]=favoritos[i];
        favoritos[i+1].idFavorito=i+2;
        i--;
    }

    favoritos[i+1].idContenido = idContenido;
    favoritos[i+1].idUsuario = idUsuario;
    favoritos[i+1].idFavorito = i+1;
    validosFavoritos++;
    for (int i =0; i<validosFavoritos; i++){
        printf("\n------------------------------------------\n");
        printf("IdFavorito: %d\n",favoritos[i].idFavorito);
        printf("Idcontenido: %d\n",favoritos[i].idContenido);
        printf("IdUsuario: %d\n",favoritos[i].idUsuario);
    }

    return validosFavoritos;

}*/


/**
    leo archivo favoritos->cargo arreglo de fav->con esto creo la lista de los fav usuario

    cuando doy like guardo en favoritos

    caudno termino el programa escribo el archivo con las listas de mis usuarios!


    celda -> usuario
          -> lista * contenidos;
          -> mensajes * mensajes;

          al principio levanto los favoritos del archivo al arreglo

          al fial paso las listas de los usuario al archivo de fav

*/
