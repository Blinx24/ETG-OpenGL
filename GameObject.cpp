//
// Created by rcabido on 7/11/19.
//
#include "GameObject.h"

//// MÉTODOS CLASE GAMEOBJECT ////
//* Constructores *//
GameObject::GameObject() {
	this->position = Vector3D();
	this->color = Color();
	this->speed = Vector3D();
	this->orientation = Vector3D();
	this->rotationSpeed = Vector3D();
	this->gravity = true;
}

GameObject::GameObject(const Vector3D& position, const Color& color, const Vector3D& speed, const Vector3D& orientation, const Vector3D& rotationSpeed, bool gravity) {
	this->position = position;
	this->color = color;
	this->speed = speed;
	this->orientation = orientation;
	this->rotationSpeed = rotationSpeed;
	this->gravity = gravity;
}

//* Getters *//
Vector3D GameObject::getPosition() const {
	return this->position;
}

Color GameObject::getColor() const {
	return this->color;
}

Vector3D GameObject::getSpeed() const {
	return this->speed;
}

Vector3D GameObject::getOrientation() const {
	return this->orientation;
}

Vector3D GameObject::getRotationSpeed() const {
	return this->rotationSpeed;
}

bool GameObject::getGravity() const {
	return this->gravity; 
}

//* Setters *//
void GameObject::setPosition(const Vector3D& pos) {
	this->position = pos; 
}

void GameObject::setColor(const Color& color) { 
	this->color = color; 
}

void GameObject::setSpeed(const Vector3D& speed) { 
	this->speed = speed; 
}

void GameObject::setOrientation(const Vector3D& orientation) { 
	this->orientation = orientation; 
}

void GameObject::setRotationSpeed(const Vector3D& rSpeed) { 
	this->rotationSpeed = rSpeed; 
}

void GameObject::setGravity(const bool& gravity) { 
	this->gravity = gravity; 
}

//* Otros *//
//Actualización
void GameObject::update(const float& time, const Vector3D& gravity)
{
    if (this->getGravity())
    {
        this->setSpeed(Vector3D(this->getSpeed() + gravity * time));
    }
    this->setPosition(Vector3D(this->getPosition() + this->getSpeed() * time));
    this->setOrientation(
            Vector3D(
                    this->getOrientation().getX() + time * this->getRotationSpeed().getX(),
                    this->getOrientation().getY() + time * this->getRotationSpeed().getY(),
                    this->getOrientation().getZ() + time * this->getRotationSpeed().getZ()
            )
    );
}