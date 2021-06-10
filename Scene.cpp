#define _USE_MATH_DEFINES

#include "Scene.h"
#include "Bullet.h"
#include "OtherFuncsAndVariables.h"

#include <math.h>
#include <Windows.h>
#include <MMSystem.h>
#include <fstream>

//// MÉTODOS CLASE SCENE ////
//* Constructor *//
Scene::Scene(const int& id, const bool& completed, const Vector3D& size, const Vector3D& cameraPos, const Vector3D& cameraOr, const Vector3D& gravity, const Player& p) {
	this->size = size;
	this->gravity = gravity;
	this->camera = FlyingCamera(0, cameraPos, cameraOr);
	this->p = p;
}

//* Getters *//
Vector3D Scene::getSize() const {
	return this->size;
}

Vector3D Scene::getGravity() const {
	return this->gravity;
}

FlyingCamera Scene::getCamera() const {
	return this->camera;
}

Player Scene::getPlayer() {
	return this->p;
}

vector<Enemy*> Scene::getEnemies() const {
	return this->enemies;
}

bool Scene::getCompleted() const {
	return this->completed;
}

int Scene::getId() const {
	return this->id;
}

//* Setters *//
void Scene::setCamera(FlyingCamera camera) {
	this->camera = camera;
}

void Scene::setPlayer(Player p) {
	this->p = p;
}

void Scene::setFirstPersonCamera(FlyingCamera fC) {
	this->camera = fC;
	this->cameras[1] = fC;
}

Player Scene::setNewPlayer(Vector3D pos) {
	//Creación de jugador auxiliar
	Player pAux;

	//Configuración de sus atributos
	pAux.setPosition(pos);
	pAux.setColor(this->p.getColor());
	pAux.setOrientation(Vector3D(0.0, 90.0, 0.0));
	pAux.setWeapon(this->p.getWeapon());
	pAux.setHealth(this->p.getHealth());
	pAux.setSize(this->p.getSize());
	pAux.setScore(this->p.getScore());
	pAux.setKills(this->p.getKills());

	//Devolución del jugador
	return pAux;
}

FlyingCamera Scene::setNewFirstPersonCamera(Vector3D pos) {
	//Cámara primera persona auxiliar
	FlyingCamera cAux;

	//Configuración de atributos
	cAux.setPosition(pos);
	cAux.setOrientation(Vector3D(0.0, 90.0, 0.0));
	cAux.setState('a');
	cAux.setId(1);

	//Devolución de la cámara
	return cAux;
}

void Scene::setId(int i) {
	this->id = i;
}

void Scene::setCompleted(bool c) {
	this->completed = c;
}

//* Edición de escena *//
//Inserción de cámara
void Scene::addCamera(FlyingCamera cam)
{
	this->cameras.push_back(cam);
}

//Inserción de límite del escenario
void Scene::addLimitScenario(Cuboid* obj)
{
	this->limitsScenario.push_back(obj);
}

//Inserción de bala
void Scene::addBullet(Bullet* b)
{
	this->bullets.push_back(b);
}

//Inserción de enemigo
void Scene::addEnemy(Enemy* e)
{
	this->enemies.push_back(e);
}

//Limpieza de escena
void Scene::clearScene()
{
	this->cameras.clear();
	this->limitsScenario.clear();
	this->bullets.clear();
	this->enemies.clear();
}

//* Movimiento *//
void Scene::processMouseMovement(const int& x, const int& y)
{
	this->camera.processMouseMovement(x, y);
	this->cameras[1].processMouseMovement(x, y);
	this->p.processMouseMovement(x, y);
}

void Scene::processMouseClick(const int& button, const int& state, const int& x, const int& y)
{
	this->camera.processMouseClick(button, state, x, y);
	this->cameras[1].processMouseClick(button, state, x, y);
	this->p.processMouseClick(button, state, x, y);
}

