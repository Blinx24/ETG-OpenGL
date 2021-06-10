#define _USE_MATH_DEFINES

#include "Game.h"
#include "Cuboid.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "OtherFuncsAndVariables.h"

#include <math.h>
#include <stdlib.h>
#include <Windows.h>
#include <MMSystem.h>
#include <ctime>

//// MÉTODOS CLASE GAME ////
//* Constructor *//
Game::Game() {
	this->t = 0.0;
	this->deltaTime = 0.25;
	this->activeScene = nullptr;
}

//* Métodos de movimiento *//
void Game::processMouseMovement(const int& xPosition, const int& yPosition)
{
    this->activeScene->processMouseMovement(xPosition, yPosition);
}

void Game::processKeyPressed(const unsigned char& key, const int& xPosition, const int& yPosition)
{
	//ID nueva escena
	int newScene = 0;

	switch (key) {
	//Se ha pulsado la F
	case 'f':
	case 'F':
		//Si la escena actual es 0 y está completa
		if (this->activeScene->getId() == 0 && this->activeScene->getCompleted()) {
			//Reinicio de la semilla del programa para obtener el número aleatorio
			srand(time(NULL));
			
			//Selección del escenario de manera aleatoria
			newScene = (rand() % 3) + 1;

			//Actualización de jugador y de cámara
			this->scenes[newScene]->setPlayer(this->activeScene->setNewPlayer(this->scenes[newScene]->getPlayer().getPosition()));
			this->scenes[newScene]->setFirstPersonCamera(this->activeScene->setNewFirstPersonCamera(this->scenes[newScene]->getPlayer().getPosition()));

			//Limpieza de consola
			system("cls");

			//Reinicio de contexto
			initContext = false;

			//Número de escenas completas + 1
			completedScenes++;

			//Cambio de la escena activa
			this->activeScene = scenes[newScene];

		//Si la escena activa no es la 0 y está completa
		}else if (this->activeScene->getId() != 0 && this->activeScene->getCompleted()) {
			//Siguiente escena a la actual
			newScene = this->activeScene->getId() + 1;

			//Si el id supera el índice máximo del array
			if (newScene == this->scenes.size())
				//Primera escena
				newScene = 1;

			//Actualización del jugador y la cámara
			this->scenes[newScene]->setPlayer(this->activeScene->setNewPlayer(this->scenes[newScene]->getPlayer().getPosition()));
			this->scenes[newScene]->setFirstPersonCamera(this->activeScene->setNewFirstPersonCamera(this->scenes[newScene]->getPlayer().getPosition()));

			//Limpieza de la consola
			system("cls");

			//Reinicio del contexto
			initContext = false;

			//Número de escenas completas + 1
			completedScenes++;

			//Cambio de la escena activa
			this->activeScene = scenes[newScene];
		}
		break;
	default:
		this->activeScene->processKeyPressed(key, xPosition, yPosition);
		break;
	}
    
}

void Game::processMouseClick(const int& button, const int& state, const int& xPosition, const int& yPosition)
{
    this->activeScene->processMouseClick(button, state, xPosition, yPosition);
}

//* Ficheros *//
//Guardado de datos
void Game::saveDataOnFile() {
	//Variables
	ofstream wF("players.txt", ios::app);	//Buffer de escritura
	string h, k, p, e;						//Cadenas para almacenar la información del jugador

	//Cálculo de los puntos totales
	int totalPoints = this->activeScene->getPlayer().getScore();

	for (int i = 0; i < this->activeScene->getPlayer().getHealth(); i++)
	{
		totalPoints += 100;
	}

	//Inserción de los datos del jugador
	h = to_string(this->activeScene->getPlayer().getHealth());
	k = to_string(this->activeScene->getPlayer().getKills());
	p = to_string(totalPoints);
	e = to_string(completedScenes);

	//Cadenas a introducir en el fichero
	string intro = "//////////////////////////////////////////////////";
	string user = "Jugador: " + userName;
	string health = "Vida: " + h;
	string kills = "Asesinatos: " + k;
	string points = "Puntos: " + p;
	string scenes = "Escenas completadas: " + e;

	//Escritura en fichero
	wF << intro << endl;
	wF << user << endl;
	wF << health << endl;
	wF << kills << endl;
	wF << points << endl;
	wF << scenes << endl;

	//Cierre del buffer
	wF.close();
}

//Lectura de datos (ranking)
void Game::readAllDataFromFile() {
	//Buffer de lectura
	ifstream rF;
	rF.exceptions(std::ifstream::failbit);

	//Booleano auxiliar para indicar si salta excepción
	bool exception = true;

	try {
		rF.open("players.txt");

		//Cadena para almacenar los datos
		char data[128];					

		//Lectura del fichero
		while (!rF.eof()) {
			//Obtención de la información
			rF.getline(data, 128);

			//Impresión en pantalla
			cout << data << endl;

			//Si se ha podido leer el fichero
			if(exception)
				//No se produce la excepción
				exception = false;
		}
		
		//Cierre del buffer
		rF.close();
	}
	catch (std::ios_base::failure& e) {
		//Si se ha producido la excepción
		if(exception)
			cout << "[SISTEMA] No existe el fichero." << endl;
	}	
}

