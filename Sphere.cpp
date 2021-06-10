//
// Created by rcabido on 25/10/19.
//

#include "Sphere.h"
#include <GL/glut.h>

//// MÉTODOS CLASE SPHERE ////
//* Constructores *//
Sphere::Sphere() : GameObject() {
	this->radius = 0.0;
	this->slices = 0;
	this->stacks = 0;
}

Sphere::Sphere(const Vector3D& position, const Color& color, const Vector3D& speed, const Vector3D& orientation,
	float radius, int slices, int stacks) 
	: GameObject(position, color, speed, orientation, Vector3D(), true) {
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
}

//* Getters *//
float Sphere::getRadius() const {
	return this->radius;
}

int Sphere::getSlices() const {
	return this->slices;
}

int Sphere::getStacks() const {
	return this->stacks;
}