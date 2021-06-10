#ifndef ENGINE_HERENCIA_WEAPON_H
#define ENGINE_HERENCIA_WEAPON_H

#include "GameObject.h"

class Weapon : public GameObject {
private:
	int damage;					//Daño del arma
	int cylinderSize;			//Tamaño del cilindro
	int ammunition;				//Munición
	int initialAmmunition;		//Munición inicial
	float cadence;				//Cadencia

public:
	//Constructores
	Weapon();
	Weapon(int damage, int cylinderSize, int ammunition, int initialAmmunition, float cadence);
	Weapon(const Vector3D& position, const Color& color, const Vector3D& speed, const Vector3D& orientation,
		int damage, int cylinderSize, int ammunition, int initialAmmunition, float cadence);

	//Getters
	int getDamage() const;
	int getCylinderSize() const;
	int getAmmunition() const;
	int getInitialAmmunition() const;
	float getCadence() const;

	//Setters
	void setDamage(const int& d);
	void setCylinderSize(const int cS);
	void setAmmunition(const int a);
	void setInitialAmmunition(const int& iA);
	void setCadence(const float& c);

	//Otros métodos
	void render() const;
	void update();
};

#endif //ENGINE_HERENCIA_WEAPON_H