//* Consola *//
//Inicialización información consola
void Game::initConsole()
{
	//Limpieza de consola
	system("cls");

	//Ocultación cursor 
	hideCursor();

	//Variable auxiliar
	char l = 219;			//Carácter para vida

	//Controles del juego
	cout << "//////////// CONTROLES ///////////" << endl;

	changeColorConsole(7);
	cout << "# ";
	changeColorConsole(6);
	cout << "W A S D";
	changeColorConsole(7);
	cout << " -> Mover el jugador" << endl;

	cout << "# ";
	changeColorConsole(6);
	cout << "Espacio";
	changeColorConsole(7);
	cout << " -> Disparar" << endl;

	cout << "# ";
	changeColorConsole(6);
	cout << "R";
	changeColorConsole(7);
	cout << " -> Recargar" << endl;

	cout << "# ";
	changeColorConsole(6);
	cout << "Click izquierdo + Arrastrar";
	changeColorConsole(7);
	cout << " -> Mover la camara (solo eje X)" << endl;

	cout << "# ";
	changeColorConsole(6);
	cout << "C";
	changeColorConsole(7);
	cout << " -> Cambiar la camara" << endl;

	cout << "# ";
	changeColorConsole(6);
	cout << "F11";
	changeColorConsole(7);
	cout << " -> Pantalla completa" << endl;
	cout << "////////////////////////////////" << endl;

	//Jugador
	cout << "//////////// JUGADOR ///////////" << endl;

	changeColorConsole(7);
	cout << "# Vida: ";
	changeColorConsole(4);
	for (int i = 0; i < this->activeScene->getPlayer().getHealth(); i++)
	{
		cout << l;
	}
	cout << endl;

	changeColorConsole(7);
	cout << "# Municion: ";
	cout << this->activeScene->getPlayer().getWeapon().getAmmunition() << " / " << this->activeScene->getPlayer().getWeapon().getCylinderSize() << endl;

	cout << "# Puntos: ";
	cout << this->activeScene->getPlayer().getScore() << endl;;
	cout << "////////////////////////////////" << endl;

	//Mundo
	cout << "//////////// MUNDO ///////////" << endl;
	cout << "# Enemigos: ";
	cout << numberOfEnemies[this->activeScene->getId()] << endl;

	cout << "# Tiempo de juego: ";
	cout << "00:00:00" << endl;
	cout << "////////////////////////////////" << endl;

}

//Actualización tiempo
void Game::updateTimeGameplay() {
	changeColorConsole(7);

	//Aumento del tiempo de juego
	timeGameplay++;

	//Cálculos de los segundos, minutos y horas
	if (timeGameplay == 125) {
		timeGameplay = 0;

		seconds++;

		if (seconds >= 10) {
			seconds2 += (seconds / 10);
			seconds = 0;
		}

		if (seconds2 == 6) {
			seconds2 = 0;

			minutes++;

			if (minutes >= 10) {
				minutes2 += (minutes / 10);
				minutes = 0;
			}

			if (minutes2 == 6) {
				minutes2 = 0;

				hours++;

				if (hours >= 10) {
					hours2 += (hours / 10);
					hours = 0;
				}
			}
		}
	}

	//Impresión de la información en pantalla
	goToXY(19, 15);
	cout << hours2;
	goToXY(20, 15);
	cout << hours;

	goToXY(21, 15);
	cout << ":";

	goToXY(22, 15);
	cout << minutes2;
	goToXY(23, 15);
	cout << minutes;

	goToXY(24, 15);
	cout << ":";

	goToXY(25, 15);
	cout << seconds2;
	goToXY(26, 15);
	cout << seconds;
}

//Escena completada
void Game::completedScene() {
	//Si la escena ha sido completada
	if (this->activeScene->getCompleted()) {
		//Impresión en consola
		goToXY(0, 17);
		cout << "Pulsa F para pasar al siguiente nivel." << endl;
	}
}

//* Otros métodos *//
//Menú principal
void Game::startGame() {
	//Variables auxiliares
	bool done = false;			//Salida del menú - Entrada al juego
	int op = 0;					//Opción del menú
	int ex;						//Salir del juego
	int outRanking;				//Salir del ranking

	//Limpieza de la consola
	system("cls");

	//Reproducción de la música del menú
	PlaySound(TEXT("menu.wav"), NULL, SND_ASYNC);

	//Menú
	do {	
		//Introducción
		changeColorConsole(6);
		cout << "////// ENTER THE GUNGEON //////" << endl;

		changeColorConsole(7);

		//Menú
		cout << "[SISTEMA] 1. Empezar partida." << endl;
		cout << "[SISTEMA] 2. Ver puntuaciones." << endl;
		cout << "[SISTEMA] 3. Salir del juego." << endl;
		cout << "[SISTEMA] > ";
		cin >> op;

		//Comprobación de la opción
		while (op < 1 || op > 3) {
			cout << "[SISTEMA] ERROR. Opcion no valida." << endl;

			Sleep(1000);

			system("cls");

			changeColorConsole(6);
			cout << "////// ENTER THE GUNGEON //////" << endl;

			changeColorConsole(7);

			cout << "[SISTEMA] 1. Empezar partida." << endl;
			cout << "[SISTEMA] 2. Ver puntuaciones." << endl;
			cout << "[SISTEMA] 3. Salir del juego." << endl;
			cout << "[SISTEMA] > ";
			cin >> op;
		}

		switch (op) {
			//Empezar partida
		case 1:
			//Inserción del nombre de usuario
			cout << "[SISTEMA] Introduce tu nombre de jugador (1 palabra)." << endl;
			cout << "[SISTEMA] > ";
			cin >> userName;

			cout << "[SISTEMA] Usuario registrado con exito." << endl;
			cout << "[SISTEMA] Cargando juego...";
			Sleep(1000);

			//Salida del bucle y entrada al juego
			done = true;
			break;
			//Visualización de todas las puntuaciones
		case 2:
			cout << "[SISTEMA] Leyendo todos los datos de jugadores..." << endl;
			Sleep(1000);

			system("cls");

			cout << "[SISTEMA] RANKING" << endl;

			//Lectura del fichero
			this->readAllDataFromFile();
			cout << "//////////////////////////////////////////////////" << endl;

			//Salida de la opción
			cout << "[SISTEMA] Introduce 1 para salir." << endl;
			cout << "[SISTEMA] > ";
			cin >> outRanking;

			//Comrpobación de la opción insertada
			while (outRanking != 1) {
				cout << "[SISTEMA] ERROR. Opcion no valida." << endl;
				cout << "[SISTEMA] > ";
				cin >> outRanking;
			}

			break;
			//Salida del juego
		case 3:
			cout << "[SISTEMA] Seguro que quieres salir?" << endl;
			cout << "[SISTEMA] 1. Si." << endl;
			cout << "[SISTEMA] 2. No." << endl;
			cout << "[SISTEMA] > ";
			cin >> ex;

			//Comprobación de la opción
			while (ex < 1 || ex > 2) {
				cout << "[SISTEMA] ERROR. Opcion no valida." << endl;
				cout << "[SISTEMA] > ";
				cin >> ex;
			}

			//Salida
			if (ex == 1) {
				exit(0);
			}
			break;
		}

		//Limpieza de la consola
		system("cls");

	} while (!done);

	//Limpieza de la consola
	system("cls");
}

