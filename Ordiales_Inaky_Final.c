#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>


#define ATRAS      8	//Valor ascii para la tecla "delete", "backspace", "atras", "borrar".
#define SPACE	   32	//Valor ascii para la tecla espacio
#define ARRIBA     72	//Valor ascii para la tecla flecha arriba
#define ABAJO      80	//Valor ascii para la tecla flecha abajo
#define IZQUIERDA  75	//Valor ascii para la tecla flecha izquierda
#define DERECHA    77	//Valor ascii para la tecla flecha derecha

int atoi(const char *str); // Cambiar de caracter a entero.
void dormir(int); // Hacer que el programa se pare unos segundos.
void colores(int); // Cambia el color de las letras mostradas en pantalla.

void pintar_bienvenida(int); // Imprime en pantalla la bienvenida

void pintar_inicio(); // Imprime en pantalla el menu de inicio.
void teclear_inicio(); // Se encarga de las selecciones por medio del teclado en el inicio.

void juego_1(); // Es la funcion base del juego 1, se llama al seleccionarlo en el menú de inicio.
void pintar_juego1(); // Imprime en pantalla el juego 1.
void teclear_juego1(); // Se encarga de las selecciones y cambios en el juego 1.
void mover_jugador_1(int, int); // Analiza junto con teclear_juego1 el movimiento del jugador y cambia su posición en el mapa.

void juego_2(); // Es la funcion base del juego 2, se llama al seleccionarlo en el menú de inicio.
void pintar_juego2(); // Imprime en pantalla el juego 2.
void teclear_juego2(); // Se encarga de la selección de movimientos del juego 2.
void mover_jugador_2(int, int); // Analiza junto con teclear_juego2 el movimiento del jugador y cambia su posición.

void juego_3(); // Es la funcion base del juego 3, se llama al seleccionarlo en el menú de inicio.
void juego_4(); // Es la funcion base del juego 4, se llama al seleccionarlo en el menú de inicio.

void juego_vacio(); // Esta función es llamada en los juegos 2, 3, 4 ya que están vacíos.
void pintar_juego_vacio(int); // Pinta en pantalla un aviso de que el juego está vacío.
void teclear_vacio(); // Se encarga de las selecciones al entrar a un juego vacío.

void checar_si_entra_puntajes(int, int); // Al acabar un juego se llama esta funcion para ver si el puntaje es record.
void transformar (int); // Transforma los puntos obtenidos de int a un arreglo char (puntos_transfor_carac_global).
int comparar(int); // Se encarga de ver en que lugar de los records estás.
void formatear(int, int); // Cambia el arreglo de los puntajes poniendote en tu lugar.

void puntajes(); // Es la funcion del menú de puntuaciones, se llama al seleccionarlo en el menú de inicio.
void pintar_puntajes(); // Imprime en pantalla el menú de puntuaciones
void teclear_puntajes(); // Se encarga de las selecciones a través del teclado del menú de puntuaciones.
void pintar_record(int); // Imprime en pantalla los records de algún juego al ser seleccionados.
void formatear_puntajes(); // Reinicia las puntuaciones a los valores predeterminados.

char tecla; //La entrada del teclado
char posicion_jugador1[2]; //Se usa en el juego para que una función modifique el mapa.

int con_colores; //Variable para ver si quieren jugar con colores.

//Variables menú inicio
int opcion_select_inicio = 0;
int enter_inicio = 0;
int eleccion_inicio = 0;
int salir_programa = 0;

//Variables juego 1
int direccion_1 = 0;
int meta_1 = 0;
int terminar_juego1 = 0;

//Variables juego 2
int direccion_2 = 0;
int meta_2 = 0;
int terminar_juego2 = 0;

//Variables juegos vacíos
int eleccion_vacio = 0;
int enter_vacio = 0;

//Variable menú puntajes
int enter_puntajes = 0;
int opcion_select_puntajes = 0;
int eleccion_puntajes = 0;

//Variables cambiar puntajes
int lugar_puntos;
int columna;
int digito_puntos;
int fin_comparar;
char puntos_transfor_carac_global[5];
char apodo[15];


char mapa_bienvenida[22][61] = {
	"                                                            \n",
	"                                                            \n",
    "                                                            \n",
	"                                                            \n",
	"                        BIENVENIDOS                         \n",
	"                                                            \n",
	"                                                            \n",
	"                    MINIJUEGOS   INOR...                    \n",
	"                                                            \n",
	"                                                            \n",
	"                                                            \n",
	"                                                            \n",
	"           CARGANDO...                                      \n",
	"                                                            \n",
	"                                                            \n",
	"                                                            \n",
	"                                                            \n",
	"                                                            \n",
	"                                                            \n",
	"                                                            \n",
	"                                                            \n",
	"                                                            \n",
};

char mapa_inicio[22][61] = {
	"                                                            \n",
	"                                                            \n",
    "     -----     Bienvenido a Minijuegos INOR     -----       \n",
	"                                                            \n",
	"         Selecciona el juego que quieras y dale ESPACIO,    \n",
	"     para seleccionar teclea el numero de lo que quieres.   \n",
	"                                                            \n",
	"                  !!!!!! DIVIERTETE !!!!!                   \n",
	"                                                            \n",
	"                                                           \n",
	"    Juegos individuales:                                    ",
	"                                                            ",
	"     1. CORRE CORRE                                         ",
	"                               Juegos multijugador:         ",
	"     2. LABERINTOS                                          ",
	"                                 4. CARRERAS                ",
	"     3. ESCAPE                                              ",
	"                                                            ",
	"                5. PUNTAJES MAS ALTOS                       ",
	"                                                            ",
	" 6. SALIR DEL PROGRAMA                                      ",
	"                                                            ",
};

