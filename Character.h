#pragma once
#include "Weapon.h"
#include "Model.h"

///////////////////////////////////////////////////////////////////////////
// CLASE CHARACTER //
class Character : public Model{
private:
	int health;			//Salud
	Weapon weapon;		//Arma
	float size;			//Tamaño

public:
	//Constructores
	Character();
	Character(const Vector3D& position, const Color& color, const Vector3D& speed,
		const Vector3D& orientation, int health, Weapon& weapon, float size);

	//Getters
	int getHealth() const;
	Weapon getWeapon();
	float getSize() const;

	//Setters
	void setHealth(int h);
	void setWeapon(const Weapon& w);
	void setSize(const float& s);

	//Métodos del arma
	bool shoot();
	void reload();

	//Otros métodos
	//virtual void render() const = 0;
	//virtual void update() const;
};