//Creación escena 0
Scene* Game::createScene() {
	//* Escena *//
	Scene* scene = new Scene();
	scene->setCompleted(true);
	scene->setId(0);

	//* Cámara cenital *//
	FlyingCamera upperCamera = scene->getCamera();
	upperCamera.setPosition(Vector3D((5.0), (20.0), (5.0)));
	upperCamera.setOrientation((Vector3D(90.0f, 90.0f, 0.0f)));
	upperCamera.setId(0);
	upperCamera.setState('f');
	scene->addCamera(upperCamera);

	//* Cámara en primera persona *//
	FlyingCamera firstPerson = scene->getCamera();
	firstPerson.setPosition(Vector3D((5.0), (1.0), (5.0)));
	firstPerson.setOrientation((Vector3D(0.0f, 90.0f, 0.0f)));
	firstPerson.setState('a');
	firstPerson.setId(1);
	scene->addCamera(firstPerson);
	scene->setCamera(firstPerson);

	//* Jugador *//
	Player pl = scene->getPlayer();
	pl.setPosition(Vector3D((5.0), (1.0), (5.0)));
	pl.setColor(Color((1.0), (0.0), (0.0)));
	pl.setOrientation(Vector3D(0.0f, 90.0f, 0.0f));
	pl.setWeapon(Weapon(1, 24, 8, 8, 0.1));
	pl.setHealth(10);
	pl.setSize(1.0);
	pl.setScore(0);
	scene->setPlayer(pl);

	//Cálculo del número de enemigos
	numberOfEnemies[0] = 0;

	//* Límites de la escena *//
	Cuboid* left = new Cuboid();
	left->setPosition(Vector3D(5.0f, 2.5f, -0.5f));
	left->setColor(Color(0.9f, 0.6f, 0.5f));
	left->setHeight(5.0);
	left->setLength(10.0);
	left->setWidth(1.0);
	left->setGravity(false);
	scene->addLimitScenario(left);

	Cuboid* right = new Cuboid();
	right->setPosition(Vector3D(5.0f, 2.5f, 10.5f));
	right->setColor(Color(0.9f, 0.6f, 0.5f));
	right->setHeight(5.0);
	right->setLength(10.0);
	right->setWidth(1.0);
	right->setGravity(false);
	scene->addLimitScenario(right);

	Cuboid* floor = new Cuboid();
	floor->setPosition(Vector3D(5.0f, -0.5f, 5.0f));
	floor->setColor(Color(0.5f, 0.9f, 0.6f));
	floor->setHeight(1.0);
	floor->setLength(10.0);
	floor->setWidth(10.0);
	floor->setCanCollide(false);
	floor->setGravity(false);
	scene->addLimitScenario(floor);

	Cuboid* top = new Cuboid();
	top->setPosition(Vector3D(10.5f, 2.5f, 5.0f));
	top->setColor(Color(0.6, 0.5, 0.9));
	top->setHeight(5.0);
	top->setLength(1.0);
	top->setWidth(10.0);
	top->setGravity(false);
	scene->addLimitScenario(top);

	Cuboid* bottom = new Cuboid();
	bottom->setPosition(Vector3D(-0.5f, 2.5f, 5.0f));
	bottom->setColor(Color(0.6, 0.5, 0.9));
	bottom->setHeight(5.0);
	bottom->setLength(1.0);
	bottom->setWidth(10.0);
	bottom->setGravity(false);
	scene->addLimitScenario(bottom);

	return scene;
}

