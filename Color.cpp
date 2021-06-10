//
// Created by rcabido on 7/11/19.
//

#include "Color.h"

//// MÉTODOS CLASE COLOR ////
//* Constructores *//
Color::Color() {
	this->red = 0.0;
	this->green = 0.0;
	this->blue = 0.0;
}

Color::Color(float r, float g, float b) {
	this->red = r;
	this->green = g;
	this->blue = b;
}

//* Getters *//
float Color::getRed() const {
	return this->red;
}

float Color::getGreen() const {
	return this->green;
}

float Color::getBlue() const {
	return this->blue;
}

//* Setters *//
void Color::setRed(const float& r) {
	this->red = ((r >= 0.0 && r <= 1.0) ? r : this->red);
}

void Color::setGreen(const float& g) {
	this->green = ((g >= 0.0 && g <= 1.0) ? g : this->green);
}

void Color::setBlue(const float& b) {
	this->blue = ((b >= 0.0 && b <= 1.0) ? b : this->blue);
}