#include "estilos.h"

void interfaz()
{
    cuadro(0,0,98,390);

}
void centrarTextoo(char *texto, int y)
{
    int longitud=strlen(texto);
    gotoxy(48-longitud/2,y) ;
    printf(texto);
}
void barra()
{
    system("cls");
    gotoxy(50,30);
    printf("CARGANDO ... ");
    for(int i=3; i<114; i++)
    {
        gotoxy(i,33);
        printf("%c",177);
    }
    for(int i=3; i<114; i++)
    {
        gotoxy(i,33);
        printf("%c",219);
        usleep();
    }
}
void gotoxy(int X,int Y)                                                        /// Cambia las coordenadas del cursor
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X=X;
    dwPos.Y=Y;
    SetConsoleCursorPosition(hcon,dwPos);
}
void cuadro(int x1, int y1,int x2, int y2)
{
    int i;
    for(i=x1; i<x2; i++)
    {
        gotoxy(i,y1);
        printf("Ä");
        gotoxy(i,y2);
        printf("Ä");
    }
    for(i=y1; i<y2; i++)
    {
        gotoxy(x1,i);
        printf("³");
        gotoxy(x2,i);
        printf("³");
    }
    gotoxy(x1,y1);
    printf("Ú");
    gotoxy(x1,y2);
    printf("À");
    gotoxy(x2,y1);
    printf("¿");
    gotoxy(x2,y2);
    printf("Ù");
}

void bienvenidoAlSistema(){
        cuadro(5,0,115,20);
        cuadro(35,1,85,3);
        gotoxy(40,2);
        printf("B I E N V E N I D O   A L   S I S T E M A");
        cuadro(46,6,74,8);
        gotoxy(52,7);
        printf("[1] Iniciar sesion ");
        cuadro(46,9,74,11);
        gotoxy(52,10);
        printf("[2] Registrarse ");
        gotoxy(52,11);
}

void registro(){
        system("cls");
        cuadro(28,1,90,3);
        gotoxy(30,2);
        printf("BIENVENIDO! Ingrese sus datos para completar el registro!\n\n");
}

void registroExitoso(){
        system("cls");
        cuadro(28,14,98,16);
        gotoxy(30,15);
        printf("Su registro se completo con exito! sera redirigido al menu principal\n\n");
}

void muroUsuario(){

    system("cls");
    cuadro(15,0,105,2);
    gotoxy(25,1);
    printf("[1]PERFIL                     [2]CONTENIDOS                     [3]MENSAJES\n\n\n");


}

void vistaPerfil(){

    system("cls");
    cuadro(15,0,105,2);
    gotoxy(25,1);
    printf("[1]MODIFICAR DATOS\t[2]VOLVER MENU PRINCIPAL\t[3]BAJA USUARIO\n");

}

void vistaContenidoUsuario(){

    system("cls");
    cuadro(10,0,115,2);
    gotoxy(15,1);
    printf("[1]BUSCAR CONTENIDO\t[2]MIS FAVORITOS\t[3]CREAR CONTENIDO\t[4]VOLVER MENU PRINCIPAL\n");

}

void vistaCargarContenido(){
    system("cls");
    cuadro(25,0,80,2);
    gotoxy(30,1);
    printf("\t\tCARGA DE UN NUEVO CONTENIDO\n\n");
}
void menuBuscarContenido(){
    system("cls");
    cuadro(10,0,115,2);
    gotoxy(15,1);
    printf("\t[1]DAR LIKE/DISLIKE\t[2]SHARE CONTENIDO\t[3]VOLVER MENU ANTERIOR\n\n");
}
void muroAdmin(){

    system("cls");
    cuadro(15,0,105,2);
    gotoxy(25,1);
    printf("[1]MENU USUARIOS\t\t\t\t[2]MENU CONTENIDOS\n\n");


}

void vistaAdminUsuarios(){

    system("cls");
    cuadro(15,0,105,2);
    gotoxy(18,1);
    printf("[1]BUSCAR POR ID\t\t\t[3]VOLVER MENU PRINCIPAL\n\n");

}

void vistaContenidoAdmin(){

    system("cls");
    cuadro(15,0,105,2);
    gotoxy(18,1);
    printf("[1]BUSCAR POR ID\t\t\t[3]VOLVER MENU PRINCIPAL\n\n");

}

void menuMensajeUsuario(int mensajesNoLeidos)
{
    system("cls");
     cuadro(15,0,105,2);
    gotoxy(25,1);
    printf("[1]VER NO LEIDOS %d       [2]VER LEIDOS              [3]MENU ANTERIOR\n\n",mensajesNoLeidos);

}

void irArriba(){
    gotoxy(0,0);
}
