#define _USE_MATH_DEFINES

#include "Enemy.h"
#include <GL/glut.h>
#include <math.h>

//// M�TODOS CLASE ENEMY ////
//* Constructores *//
Enemy::Enemy() : Character() {

}

Enemy::Enemy(const Vector3D& position, const Vector3D& speed, const Color& color, const Vector3D& orientation,
	int health, int size, Weapon& weapon)
	: Character(position, color, speed, orientation, health, weapon, size) {

}

//* Otros *//
//Actualizaci�n
void Enemy::update(const float& time, const Vector3D& playerPos)  {
	//C�lculo del �ngulo a rotar en funci�n de la posici�n del jugador
	float alpha = atan2(playerPos.getX()-this->getPosition().getX(), playerPos.getZ() - this->getPosition().getZ());
	alpha *= (180 / M_PI);
	
	//Actualizaci�n de la orientaci�n
	this->setOrientation(Vector3D((0.0), (alpha), (0.0)));
}