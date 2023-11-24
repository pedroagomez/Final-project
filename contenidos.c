#include "contenidos.h"


///FUNCIONES LISTA CONTENIDO
stContenido cargarContenido(stCategorias categorias[], int validosCategorias, nodoArbolContenido * arbol)///pasar el arbol de contenidos levantado para agregar los contenidos nuevos
{
    stContenido aux;
    aux.idContenido = 1 + contarCantidadPublicaciones(arbol);
    int flag=0, posCategoria;
    printf("\t\t\tTitulo : ");
    fflush(stdin);
    gets(aux.titulo);
    while (flag == 0)
    {
        printf("\t\t\tDescripcion: ");
        fflush(stdin);
        gets(aux.descripcion);

        if (strlen(aux.descripcion) > 400)
        {
            printf("\t\t\tUps, parece que te has pasado del límite de caracteres (%d). Vuelve a intentarlo: ", 400);
            flag=0;
        }
        else
        {
            flag = 1;
        }
    }
    printf("\t\t\tIngrese la categoria del contenido: ");
    mostrarTodasCategorias(categorias,validosCategorias);
    do{
        scanf("%d",&posCategoria);
    }while(posCategoria<0 && posCategoria<validosCategorias);
    strcpy(aux.categoria,categorias[posCategoria-1].categoria);
    aux.likes=rand()%100;
    aux.activo=1;
    aux.puntosPorCompartir=0;
    return aux;

}

void deArbolToArchivo(nodoArbolContenido * arbol, char nombreArchivo[]){

    FILE * archi = fopen(nombreArchivo,"wb");

    if (archi){
        cargarArchivo(arbol,archi);
    }
    fclose(archi);
}

void cargarArchivo(nodoArbolContenido * arbol, FILE * archi){
    if (arbol){
        cargarArchivo(arbol->izq,archi);
        fwrite(&arbol->c,sizeof(stContenido),1,archi);
        cargarArchivo(arbol->der,archi);
    }

}

int deArchivoAarregloDeContenido(stContenido arreglo[], int dim, char nombreArchivo[])
{
    stContenido aux;
    int i=0;
    FILE* archi=fopen(nombreArchivo,"rb");
    if(archi)
    {
        while(fread(&aux,sizeof(stContenido),1,archi)>0)
        {
            if(i<dim)
            {
                arreglo[i]=aux;
                i++;
            }
        }
    }
    return i;
}

nodoArbolContenido* arregloToArbolBalanceado(stContenido arreglo[], int inicio, int fin, nodoArbolContenido * arbol)   /// INICIO 0, FIN VALIDOS-1;
{
    if(inicio<=fin)
    {
        int posMedio = floor((inicio + fin) / 2);
        arbol = insertarEnArbol(arbol,crearNodoArbol(arreglo[posMedio]));
        arbol = arregloToArbolBalanceado(arreglo,inicio,posMedio-1,arbol);
        arbol = arregloToArbolBalanceado(arreglo,posMedio+1,fin,arbol);
    }

    return arbol;
}

nodoArbolContenido* inicArbol()
{
    return NULL;
}


nodoArbolContenido* crearNodoArbol(stContenido nuevo)
{
    nodoArbolContenido* arbol=(nodoArbolContenido*)malloc(sizeof(nodoArbolContenido));
    arbol->c=nuevo;
    arbol->izq=NULL;
    arbol->der=NULL;
    return arbol;
}

nodoArbolContenido* insertarEnArbol(nodoArbolContenido* arbol, nodoArbolContenido* nuevo)
{
    if(arbol==NULL)
    {
        arbol=nuevo;
    }
    else
    {
        if(nuevo->c.idContenido>arbol->c.idContenido)
        {
            arbol->der=insertarEnArbol(arbol->der,nuevo);
        }
        else
        {
            arbol->izq=insertarEnArbol(arbol->izq,nuevo);
        }
    }
    return arbol;
}

nodoArbolContenido * buscarContenidoPorId(nodoArbolContenido* arbol, int idContenido)
{
    nodoArbolContenido * aux = NULL;
    if(arbol)
    {
        if(arbol->c.idContenido == idContenido)
        {
            aux=arbol;
        }
        else
        {
            if(idContenido > arbol->c.idContenido)
            {
                aux=buscarContenidoPorId(arbol->der,idContenido);
            }
            else
            {
                aux=buscarContenidoPorId(arbol->izq,idContenido);
            }
        }
    }
    return aux;
}

nodoArbolContenido * buscarContenidoPorTitulo(nodoArbolContenido* arbol, char tituloContenido[])
{
    nodoArbolContenido * aux = NULL;
    if(arbol)
    {

        if(strstr(arbol->c.titulo,tituloContenido)!= NULL)
        {
            aux=arbol;
        }
        else
        {

                aux=buscarContenidoPorTitulo(arbol->izq,tituloContenido);
                if (!aux)
                    aux=buscarContenidoPorTitulo(arbol->der,tituloContenido);


        }
    }
    return aux;
}