//Creación escena 1
Scene* Game::createScene1() {
	//* Escena *//
	Scene* scene = new Scene();
	scene->setId(1);
	scene->setCompleted(false);

	//* Cámara cenital *//
	FlyingCamera upperCamera = scene->getCamera();
	upperCamera.setPosition(Vector3D((5.0), (20.0), (10.0)));
	upperCamera.setOrientation((Vector3D(90.0f, 90.0f, 0.0f)));
	upperCamera.setId(0);
	upperCamera.setState('f');
	scene->addCamera(upperCamera);

	//* Cámara en primera persona *//
	FlyingCamera firstPerson = scene->getCamera();
	firstPerson.setPosition(Vector3D((5.0), (1.0), (5.0)));
	firstPerson.setOrientation((Vector3D(0.0f, 90.0f, 0.0f)));
	firstPerson.setState('a');
	firstPerson.setId(1);
	scene->addCamera(firstPerson);
	scene->setCamera(firstPerson);

	//* Jugador *//
	Player pl = scene->getPlayer();
	pl.setPosition(Vector3D((5.0), (1.0), (5.0)));
	pl.setColor(Color((1.0), (0.0), (0.0)));
	pl.setOrientation(Vector3D(0.0f, 90.0f, 0.0f));
	pl.setWeapon(Weapon(1, 24, 8, 8, 0.1));
	pl.setHealth(10);
	pl.setSize(1.0);
	pl.setScore(0);
	scene->setPlayer(pl);

	//* Enemigo 1 *//
	Enemy* e1 = new Enemy();
	e1->loadModel("enemy.obj");
	e1->setPosition(Vector3D((6.2), (0.0), (18.6)));
	e1->setColor(Color((1.0), (0.0), (1.0)));

	// Ángulo de rotación en función de la posición del jugador
	float alpha1 = atan2(pl.getPosition().getX() - e1->getPosition().getX(), pl.getPosition().getZ() - e1->getPosition().getZ());
	alpha1 *= (180.0 / M_PI);

	e1->setOrientation(Vector3D((0.0), (alpha1), (0.0)));
	e1->setWeapon(Weapon(1, 24, 8, 8, 0.3));
	e1->setHealth(1);
	e1->setSize(1.0);
	scene->addEnemy(e1);

	//* Enemigo 2 *//
	Enemy* e2 = new Enemy();
	e2->loadModel("enemy.obj");
	e2->setPosition(Vector3D((5.2), (0.0), (13.0)));
	e2->setColor(Color((1.0), (0.0), (1.0)));

	// Ángulo de rotación en función de la posición del jugador
	float alpha2 = atan2(pl.getPosition().getX() - e2->getPosition().getX(), pl.getPosition().getZ() - e2->getPosition().getZ());
	alpha2 *= (180.0 / M_PI);

	e2->setOrientation(Vector3D((0.0), (alpha2), (0.0)));
	e2->setWeapon(Weapon(1, 24, 8, 8, 0.8));
	e2->setHealth(3);
	e2->setSize(1.0);
	scene->addEnemy(e2);

	//* Enemigo 3 *//
	Enemy* e3 = new Enemy();
	e3->loadModel("enemy.obj");
	e3->setPosition(Vector3D((1.0), (0.0), (18.6)));
	e3->setColor(Color((1.0), (0.0), (1.0)));

	// Ángulo de rotación en función de la posición del jugador
	float alpha3 = atan2(pl.getPosition().getX() - e3->getPosition().getX(), pl.getPosition().getZ() - e3->getPosition().getZ());
	alpha3 *= (180.0 / M_PI);

	e3->setOrientation(Vector3D((0.0), (alpha3), (0.0)));
	e3->setWeapon(Weapon(1, 24, 8, 8, 0.5));
	e3->setHealth(1);
	e3->setSize(1.0);
	scene->addEnemy(e3);

	//Reinicio de la semilla del programa para obtener el número aleatorio
	srand(time(NULL) * 3);

	//Cálculo del número de enemigos
	numberOfEnemies[scene->getId()] = (rand() % 3) + 1;

	//* Límites de la escena *//
	Cuboid* left = new Cuboid();
	left->setPosition(Vector3D(5.0f, 2.5f, -0.5f));
	left->setColor(Color(0.9f, 0.6f, 0.5f));
	left->setHeight(5.0);
	left->setLength(10.0);
	left->setWidth(1.0);
	left->setGravity(false);
	scene->addLimitScenario(left);

	Cuboid* right = new Cuboid();
	right->setPosition(Vector3D(5.0f, 2.5f, 20.5f));
	right->setColor(Color(0.9f, 0.6f, 0.5f));
	right->setHeight(5.0);
	right->setLength(10.0);
	right->setWidth(1.0);
	right->setGravity(false);
	scene->addLimitScenario(right);

	Cuboid* wall = new Cuboid();
	wall->setPosition(Vector3D(5.0f, 2.5f, 10.5f));
	wall->setColor(Color(0.4f, 0.2f, 0.1f));
	wall->setHeight(5.0);
	wall->setLength(4.0);
	wall->setWidth(1.0);
	wall->setGravity(false);
	scene->addLimitScenario(wall);

	Cuboid* floor = new Cuboid();
	floor->setPosition(Vector3D(5.0f, -0.5f, 10.0f));
	floor->setColor(Color(0.5f, 0.9f, 0.6f));
	floor->setHeight(1.0);
	floor->setLength(10.0);
	floor->setWidth(20.0);
	floor->setCanCollide(false);
	floor->setGravity(false);
	scene->addLimitScenario(floor);

	Cuboid* top = new Cuboid();
	top->setPosition(Vector3D(10.5f, 2.5f, 10.0f));
	top->setColor(Color(0.6, 0.5, 0.9));
	top->setHeight(5.0);
	top->setLength(1.0);
	top->setWidth(20.0);
	top->setGravity(false);
	scene->addLimitScenario(top);

	Cuboid* bottom = new Cuboid();
	bottom->setPosition(Vector3D(-0.5f, 2.5f, 10.0f));
	bottom->setColor(Color(0.6, 0.5, 0.9));
	bottom->setHeight(5.0);
	bottom->setLength(1.0);
	bottom->setWidth(20.0);
	bottom->setGravity(false);
	scene->addLimitScenario(bottom);

	return scene;
}