char mapa_menu_puntajes[22][61] = {
	"                                                            \n",
	"                                                            \n",
    "      -----     Records de Minijuegos INOR     -----        \n",
	"                                                            \n",
	"         Selecciona el juego del que quieras ver            \n",
	"         el puntaje:                                        \n",
	"                                                            \n",
	"                                                            ",
	"                          1. CORRE CORRE                    ",
	"                                                            ",
	"                                                            ",
	"                          2. LABERINTOS                     ",
	"                                                            ",
	"                                                            ",
	"                          3. ESCAPE                         ",
	"                                                            ",
	"                                                            ",
	"                          4. CARRERAS                       ",
	"                                                            ",
	"                                                            ",
	"      5. REGRESAR                 6. FORMATEAR PUNTAJES     ",
	"                                                            ",
};

char mapa1_juego_vacio[22][61] = {
	"                                                            \n",
	"                                                            \n",
	"                 *** Minijuegos INOR ***                    \n",
	"                      ...........                           \n",
    "                                                            \n",
	"                                                            \n",
	"                                                            ",
	"             _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _            ",
	"                                                |           ",
	"            |         PROXIMAMENTE !!!!                     ",
	"                                                |           ",
	"            |           ESPERALO !!!                        ",
	"                                                |           ",
	"            |              2020 !!                          ",
	"              _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |           ",
	"                                                            ",
	"                                                            ",
	"                                                            ",
	"                                                            ",
	"     1.REGRESAR                    2.SALIR Programa.        ",
	"                                                            ",
	"                                                            ",
};

char mapa2_juego_vacio[22][61] = {
	"                                                            \n",
	"                                                            \n",
	"                 *** Minijuegos INOR ***                    \n",
	"                      ...........                           \n",
    "                                                            \n",
	"                                                            \n",
	"                                                            ",
	"              _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _           ",
	"            |                                               ",
	"                      PROXIMAMENTE !!!!         |           ",
	"            |                                               ",
	"                        ESPERALO !!!            |           ",
	"            |                                               ",
	"                           2020 !!              |           ",
	"            |_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _            ",
	"                                                            ",
	"                                                            ",
	"                                                            ",
	"                                                            ",
	"     1.REGRESAR                    2.SALIR Programa.        ",
	"                                                            ",
	"                                                            ",
};

char mapa_formato_juego1[22][61] = {
	"                 *** Minijuegos INOR ***                    ",
	"                      CORRE CORRE                           ",
    "   _____________________________________________________    ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                  &                                  |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |_____________________________________________________|   ",
	"   Para moverte utiliza las flechas. El tiempo da puntos,   ",
	"   date prisa en recoger todas las 'k'.  Salir --> q        ",
};

char mapa_formato_juego2[22][61] = {
	"                 *** Minijuegos INOR ***                    ",
	"                       LABERINTOS                           ",
    "  IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII   ",
	"  || |I| |                       |IIIIIII|           || |   ",
	"  ||       |IIIIIIII| |IIIIIIII| |IIIIIII| |IIIII| |I|| |   ",
	"  || |III| |IIIIIIII| |IIIIIIII|                      | |   ",
	"  |  |III| |IIIIII|  &  |IIIIII| |IIIIIIIII| |IIIIII| | |   ",
	"  | |IIII| |IIIIIIII| |IIIIIIII| |IIII|IIII|      |   | |   ",
	"  | |IIII| |IIIIIIII| |IIIIIIII| |   |I|   |III| || |I|M|   ",
	"  | |IIII|                         | ||  |  ||   ||   |E|   ",
	"  | |IIIIIIIIIIIIIIIIIIIIIIIIIII| ||I|  |I| || |IIII| |T|   ",
	"  | |IIIIIII|                     ||   |I|  ||        |A|   ",
	"  | |IIIIIII|III| |IIIIIIIIIIIIIIII| |III| |IIIIIIIIII| |   ",
	"  | |IIIIIIIIIII| |III|              |     |            |   ",
	"  | |IIIIII|      |III| |IIIIIIIIIIII| |III| |III|IIII| |   ",
	"  | |IIIIII| |IIIIIIII| |IIIIIIIIII|I| |III| |I| |IIII| |   ",
	"  | |IIIIII| |          |IIIIII|   |I|       |I| |IIII| |   ",
	"  | |IIIIII| | |IIIIIIIIIIIIIII| | |IIIIIIIIIII| |IIII| |   ",
	"  |                              |               |IIII| |   ",
	"  |IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII|   ",
	"   Para moverte utiliza las flechas. El tiempo da puntos,   ",
	"   date prisa en llegar a la meta.       Salir --> q        ",
};

char mapa_juego1[22][61] = {
	"                 *** Minijuegos INOR ***                    ",
	"                      CORRE CORRE                           ",
    "   _____________________________________________________    ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                  &                                  |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |                                                     |   ",
	"  |_____________________________________________________|   ",
	"   Para moverte utiliza las flechas. El tiempo da puntos,   ",
	"   date prisa en recoger todas las 'k'.  Salir --> q        ",
};

char mapa_juego2[22][61] = {
	"                 *** Minijuegos INOR ***                    \n",
	"                       LABERINTOS                          \n",
    "  IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII   ",
	"  || |I| |                       |IIIIIII|           || |   ",
	"  ||       |IIIIIIII| |IIIIIIII| |IIIIIII| |IIIII| |I|| |   ",
	"  || |III| |IIIIIIII| |IIIIIIII|                      | |   ",
	"  |  |III| |IIIIII|  &  |IIIIII| |IIIIIIIII| |IIIIII| | |   ",
	"  | |IIII| |IIIIIIII| |IIIIIIII| |IIII|IIII|      |   | |   ",
	"  | |IIII| |IIIIIIII| |IIIIIIII| |   |I|   |III| || |I|M|   ",
	"  | |IIII|                         | ||  |  ||   ||   |E|   ",
	"  | |IIIIIIIIIIIIIIIIIIIIIIIIIII| ||I|  |I| || |IIII| |T|   ",
	"  | |IIIIIII|                     ||   |I|  ||        |A|   ",
	"  | |IIIIIII|III| |IIIIIIIIIIIIIIII| |III| |IIIIIIIIII| |   ",
	"  | |IIIIIIIIIII| |III|              |     |            |   ",
	"  | |IIIIII|      |III| |IIIIIIIIIIII| |III| |III|IIII| |   ",
	"  | |IIIIII| |IIIIIIII| |IIIIIIIIII|I| |III| |I| |IIII| |   ",
	"  | |IIIIII| |          |IIIIII|   |I|       |I| |IIII| |   ",
	"  | |IIIIII| | |IIIIIIIIIIIIIII| | |IIIIIIIIIII| |IIII| |   ",
	"  |                              |               |IIII| |   ",
	"  |IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII|   ",
	"   Para moverte utiliza las flechas. El tiempo da puntos,   ",
	"   date prisa en llegar a la meta.       Salir --> q        ",
};

