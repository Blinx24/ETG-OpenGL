//
// Created by rcabido on 25/10/19.
//

#ifndef ENGINE_SPHERE_H
#define ENGINE_SPHERE_H

#include "Vector3D.h"
#include "Color.h"
#include "GameObject.h"

///////////////////////////////////////////////////////////////////////////
// CLASE SPHERE //
class Sphere : public GameObject {
private:
	float radius;		//Radio de la esfera
	int slices;			//Divisiones longitudinales
	int stacks;			//Divisiones latitudinales

public:
	//Constructores
	Sphere();
	Sphere(const Vector3D& position, const Color& color, const Vector3D& speed,
		const Vector3D& orientation, float radius, int slices, int stacks);

	//Getters
	float getRadius() const;
	int getSlices() const;
	int getStacks() const;

	//Otros métodos
	virtual void render() const = 0;
	//virtual void update(const float &deltaTime, const Vector3D& gravity) const = 0;
};

#endif //ENGINE_SPHERE_H