//Creación escena 2
Scene* Game::createScene2() {
	//* Escena *//
	Scene* scene = new Scene();
	scene->setId(2);
	scene->setCompleted(false);

	//* Cámara cenital *//
	FlyingCamera upperCamera = scene->getCamera();
	upperCamera.setPosition(Vector3D((9.5), (15.0), (5.0)));
	upperCamera.setOrientation((Vector3D(90.0f, 90.0f, 0.0f)));
	upperCamera.setId(0);
	upperCamera.setState('m');
	scene->addCamera(upperCamera);

	//* Cámara en primera persona *//
	FlyingCamera firstPerson = scene->getCamera();
	firstPerson.setPosition(Vector3D((9.5), (1.0), (5.0)));
	firstPerson.setOrientation((Vector3D(0.0f, 90.0f, 0.0f)));
	firstPerson.setState('a');
	firstPerson.setId(1);
	scene->addCamera(firstPerson);
	scene->setCamera(firstPerson);

	//* Jugador *//
	Player pl = scene->getPlayer();
	pl.setPosition(Vector3D((9.5), (1.0), (5.0)));
	pl.setColor(Color((1.0), (0.0), (0.0)));
	pl.setOrientation(Vector3D(0.0f, 90.0f, 0.0f));
	pl.setWeapon(Weapon(1, 24, 8, 8, 0.1));
	pl.setHealth(10);
	pl.setSize(1.0);
	pl.setScore(0);
	scene->setPlayer(pl);

	//* Enemigo 1 *//
	Enemy* e1 = new Enemy();
	e1->loadModel("enemy.obj");
	e1->setPosition(Vector3D(15.5f, 0.0f, 20.0f));
	e1->setColor(Color((1.0), (0.0), (1.0)));

	// Ángulo de rotación en función de la posición del jugador
	float alpha1 = atan2(pl.getPosition().getX() - e1->getPosition().getX(), pl.getPosition().getZ() - e1->getPosition().getZ());
	alpha1 *= (180.0 / M_PI);

	e1->setOrientation(Vector3D((0.0), (alpha1), (0.0)));
	e1->setWeapon(Weapon(1, 24, 8, 8, 0.3));
	e1->setHealth(1);
	e1->setSize(1.0);
	scene->addEnemy(e1);

	//* Enemigo 2 *//
	Enemy* e2 = new Enemy();
	e2->loadModel("enemy.obj");
	e2->setPosition(Vector3D(23.0f, 0.0f, 13.0f));
	e2->setColor(Color((1.0), (0.0), (1.0)));

	// Ángulo de rotación en función de la posición del jugador
	float alpha2 = atan2(pl.getPosition().getX() - e2->getPosition().getX(), pl.getPosition().getZ() - e2->getPosition().getZ());
	alpha2 *= (180.0 / M_PI);

	e2->setOrientation(Vector3D((0.0), (alpha2), (0.0)));
	e2->setWeapon(Weapon(1, 24, 8, 8, 0.8));
	e2->setHealth(3);
	e2->setSize(1.0);
	scene->addEnemy(e2);

	//* Enemigo 3 *//
	Enemy* e3 = new Enemy();
	e3->loadModel("enemy.obj");
	e3->setPosition(Vector3D(5.0f, 0.0f, 27.0f));
	e3->setColor(Color((1.0), (0.0), (1.0)));

	// Ángulo de rotación en función de la posición del jugador
	float alpha3 = atan2(pl.getPosition().getX() - e3->getPosition().getX(), pl.getPosition().getZ() - e3->getPosition().getZ());
	alpha3 *= (180.0 / M_PI);

	e3->setOrientation(Vector3D((0.0), (alpha3), (0.0)));
	e3->setWeapon(Weapon(1, 24, 8, 8, 0.5));
	e3->setHealth(1);
	e3->setSize(1.0);
	scene->addEnemy(e3);

	//Reinicio de la semilla del programa para obtener el número aleatorio
	srand(time(NULL)*2);

	//Cálculo del número de enemigos
	numberOfEnemies[scene->getId()] = (rand() % 3) + 1;

	//* Límites de la escena *//
	Cuboid* left = new Cuboid();
	left->setPosition(Vector3D(7.5f, 2.5f, -0.5f));
	left->setColor(Color(0.9f, 0.6f, 0.5f));
	left->setHeight(5.0);
	left->setLength(15.0);
	left->setWidth(1.0);
	left->setGravity(false);
	scene->addLimitScenario(left);

	Cuboid* left2 = new Cuboid();
	left2->setPosition(Vector3D(18.0f, 2.5f, 15.5f));
	left2->setColor(Color(0.9f, 0.6f, 0.5f));
	left2->setHeight(5.0);
	left2->setLength(6.0);
	left2->setWidth(1.0);
	left2->setGravity(false);
	scene->addLimitScenario(left2);

	Cuboid* left3 = new Cuboid();
	left3->setPosition(Vector3D(26.0f, 2.5f, 9.5f));
	left3->setColor(Color(0.9f, 0.6f, 0.5f));
	left3->setHeight(5.0);
	left3->setLength(10.0);
	left3->setWidth(1.0);
	left3->setGravity(false);
	scene->addLimitScenario(left3);

	Cuboid* right = new Cuboid();
	right->setPosition(Vector3D(7.5f, 2.5f, 30.5f));
	right->setColor(Color(0.9f, 0.6f, 0.5f));
	right->setHeight(5.0);
	right->setLength(15.0);
	right->setWidth(1.0);
	right->setGravity(false);
	scene->addLimitScenario(right);

	Cuboid* right2 = new Cuboid();
	right2->setPosition(Vector3D(18.0f, 2.5f, 24.5f));
	right2->setColor(Color(0.9f, 0.6f, 0.5f));
	right2->setHeight(5.0);
	right2->setLength(6.0);
	right2->setWidth(1.0);
	right2->setGravity(false);
	scene->addLimitScenario(right2);

	Cuboid* right3 = new Cuboid();
	right3->setPosition(Vector3D(26.0f, 2.5f, 30.5f));
	right3->setColor(Color(0.9f, 0.6f, 0.5f));
	right3->setHeight(5.0);
	right3->setLength(10.0);
	right3->setWidth(1.0);
	right3->setGravity(false);
	scene->addLimitScenario(right3);

	Cuboid* wall = new Cuboid();
	wall->setPosition(Vector3D(10.0f, 2.5f, 15.5f));
	wall->setColor(Color(0.4f, 0.2f, 0.1f));
	wall->setHeight(5.0);
	wall->setLength(7.0);
	wall->setWidth(1.0);
	wall->setGravity(false);
	scene->addLimitScenario(wall);

	Cuboid* floor = new Cuboid();
	floor->setPosition(Vector3D(7.5f, -0.5f, 15.0f));
	floor->setColor(Color(0.5f, 0.9f, 0.6f));
	floor->setHeight(1.0);
	floor->setLength(15.0);
	floor->setWidth(30.0);
	floor->setCanCollide(false);
	floor->setGravity(false);
	scene->addLimitScenario(floor);

	Cuboid* floor2 = new Cuboid();
	floor2->setPosition(Vector3D(18.0f, -0.5f, 20.0f));
	floor2->setColor(Color(0.5f, 0.9f, 0.6f));
	floor2->setHeight(1.0);
	floor2->setLength(6.0);
	floor2->setWidth(8.0);
	floor2->setCanCollide(false);
	floor2->setGravity(false);
	scene->addLimitScenario(floor2);

	Cuboid* floor3 = new Cuboid();
	floor3->setPosition(Vector3D(26.0f, -0.5f, 20.0f));
	floor3->setColor(Color(0.5f, 0.9f, 0.6f));
	floor3->setHeight(1.0);
	floor3->setLength(10.0);
	floor3->setWidth(20.0);
	floor3->setCanCollide(false);
	floor3->setGravity(false);
	scene->addLimitScenario(floor3);

	Cuboid* top = new Cuboid();
	top->setPosition(Vector3D(15.5f, 2.5f, 7.5f));
	top->setColor(Color(0.6, 0.5, 0.9));
	top->setHeight(5.0);
	top->setLength(1.0);
	top->setWidth(15.0);
	top->setGravity(false);
	scene->addLimitScenario(top);

	Cuboid* top2 = new Cuboid();
	top2->setPosition(Vector3D(15.5f, 2.5f, 27.5f));
	top2->setColor(Color(0.6, 0.5, 0.9));
	top2->setHeight(5.0);
	top2->setLength(1.0);
	top2->setWidth(5.0);
	top2->setGravity(false);
	scene->addLimitScenario(top2);

	Cuboid* top3 = new Cuboid();
	top3->setPosition(Vector3D(31.5f, 2.5f, 20.0f));
	top3->setColor(Color(0.6, 0.5, 0.9));
	top3->setHeight(5.0);
	top3->setLength(1.0);
	top3->setWidth(20.0);
	top3->setGravity(false);
	scene->addLimitScenario(top3);

	Cuboid* bottom = new Cuboid();
	bottom->setPosition(Vector3D(-0.5f, 2.5f, 15.0f));
	bottom->setColor(Color(0.6, 0.5, 0.9));
	bottom->setHeight(5.0);
	bottom->setLength(1.0);
	bottom->setWidth(30.0);
	bottom->setGravity(false);
	scene->addLimitScenario(bottom);

	Cuboid* bottom2 = new Cuboid();
	bottom2->setPosition(Vector3D(20.5f, 2.5f, 27.5f));
	bottom2->setColor(Color(0.6, 0.5, 0.9));
	bottom2->setHeight(5.0);
	bottom2->setLength(1.0);
	bottom2->setWidth(5.0);
	bottom2->setGravity(false);
	scene->addLimitScenario(bottom2);

	Cuboid* bottom3 = new Cuboid();
	bottom3->setPosition(Vector3D(20.5f, 2.5f, 12.5f));
	bottom3->setColor(Color(0.6, 0.5, 0.9));
	bottom3->setHeight(5.0);
	bottom3->setLength(1.0);
	bottom3->setWidth(5.0);
	bottom3->setGravity(false);
	scene->addLimitScenario(bottom3);

	return scene;
}