char mapa_formato_puntaje1[22][61] = {
	"                                                           \n",
	"                                                           \n",
    "   ------  Mejores Puntajes Juego 1 - CORRE CORRE  -----   \n",
	"                                                           \n",
	"                                                           \n",
	"     PUESTO        NOMBRE        PUNTOS                    \n",
	"                                                           \n",
	"       1.          -----         00010                     \n",
	"       2.          -----         00009                     \n",
	"       3.          -----         00008                     \n",
	"       4.          -----         00007                     \n",
	"       5.          -----         00006                     \n",
	"       6.          -----         00005                     \n",
	"       7.          -----         00004                     \n",
	"       8.          -----         00003                     \n",
	"       9.          -----         00002                     \n",
	"      10.          -----         00002                     \n",
	"                                                           \n",
	"                                                           \n",
	"     1.Regresar                                            \n",
	"                                                           \n",
	"                                                           \n",
}; 

char mapa_formato_puntaje2[22][61] = {
	"                                                           \n",
	"                                                           \n",
    "   ------  Mejores Puntajes Juego 2 - LABERINTOS  -----    \n",
	"                                                           \n",
	"                                                           \n",
	"     PUESTO        NOMBRE        PUNTOS                    \n",
	"                                                           \n",
	"       1.          -----         00010                     \n",
	"       2.          -----         00009                     \n",
	"       3.          -----         00008                     \n",
	"       4.          -----         00007                     \n",
	"       5.          -----         00006                     \n",
	"       6.          -----         00005                     \n",
	"       7.          -----         00004                     \n",
	"       8.          -----         00003                     \n",
	"       9.          -----         00002                     \n",
	"      10.          -----         00002                     \n",
	"                                                           \n",
	"                                                           \n",
	"     1.Regresar                                            \n",
	"                                                           \n",
	"                                                           \n",
}; 

char mapa_puntaje1[22][61];

char mapa_puntaje2[22][61];



void dormir(int x) { // Hacer que el programa se pare unos segundos.
	float time = clock();
	float fin = time +(float)x;
	
	while (clock()<=fin){
	}

}

void colores(int x) { // Cambia el color de las letras mostradas en pantalla.
	if (con_colores==1){
		switch (x) {
			case 0:
			  //textcolor(4);
			  //system("COLOR 4");
			  printf("\033[1;31m");//Rojo
			  break;
			case 1:
			  //textcolor(2);
			  //system("COLOR 2");
			  printf("\033[1;32m");//Verde
			  break;
			case 2:
			  //textcolor(14);
			  //system("COLOR 6");
		  	  printf("\033[1;33m");//Amarillo
		  	  break;
			case 3:
			  //textcolor(1);
			  //system("COLOR 1");
			  printf("\033[1;34m");//Azul
			  break;
			case 4:
			  //textcolor(5);
			  //system("COLOR 5");
			  printf("\033[1;35m");//Magenta
			  break;
			case 5:
			  //textcolor(3);
			  //system("COLOR 3");
			  printf("\033[1;36m");//Cyan
			  break;
			default:
			  //textcolor(15);
			  printf("\033[0m");
			  break;
		}
	}
}


void pintar_bienvenida(int k){ // Imprime en pantalla la bienvenida
	int j;

	system("cls");
	mapa_bienvenida[12][24+((k-2)%12)] = ' ';
	mapa_bienvenida[12][24+k%12] = '!';
	colores(1);
	
	printf("%s", mapa_bienvenida);
	
}


void pintar_inicio(){ // Imprime en pantalla el menu de inicio.
	int j;
	system("cls");
	
	for (j = 9; j < 22; j++){
		if (j<10) {
			colores(5);
			printf("%s", mapa_inicio);
		} else if (opcion_select_inicio==1 && j==12){
			colores(0);
			printf("    >1. CORRE CORRE                                         \n");
		} else if (opcion_select_inicio==2 && j==14){
			colores(0);
			printf("    >2. LABERINTOS                                          \n");
		} else if (opcion_select_inicio==3 && j==16){
			colores(0);
			printf("    >3. ESCAPE                                              \n");
		} else if (opcion_select_inicio==4 && j==15){
			colores(0);
			printf("                                >4. CARRERAS                \n");
		} else if (opcion_select_inicio==5 && j==18){
			colores(0);
			printf("               >5. PUNTAJES MAS ALTOS                       \n");
		} else if (opcion_select_inicio==6 && j==20){
			colores(0);
			printf(">6. SALIR DEL PROGRAMA                                      \n");
		} else if (opcion_select_inicio>0 && opcion_select_inicio<5 && enter_inicio==1 && j==20){
			colores(5);			
			printf("Seguro que quieres jugar el juego %d ? espacio -> si, atras -> no.\n", opcion_select_inicio);
		} else if (opcion_select_inicio==5 && enter_inicio==1 && j==20){
			colores(5);	
			printf(" Seguro que quieres ver los puntajes? espacio -> si, atras -> no.\n");
		} else if (opcion_select_inicio==6 && enter_inicio==1 && j==21){
			colores(5);	
			printf(" Seguro desea salir?   espacio -> confirmar, atras -> Regresar.\n");
		} else {
			colores(6);
			printf("%s\n", mapa_inicio[j]);
		}
	}

}

