#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VARIABLES GLOBALES //
extern float cont[];				//Contador disparo enemigos
extern int numberOfEnemies[];		//Número de enemigos
extern int completedScenes;			//Número de escenas completas
extern bool initContext;			//Inicio del contexto
extern int timeGameplay;			//Tiempo total de juego
extern int hours;					//Horas
extern int hours2;
extern int minutes;					//Minutos
extern int minutes2;
extern int seconds;					//Segundos
extern int seconds2;
extern string userName;				//Nombre de usuario

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCIONES GENERALES //
//Cambio de posición del cursor
extern void goToXY(int x, int y);

//Cambio de color de la consola
extern void changeColorConsole(int c);

//Ocultación del cursor
extern void hideCursor();