//Creación escena 3
Scene* Game::createScene3() {
	//* Escena *//
	Scene* scene = new Scene();
	scene->setId(3);
	scene->setCompleted(false);

	//* Cámara cenital *//
	FlyingCamera upperCamera = scene->getCamera();
	upperCamera.setPosition(Vector3D((5.0), (15.0), (5.0)));
	upperCamera.setOrientation((Vector3D(90.0f, 90.0f, 0.0f)));
	upperCamera.setId(0);
	upperCamera.setState('m');
	scene->addCamera(upperCamera);

	//* Cámara en primera persona *//
	FlyingCamera firstPerson = scene->getCamera();
	firstPerson.setPosition(Vector3D((5.0), (1.0), (5.0)));
	firstPerson.setOrientation((Vector3D(0.0f, 90.0f, 0.0f)));
	firstPerson.setState('a');
	firstPerson.setId(1);
	scene->addCamera(firstPerson);
	scene->setCamera(firstPerson);

	//* Jugador *//
	Player pl = scene->getPlayer();
	pl.setPosition(Vector3D((5.0), (1.0), (5.0)));
	pl.setColor(Color((1.0), (0.0), (0.0)));
	pl.setOrientation(Vector3D(0.0f, 90.0f, 0.0f));
	pl.setWeapon(Weapon(1, 24, 8, 8, 0.1));
	pl.setHealth(10);
	pl.setSize(1.0);
	pl.setScore(0);
	scene->setPlayer(pl);

	//* Enemigo 1 *//
	Enemy* e1 = new Enemy();
	e1->loadModel("enemy.obj");
	e1->setPosition(Vector3D((10.5), (0.0), (28.5)));
	e1->setColor(Color((1.0), (0.0), (1.0)));

	// Ángulo de rotación en función de la posición del jugador
	float alpha1 = atan2(pl.getPosition().getX() - e1->getPosition().getX(), pl.getPosition().getZ() - e1->getPosition().getZ());
	alpha1 *= (180.0 / M_PI);

	e1->setOrientation(Vector3D((0.0), (alpha1), (0.0)));
	e1->setWeapon(Weapon(1, 24, 8, 8, 0.3));
	e1->setHealth(1);
	e1->setSize(1.0);
	scene->addEnemy(e1);

	//* Enemigo 2 *//
	Enemy* e2 = new Enemy();
	e2->loadModel("enemy.obj");
	e2->setPosition(Vector3D((5.2), (0.0), (13.0)));
	e2->setColor(Color((1.0), (0.0), (1.0)));

	// Ángulo de rotación en función de la posición del jugador
	float alpha2 = atan2(pl.getPosition().getX() - e2->getPosition().getX(), pl.getPosition().getZ() - e2->getPosition().getZ());
	alpha2 *= (180.0 / M_PI);

	e2->setOrientation(Vector3D((0.0), (alpha2), (0.0)));
	e2->setWeapon(Weapon(1, 24, 8, 8, 0.8));
	e2->setHealth(3);
	e2->setSize(1.0);
	scene->addEnemy(e2);

	//* Enemigo 3 *//
	Enemy* e3 = new Enemy();
	e3->loadModel("enemy.obj");
	e3->setPosition(Vector3D((-1.2), (0.0), (32.5)));
	e3->setColor(Color((1.0), (0.0), (1.0)));

	// Ángulo de rotación en función de la posición del jugador
	float alpha3 = atan2(pl.getPosition().getX() - e3->getPosition().getX(), pl.getPosition().getZ() - e3->getPosition().getZ());
	alpha3 *= (180.0 / M_PI);

	e3->setOrientation(Vector3D((0.0), (alpha3), (0.0)));
	e3->setWeapon(Weapon(1, 24, 8, 8, 0.5));
	e3->setHealth(1);
	e3->setSize(1.0);
	scene->addEnemy(e3);

	//Reinicio de la semilla del programa para obtener el número aleatorio
	srand(time(NULL) * 5);

	//Cálculo del número de enemigos
	numberOfEnemies[scene->getId()] = (rand() % 3) + 1;

	//* Límites de la escena *//
	Cuboid* left = new Cuboid();
	left->setPosition(Vector3D(5.0f, 2.5f, -0.5f));
	left->setColor(Color(0.9f, 0.6f, 0.5f));
	left->setHeight(5.0);
	left->setLength(16.0);
	left->setWidth(1.0);
	left->setGravity(false);
	scene->addLimitScenario(left);

	Cuboid* left2 = new Cuboid();
	left2->setPosition(Vector3D(11.0f, 2.5f, 26.5f));
	left2->setColor(Color(0.9f, 0.6f, 0.5f));
	left2->setHeight(5.0);
	left2->setLength(6.0);
	left2->setWidth(1.0);
	left2->setGravity(false);
	scene->addLimitScenario(left2);

	Cuboid* left3 = new Cuboid();
	left3->setPosition(Vector3D(-1.0f, 2.5f, 26.5f));
	left3->setColor(Color(0.9f, 0.6f, 0.5f));
	left3->setHeight(5.0);
	left3->setLength(6.0);
	left3->setWidth(1.0);
	left3->setGravity(false);
	scene->addLimitScenario(left3);

	Cuboid* right = new Cuboid();
	right->setPosition(Vector3D(10.5f, 2.5f, 20.5f));
	right->setColor(Color(0.9f, 0.6f, 0.5f));
	right->setHeight(5.0);
	right->setLength(5.0);
	right->setWidth(1.0);
	right->setGravity(false);
	scene->addLimitScenario(right);

	Cuboid* right2 = new Cuboid();
	right2->setPosition(Vector3D(-0.5f, 2.5f, 20.5f));
	right2->setColor(Color(0.9f, 0.6f, 0.5f));
	right2->setHeight(5.0);
	right2->setLength(5.0);
	right2->setWidth(1.0);
	right2->setGravity(false);
	scene->addLimitScenario(right2);

	Cuboid* right3 = new Cuboid();
	right3->setPosition(Vector3D(5.0f, 2.5f, 35.5f));
	right3->setColor(Color(0.9f, 0.6f, 0.5f));
	right3->setHeight(5.0);
	right3->setLength(18.0);
	right3->setWidth(1.0);
	right3->setGravity(false);
	scene->addLimitScenario(right3);

	Cuboid* wall = new Cuboid();
	wall->setPosition(Vector3D(5.0f, 2.5f, 10.5f));
	wall->setColor(Color(0.4f, 0.2f, 0.1f));
	wall->setHeight(5.0);
	wall->setLength(8.0);
	wall->setWidth(1.0);
	wall->setGravity(false);
	scene->addLimitScenario(wall);

	Cuboid* wall2 = new Cuboid();
	wall2->setPosition(Vector3D(8.5f, 2.5f, 29.5f));
	wall2->setColor(Color(0.4f, 0.2f, 0.1f));
	wall2->setHeight(5.0);
	wall2->setLength(1.0);
	wall2->setWidth(5.0);
	wall2->setGravity(false);
	scene->addLimitScenario(wall2);

	Cuboid* wall3 = new Cuboid();
	wall3->setPosition(Vector3D(1.0f, 2.5f, 32.5f));
	wall3->setColor(Color(0.4f, 0.2f, 0.1f));
	wall3->setHeight(5.0);
	wall3->setLength(1.0);
	wall3->setWidth(5.0);
	wall3->setGravity(false);
	scene->addLimitScenario(wall3);

	Cuboid* floor = new Cuboid();
	floor->setPosition(Vector3D(5.0f, -0.5f, 10.0f));
	floor->setColor(Color(0.5f, 0.9f, 0.6f));
	floor->setHeight(1.0);
	floor->setLength(16.0);
	floor->setWidth(20.0);
	floor->setCanCollide(false);
	floor->setGravity(false);
	scene->addLimitScenario(floor);

	Cuboid* floor2 = new Cuboid();
	floor2->setPosition(Vector3D(5.0f, -0.5f, 23.5f));
	floor2->setColor(Color(0.5f, 0.9f, 0.6f));
	floor2->setHeight(1.0);
	floor2->setLength(6.5);
	floor2->setWidth(7.0);
	floor2->setCanCollide(false);
	floor2->setGravity(false);
	scene->addLimitScenario(floor2);

	Cuboid* floor3 = new Cuboid();
	floor3->setPosition(Vector3D(5.0f, -0.5f, 31.0f));
	floor3->setColor(Color(0.5f, 0.9f, 0.6f));
	floor3->setHeight(1.0);
	floor3->setLength(18.0);
	floor3->setWidth(8.0);
	floor3->setCanCollide(false);
	floor3->setGravity(false);
	scene->addLimitScenario(floor3);

	Cuboid* top = new Cuboid();
	top->setPosition(Vector3D(13.5f, 2.5f, 10.0f));
	top->setColor(Color(0.6, 0.5, 0.9));
	top->setHeight(5.0);
	top->setLength(1.0);
	top->setWidth(20.0);
	top->setGravity(false);
	scene->addLimitScenario(top);

	Cuboid* top2 = new Cuboid();
	top2->setPosition(Vector3D(8.5f, 2.5f, 23.5f));
	top2->setColor(Color(0.6, 0.5, 0.9));
	top2->setHeight(5.0);
	top2->setLength(1.0);
	top2->setWidth(5.0);
	top2->setGravity(false);
	scene->addLimitScenario(top2);

	Cuboid* top3 = new Cuboid();
	top3->setPosition(Vector3D(14.5f, 2.5f, 31.0f));
	top3->setColor(Color(0.6, 0.5, 0.9));
	top3->setHeight(5.0);
	top3->setLength(1.0);
	top3->setWidth(8.0);
	top3->setGravity(false);
	scene->addLimitScenario(top3);

	Cuboid* bottom = new Cuboid();
	bottom->setPosition(Vector3D(-3.5f, 2.5f, 10.0f));
	bottom->setColor(Color(0.6, 0.5, 0.9));
	bottom->setHeight(5.0);
	bottom->setLength(1.0);
	bottom->setWidth(20.0);
	bottom->setGravity(false);
	scene->addLimitScenario(bottom);

	Cuboid* bottom2 = new Cuboid();
	bottom2->setPosition(Vector3D(1.5f, 2.5f, 23.5f));
	bottom2->setColor(Color(0.6, 0.5, 0.9));
	bottom2->setHeight(5.0);
	bottom2->setLength(1.0);
	bottom2->setWidth(5.0);
	bottom2->setGravity(false);
	scene->addLimitScenario(bottom2);

	Cuboid* bottom3 = new Cuboid();
	bottom3->setPosition(Vector3D(-4.5f, 2.5f, 31.0f));
	bottom3->setColor(Color(0.6, 0.5, 0.9));
	bottom3->setHeight(5.0);
	bottom3->setLength(1.0);
	bottom3->setWidth(8.0);
	bottom3->setGravity(false);
	scene->addLimitScenario(bottom3);

	return scene;
}