void teclear_inicio(){ // Se encarga de las selecciones por medio del teclado en el inicio.
	if (kbhit()) {
		tecla = getch();
		
		if (opcion_select_inicio == 0) {
		
			switch (tecla) {
				case '1':
					opcion_select_inicio = 1;
					pintar_inicio();
					break;
				case '2':
					opcion_select_inicio = 2;
					pintar_inicio();
					break;
				case '3':
					opcion_select_inicio = 3;
					pintar_inicio();
					break;
				case '4':
					opcion_select_inicio = 4;
					pintar_inicio();
					break;
				case '5':
					opcion_select_inicio = 5;
					pintar_inicio();
					break;
				case '6':
					opcion_select_inicio = 6;
					pintar_inicio();
					break;
				default:
					break;
			}
		} else if (enter_inicio == 1) {
			switch (tecla) {
				case SPACE:
					eleccion_inicio = opcion_select_inicio;
					break;
				case ATRAS:
					enter_inicio = 0;
					pintar_inicio();
				default:
					break;
			}
		}else {
			switch (tecla) {
				case '1':
					opcion_select_inicio = 1;
					pintar_inicio();
					break;
				case '2':
					opcion_select_inicio = 2;
					pintar_inicio();
					break;
				case '3':
					opcion_select_inicio = 3;
					pintar_inicio();
					break;
				case '4':
					opcion_select_inicio = 4;
					pintar_inicio();
					break;
				case '5':
					opcion_select_inicio = 5;
					pintar_inicio();
					break;
				case '6':
					opcion_select_inicio = 6;
					pintar_inicio();
					break;
				case SPACE:
					enter_inicio = 1;
					pintar_inicio();
					break;
				default:
					break;
			}
		}
	
	}
}


void juego_1(){ // Es la funcion base del juego 1, se llama al seleccionarlo en el menú de inicio.
	int x=21, y=6, j, i, puntos_juego1 = 0;
	terminar_juego1 = 0;
	meta_1=0;

	for ( j=0; j<22; j++){
		for ( i=0; i<60; i++){
			mapa_juego1[j][i]=mapa_formato_juego1[j][i];
		}
	}

	srand(time(NULL));
	int a;
	int b;
	
	for ( i=0; i<15; i++){
		a=(rand()%16)+3;
		b=(rand()%53)+3;
		while (mapa_juego1[a][b]=='k' ||mapa_juego1[a][b]=='&'){
			a=(rand()%16)+3;
			b=(rand()%53)+3;
		}
		mapa_juego1[a][b]='k';
	}
	
	posicion_jugador1[0] = 21;
	posicion_jugador1[1] = 6;
	pintar_juego1();
	float tiempo_inicio_juego1 = clock();
	float tiempo_final_juego1 = 0;
	while (terminar_juego1!=1){
		teclear_juego1();
		x = posicion_jugador1[0];
		y = posicion_jugador1[1];
		mover_jugador_1(x, y);
		if (meta_1>=15) {
			tiempo_final_juego1 = clock();
			puntos_juego1 = 99999 - (int)(tiempo_final_juego1 - tiempo_inicio_juego1);
			system ("cls");
			printf("\n\n GANASTE\n\n");
			printf("\nPuntaje: %d", puntos_juego1);
			checar_si_entra_puntajes(puntos_juego1, 1);
			printf("\n\nPresiona la tecla ENTER para continuar...");
			getchar();
			getchar();
			terminar_juego1 = 1;
		}
	}	
}

void pintar_juego1(){ // Imprime en pantalla el juego 1.
	system("cls");
	int j, i;
	printf("\n");
	
	for (j=0; j<22; j++){
		if (direccion_1== 5 && j== 21) {
			colores(0);
			printf("Seguro quieres salir del juego?  Espacio -> confirmar,    Atras -> no.");
		} else if (j == posicion_jugador1[1]) {
			for (i=0; i<60; i++) {
				if (mapa_juego1[j][i]=='&'){
					colores (2);
				} else {
					colores(3);
				}
				printf("%c", mapa_juego1[j][i]);
			}
			printf("\n");
		} else {
			if (j<2 || j>19){
				colores(5);
			} else {
				colores(3);
			}
			printf("%s\n", mapa_juego1[j]);	
		}	
	}
}

void teclear_juego1(){ // Se encarga de las selecciones y cambios en el juego 1.
	if (kbhit()) {
		tecla = getch();
		
		if (direccion_1==5){
			switch (tecla) {
				case SPACE:
					direccion_1 = 0;
					terminar_juego1 = 1;
					break;
				case ATRAS:
					direccion_1 = 0;
					pintar_juego1();
					break;
			}
			
		} else {
		
			switch (tecla) {
				case ARRIBA:
					direccion_1 = 1;
					break;
	
				case ABAJO:
					direccion_1 = 2;
					break;

				case DERECHA:
					direccion_1 = 3;
					break;
	
				case IZQUIERDA:
					direccion_1 = 4;
					break;

				case 'q':
					direccion_1 = 5;
					pintar_juego1();
					break;
					
				default:
					break;
			}
		}
		
	}

}