void mostrarContenidosPorCategorias(stContenido c, int categoriasUsuario[],int validosCat,stCategorias categorias[])///SE CAMBIO QUE MUESTRE TANTO NODO ARBOL COMO NODOLISTA
{
    for (int i=0; i<validosCat; i++){
        if (strcmpi(categorias[categoriasUsuario[i]-1].categoria,c.categoria)==0 && c.activo){
            printf("\t\t=========================================================================================\n");
            printf("\t\t");
            saltoDeLineaCada60Caracteres(c.titulo);
            printf("\n\n\t\t");
            saltoDeLineaCada60Caracteres(c.descripcion);
            printf("\n\t\tCategoria.................... :%s\n",c.categoria);
            printf("\t\t<3......................... :%d\n\n",c.likes);
        }
    }
}
void saltoDeLineaCada60Caracteres(const char* texto) {
    int longitud = strlen(texto);
    int i;

    for (i = 0; i < longitud; i++) {
        printf("%c", texto[i]);

        if ((i + 1) % 90 == 0) {
            printf("\n\t\t");
        }
    }
}
void mostrarInOrden(nodoArbolContenido* arbol,int categoriasUsuario[], int validosCat, stCategorias categorias[])
{
    if(arbol)
    {
        mostrarInOrden(arbol->izq,categoriasUsuario,validosCat,categorias);
        mostrarContenidosPorCategorias(arbol->c,categoriasUsuario,validosCat,categorias);
        mostrarInOrden(arbol->der,categoriasUsuario,validosCat,categorias);
    }
}

void mostrarInOrderAdmin (nodoArbolContenido * arbol){

    if (arbol){
        mostrarInOrderAdmin(arbol->izq);
        mostrarContenidoAdmin(arbol->c);
        mostrarInOrderAdmin(arbol->der);

    }

}

void mostrarContenidoAdmin(stContenido contenido){
    printf("\t\t=========================================================================================\n");
    printf("\t\tId contenido: %d",contenido.idContenido);
    printf("\t\tContenido activo: %d\n\n",contenido.activo);
    printf("\t\t");
    saltoDeLineaCada60Caracteres(contenido.titulo);
    printf("\n\n\t\t");
    saltoDeLineaCada60Caracteres(contenido.descripcion);
    printf("\n\t\tCategoria.................... :%s\n",contenido.categoria);
    printf("\t\t<3......................... :%d\n",contenido.likes);
    printf("\t\tPuntos por compartido: %d\n\n",contenido.puntosPorCompartir);
}
int contarCantidadPublicaciones(nodoArbolContenido * arbol){

    int cant=0;
    if (arbol){
        cant+= 1 +contarCantidadPublicaciones(arbol->izq) + contarCantidadPublicaciones(arbol->der);
    }

    return cant;
}

void mostrarPreOrden(nodoArbolContenido* arbol)
{
    if(arbol)
    {
        printf("======================================\n");
        printf("Id contenido:... :%d",arbol->c.idContenido);
        printf("Titulo.......... :%s\n",arbol->c.titulo);
        printf("Descripcion..... :%s\n",arbol->c.descripcion);
        printf("Categorias...... :%s\n",arbol->c.categoria);
        printf("Likes........... :%d\n",arbol->c.likes);
        printf("Activo.......... :%d\n",arbol->c.activo);
        mostrarPreOrden(arbol->izq);
        mostrarPreOrden(arbol->der);
    }
}

void mostrarUncontenido(stContenido contenido){
        printf("\t\t=========================================================================================\n");
        printf("\t\t");
        saltoDeLineaCada60Caracteres(contenido.titulo);
        printf("\n\n\t\t");
        saltoDeLineaCada60Caracteres(contenido.descripcion);
        printf("\n\t\tCategoria.................... :%s\n",contenido.categoria);
        printf("\t\t<3......................... :%d\n\n",contenido.likes);
}
nodoListaContenido * inicListaContenidos(){
    return NULL;
}

nodoListaContenido * crearNodoContenidoFavorito(stContenido contenido){

    nodoListaContenido * nuevo = malloc(sizeof(nodoListaContenido));

    nuevo->c = contenido;
    nuevo->sig = NULL;

    return nuevo;

}

nodoListaContenido * agregarFinalLista(nodoListaContenido * lista,nodoListaContenido * nuevo){

    nodoListaContenido * aux = lista;
    if (!lista)
        lista=nuevo;
    else {
        while (aux->sig){
            aux = aux->sig;

        }
        aux->sig = nuevo;
    }

    return lista;
}

void mostrarListaContenidoFavorito(nodoListaContenido * lista,int categoriasUsuario[], int validosCat, stCategorias categorias[]){

    if (!lista){
        printf("\n\t\t\t\tUsted no posee ningun contenido favorito!!\n\n\t\t\t\t");
    }
    while (lista){
        if (lista->c.activo)
            mostrarUncontenido(lista->c);
        lista = lista->sig;
    }
}

