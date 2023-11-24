#include "categorias.h"
void cargarCategorias(){

    stCategorias categorias;
    FILE * archivo = fopen("categorias.bin","ab");
    if(archivo!=NULL)
    {
        for (int i=0; i<10; i++){
            ///ARREGLAR INTERES GENERAL
            printf("\nIngrese categoria: ");
            fflush(stdin);
            gets(categorias.categoria);
            categorias.idCategoria = i+1;
            fwrite(&categorias,sizeof (stCategorias),1,archivo);
        }
    }
    else
    {
        printf("Error en el servidor.\n");
    }
    fclose(archivo);
    //system("pause");
}

void mostrarTodasCategorias(stCategorias categorias[], int validosCategorias){

    printf("\n\t\t\t\t\tCATEGORIAS\n");
    for (int i=0; i<validosCategorias; i++){
        printf("\t\t\t\t\t[%d]",categorias[i].idCategoria);
        printf("%s\n", categorias[i].categoria);

    }
}

int pasarCategoriasToArray(stCategorias categorias[]){

    int validosCategorias=0;
    FILE * archivo = fopen("categorias.bin","rb");
    if(archivo != NULL)
    {
        while (fread(&categorias[validosCategorias],sizeof(stCategorias),1,archivo)>0){
            validosCategorias++;
        }
    }
    fclose(archivo);
    return validosCategorias;
}

void mostrarCategoria(stCategorias categorias[], int idCategoria){

    printf("%s\t",categorias[idCategoria-1].categoria);
}
