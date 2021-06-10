#define _USE_MATH_DEFINES

#include "Enemy.h"
#include <GL/glut.h>
#include <math.h>

//// MÉTODOS CLASE ENEMY ////
//* Constructores *//
Enemy::Enemy() : Character() {

}

Enemy::Enemy(const Vector3D& position, const Vector3D& speed, const Color& color, const Vector3D& orientation,
	int health, int size, Weapon& weapon)
	: Character(position, color, speed, orientation, health, weapon, size) {

}

//* Otros *//
//Actualización
void Enemy::update(const float& time, const Vector3D& playerPos)  {
	//Cálculo del ángulo a rotar en función de la posición del jugador
	float alpha = atan2(playerPos.getX()-this->getPosition().getX(), playerPos.getZ() - this->getPosition().getZ());
	alpha *= (180 / M_PI);
	
	//Actualización de la orientación
	this->setOrientation(Vector3D((0.0), (alpha), (0.0)));
}