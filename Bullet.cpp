#include "Bullet.h"
#include <GL/glut.h>

//// MÉTODOS CLASE BULLET ////
//* Constructores *//
Bullet::Bullet() : Sphere() {

}

Bullet::Bullet(const Vector3D& position, const Color& color, const Vector3D& speed,
	const Vector3D& orientation, float radius, int slices, int stacks)
	: Sphere(position, color, speed, orientation, radius, slices, stacks) {}

//* Getters *//
char Bullet::getId() const {
	return this->id;
}

//* Setters *//
void Bullet::setId(const char i) {
	this->id = i;
}

//* Otros *//
//Renderizado
void Bullet::render() const {
	glPushMatrix();
	glTranslatef(getPosition().getX(), getPosition().getY(), getPosition().getZ());
	glColor3f(getColor().getRed(), getColor().getGreen(), getColor().getBlue());
	glRotatef(getOrientation().getX(), 1.0, 0.0, 0.0);
	glRotatef(getOrientation().getY(), 0.0, 1.0, 0.0);
	glRotatef(getOrientation().getZ(), 0.0, 0.0, 1.0);
	glutSolidSphere(this->getRadius(), this->getSlices(), this->getStacks());
	glPopMatrix();
}

//Actualización
void Bullet::update(const float& deltaTime, const Vector3D& gravity) {
	this->setPosition(Vector3D(this->getPosition() + this->getSpeed() * deltaTime));
}