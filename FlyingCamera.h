#pragma once
#include "Camera.h"

///////////////////////////////////////////////////////////////////////////
// CLASE FLYINGCAMERA //
class FlyingCamera : public Camera {
private:
	int mouseX;			//Posición X del mouse
	int mouseY;			//Posición Y del mouse
	char state;			//Estado de la cámara (a - libre / f - fija / m - móvil)

public:
	//Constructores
	FlyingCamera();
	FlyingCamera(int id, const Vector3D& pos, const Vector3D& orientation);
	FlyingCamera(int id, float& x, float& y, float& z);

	//Getters
	inline float getMouseX() const;
	inline float getMouseY() const;
	char getState() const;

	//Setters
	inline void setMouseY(const int& mouseY);
	inline void setMouseX(const int& mouseX);
	void setState(const char c);

	//Métodos de movimiento
	void processMouseMovement(const int& x, const int& y);
	void processMouseClick(const int& button, const int& state, const int& x, const int& y);
	void processKeyPressed(unsigned char key, int px, int py);

	//Otros métodos
	void render();
	void update(const float& time, const Vector3D& direction) override;
};