void mover_jugador_1(int x, int y){ // Analiza junto con teclear_juego1 el movimiento del jugador y cambia su posición en el mapa.
	
	if (direccion_1==1 && mapa_juego1[y-1][x]!='_'){
		if (mapa_juego1[y-1][x]=='k'){
			meta_1+=1;
		}
		mapa_juego1[y][x]=' ';
		mapa_juego1[y-1][x]='&';
		y=y-1;
		x=x;
		direccion_1=0;
		posicion_jugador1[0]=x;
		posicion_jugador1[1]=y;
		pintar_juego1();
	}else if (direccion_1==2 && mapa_juego1[y+1][x]!='_'){
		if (mapa_juego1[y+1][x]=='k'){
			meta_1+=1;
		}
		mapa_juego1[y][x]=' ';
		mapa_juego1[y+1][x]='&';
		y=y+1;
		x=x;
		direccion_1=0;
		posicion_jugador1[0]=x;
		posicion_jugador1[1]=y;
		pintar_juego1();
	}else if (direccion_1==3 && mapa_juego1[y][x+1]!='|'){
		if (mapa_juego1[y][x+1]=='k'){
			meta_1+=1;
		}
		mapa_juego1[y][x]=' ';
		mapa_juego1[y][x+1]='&';
		y=y;
		x=x+1;
		direccion_1=0;
		posicion_jugador1[0]=x;
		posicion_jugador1[1]=y;
		pintar_juego1();
	}else if (direccion_1==4 && mapa_juego1[y][x-1]!='|'){
		if (mapa_juego1[y][x-1]=='k'){
			meta_1+=1;
		}
		mapa_juego1[y][x]=' ';
		mapa_juego1[y][x-1]='&';
		y=y;
		x=x-1;
		direccion_1=0;
		posicion_jugador1[0]=x;
		posicion_jugador1[1]=y;
		pintar_juego1();
	}
}


void juego_2(){ // Es la funcion base del juego 2, se llama al seleccionarlo en el menú de inicio.
	int x=21, y=6, j, i, puntos_juego2 = 0;
	terminar_juego2 = 0;
	meta_2 = 0;
	posicion_jugador1[0] = x;
	posicion_jugador1[1] = y;
	
		for ( j=0; j<22; j++){
		for ( i=0; i<60; i++){
			mapa_juego2[j][i]=mapa_formato_juego2[j][i];
		}
	}
	
	pintar_juego2();
	float tiempo_inicio_juego2 = clock();
	float tiempo_final_juego2 = 0;
	
	while (terminar_juego2!=1){
		teclear_juego2();
		x = posicion_jugador1[0];
		y = posicion_jugador1[1];
		mover_jugador_2(x, y);
		if (meta_2==1) {
			tiempo_final_juego2 = clock();
			puntos_juego2 = 99999 - (int)(tiempo_final_juego2 - tiempo_inicio_juego2);
			system ("cls");
			colores(5);
			printf("\n\n GANASTE\n\n");
			printf("\nPuntaje: %d", puntos_juego2);
			checar_si_entra_puntajes(puntos_juego2, 2);
			printf("\n\nPresiona la tecla ENTER para continuar...");
			getchar();
			getchar();
			terminar_juego2 = 1;
		}
	}
}

void pintar_juego2(){ // Imprime en pantalla el juego 2.
	system("cls");
	int j, i;
	printf("\n");
	
	for (j = 1; j < 22; j++) {
		if (j<2){
			colores(0);
			printf("%s\n", mapa_juego2);
		} else if (j == posicion_jugador1[1]){
			for (i = 0; i<60; i++){
				if (mapa_juego2[j][i]=='&'){
					colores(0);
				} else {
					colores(6);
				}
				printf("%c", mapa_juego2[j][i]);
			}
			printf("\n");
		} else if (direccion_2 == 5 && j==20){
			colores(3);
			printf("Seguro que quieres salir del juego? ESPACIO -> si,  ATRAS -> continuar");
			j=22;
		} else if (j>19){
			colores(0);
			printf("%s\n", mapa_juego2[j]);	
		} else {
			colores(6);
			printf("%s\n", mapa_juego2[j]);
		}
	}
	
}

void teclear_juego2(){ // Se encarga de la selección de movimientos del juego 2.
	if (kbhit()) {
		tecla = getch();
		
		if (direccion_2==5){
			switch (tecla) {
				case SPACE:
					direccion_2 = 0;
					terminar_juego2 = 1;
					break;
				case ATRAS:
					direccion_2 = 0;
					pintar_juego2();
					break;
			}
			
		} else {
		
			switch (tecla) {
				case ARRIBA:
					direccion_2 = 1;
					break;
	
				case ABAJO:
					direccion_2 = 2;
					break;

				case DERECHA:
					direccion_2 = 3;
					break;
	
				case IZQUIERDA:
					direccion_2 = 4;
					break;

				case 'q':
					direccion_2 = 5;
					pintar_juego2();
					break;
					
				default:
					break;
			}
		}
		
	}

}

void mover_jugador_2(int x, int y){ // Analiza junto con teclear_juego2 el movimiento del jugador y cambia su posición.
	
	if (direccion_2==1 && mapa_juego2[y-1][x]!='|' &&  mapa_juego2[y-1][x]!='I'){
		mapa_juego2[y][x]=' ';
		mapa_juego2[y-1][x]='&';
		y=y-1;
		x=x;
		posicion_jugador1[1]=y;
		pintar_juego2();
		direccion_2=0;
	}else if (direccion_2==2 && mapa_juego2[y+1][x]!='|' &&  mapa_juego2[y+1][x]!='I'){
		mapa_juego2[y][x]=' ';
		mapa_juego2[y+1][x]='&';
		y=y+1;
		x=x;
		posicion_jugador1[1]=y;
		pintar_juego2();
		direccion_2=0;
	}else if (direccion_2==3 && mapa_juego2[y][x+1]!='|' &&  mapa_juego2[y][x+1]!='I'){
		if (x+1>53){
			meta_2 = 1;
		}
		mapa_juego2[y][x]=' ';
		mapa_juego2[y][x+1]='&';
		y=y;
		x=x+1;
		pintar_juego2();
		direccion_2=0;
	}else if (direccion_2==4 && mapa_juego2[y][x-1]!='|' &&  mapa_juego2[y][x-1]!='I'){
		mapa_juego2[y][x]=' ';
		mapa_juego2[y][x-1]='&';
		y=y;
		x=x-1;
		pintar_juego2();
		direccion_2=0;
	}else {
		y=y;
		x=x;
	}
	posicion_jugador1[0]=x;
	posicion_jugador1[1]=y;
}