//Creación del juego
void Game::create()
{
	//// MENÚ PRINCIPAL ////
	this->startGame();

	//// ESCENA 0 (Tutorial) ////
	//Creación escena
	Scene* scene0 = this->createScene();
	//Insertado de la escena en el array
	this->scenes.push_back(scene0);

	//// ESCENA 1 ////
	Scene* scene1 = this->createScene1();
    this->scenes.push_back(scene1);

	//// ESCENA 2 ////
	Scene* scene2 = this->createScene2();
	this->scenes.push_back(scene2);

	//// ESCENA 3 ////
	Scene* scene3 = this->createScene3();
	this->scenes.push_back(scene3);

	//Selección de la escena activa (0)
    this->activeScene = scene0;

	//Detención de los sonidos en reproducción
	PlaySound(NULL, NULL, SND_ASYNC);
}

//Comprobación de enemigos del escenario
void Game::checkScene() {
	//Si el número de enemigos es 0
	if (numberOfEnemies[this->activeScene->getId()] == 0)
		//La escena es completada
		this->activeScene->setCompleted(true);
}

//Renderizado
void Game::render()
{
	this->activeScene->render();
}

//Actualización
void Game::update()
{
	//Inicialización de la información en consola
	if (!initContext) {
		this->initConsole();
		initContext = true;
	}

	this->updateTimeGameplay();

	this->completedScene();
	
	this->activeScene->update(this->deltaTime);

	this->checkScene();

	this->endGame();
}