//Movimiento del jugador
void Scene::playerMovement(unsigned char key, int px, int py) {
	//Almacenamiento de la antigua posición
	Vector3D oldPos = this->p.getPosition();

	//Actualización de la posición
	this->p.processKeyPressed(key, px, py);

	//Caras del jugador
	float xP = this->p.getPosition().getX() + this->p.getSize();
	float zP = this->p.getPosition().getZ() + this->p.getSize();
	float xM = this->p.getPosition().getX() - this->p.getSize();
	float zM = this->p.getPosition().getZ() - this->p.getSize();

	//Recorrido del array de límites
	for (int idxL = 0; idxL < this->limitsScenario.size(); idxL++)
	{
		//Si el límite tiene colisiones
		if (this->limitsScenario[idxL]->getCanCollide()) {
			//Caras del límite
			float limitsXP = this->limitsScenario[idxL]->getPosition().getX() + (this->limitsScenario[idxL]->getLength() / 2.0) - 0.3;
			float limitsZP = this->limitsScenario[idxL]->getPosition().getZ() + (this->limitsScenario[idxL]->getWidth() / 2.0) - 0.3;
			float limitsXM = this->limitsScenario[idxL]->getPosition().getX() - (this->limitsScenario[idxL]->getLength() / 2.0) + 0.3;
			float limitsZM = this->limitsScenario[idxL]->getPosition().getZ() - (this->limitsScenario[idxL]->getWidth() / 2.0) + 0.3;

			//Colisión
			if (xM < limitsXP && zM < limitsZP && xP > limitsXM && zP > limitsZM) {
				//Corrección de la posición
				this->p.setPosition(oldPos);
			}
		}
	}
}

//Movimiento de la cámara actual
void Scene::cameraMovement(unsigned char key, int px, int py) {
	//Almacenamiento de la antigua posición
	Vector3D oldPos = this->camera.getPosition();

	//Actualización de la posición
	//Si es la correspondiente a la primera persona
	if (this->camera.getId() == 1) {
		this->camera.processKeyPressed(key, px, py);
	}
	//Si es la cenital y tiene estado m
	else if (this->camera.getId() == 0 && this->camera.getState() == 'm') {
		//Si se pulsa alguna tecla de movimiento
		if (key == 'W' || key == 'w' || key == 'S' || key == 's' || key == 'A' || key == 'a' || key == 'D' || key == 'd') {
			//Guardado de las nuevas posiciones
			float newX = this->p.getPosition().getX();
			float newY = this->camera.getPosition().getY();
			float newZ = this->p.getPosition().getZ();

			//Actualización de la posición de la cámara
			this->camera.setPosition(Vector3D(newX, newY, newZ));
		}
	}

	//Posición de la cámara
	float xP = this->camera.getPosition().getX() + this->p.getSize();
	float zP = this->camera.getPosition().getZ() + this->p.getSize();
	float xM = this->camera.getPosition().getX() - this->p.getSize();
	float zM = this->camera.getPosition().getZ() - this->p.getSize();

	//Recorrido del array de límites
	for (int idxL = 0; idxL < this->limitsScenario.size(); idxL++)
	{
		//Si el límite tiene colisiones
		if (this->limitsScenario[idxL]->getCanCollide()) {
			//Caras del límite
			float limitsXP = this->limitsScenario[idxL]->getPosition().getX() + (this->limitsScenario[idxL]->getLength() / 2.0) - 0.3;
			float limitsZP = this->limitsScenario[idxL]->getPosition().getZ() + (this->limitsScenario[idxL]->getWidth() / 2.0) - 0.3;
			float limitsXM = this->limitsScenario[idxL]->getPosition().getX() - (this->limitsScenario[idxL]->getLength() / 2.0) + 0.3;
			float limitsZM = this->limitsScenario[idxL]->getPosition().getZ() - (this->limitsScenario[idxL]->getWidth() / 2.0) + 0.3;

			//Colisión
			if (xM < limitsXP && zM < limitsZP && xP > limitsXM && zP > limitsZM) {
				//Corrección de la posición
				this->camera.setPosition(oldPos);
			}
		}
	}
}

//Movimiento de la cámara de primera persona
void Scene::firstPersonCameraMovement(unsigned char key, int px, int py) {
	//Almacenamiento de la antigua posición
	Vector3D oldPos = this->cameras[1].getPosition();

	//Actualización de la posición
	this->cameras[1].processKeyPressed(key, px, py);

	//Posición de la cámara
	float xP = this->cameras[1].getPosition().getX() + this->p.getSize();
	float zP = this->cameras[1].getPosition().getZ() + this->p.getSize();
	float xM = this->cameras[1].getPosition().getX() - this->p.getSize();
	float zM = this->cameras[1].getPosition().getZ() - this->p.getSize();

	//Recorrido del array de límites
	for (int idxL = 0; idxL < this->limitsScenario.size(); idxL++)
	{
		//Si el límite tiene colisiones
		if (this->limitsScenario[idxL]->getCanCollide()) {
			//Caras del límite
			float limitsXP = this->limitsScenario[idxL]->getPosition().getX() + (this->limitsScenario[idxL]->getLength() / 2.0) - 0.3;
			float limitsZP = this->limitsScenario[idxL]->getPosition().getZ() + (this->limitsScenario[idxL]->getWidth() / 2.0) - 0.3;
			float limitsXM = this->limitsScenario[idxL]->getPosition().getX() - (this->limitsScenario[idxL]->getLength() / 2.0) + 0.3;
			float limitsZM = this->limitsScenario[idxL]->getPosition().getZ() - (this->limitsScenario[idxL]->getWidth() / 2.0) + 0.3;

			//Colisión
			if (xM < limitsXP && zM < limitsZP && xP > limitsXM && zP > limitsZM) {
				//Corrección de la posición
				this->cameras[1].setPosition(oldPos);
			}
		}
	}
}

