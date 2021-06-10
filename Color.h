//
// Created by rcabido on 7/11/19.
//
#ifndef ENGINE_COLOR_H
#define ENGINE_COLOR_H

///////////////////////////////////////////////////////////////////////////
// CLASE COLOR //
class Color {
private:
    float red;		//Rojo
    float green;	//Verde
    float blue;		//Azul
public:
	//Constructores
	Color();
	Color(float r, float g, float b);

	//Getters
	float getRed() const;
	float getGreen() const;
	float getBlue() const;

	//Setters
	void setRed(const float& r);
	void setGreen(const float& g);
	void setBlue(const float& b);
};

#endif //ENGINE_COLOR_H
