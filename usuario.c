#include "usuario.h"

int validacionMail(char mail[])
{
    int flag=0;
    if ((strstr(mail, "@hotmail.com") != NULL) || (strstr(mail, "@gmail.com") != NULL) || (strstr(mail,"@outlook.com") !=NULL))
    {
        flag=1;
    }
    else
    {
        flag=0;
    }
    return flag;
}

int buscarUsuarioPorNombre(stCelda arreglo[], int validosCelda,char nombre[])///va a recibir el arrglo de lista de usuarios
{
    ///se trabaja en celda
    int i=0,flag=-1;

    while(i<validosCelda && flag == -1)
    {
        ///busca el usuario en el arreglo sino lo encuentra setea el id en 0;
        if(strcmpi(arreglo[i].usuario.userName,nombre)==0)
        {
            flag=i;
        }
        i++;
    }

    return flag;
}

int logear(stCelda arreglo[],int validos, char nombreUsuario[], char password[])       ///FUNCION QUE LOGUEA COMPARANDO CON DATOS DE ARREGLO
///recibe arreglo de lista, y devuelve el usuario~!
{
    //stUsuario usuario;///preguntar al profe si se puede usar la celda
    int i = 0,flag=-1;

    while (i<validos && flag == -1)
    {
        ///valida que el usuario a loguear sea igual al usario del arreglo!
        if (strcmp(arreglo[i].usuario.userName, nombreUsuario) == 0 && strcmpi(arreglo[i].usuario.password, password) == 0 && arreglo[i].usuario.activo)
        {
            //usuario = array[i];
            flag = i;
        }
        i++;
    }

    return flag;
}

int validarPassword(char contrasenia[])
{
    int longitud=strlen(contrasenia);
    int flag,i=0;
    int tieneMayuscula=0, tieneMinuscula=0, tieneNumero=0;
    for(i=0; i<longitud; i++)
    {
        if(isupper(contrasenia[i]))                         /// isUpper sacada de la libreria #include <ctype.h>  Controla si hay mayusculas
        {
            tieneMayuscula=1;
        }
        if(islower(contrasenia[i]))                             ///CONTROLA MINUSCULAS
        {
            tieneMinuscula=1;
        }
        if(isdigit(contrasenia[i]))                           ///CONTROLA SI HAY NUMEROS
        {
            tieneNumero=1;
        }
    }
    if((tieneMayuscula) && (tieneMinuscula) && (tieneNumero) && (longitud >= 8))
    {
        flag=1;
    }
    else
    {
        flag=0;
    }
    return flag;
}
int verificarExistenciaUsuario(stCelda arreglo[], int validosCelda, char userName[])
{
    int flag = 0;

    for (int i=0; i<validosCelda; i++)
    {
        if (strcmpi(arreglo[i].usuario.userName,userName)==0)
            flag = 1;
    }
    return flag;
}
int verificarExistenciaMail(stCelda arreglo[], int validosCelda, char mail[])                                                       ///se puede mejorar para avisar si es mail o nombreusuario
{
    int flag = 0;

    for (int i=0; i<validosCelda; i++)
    {
        if (strcmpi(arreglo[i].usuario.mail,mail)==0) ///agregue la "i" a la funcion
            flag = 1;
    }
    return flag;
}

stUsuario carga(stCategorias categorias[], int validosCategorias, stCelda arreglo[], int validosCelda)///pasar el arreglo de celdas, validos de celda
{
    stUsuario usuario;
    char opcion='0';
    usuario.validosCat=0;
    printf("\t\t\t\t\tNombre : ");
    fflush(stdin);
    gets(usuario.nombre);

    printf("\t\t\t\t\tApellido : ");
    fflush(stdin);
    gets(usuario.apellido);

    do
    {
        printf("\t\t\t\t\tNombre de usuario : ");
        fflush(stdin);
        gets(usuario.userName);

    }
    while (verificarExistenciaUsuario(arreglo,validosCelda,usuario.userName));/// pasar el arreglo de celdas los validos
    do
    {
        printf("\t\t\t\t\tMail: ");///hacer una funcion que valide mail
        fflush(stdin);
        gets(usuario.mail);

    }
    while(!validacionMail(usuario.mail) || (verificarExistenciaMail(arreglo,validosCelda,usuario.mail)));
    do
    {
        printf("\t\t\t\t\tContrasenia : ");
        fflush(stdin);
        gets(usuario.password);///ojo que pasa los espacios
    }
    while(!validarPassword(usuario.password));

    printf("\n\t\t\t\t\tIngrese las categorias que son de su interes: ");
    mostrarTodasCategorias(categorias,validosCategorias);
    do
    {
        if(opcion != '0')
        {
            printf("\t\t\t\t\tIngrese otra categoria: ");
        }
        printf("\n\t\t\t\t\t");
        scanf("%d",&usuario.cat[usuario.validosCat]);
        printf("\t\t\t\t\tDesea cargar otra categoria? s/n: ");
        fflush(stdin);
        scanf("%c",&opcion);
        usuario.validosCat++;
    }
    while(opcion != 'n');
    usuario.idUsuario=validosCelda+1;
    usuario.rol = 0;                ///0 usuario normal | 1 admin
    usuario.nivel = 0;
    printf("\t\t\t\t\tIngrege su genero: ");
    fflush(stdin);
    scanf("%c",&usuario.genero);
    usuario.puntaje = 0;
    usuario.activo = 1;///1 activo | 0 inactivo
    return usuario;
}

