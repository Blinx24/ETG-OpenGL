//
// Created by rcabido on 7/11/19.
//
#ifndef ENGINE_GAME_H
#define ENGINE_GAME_H

#include "Scene.h"
#include "Bullet.h"
#include "OtherFuncsAndVariables.h"

///////////////////////////////////////////////////////////////////////////
// CLASE GAME //
class Game {
private:
	float t;						//Tiempo
	float deltaTime;				//Frames
	Scene* activeScene;				//Escena activa
	std::vector<Scene*> scenes;		//Vector de escenas

public:
	//Constructor
	Game();

	//Métodos de movimiento
    void processMouseMovement(const int& xPosition, const int& yPosition);
    void processKeyPressed(const unsigned char& key, const int& xPosition, const int& yPosition);
    void processMouseClick(const int& button, const int& state, const int& xPosition, const int& yPosition);

	//Métodos de ficheros
	void saveDataOnFile();
	void readAllDataFromFile();

	//Métodos de consola
	void initConsole();
	void updateTimeGameplay();
	void completedScene();

	//Otros métodos
	void startGame();
	Scene* createScene();
	Scene* createScene1();
	Scene* createScene2();
	Scene* createScene3();
	void create();
	void checkScene();
	void render();
	void update();
	void endGame();
};
#endif