//Fin del juego
void Game::endGame() {
	//Victoria
	//Si se completan todas las escenas
	if (completedScenes == 4) {
		//Impresión en consola
		goToXY(0, 17);
		cout << "[SISTEMA] Enhorabuena! Has conseguido completar: Enter The Gungeon!" << endl;
		cout << "[SISTEMA] Guardando resumen de la partida..." << endl;

		//Guardado de datos en fichero
		this->saveDataOnFile();

		//Pausa del programa
		Sleep(1000);

		//Salida de la ejecución
		cout << "[SISTEMA] Gracias por jugar!" << endl;
		exit(0);
	}

	//Derrota
	//Si la salud llega a 0
	if (this->activeScene->getPlayer().getHealth() == 0) {
		//Reproducción de sonido de muerte del jugador
		PlaySound(TEXT("killPlayer.wav"), NULL, SND_ASYNC);

		//Impresión de información en consola
		goToXY(0, 17);
		cout << "[SISTEMA] Una pena! Los monstruos de la armazmorra te asesinaron!" << endl;
		cout << "[SISTEMA] Mas suerte a la proxima!" << endl;
		cout << "[SISTEMA] Guardando resumen de la partida..." << endl;

		//Guardado de datos de la partida en fichero
		this->saveDataOnFile();

		//Pausa de la ejecución
		Sleep(1000);

		//Salida de la ejecución
		cout << "[SISTEMA] Gracias por jugar!" << endl;
		exit(0);
	}
}