//
// Created by rcabido on 7/11/19.
//

#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include "Vector3D.h"
#include "GameObject.h"

///////////////////////////////////////////////////////////////////////////
// CLASE CAMERA //
class Camera: public GameObject {
private:
	int id;		//ID de la cámara

public:
	//Constructores
    Camera();
    Camera(int id, const Vector3D &positionToSet, const Vector3D &orientationToSet);
    Camera(int id, float x, float y, float z);

	//Getters
	int getId() const;

	//Setters
	void setId(const int id);

	//Otros métodos
    void render() const;
    void update(const float &deltaTime,  const Vector3D& direction);
};

#endif //ENGINE_CAMERA_H
