#ifndef ENGINE_HERENCIA_ENEMY_H
#define ENGINE_HERENCIA_ENEMY_H

#include "Character.h"

class Enemy : public Character {
public:
	//Constructores
	Enemy();
	Enemy(const Vector3D& position, const Vector3D& speed, const Color& color, const Vector3D& orientation,
		int health, int size, Weapon& weapon);

	//Otros métodos
	//void render();
	void update(const float& time, const Vector3D& playerPos);
};
#endif //ENGINE_HERENCIA_ENEMY_H