nodoListaContenido * borrarNodo(nodoListaContenido * listaContenido, char titulo[])
{
    nodoListaContenido * anterior=listaContenido;
    nodoListaContenido * seguidora=listaContenido;
    nodoListaContenido * borrado=NULL;
    if(listaContenido->sig == NULL && strcmpi(listaContenido->c.titulo,titulo)==0)
    {
        seguidora = listaContenido;
        listaContenido=listaContenido->sig;
        free(seguidora);
        listaContenido = inicListaContenidos();
    }
    else
    {
        while(seguidora!=NULL && strcmpi(seguidora->c.titulo,titulo)!=0)
        {
            anterior=seguidora;
            seguidora=seguidora->sig;
        }
        if(seguidora!=NULL)
        {
            anterior->sig=seguidora->sig;
            free(seguidora);
        }
    }
    return listaContenido;
}

int dioLike(nodoListaContenido * lista,int idContenido){

    int flag =0;

    while (flag==0 && lista){

        if(idContenido == lista->c.idContenido)
            flag = 1;
        lista=lista->sig;
    }
    return flag;
}

nodoArbolContenido * subprogramaModificarContenidoAdmin(nodoArbolContenido * arbol){

    int idContenido;
    char opcion;
    system("cls");
    printf("\t\t\t\tIngrese el id del contenido a modificar: ");
    scanf("%d",&idContenido);

    nodoArbolContenido * aux = buscarContenidoPorId(arbol,idContenido);

    if (aux!=NULL){
        do{
            system("cls");
            cuadro(10,1,110,3);
            gotoxy(12,2);
            printf("[1]Baja/Alta\t\t[2]Borrar contenido defenitivamente.\n\n");
            mostrarContenidoAdmin(aux->c);
            opcion = getch();
            switch(opcion){
            case '1':
                if (aux->c.activo)
                    aux->c.activo=0;
                else
                    aux->c.activo=1;
                break;
            case '2':
                arbol = borrarNodoArbol(arbol,aux->c.idContenido);///comentar esta linea luego de probar borrar nodo arbol
            default:
                break;
            }
        }while(opcion!='2');

    }else {
        printf("\n\t\t\tNo se encontro publicacion con ese id!\n\t\t");
        system("pause");
    }
    return arbol;
}

int pasarListaToArchivo(nodoListaContenido * lista,FILE * archi,int cont,int idUsuario){

    stFavorito dato;
    while (lista){
        cont++;
        dato.idFavorito = cont;
        dato.idUsuario = idUsuario;
        dato.idContenido = lista->c.idContenido;
        fwrite(&dato,sizeof(stFavorito),1,archi);
        lista = lista->sig;
    }

    return cont;
}

nodoListaContenido * actualizarListaFavoritosUsuario(nodoListaContenido * lista,nodoArbolContenido * arbol){
    nodoListaContenido * aux = lista;
    while (aux){
        nodoArbolContenido * abuscar = buscarContenidoPorId(arbol,lista->c.idContenido);

        if (lista->c.likes != abuscar->c.likes)
            aux->c.likes = abuscar->c.likes;
        if (lista->c.activo != abuscar->c.activo)
            aux->c.activo = abuscar->c.activo;
        aux=aux->sig;
    }
    return lista;
}
///profe le voy a dejar esto comentado para que no me rompa el programa cuando se guarde en el archivo o se levante
///
nodoArbolContenido * borrarNodoArbol(nodoArbolContenido * arbol, int idContenido)
{
    stContenido aux;
    if (arbol)
    {
        if (arbol->c.idContenido == idContenido)
        {
            if (!arbol->der && !arbol->izq)
            {
                free(arbol);
                arbol = NULL;
            }
            else
            {
                if (arbol->izq)
                {
                    arbol->c = nodoMasDer(arbol->izq);
                    arbol->izq = borrarNodoArbol(arbol->izq,arbol->c.idContenido);
                }
                else
                {
                    arbol->c = nodoMasIzq(arbol->der);
                    arbol->der = borrarNodoArbol(arbol->der,arbol->c.idContenido);
                }
            }

        }
        else
        {
            if (idContenido > arbol->c.idContenido)
                arbol->der = borrarNodoArbol(arbol->der,idContenido);
            else
                arbol->izq = borrarNodoArbol(arbol->izq,idContenido);
        }
    }
    return arbol;
}

stContenido nodoMasIzq(nodoArbolContenido * arbol)
{
    if(arbol->izq)
        nodoMasIzq(arbol->izq);
    return arbol->c;
}

stContenido nodoMasDer(nodoArbolContenido * arbol)
{
    if (arbol->der)
        nodoMasDer(arbol->der);
    return arbol->c;
}


/*
POR CADA REGISTRO DEL ARCHIVO
LEER ARCHIVO CONTENIDO--->BUSCAR POSICION USUARIO----> BUSCAR CONTENIDO-----> USUARIO[POS].LISTA AGREGARFINAL(CONTENIDO)

*/