void juego_3(){ // Es la funcion base del juego 3, se llama al seleccionarlo en el menú de inicio.
	juego_vacio();
}

void juego_4(){ // Es la funcion base del juego 4, se llama al seleccionarlo en el menú de inicio.
	juego_vacio();
}


void juego_vacio (){ // Esta función es llamada en los juegos 2, 3, 4 ya que están vacíos.
	int k=0;
	int num_mapa=0;
	enter_vacio = 0;
	eleccion_vacio = 0;
	system("cls");
	pintar_juego_vacio(1);
	
	while (enter_vacio!=1 && enter_vacio!=2){
		num_mapa=k%2;
		teclear_vacio();
		system("cls");
		pintar_juego_vacio(num_mapa);
		
		dormir(750);
		k++;	
	}
	
	if (eleccion_vacio == 1) {
		salir_programa = 0;
		eleccion_inicio = 0;
		enter_inicio = 0;
		pintar_inicio();
	} else {
		salir_programa = 1;
	}

}

void pintar_juego_vacio(int x) { // Pinta en pantalla un aviso de que el juego está vacío.
	int j, i;
	
	switch (x) {
		case 0:
			for (j = 0; j < 22; j++){
				if (j<7) {
					colores(3);
					printf("%s\n", mapa1_juego_vacio[j]);
					j=6;
				} else if (eleccion_vacio==1 && j==19){
					colores(0);
					printf("    >1.REGRESAR                   ");
					colores(3);
					printf(" 2.SALIR Programa.        \n");
				} else if (eleccion_vacio==2 && j==19){
					colores(3);
					printf("     1.REGRESAR                   ");
					colores(0);
					printf(">2.SALIR Programa.        \n");
				} else if (j>17){
					colores(3);
					printf("%s\n", mapa1_juego_vacio[j]);
				} else {
					colores(5);
					printf("%s\n", mapa1_juego_vacio[j]);
				}
			}
			break;
		
		case 1:
			for (j = 0; j < 22; j++){
				if (j<7) {
					colores(3);
					printf("%s\n", mapa2_juego_vacio[j]);
					j=6;
				} else if (eleccion_vacio==1 && j==19){
					colores(0);
					printf("    >1.REGRESAR                   ");
					colores(3);
					printf(" 2.SALIR Programa.        \n");
				} else if (eleccion_vacio==2 && j==19){
					colores(3);
					printf("     1.REGRESAR                   ");
					colores(0);
					printf(">2.SALIR Programa.        \n");
				} else if (j>17){
					colores(3);
					printf("%s\n", mapa2_juego_vacio[j]);
				} else {
					colores(4);
					printf("%s\n", mapa2_juego_vacio[j]);
				}
			}
			break;
		default:
			break;
	}
	
}

void teclear_vacio(){ // Se encarga de las selecciones al entrar a un juego vacío.
	if (kbhit()) {
		tecla = getch();
		
		if (eleccion_vacio == 0){
			
			switch (tecla){
				case '1':
					eleccion_vacio = 1;
					break;
				case '2':
					eleccion_vacio = 2;
					break;
				default:
					break;
			}
		} else {
			
			switch (tecla){
				case '1':
					eleccion_vacio = 1;
					break;
				case '2':
					eleccion_vacio = 2;
					break;
				case SPACE:
					enter_vacio = 1;
					break;
				default:
					break;
			}
		}
	}
}


void checar_si_entra_puntajes(int p, int num_juego) { // Al acabar un juego se llama esta funcion para ver si el puntaje es record.
	lugar_puntos=16;
	columna=33;
	digito_puntos=0;
	fin_comparar=0;
	transformar(p);
	if (comparar(num_juego)<11){
		formatear(comparar(num_juego), num_juego);
	}
	
}

void transformar(int p){ // Transforma los puntos obtenidos de int a un arreglo char (puntos_transfor_carac_global).
	int i;
	int recorrer_ceros_puntaje=0;
	char puntos_transfor_carac_local[5]={NULL};

	sprintf(puntos_transfor_carac_local, "%d", p);
	for (i=0; i<5; i++){
		if (puntos_transfor_carac_local[i]==NULL){
			puntos_transfor_carac_local[i]='0';
			recorrer_ceros_puntaje++;
		}
	}

	while (recorrer_ceros_puntaje>0){
		for (i=0; i<4; i++) {
			puntos_transfor_carac_local[4-i]=puntos_transfor_carac_local[3-i];
		}
		puntos_transfor_carac_local[0]='0';
		recorrer_ceros_puntaje--;
	}

	for (i=0; i<5; i++) {
		puntos_transfor_carac_global[i]=puntos_transfor_carac_local[i];
	}

}

int comparar(int num_juego){ // Se encarga de ver en que lugar de los records estás.

	switch(num_juego){
		case 1:
			while(lugar_puntos>6 && fin_comparar!=1){
				if (atoi(&puntos_transfor_carac_global[digito_puntos])>atoi(&mapa_puntaje1[lugar_puntos][columna])) {
					lugar_puntos-=1;
					columna=33;
					digito_puntos=0;
					comparar(1);
				} else if (atoi(&puntos_transfor_carac_global[digito_puntos])==atoi(&mapa_puntaje1[lugar_puntos][columna]) && columna<38){
					columna+=1;
					digito_puntos+=1;
					comparar(1);
				} else {
					fin_comparar=1;
				}
			}
			break;
		case 2:
			while(lugar_puntos>6 && fin_comparar!=1){
				if (atoi(&puntos_transfor_carac_global[digito_puntos])>atoi(&mapa_puntaje2[lugar_puntos][columna])) {
					lugar_puntos-=1;
					columna=33;
					digito_puntos=0;
					comparar(2);
				} else if (atoi(&puntos_transfor_carac_global[digito_puntos])==atoi(&mapa_puntaje2[lugar_puntos][columna]) && columna<38){
					columna+=1;
					digito_puntos+=1;
					comparar(2);
				} else {
					fin_comparar=1;
				}
			}
			break;
		default:
			break;
	}
	
	return (lugar_puntos-5);
}