//Movimiento de la cámara cenital
void Scene::upperCameraMovement(unsigned char key, int px, int py) {
	//Almacenamiento de la antigua posición
	Vector3D oldPos = this->cameras[0].getPosition();

	//Actualización de la posición
	if (key == 'W' || key == 'w' || key == 'S' || key == 's' || key == 'A' || key == 'a' || key == 'D' || key == 'd') {
		//Guardado de las nuevas posiciones
		float newX = this->p.getPosition().getX();
		float newY = this->cameras[0].getPosition().getY();
		float newZ = this->p.getPosition().getZ();

		//Actualización de la posición
		this->cameras[0].setPosition(Vector3D(newX, newY, newZ));
	}

	//Posición de la cámara
	float xP = this->cameras[0].getPosition().getX() + this->p.getSize();
	float zP = this->cameras[0].getPosition().getZ() + this->p.getSize();
	float xM = this->cameras[0].getPosition().getX() - this->p.getSize();
	float zM = this->cameras[0].getPosition().getZ() - this->p.getSize();

	//Recorrido del array de límites
	for (int idxL = 0; idxL < this->limitsScenario.size(); idxL++)
	{
		//Si el límite tiene colisiones
		if (this->limitsScenario[idxL]->getCanCollide()) {
			//Caras del límite
			float limitsXP = this->limitsScenario[idxL]->getPosition().getX() + (this->limitsScenario[idxL]->getLength() / 2.0) - 0.3;
			float limitsZP = this->limitsScenario[idxL]->getPosition().getZ() + (this->limitsScenario[idxL]->getWidth() / 2.0) - 0.3;
			float limitsXM = this->limitsScenario[idxL]->getPosition().getX() - (this->limitsScenario[idxL]->getLength() / 2.0) + 0.3;
			float limitsZM = this->limitsScenario[idxL]->getPosition().getZ() - (this->limitsScenario[idxL]->getWidth() / 2.0) + 0.3;

			//Colisión
			if (xM < limitsXP && zM < limitsZP && xP > limitsXM && zP > limitsZM) {
				//Corrección de la posición
				this->cameras[0].setPosition(oldPos);
			}
		}
	}
}

void Scene::processKeyPressed(unsigned char key, int px, int py)
{
	//Variables
	Bullet* pointerBullet = nullptr;	//Puntero a bala
	int indx = 0;						//Índice auxiliar para las ids de cámara

	switch (key)
	{
	case 'c':
	case 'C':
		//Nueva id de cámara
		indx = (this->camera.getId()) + 1;

		//Si es mayor al máximo índice permitido
		if (indx == cameras.size()) {
			//Índice inicial
			indx = 0;
		}

		//Actualización a la nueva cámara
		this->setCamera(cameras[indx]);
		break;
	case 32:
		//Si se ha podido disparar
		if (p.shoot()) {
			//Cálculo de la velocidad de la pelota en función de la orientación del jugador
			float xSpeed = (sin(p.getOrientation().getY() * M_PI / 180)) / 2;
			float zSpeed = (cos(p.getOrientation().getY() * M_PI / 180)) / 2;
			float xPos = xSpeed * 2;
			float zPos = zSpeed * 2;

			//Creaciçon de la bala
			pointerBullet = new Bullet(
				Vector3D((p.getPosition().getX() + xPos), (p.getPosition().getY()), (p.getPosition().getZ() + zPos)),
				Color((0.8), (0.7), (0.2)),
				Vector3D((xSpeed), (0.0), (zSpeed)),
				Vector3D(),
				0.2, 20, 20
			);

			//Selección de la ID de la pelota
			pointerBullet->setId('p');

			//Insertado de la bala en el array
			this->addBullet(pointerBullet);
		}

	default:
		this->playerMovement(key, px, py);
		this->cameraMovement(key, px, py);
		this->firstPersonCameraMovement(key, px, py);
		if (this->cameras[0].getState() == 'm')
			this->upperCameraMovement(key, px, py);
		break;
	}

}

