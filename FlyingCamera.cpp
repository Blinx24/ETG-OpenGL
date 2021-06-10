#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "FlyingCamera.h"
#include <GL/glut.h>

//// MÉTODOS CLASE FLYINGCAMERA ////
//* Constructores *//
FlyingCamera::FlyingCamera() {
	Camera();
	this->mouseX = 0;
	this->mouseY = 0;
	this->state = false;
}

FlyingCamera::FlyingCamera(int id, const Vector3D& pos, const Vector3D& orientation) {
	Camera(id, pos, orientation);
}

FlyingCamera::FlyingCamera(int id, float& x, float& y, float& z) {
	Camera(id, x, y, z);
	this->mouseX = 0;
	this->mouseY = 0;
	this->state = false;
}

//* Getters *//
inline float FlyingCamera::getMouseX() const { 
	return this->mouseX; 
}

inline float FlyingCamera::getMouseY() const { 
	return this->mouseY; 
}

char FlyingCamera::getState() const {
	return this->state;
}

//* Setters *//
inline void FlyingCamera::setMouseY(const int& mouseY) { 
	this->mouseY = mouseY; 
}

inline void FlyingCamera::setMouseX(const int& mouseX) { 
	this->mouseX = mouseX; 
}

void FlyingCamera::setState(const char c) {
	this->state = c;
}

//* Movimiento *//
void FlyingCamera::processMouseMovement(const int& x, const int& y) 
{
	if (this->state == 'a') {
		this->setOrientation(this->getOrientation() + Vector3D(0.0, x - this->getMouseX(), 0.0));
		this->setMouseX(x);
		this->setMouseY(y);
	}

}

void FlyingCamera::processMouseClick(const int& button, const int& state, const int& x, const int& y)
{
	if (this->state == 'a') {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			this->setMouseX(x);
			this->setMouseY(y);
		}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			this->setMouseX(0);
			this->setMouseY(0);
		}
	}
}

void FlyingCamera::processKeyPressed(unsigned char key, int px, int py)
{
	if (this->state == 'a') {
		switch (key) {
		case 'w':
		case 'W':
			this->update(0.1, Vector3D(1.0, 0.0, 0.0));
			break;
		case 's':
		case 'S':
			this->update(-0.1, Vector3D(1.0, 0.0, 0.0));
			break;
		case 'd':
		case 'D':
			this->update(-0.1, Vector3D(0.0, 0.0, 1.0));
			break;
		case 'a':
		case 'A':
			this->update(0.1, Vector3D(0.0, 0.0, 1.0));
			break;
		}
	}
}

//* Otros *//
//Renderizado
void FlyingCamera::render() {
	glRotatef(getOrientation().getX(), 1.0, 0.0, 0.0);
	glRotatef(getOrientation().getY(), 0.0, 1.0, 0.0);
	glRotatef(getOrientation().getZ(), 0.0, 0.0, 1.0);
	glTranslatef(-this->getPosition().getX(), -this->getPosition().getY(), -this->getPosition().getZ());
}

//Actualización
void FlyingCamera::update(const float& time, const Vector3D& direction)
{
	//Cálculo de los nuevos ejes en función de la orientación
	float yOrientationInRadians = this->getOrientation().getY() * M_PI / 180;
	float xOrientationInRadians = this->getOrientation().getX() * M_PI / 180;
	float xComponent = -cos(xOrientationInRadians) * sin(yOrientationInRadians);
	float yComponent = sin(xOrientationInRadians);
	float zComponent = cos(xOrientationInRadians) * cos(yOrientationInRadians);
	Vector3D velocity(xComponent, yComponent, zComponent);

	//Si se mueve en el eje X
	if (direction.getX() == 1.0) {
		this->setPosition(this->getPosition() - velocity * time);
	}
	//Si se mueve en otro eje (Z)
	else {
		velocity = Vector3D(zComponent, yComponent, -xComponent);
		this->setPosition(this->getPosition() - velocity * time);
	}
}



