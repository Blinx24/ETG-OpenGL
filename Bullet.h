#ifndef ENGINE_BULLET_H
#define ENGINE_BULLET_H

#include "Vector3D.h"
#include "Color.h"
#include "GameObject.h"
#include "Sphere.h"

///////////////////////////////////////////////////////////////////////////
// CLASE BULLET //
class Bullet : public Sphere {
private:
	char id;		//ID de la bala
public:
	//Constructores
	Bullet();
    Bullet(const Vector3D& position, const Color& color, const Vector3D& speed,
		const Vector3D& orientation, float radius, int slices, int stacks);

	//Getters
	char getId() const;

	//Setters
	void setId(const char i);

	//Otros métodos
    void render() const;
    void update(const float &deltaTime, const Vector3D& direction);
};


#endif //ENGINE_BULLET_H
