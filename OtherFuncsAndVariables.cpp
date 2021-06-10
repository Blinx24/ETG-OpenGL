#include "OtherFuncsAndVariables.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIABLES GLOBALES //
float cont[] = {100.0, 100.0, 100.0};
int numberOfEnemies[] = {0, 0, 0, 0};
int completedScenes = 0;
bool initContext = false;
int timeGameplay = 0;
int hours = 0;
int hours2 = 0;
int minutes = 0;
int minutes2 = 0;
int seconds = 0;
int seconds2 = 0;
string userName = "";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCIONES GENERALES //
void goToXY(int x, int y) {
	//Identificador
	HANDLE conOut = GetStdHandle(STD_OUTPUT_HANDLE); //Tomamos el control de la salida de la consola

	//Estructura que guarda coordenadas
	COORD cursorPos;

	//Asignación de la coordenada x e y
	cursorPos.X = x;
	cursorPos.Y = y;

	//Colocación del cursor en dichas coordenadas
	SetConsoleCursorPosition(conOut, cursorPos);	//Funcion para colocar el cursos en cierta posición
}

void changeColorConsole(int c) {
	//Identificador
	HANDLE conOut = GetStdHandle(STD_OUTPUT_HANDLE);

	//Asignamos el color al texto
	SetConsoleTextAttribute(conOut, c);
}

void hideCursor() {
	//Identificador
	HANDLE conOut = GetStdHandle(STD_OUTPUT_HANDLE);

	//Obtención de la información del cursor
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(conOut, &cursor);

	//Cambio del parámetro de visibilidad
	cursor.bVisible = false;

	//Asignación de nuevo al cursor
	SetConsoleCursorInfo(conOut, &cursor);
}