//* Colisiones *//
//Colisiones con los límites
void Scene::collisionWithLimits(int& i, float& xP, float& zP, float& xM, float& zM)
{
	//Variables
	bool checkedCollision = false;		//Booleano para almacenar si se comprobó la colisión

	//Bucle para recorrer el array de límites
	for (int idxL = 0; idxL < this->limitsScenario.size(); idxL++)
	{
		//Si el límite tiene colisiones
		if (this->limitsScenario[idxL]->getCanCollide()) {
			//Caras del límite
			float limitsXP = this->limitsScenario[idxL]->getPosition().getX() + (this->limitsScenario[idxL]->getLength() / 2.0);
			float limitsZP = this->limitsScenario[idxL]->getPosition().getZ() + (this->limitsScenario[idxL]->getWidth() / 2.0);
			float limitsXM = this->limitsScenario[idxL]->getPosition().getX() - (this->limitsScenario[idxL]->getLength() / 2.0);
			float limitsZM = this->limitsScenario[idxL]->getPosition().getZ() - (this->limitsScenario[idxL]->getWidth() / 2.0);

			//Colisión
			if (!checkedCollision) {
				if (xM < limitsXP && zM < limitsZP && xP > limitsXM && zP > limitsZM) {
					//Borrado de la bala
					this->bullets.erase(this->bullets.begin() + i);

					//Se comprobó la colisión
					checkedCollision = true;
				}
			}
		}
	}
}

//Colisiones con el jugador
void Scene::collisionWithPlayer(int& i, float& xP, float& zP, float& xM, float& zM)
{
	//Caras del jugador
	float playersXP = this->p.getPosition().getX() + this->p.getSize() / 2.0;
	float playersZP = this->p.getPosition().getZ() + this->p.getSize() / 2.0;
	float playersXM = this->p.getPosition().getX() - this->p.getSize() / 2.0;
	float playersZM = this->p.getPosition().getZ() - this->p.getSize() / 2.0;

	//Colisión
	if (xM < playersXP && zM < playersZP && xP > playersXM && zP > playersZM) {
		//Borrado de la bala
		this->bullets.erase(this->bullets.begin() + i);

		//Modificación de los puntos y salud
		this->p.setScore(this->p.getScore() - 5);
		this->p.setHealth(this->p.getHealth() - 1);

		//Modificación de la consola
		goToXY(10, 11);
		cout << this->p.getScore() << " " << " ";

		goToXY(8 + this->p.getHealth(), 9);
		cout << " ";
	}
}

//Colisiones con enemigos
void Scene::collisionWithEnemies(int& i, float& xP, float& zP, float& xM, float& zM)
{
	//Recorrido del array
	for (int idxE = 0; idxE < numberOfEnemies[this->id]; idxE++)
	{
		//Caras de los enemigos
		float enemyXP = this->enemies[idxE]->getPosition().getX() + this->enemies[idxE]->getSize() / 2.0;
		float enemyZP = this->enemies[idxE]->getPosition().getZ() + this->enemies[idxE]->getSize() / 2.0;
		float enemyXM = this->enemies[idxE]->getPosition().getX() - this->enemies[idxE]->getSize() / 2.0;
		float enemyZM = this->enemies[idxE]->getPosition().getZ() - this->enemies[idxE]->getSize() / 2.0;

		//Colisión
		if (xM < enemyXP && zM < enemyZP && xP > enemyXM && zP > enemyZM) {
			//Eliminación de la bala
			this->bullets.erase(this->bullets.begin() + i);

			//Modificación de la salud del enemigo
			this->enemies[idxE]->setHealth(this->enemies[idxE]->getHealth() - 1);

			//Si la salud llega a 0
			if (this->enemies[idxE]->getHealth() == 0) {
				//Eliminación del enemigo
				this->enemies.erase(this->enemies.begin() + idxE);

				//Modificación de valores de jugador
				this->p.setScore(this->p.getScore() + 100);
				this->p.setKills(this->p.getKills() + 1);

				//Modificación de la consola
				goToXY(10, 11);
				cout << this->p.getScore() << " ";

				numberOfEnemies[this->id]--;
				goToXY(12, 14);
				cout << numberOfEnemies[this->id];

				//Reproducción de sonido
				PlaySound(TEXT("killEnemy.wav"), NULL, SND_ASYNC);
			}
		}
	}
}