void modificarPerfilUsuario(stCelda arreglo[],int validosCelda, int pos)
{
    char option,userName[30],mail[30],optionSalir;
    do
    {
        system("cls");
        cuadro(40,2,79,4);
        gotoxy(44,3);
        printf("[1]- Modificar nombre usuario.\n");
        cuadro(40,6,79,8);
        gotoxy(44,7);
        printf("[2]- Modificar Mail.\n");
        cuadro(40,10,79,12);
        gotoxy(44,11);
        printf("[3]- Modificar Nombre/Apellido.\n");
        cuadro(40,14,79,16);
        gotoxy(44,15);
        printf("[4]- Modificar contrasena.\n");
        option=getch();
        switch (option)
        {
        case '1':
            do
            {
                printf("\n\t\t\t\t\tNombre de usuario : ");
                fflush(stdin);
                gets(userName);
            }
            while (verificarExistenciaUsuario(arreglo,validosCelda,userName));/// pasar el arreglo de celdas los validos
            strcpy (arreglo[pos].usuario.userName,userName);
            break;
        case '2':
            do
            {
                printf("\n\t\t\t\t\tMail : ");///hacer una funcion que valide mail
                fflush(stdin);
                gets(mail);

            }
            while(!validacionMail(arreglo[pos].usuario.mail) || (verificarExistenciaMail(arreglo,validosCelda,mail)));
            strcpy(arreglo[pos].usuario.mail,mail);
            break;
        case '3':
            printf("\n\t\t\t\t\tNombre : ");
            fflush(stdin);
            gets(arreglo[pos].usuario.nombre);

            printf("\t\t\t\t\tApellido : ");
            fflush(stdin);
            gets(arreglo[pos].usuario.apellido);
            break;
        case '4':
            do
            {
                printf("\n\t\t\t\t\tContrasenia : ");
                fflush(stdin);
                gets(arreglo[pos].usuario.password);///ojo que pasa los espacios
            }
            while(!validarPassword(arreglo[pos].usuario.password));
            break;
        default:
            printf("\n\t\t\t\t\tIngreso una opcion no valida...");
            break;
        }
        printf("\n\t\t\t\t\tDesea realizar otro cambio? s/n");
        optionSalir=getch();
    }
    while (optionSalir != 'n');
}

void mostrarUsuario(stUsuario usuario, stCategorias categorias[])
{
    int i=0;
    printf("\n\t\t\t\t\t===============================================\n");
    /*if (usuario.rol)
    {
        printf("\t\t\t\t\tID: %d\n", usuario.idUsuario);
        printf("\t\t\t\t\tPassword : %s \n", usuario.password);
        printf("\t\t\t\t\tEsta Activo: %d\n", usuario.activo);
    }*/
    printf("\t\t\t\t\tNombre: %s \n", usuario.nombre);
    printf("\t\t\t\t\tApellido: %s \n", usuario.apellido);
    printf("\t\t\t\t\tUsuario: %s \n", usuario.userName);
    printf("\t\t\t\t\tMail: %s \n", usuario.mail);
    printf("\t\t\t\t\tCategorias: ");
    ///trae las categorias del usuario y las muestra se puede poner en algun lugar de su perfil..
    while(i<usuario.validosCat)
    {
        mostrarCategoria(categorias,usuario.cat[i]);///cat=[1,10]
        i++;
    }
    printf("\n\t\t\t\t\tGenero: %c\n", usuario.genero);
    printf("\t\t\t\t\tNivel Usuario: %d",usuario.nivel);
    //printf("\n =============================================== \n ");

}

