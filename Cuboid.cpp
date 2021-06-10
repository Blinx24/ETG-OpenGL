#include "Cuboid.h"
#include <GL/glut.h>

//// MÉTODOS CLASE CUBOID ////
//* Constructor *//
Cuboid::Cuboid() : GameObject() {
	this->height = 1.0;
	this->length = 2.0;
	this->width = 0.5;
	this->canCollide = true;
}

//* Getters *//
inline float Cuboid::getHeight() const { 
	return this->height; 
}

inline float Cuboid::getLength() const { 
	return this->length; 
}

inline float Cuboid::getWidth() const { 
	return this->width; 
}

bool Cuboid::getCanCollide() const {
	return this->canCollide;
}

//* Setters *//
void Cuboid::setCanCollide(const bool c) {
	this->canCollide = c;
}

//* Otros *//
//Renderizado
void Cuboid::render() const
{
	glPushMatrix();
	glTranslatef(this->getPosition().getX(), this->getPosition().getY(), this->getPosition().getZ());
	glRotatef(getOrientation().getX(), 1.0, 0.0, 0.0);
	glRotatef(getOrientation().getY(), 0.0, 1.0, 0.0);
	glRotatef(getOrientation().getZ(), 0.0, 0.0, 1.0);
	glColor3f(getColor().getRed(), getColor().getGreen(), getColor().getBlue());
	glScalef(getLength(), getHeight(), getWidth());
	glutSolidCube(1);
	glPopMatrix();
}