void formatear(int lugar, int num_juego){ // Cambia el arreglo de los puntajes poniendote en tu lugar.
	int linea=0;
	int j, i;
	
	switch (num_juego) {
		case 1:
			for (j=16; j>(lugar+6); j--){
				for (i=19; i<38; i++){
					mapa_puntaje1[j][i]=mapa_puntaje1[j-1][i];
				}
			}
			break;
		case 2:
			for (j=16; j>(lugar+6); j--){
				for (i=19; i<38; i++){
					mapa_puntaje2[j][i]=mapa_puntaje2[j-1][i];
				}
			}
			break;
		default:
			break;
	}
	
	printf("\n\nFelicidades !!! Lograste el puntaje para entrar en los records.\n\n");
	printf("Tu puntaje fue de: %s puntos.\n\n", puntos_transfor_carac_global);
	printf("\nPor favor ingresa un apodo de 5 letras para records:\n");
	scanf("%s", apodo);
	printf("\n\nVe a checar los puntajes para ver tu nombre!!!");
	
	switch (num_juego) {
		case 1:
			for (i=19; i<24; i++) {
				mapa_puntaje1[lugar+6][i]=apodo[i-19];
			}

			for (i=33; i<38; i++) {
				mapa_puntaje1[lugar+6][i]=puntos_transfor_carac_global[i-33];
			}
			break;
		case 2:
			for (i=19; i<24; i++) {
				mapa_puntaje2[lugar+6][i]=apodo[i-19];
			}

			for (i=33; i<38; i++) {
				mapa_puntaje2[lugar+6][i]=puntos_transfor_carac_global[i-33];
			}
			break;
		default:
			break;
	}

}


void puntajes(){ // Es la funcion del menú de puntuaciones, se llama al seleccionarlo en el menú de inicio.
	eleccion_puntajes = 0;
	opcion_select_puntajes = 0;
	enter_puntajes = 0;
	
	pintar_puntajes();

	while (eleccion_puntajes!= 5 ) {
		teclear_puntajes();
		if (eleccion_puntajes!= 0) {
			switch (eleccion_puntajes) {
				case 1:
					pintar_record(1);
					break;
				case 2:
					pintar_record(2);
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					salir_programa=0;
					eleccion_inicio=0;
					break;
				case 6:
					formatear_puntajes();
					break;
				default:
					break;
			}
		}
	}
}

void pintar_puntajes(){ // Imprime en pantalla el menú de puntuaciones
	int j;
	system("cls");
	
	for (j = 0; j < 22; j++) {
		if (j<8){
			colores(5);
			printf("%s\n", mapa_menu_puntajes[j]);
			j=7;
		} else if ( opcion_select_puntajes==1 && j==8){
			colores(0);
			printf("                         >1. CORRE CORRE                    \n");
		} else if (opcion_select_puntajes==2 && j==11){
			colores(0);
			printf("                         >2. LABERINTOS                     \n");
		} else if (opcion_select_puntajes==3 && j==14){
			colores(0);
			printf("                         >3. ESCAPE                         \n");
		} else if (opcion_select_puntajes==4 && j==17){
			colores(0);
			printf("                         >4. CARRERAS                       \n");
		} else if (opcion_select_puntajes==5 && j==20){
			colores(0);
			printf("     >5. REGRESAR                ");
			colores(6);
			printf(" 6. FORMATEAR PUNTAJES     \n");
		} else if (opcion_select_puntajes==6 && j==20){
			colores(6);
			printf("      5. REGRESAR                ");
			colores(0);
			printf(">6. FORMATEAR PUNTAJES     \n");
		} else if (opcion_select_puntajes>0 && opcion_select_puntajes<3 && enter_puntajes==1 && j==21){
			colores(5);
			printf("Quieres ver el puntaje del juego %d ? espacio -> si, atras -> no.\n", opcion_select_puntajes);
		} else if (opcion_select_puntajes==5 && enter_puntajes==1 && j==21){
			colores(5);
			printf(" Seguro que quieres regresar al inicio? espacio -> si, atras -> no.\n");
		} else if (opcion_select_puntajes==6 && enter_puntajes==1 && j==21){
			colores(5);
			printf(" Seguro que quieres formatear los puntajes? espacio -> si, atras -> no.\n");
		} else if ((opcion_select_puntajes==4 || opcion_select_puntajes ==3) && enter_puntajes==1 && j==21){
			colores(4);
			printf(" PROXIMAMENTE , seguimos trabajando en ello...  teclea ATRAS -> continuar\n");
		} else {
			colores(6);
			printf("%s\n", mapa_menu_puntajes[j]);
		}
	}

}