void mostrarUsuarioAdmin(stUsuario usuario, stCategorias categorias[])
{
    int i=0;
    printf("\n\t\t\t\t\t===============================================\n");
    printf("\t\t\t\t\tID: %d\n", usuario.idUsuario);
    printf("\t\t\t\t\tUsuario: %s \n", usuario.userName);
    printf("\t\t\t\t\tPassword : %s \n", usuario.password);
    printf("\t\t\t\t\tEsta Activo: %d\n", usuario.activo);
    printf("\t\t\t\t\tRol: %d \n",usuario.rol);
    printf("\t\t\t\t\tNombre: %s \n", usuario.nombre);
    printf("\t\t\t\t\tApellido: %s \n", usuario.apellido);
    printf("\t\t\t\t\tNivel: %d \n", usuario.nivel);
    printf("\t\t\t\t\tMail: %s \n", usuario.mail);
    printf("\t\t\t\t\tCategorias: ");
    ///trae las categorias del usuario y las muestra se puede poner en algun lugar de su perfil..
    while(i<usuario.validosCat)
    {
        mostrarCategoria(categorias,usuario.cat[i]);///cat=[1,10]
        i++;
    }
    printf("\n\t\t\t\t\tGenero: %c \n\n", usuario.genero);
    //printf("\n =============================================== \n ");

}

int menuIniciarSesion(stCelda arreglo[], int validosCelda)
{

    char nombreUsuario[20];
    char password[20];
    int intento = 0;
    //int loginExitoso = -1;
    char caracter;
    int i=0,flag=0, pos=-1;
    memset(password, 0, 10);
    do
    {
        system("cls");
        cuadro(5,0,115,20);
        cuadro(35,1,75,3);
        gotoxy(45,2);
        printf("INGRESAR AL SISTEMA\n");
        gotoxy(35,5);
        printf("USUARIO: ");
        gotoxy(44,5);
        scanf("%s", nombreUsuario);
        gotoxy(35,6);
        printf("CLAVE: ");

        ///maneja el arreglo de password y tiene un limite de 3 intentos para loguearse
        do
        {
            caracter = getch();
            if(caracter != 13 && caracter!= 8)
            {
                password[i] = caracter;
                printf("*");
                i++;
            }
            if(caracter == 8 && i > 0)
            {
                printf("\b \b");
                password[i] = 00;  ///password "hoa" backspace 4 "" "chau"
                i--;

            }

        }
        while(caracter != 13);

        ///toma el valor de loguear -1 error en los datos sino devuelve el id de usuario
        pos = logear(arreglo,validosCelda,nombreUsuario, password);

        if (pos == -1)
        {
            printf("\n\t\t\t\t\tUsuario y/o password incorrectos \n\t\t\t\t\t");
            system("pause");
            memset(password, 0, 10);///con esto se limpia el arreglo para resetear la pass
            i = 0;
            intento++;
        }
    }
    while (intento < 3 && pos == -1);

    return  pos;
}

