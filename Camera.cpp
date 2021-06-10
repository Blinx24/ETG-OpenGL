//
// Created by rcabido on 7/11/19.
//

#include "Camera.h"
#include "GameObject.h"
#include <GL/glut.h>

//// MÉTODOS CLASE CAMERA ////
//* Constructores *//
Camera::Camera() : GameObject() {
	this->id = 0;
}

Camera::Camera(int id, const Vector3D &pos, const Vector3D &orientation) 
	: GameObject(pos, Color(), Vector3D(), orientation, Vector3D(), true) {
	this->id = id;
}


Camera::Camera(int id, float x, float y, float z) 
	: GameObject(Vector3D(x, y, z), Color(), Vector3D(), Vector3D(), Vector3D(), true) {
	this->id = id;
}

//* Getters *//
int Camera::getId() const {
	return this->id;
}

//* Setters *//
void Camera::setId(const int id) {
	this->id = id;
}

//* Otros *//
//Renderizado
void Camera::render() const {
    glTranslatef(-this->getPosition().getX(), -this->getPosition().getY(), -this->getPosition().getZ());
    glRotatef(getOrientation().getX(), 1.0, 0.0, 0.0);
    glRotatef(getOrientation().getY(), 0.0, 1.0, 0.0);
    glRotatef(getOrientation().getZ(), 0.0, 0.0, 1.0);
}

//Actualización
void Camera::update(const float &deltaTime, const Vector3D& gravity){

}