void teclear_puntajes(){ // Se encarga de las selecciones a través del teclado del menú de puntuaciones.
	if (kbhit()) {
		tecla = getch();
		
		if (opcion_select_puntajes==0){
			switch (tecla) {
				case '1':
					opcion_select_puntajes = 1;
					pintar_puntajes();
					break;
				case '2':
					opcion_select_puntajes = 2;
					pintar_puntajes();
					break;
				case '3':
					opcion_select_puntajes = 3;
					pintar_puntajes();
					break;
				case '4':
					opcion_select_puntajes = 4;
					pintar_puntajes();
					break;
				case '5':
					opcion_select_puntajes = 5;
					pintar_puntajes();
					break;
				case '6':
					opcion_select_puntajes = 6;
					pintar_puntajes();
					break;
				default:
					break;
			}
		} else if (enter_puntajes ==1){
			switch (tecla) {
				case SPACE:
					eleccion_puntajes = opcion_select_puntajes;
					switch (eleccion_puntajes) {
						case 1:
							pintar_record(1);
							enter_puntajes = 0;
							eleccion_puntajes = 0;
							
							break;
						case 2:
							pintar_record(2);
							enter_puntajes = 0;
							eleccion_puntajes = 0;
							break;
						case 3:
							break;
						case 4:
							break;
						case 5:
							salir_programa=0;
							eleccion_inicio=0;
							break;
						case 6:
							formatear_puntajes();
							enter_puntajes = 0;
							eleccion_puntajes = 0;
							pintar_puntajes();
							break;
						default:
							break;
					}
					break;
				case ATRAS:
					enter_puntajes = 0;
					pintar_puntajes();
					break;
			}
		} else {
			switch (tecla) {
				case '1':
					opcion_select_puntajes = 1;
					pintar_puntajes();
					break;
				case '2':
					opcion_select_puntajes = 2;
					pintar_puntajes();
					break;
				case '3':
					opcion_select_puntajes = 3;
					pintar_puntajes();
					break;
				case '4':
					opcion_select_puntajes = 4;
					pintar_puntajes();
					break;
				case '5':
					opcion_select_puntajes = 5;
					pintar_puntajes();
					break;
				case '6':
					opcion_select_puntajes = 6;
					pintar_puntajes();
					break;
				case SPACE:
					enter_puntajes = 1;
					pintar_puntajes();
					break;
				default:
					break;
			}
		}
		
	}
}

void pintar_record(int x){ // Imprime en pantalla los records de algún juego al ser seleccionados.
	int j;
	opcion_select_puntajes=0;
	system("cls");
	colores(1);
	
	switch (x) {
		case 1:
			printf("%s", mapa_puntaje1);
			break;
		case 2:
			printf("%s", mapa_puntaje2);
			break;
		default:
			break;
	}
	
}

void formatear_puntajes(){ // Reinicia las puntuaciones a los valores predeterminados.
	int j, i;
	
	for ( j = 0; j < 22; j++) {
		for ( i = 0; i < 59; i++) {
			mapa_puntaje1[j][i] = mapa_formato_puntaje1[j][i];
			mapa_puntaje2[j][i] = mapa_formato_puntaje2[j][i];
		}
	}
	
}


int main() { //función principal, la que se corre al ejecutar el programa.
	int j, i;
	FILE *archivo1;
	FILE *archivo2;
	archivo1 = fopen("puntuaciones_1.txt", "r");//Abrimos los archivos de puntuaciones
	archivo2 = fopen("puntuaciones_2.txt", "r");
	char p1;
	char p2;
	
	j=0;
	i=0;
	while ((p1 = fgetc(archivo1)) != EOF) {
		if (i>60){
			i=0;
			j++;
		}
		mapa_puntaje1[j][i] = p1; //Se extraen los puntajes de un archivo y se guardan en un arreglo
		i++;	
	}
	
	j=0;
	i=0;
	while ((p2 = fgetc(archivo2)) != EOF) {
		if (i>60){
			i=0;
			j++;
		}
		mapa_puntaje2[j][i] = p2; //Se extraen los puntajes de otro archivo y se guardan
		i++;	
	}
	
	fclose(archivo2);//Cerramos los archivo de puntuaciones
	fclose(archivo1);
	
	//Esta opcion está porque no siempre funcionan los colores.
	printf("\n\nBienvenido, desea jugar con colores?");
	printf("\n\nSi, si quiere colores introduzca 1,\nSi no quiere colores introduzca 2.\n\n");
	printf("Si al seleccionar los colores no funciona el juego y la pantalla se llena de caracteres,");
	printf("\ncierrelo y vuelvalo a abrir, pero esta vez seleccionando sin colores.\nGRACIAS");
	printf("\n\n\nSeleccion: ");
	scanf("%d", &con_colores);
	
	/*Se imprime la bienvenida con 
	  pequeña animación*/
	for (i=0; i<36; i+=2){ 
		pintar_bienvenida(i);
		dormir(250);
	}	
	
	pintar_inicio(); //Se imprime el inicio
	while (salir_programa!=1) { //salir_programa adquiere valor de 1 cuando seleccionas SALIR. 
		teclear_inicio(); //Checa todo el tiempo si hay entrada en el teclado
		if (eleccion_inicio!=0){
			switch (eleccion_inicio){ //Dependiendo la elección de inicio el caso que corre.
				case 1:
					juego_1();
					eleccion_inicio = 0;
					opcion_select_inicio = 0;
					enter_inicio = 0;
					pintar_inicio();
					break;
				case 2:
					juego_2();
					eleccion_inicio = 0;
					opcion_select_inicio = 0;
					enter_inicio = 0;
					pintar_inicio();
					break;
				case 3:
					juego_3();
					break;
				case 4:
					juego_4();
					break;
				case 5:
					puntajes();
					eleccion_inicio = 0;
					opcion_select_inicio = 0;
					enter_inicio = 0;
					pintar_inicio();
					break;
				case 6:
					salir_programa = 1;
					break;
				default:
					break;
			}
		}
	}
	
	archivo1 = fopen("puntuaciones_1.txt", "w"); //Se vuelven a abrir los archivos
	archivo2 = fopen("puntuaciones_2.txt", "w");
	
	for (j = 0; j<22; j++) { //Se guardan las puntuaciones nuevas de la ejecución
		for (i = 0; i<61; i++) {
			p1 = mapa_puntaje1[j][i];
			fputc(p1, archivo1);
			p2 = mapa_puntaje2[j][i];
			fputc(p2, archivo2);
		}
	}
	fclose(archivo1); //Se cierran los archivos actualizados
	fclose(archivo2);
	return 0;
}
