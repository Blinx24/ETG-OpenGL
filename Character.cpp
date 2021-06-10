#include "Character.h"
#include "OtherFuncsAndVariables.h"

#include <Windows.h>
#include <MMSystem.h>

//// M�TODOS CLASE CHARACTER ////
//* Constructores *//
Character::Character() : Model() {
	this->health = 0;
	this->weapon = Weapon();
	this->size = 0.0;
}

Character::Character(const Vector3D& position, const Color& color, const Vector3D& speed,
	const Vector3D& orientation, int health, Weapon& weapon, float size) 
	: Model(position, color, speed, orientation) {
	this->health = health;
	this->weapon = weapon;
	this->size = size;
}

//* Getters *//
int Character::getHealth() const {
	return this->health;
}

Weapon Character::getWeapon()  {
	return this->weapon;
}

float Character::getSize() const {
	return this->size;
}

//* Setters *//
void Character::setHealth(int h) {
	this->health = h;
}

void Character::setWeapon(const Weapon& w) {
	this->weapon = w;
}

void Character::setSize(const float& s) {
	this->size = s;
}

//* Arma *//
//Disparar
bool Character::shoot() {
	//Si no hay munici�n
	if (this->weapon.getAmmunition() == 0) {

		//Devoluci�n de false
		return 0;
	}

	//Actualizaci�n de las balas
	this->weapon.setAmmunition((this->weapon.getAmmunition()) - 1);

	//Actualizaci�n del color en consola en funci�n de las balas restantes
	if (this->weapon.getAmmunition() < 4) {
		changeColorConsole(4);
	}
	else {
		changeColorConsole(7);
	}

	//Impresi�n en la consola
	goToXY(12, 10);
	cout << this->weapon.getAmmunition();
	
	//Reproducci�n del sonido disparar
	PlaySound(TEXT("shoot.wav"), NULL, SND_ASYNC);

	//Devoluci�n de true
	return 1;
}

//Recargar
void Character::reload() {
	//Si el tama�o del cilindro es mayor de 0
	if (this->weapon.getCylinderSize() > 0) {
		//C�lculo de la cantidad a recargar
		int diffAmmo = this->weapon.getInitialAmmunition() - this->weapon.getAmmunition();
		
		//Actualizaci�n del cilindro
		this->weapon.setCylinderSize(this->weapon.getCylinderSize() - diffAmmo);
		
		//Si es menor que 0
		if (this->weapon.getCylinderSize() < 0) {
			//C�lculo de las balas restantes
			int d = 0 - this->weapon.getCylinderSize();

			//Actualizaci�n del cilindro
			this->weapon.setCylinderSize(0);

			//Actualizaci�n de las balas a recargar
			diffAmmo -= d;
		}

		//Actualizaci�n de las balas
		this->weapon.setAmmunition(this->weapon.getAmmunition() + diffAmmo);

		//Cambio del color en funci�n de las balas en el cilindro
		if (this->weapon.getCylinderSize() < 9 || this->weapon.getAmmunition() < 4) {
			changeColorConsole(4);
		}
		else {
			changeColorConsole(7);
		}

		//Impresi�n de datos en la consola
		goToXY(12,10);
		cout << this->weapon.getAmmunition();

		goToXY(16,10);
		cout << this->weapon.getCylinderSize() << " ";
		
		//Reproducci�n de sonido de recarga
		PlaySound(TEXT("reload.wav"), NULL, SND_ASYNC);
	} 
}

//* Otros *//
/*void Character::render() const {

}

void Character::update() {

}
*/
