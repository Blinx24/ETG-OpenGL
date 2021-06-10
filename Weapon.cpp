#include "Weapon.h"
#include "GameObject.h"

//// MÉTODOS CLASE WEAPON ////
//* Constructores *//
Weapon::Weapon() : GameObject() {
	this->damage = 0;
	this->cylinderSize = 0;
	this->ammunition = 0;
	this->initialAmmunition = 0;
	this->cadence = 0.0;
}

Weapon::Weapon(int damage, int cylinderSize, int ammunition, int initialAmmunition, float cadence) : GameObject() {
	this->damage = damage;
	this->cylinderSize = cylinderSize;
	this->ammunition = ammunition;
	this->initialAmmunition = initialAmmunition;
	this->cadence = cadence;
}

Weapon::Weapon(const Vector3D& position, const Color& color, const Vector3D& speed, const Vector3D& orientation,
	int damage, int cylinderSize, int ammunition, int initialAmmunition, float cadence)
	: GameObject(position, color, speed, orientation, Vector3D(), false) {
	this->damage = damage;
	this->cylinderSize = cylinderSize;
	this->ammunition = ammunition;
	this->initialAmmunition = initialAmmunition;
	this->cadence = cadence;
}

//* Getters *//
int Weapon::getDamage() const {
	return this->damage;
}

int Weapon::getCylinderSize() const {
	return this->cylinderSize;
}

int Weapon::getAmmunition() const {
	return this->ammunition;
}

int Weapon::getInitialAmmunition() const {
	return this->initialAmmunition;
}

float Weapon::getCadence() const {
	return this->cadence;
}

//* Setters *//
void Weapon::setDamage(const int& d) {
	this->damage = d;
}

void Weapon::setCylinderSize(const int cS) {
	this->cylinderSize = cS;
}

void Weapon::setAmmunition(const int a) {
	this->ammunition = a;
}

void Weapon::setInitialAmmunition(const int& iA) {
	this->ammunition = iA;
}

void Weapon::setCadence(const float& c) {
	this->cadence = c;
}

//* Otros *//
//Renderizado
void Weapon::render() const {

}