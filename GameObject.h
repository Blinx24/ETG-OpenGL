//
// Created by rcabido on 7/11/19.
//

#ifndef ENGINE_GAMEOBJECT_H
#define ENGINE_GAMEOBJECT_H

#include <iostream>

#include "Vector3D.h"
#include "Color.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
// CLASE GAMEOBJECT //
class GameObject {
private:
    Vector3D position;			//Posición
    Color color;				//Color
    Vector3D speed;				//Velocidad
    Vector3D orientation;		//Orientación
    Vector3D rotationSpeed;		//Velocidad de rotación
    bool gravity;				//Gravedad
public:
	//Constructores
	GameObject();
	GameObject(const Vector3D& position, const Color& color, const Vector3D& speed, const Vector3D& orientation, const Vector3D& orientationSpeed, bool isAffectedByGravity);

	//Getters
	Vector3D getPosition() const;
	Color getColor() const;
	Vector3D getSpeed() const;
	Vector3D getOrientation() const;
	Vector3D getRotationSpeed() const;
	bool getGravity() const;

	//Setters
	void setPosition(const Vector3D& pos);
	void setColor(const Color& color);
	void setSpeed(const Vector3D& speed);
	void setOrientation(const Vector3D& orientation);
	void setRotationSpeed(const Vector3D& rSpeed);
	void setGravity(const bool& gravity);

	//Otros métodos
    virtual void render() const = 0;
    virtual void update(const float &deltaTime, const Vector3D& gravity);
};

#endif ENGINE_GAMEOBJECT_H
