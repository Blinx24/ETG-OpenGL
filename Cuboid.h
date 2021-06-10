#pragma once
#include "GameObject.h"

///////////////////////////////////////////////////////////////////////////
// CLASE CUBOID //
class Cuboid : public GameObject {
private:
	float height;					//Dimensión en el eje y
	float length;					//Dimensión en el eje x
	float width;					//Dimensión en el eje z
	bool canCollide;				//Tiene colisiones
public:
	//Constructor
	Cuboid();

	//Getters
	inline float getHeight() const;
	inline float getLength() const;
	inline float getWidth() const;
	bool getCanCollide() const;

	//Setters
	inline void setHeight(const float& h) { this->height = h; }
	inline void setLength(const float& l) { this->length = l; }
	inline void setWidth(const float& w) { this->width = w; }
	void setCanCollide(const bool c);

	//Otros métodos
	void render() const;
};