//* Otros *//
//Renderizado
void Scene::render()
{
	//Renderizado de la cámara y del jugador
	this->camera.render();
	this->p.render();

	//Renderizado de los límites
	for (int idx = 0; idx < this->limitsScenario.size(); idx++)
	{
		this->limitsScenario[idx]->render();
	}

	//Renderizado de las balas
	for (int idx = 0; idx < this->bullets.size(); idx++)
	{
		this->bullets[idx]->render();
	}

	//Renderizado de los enemigos
	for (int idx = 0; idx < numberOfEnemies[this->id]; idx++)
	{
		this->enemies[idx]->render();
	}
}

//Actualización límites
void Scene::updateLimits(const float& deltaTime)
{
	for (int idx = 0; idx < this->limitsScenario.size(); idx++)
	{
		this->limitsScenario[idx]->update(deltaTime, this->gravity);
	}
}

//Actualización balas
void Scene::updateBullets(const float& deltaTime)
{
	for (int idx = 0; idx < this->bullets.size(); idx++)
	{
		//Actualización de la bala
		this->bullets[idx]->update(deltaTime, this->gravity);

		//Obtención de la ID de la bala
		char id = this->bullets[idx]->getId();

		//Cálculo de las caras de la bala
		float bulletXP = this->bullets[idx]->getPosition().getX() + this->bullets[idx]->getRadius();
		float bulletZP = this->bullets[idx]->getPosition().getZ() + this->bullets[idx]->getRadius();
		float bulletXM = this->bullets[idx]->getPosition().getX() - this->bullets[idx]->getRadius();
		float bulletZM = this->bullets[idx]->getPosition().getZ() - this->bullets[idx]->getRadius();

		//Comprobación de la colisión con límites
		this->collisionWithLimits(idx, bulletXP, bulletZP, bulletXM, bulletZM);

		//Comprobación de colisión según su ID
		if (id == 'e')
			//Con jugador
			this->collisionWithPlayer(idx, bulletXP, bulletZP, bulletXM, bulletZM);

		if (id == 'p')
			//Con enemigo
			this->collisionWithEnemies(idx, bulletXP, bulletZP, bulletXM, bulletZM);
	}
}

//Actualización enemigos
void Scene::updateEnemies(const float& deltaTime)
{
	for (int idx = 0; idx < numberOfEnemies[this->id]; idx++)
	{
		//Actualización del enemigo
		this->enemies[idx]->update(deltaTime, this->p.getPosition());

		//* Simulación de disparo del enemigo*//
		//Cálculo de las velocidades de la bala
		float xSpeed = (sin(this->enemies[idx]->getOrientation().getY() * M_PI / 180)) / 2;
		float zSpeed = (cos(this->enemies[idx]->getOrientation().getY() * M_PI / 180)) / 2;
		float xPos = xSpeed * 2;
		float zPos = zSpeed * 2;

		//Disminución de la variable contador según la cadencia para simular disparo
		cont[idx] -= this->enemies[idx]->getWeapon().getCadence();

		//Si el contador llega a 0
		if (cont[idx] <= 0) {
			//Creación de la bala
			Bullet* pointerBullet = nullptr;
			pointerBullet = new Bullet(
				Vector3D((this->enemies[idx]->getPosition().getX() + xPos), (this->enemies[idx]->getPosition().getY() + 1.0), (this->enemies[idx]->getPosition().getZ() + zPos)),
				Color((0.8), (0.2), (0.2)),
				Vector3D((xSpeed), (0.0), (zSpeed)),
				Vector3D(),
				0.2, 20, 20
			);

			//Selección de ID de la bala
			pointerBullet->setId('e');

			//Inserción de la bala en el array
			this->addBullet(pointerBullet);

			//Reproducción de sonido de disparo
			PlaySound(TEXT("shoot.wav"), NULL, SND_ASYNC);

			//Reinicio de variable contador
			cont[idx] = 100.0;
		}
	}
}

//Actualización
void Scene::update(const float& deltaTime)
{
	this->updateLimits(deltaTime);

	this->updateBullets(deltaTime);

	this->updateEnemies(deltaTime);
}