///FUNCIONES DE ARREGLO DE USUARIO!--------------------------------------------------------------------------------!!!
int buscarPosicionCelda(stCelda arreglo[],int validos,int idUsuario)
{
    int pos=-1;
    int i=0;
    while(i<validos && pos ==-1)
    {
        if(arreglo[i].usuario.idUsuario == idUsuario)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}

int agregarUsuario(stCelda arreglo[],int validos,int dim,stUsuario nuevo)
{
    if(validos < dim)
    {
        arreglo[validos].usuario=nuevo;
        validos++;
    }
    return validos;
}

int alta(stCelda arreglo[],int validos,int dim,stUsuario usuario)
{
    int pos = buscarPosicionCelda(arreglo,validos,usuario.idUsuario);
    if(pos==-1)
    {
        validos=agregarUsuario(arreglo,validos,dim,usuario);
        pos=validos-1;
    }
    arreglo[pos].listaDeContenidosFavoritos = inicListaContenidos();
    arreglo[pos].mensajesLista=inicListaMensaje();

    return validos;
}

void cargarListasFavoritos(stCelda arregloUsuarios[],int validosCelda,nodoArbolContenido * arbol,stFavorito favoritos[],int validosFavoritos)
{
    int pos=0;
    while (pos<validosCelda)
    {
        for (int i=0; i<validosFavoritos; i++)
        {
            if (favoritos[i].idUsuario == arregloUsuarios[pos].usuario.idUsuario)///AGREGAR OTRA VALIDACION PARA CUANDO ESTE DADA DE BAJA EL CONTENDO
            {
                nodoListaContenido * aux = crearNodoContenidoFavorito(buscarContenidoPorId(arbol,favoritos[i].idContenido)->c);
                if (aux != NULL && aux->c.activo)
                {
                    arregloUsuarios[pos].listaDeContenidosFavoritos = agregarFinalLista(arregloUsuarios[pos].listaDeContenidosFavoritos,crearNodoContenidoFavorito(buscarContenidoPorId(arbol,favoritos[i].idContenido)->c));
                }
            }
        }
        pos++;
    }
}

int deArchivoToADL(stCelda arreglo[],int validos,int dim, char nombreArchivo[],nodoArbolContenido * arbol,stFavorito favoritos[],int validosFavoritos) ///carga las celdas con usuarios
{
    stUsuario usuario;
    FILE * archivo = fopen(nombreArchivo,"rb");
    if(archivo!=NULL)
    {
        while(fread(&usuario,sizeof(stUsuario),1,archivo)>0)
        {
            validos = alta(arreglo,validos,dim,usuario);
        }
    }
    else
    {
        printf("Error en el servidor.\n");
    }
    fclose(archivo);
    return validos;
}

void deADLtoArchivo(stCelda arreglo[], int validos, char nombreArchivo[]) ///escribe el archivo
{

    FILE * archivo = fopen(nombreArchivo,"wb");
    if(archivo!=NULL)
    {
        for (int i=0; i<validos; i++)
        {
            fwrite(&arreglo[i].usuario,sizeof (stUsuario),1,archivo);
        }
    }
    else
    {
        printf("Error en el servidor.\n");
    }
    fclose(archivo);
}

void darmeBajaUsuario(stCelda arreglo[],int pos)
{

    char option;

    system("cls");
    printf("\n\n\n\n\t\t\t\tEsta seguro de darse de baja? s/n ");
    fflush(stdin);
    scanf("%c",&option);

    if (option == 's' || option == 'S')
    {
        arreglo[pos].usuario.activo = 0;
    }
}

void subprogramaBuscarContenido(nodoArbolContenido ** arbol,stCelda arregloUsuario[],int pos,int validosUsuario)
{

    char tituloContenido[20], opcion;
    int flag;
    system("cls");
    printf("\n\n\t\tIngrese un titulo para iniciar la busqueda: ");
    fflush(stdin);
    gets(tituloContenido);

    nodoArbolContenido * contenido = buscarContenidoPorTitulo(*arbol,tituloContenido);

    if (contenido != NULL && contenido->c.activo)
    {
        do
        {
            menuBuscarContenido();
            mostrarUncontenido(contenido->c);
            opcion = getch();
            flag = dioLike(arregloUsuario[pos].listaDeContenidosFavoritos,contenido->c.idContenido);
            if (opcion == '1')
            {
                if (flag)
                {
                    contenido->c.likes--;
                    arregloUsuario[pos].listaDeContenidosFavoritos = borrarNodo(arregloUsuario[pos].listaDeContenidosFavoritos,contenido->c.titulo);

                }
                else
                {
                    contenido->c.likes++;
                    arregloUsuario[pos].listaDeContenidosFavoritos = agregarFinalLista(arregloUsuario[pos].listaDeContenidosFavoritos,crearNodoContenidoFavorito(contenido->c));
                }
            }
            else if(opcion== '2')
            {
                int usuarioReceptor;
                char nombreUsuario[15];
                printf("\t\t\tIngrese nombre de usuario:");
                fflush(stdin);
                gets(nombreUsuario);
                usuarioReceptor=buscarUsuarioPorNombre(arregloUsuario,validosUsuario,nombreUsuario);

                if(usuarioReceptor!= -1)
                {
                    stMensajeria aux;
                    aux=crearMensaje(arregloUsuario[usuarioReceptor].usuario.idUsuario,arregloUsuario[pos].usuario.idUsuario,contenido->c.idContenido);
                    arregloUsuario[usuarioReceptor].mensajesLista=agregarAlFinalMensaje(arregloUsuario[usuarioReceptor].mensajesLista,crearNodoMensaje(aux));
                    contenido->c.puntosPorCompartir+=30;
                    printf("\t\t\tMensaje enviado!.\n\t\t\t");
                    system("pause");
                }else {
                    printf("\t\t\tNo se encontro un usuario con ese nombre de usuario.\n\t\t\t");
                    system("pause");
                }
            }
        }
        while(opcion != '3');
    }
    else
    {
        printf("\n\n\t\t\t\tNo se encontro una publicacion con ese titulo!\n");
        Sleep(1000);
    }
}

void mostrarTodosUsuario(stCelda arregloUsuarios[],int validosUsuario, stCategorias categorias[],int validosCategorias)
{

    int i=0;

    while (i<validosUsuario)
    {
        mostrarUsuarioAdmin(arregloUsuarios[i].usuario,categorias);
        i++;
    }

}

void subprogramaBuscarUsuarioPorId(stCelda arregloUsuario[],int validosUsuarios,stCategorias categorias[])
{

    int i,idUsuario;
    system("cls");
    printf("\t\t\t\tIngrese el id del usuario a buscar: ");
    scanf("%d",&idUsuario);

    i=buscarPosicionCelda(arregloUsuario,validosUsuarios,idUsuario);

    if (i!=-1)
    {
        char option,userName[30],mail[30],optionSalir;
        do
        {
            system("cls");
            cuadro(10,1,110,3);
            gotoxy(12,2);
            printf("[1]Nombre usuario\t[2]Mail\t[3]Nombre/Apellido\t[4]Rol\t[5]Baja/Alta\t[6]Salir\n\n");
            mostrarUsuarioAdmin(arregloUsuario[i].usuario,categorias);
            option=getch();
            switch (option)
            {
            case '1':
                do
                {
                    printf("\n\t\t\t\t\tNombre de usuario : ");
                    fflush(stdin);
                    gets(userName);
                }
                while (verificarExistenciaUsuario(arregloUsuario,validosUsuarios,userName));/// pasar el arreglo de celdas los validos
                strcpy (arregloUsuario[i].usuario.userName,userName);
                break;
            case '2':
                do
                {
                    printf("\n\t\t\t\t\tMail : ");///hacer una funcion que valide mail
                    fflush(stdin);
                    gets(mail);
                }
                while(!validacionMail(arregloUsuario[i].usuario.mail) || (verificarExistenciaMail(arregloUsuario,validosUsuarios,mail)));
                strcpy(arregloUsuario[i].usuario.mail,mail);
                break;
            case '3':
                printf("\n\t\t\t\t\tNombre : ");
                fflush(stdin);
                gets(arregloUsuario[i].usuario.nombre);

                printf("\t\t\t\t\tApellido : ");
                fflush(stdin);
                gets(arregloUsuario[i].usuario.apellido);
                break;
            case '4':
                if (arregloUsuario[i].usuario.rol)
                    arregloUsuario[i].usuario.rol = 0;
                else
                    arregloUsuario[i].usuario.rol = 1;
                break;
            case '5':
                if (arregloUsuario[i].usuario.activo)
                    arregloUsuario[i].usuario.activo = 0;
                else
                    arregloUsuario[i].usuario.activo = 1;
                break;
            default:
                break;
            }
            printf("\n\t\t\t\t\tDesea realizar otro cambio? s/n");
        }
        while (option != '6');


    }



}

void deListaFavoritosToArchivo(stCelda arregloUsuarios[],int validosUsuarios,char nombreArchivo[])
{

    int i=0,cont=0;
    FILE * archi=fopen(nombreArchivo,"wb");
    if (archi)
    {
        while (i<validosUsuarios)
        {
            if (arregloUsuarios[i].listaDeContenidosFavoritos)
                cont += pasarListaToArchivo(arregloUsuarios[i].listaDeContenidosFavoritos,archi,cont,arregloUsuarios[i].usuario.idUsuario);
            i++;
        }
        fclose(archi);
    }
}


void cargarListaMensajes(stCelda arregloUsuario[],int validosUsuario,stMensajeria arregloMensajes[], int validosMensajes)
{
    int i=0;
    while(i<validosUsuario)
    {
        for(int j=0; j<validosMensajes; j++)
        {
            if(arregloMensajes[j].idUsuarioReceptor == arregloUsuario[i].usuario.idUsuario)
            {

                arregloUsuario[i].mensajesLista=agregarAlFinalMensaje(arregloUsuario[i].mensajesLista,crearNodoMensaje(arregloMensajes[j]));
            }
        }
        i++;
    }
}

void mostrarMensajesLeidos(stCelda arregloUsuario[],int pos,int validosUsuarios,nodoArbolContenido* arbol)
{
    int i=0;
    nodoMensaje* mensaje=arregloUsuario[pos].mensajesLista;
    if (!mensaje)
        printf("\n\t\t\tUsted no tiene mensajes!");
    while(mensaje)
    {
        if(mensaje->mensaje.leido)
        {
            i=buscarPosicionCelda(arregloUsuario,validosUsuarios,mensaje->mensaje.idUsuarioEmisor);
            mostrarMensaje(mensaje->mensaje,arregloUsuario[i].usuario.userName);
            mostrarUncontenido(buscarContenidoPorId(arbol,mensaje->mensaje.idContenidoEnviado)->c);
        }
        mensaje=mensaje->siguiente;
    }
}

void mostrarMensajesNoLeidos(stCelda arregloUsuario[],int pos, int validosUsuarios, nodoArbolContenido* arbol)
{
    int i=0;
    nodoMensaje* mensaje=arregloUsuario[pos].mensajesLista;
    while(mensaje)
    {
        if(!mensaje->mensaje.leido)
        {
            i=buscarPosicionCelda(arregloUsuario,validosUsuarios,mensaje->mensaje.idUsuarioEmisor);
            mostrarMensaje(mensaje->mensaje,arregloUsuario[i].usuario.userName);
            mostrarUncontenido(buscarContenidoPorId(arbol,mensaje->mensaje.idContenidoEnviado)->c);
            mensaje->mensaje.leido=1;
            printf("\t\t\t");
            system("pause");
        }
        mensaje=mensaje->siguiente;
    }
}

void deListaMensajeToArchivo(stCelda arregloUsuarios[],int validosUsuarios,char nombreArchivo[])
{
    int i=0;
    FILE * archi=fopen(nombreArchivo,"wb");
    if (archi)
    {
        while (i<validosUsuarios)
        {
            if (arregloUsuarios[i].mensajesLista)
                pasarListaMensajeToArchivo(arregloUsuarios[i].mensajesLista,archi);
            i++;
        }
        fclose(archi);
    }
}

void sumarPuntosPorCrearContenido(stCelda arregloUsuarios[],int pos){

    arregloUsuarios[pos].usuario.puntaje +=10;
    if (arregloUsuarios[pos].usuario.puntaje==50){
        arregloUsuarios[pos].usuario.puntaje = 0;
        arregloUsuarios[pos].usuario.nivel++;
    }
}

void actualizarListaFavoritos(stCelda arregloUsuarios[],int validosUsusarios,nodoArbolContenido * arbol){

    int i=0;

    while (i<validosUsusarios){
        if (arregloUsuarios[i].listaDeContenidosFavoritos){
            arregloUsuarios[i].listaDeContenidosFavoritos = actualizarListaFavoritosUsuario(arregloUsuarios[i].listaDeContenidosFavoritos,arbol);

        }
        i++;
    }
}

///HACER ESTO CON CADA NODO DE LA LISTA
/*IDP1
1       2       3       4       5
P       M       P       M       N
55      40      10      10      55*/
/*
CREAR LA LISTA
BUSCAR ID CONTENIDO CREAR LISTA EN BASE A ESO

IF (USUARIO.LEGUEADO == IDUSUARIO DE FOVORITOS)

ARREGLO DE USUARIO---> VAS A IR A CREAR LA LISTA

*/

/*
LEVANTAR EL PROGRAMA
LEER -> ARCHIVO USUARIO!-> GUARDAR TODOS LOS USUARIO EN ARREGLO DE USUARIO!-> LEGUEAR ->
BUSCAR EN EL ARREGLO DE LISTA EL USUARIO->CREAR LA LISTA DE FAVORITOS A PARTIR DE LAS ID DE CONTENIDOS


GUARDAR TODOS LO USAURIOS EN EL ARREGLO DE USUARIO--> CREAR CELDA -> PONE EN NULL TODAS LAS LISTAS!

TE LOGUEAS -> VAS A TU CELDA-> CARGAS TODOS LOS FAVORITOS TUYOS!
*/
