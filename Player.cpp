#define _USE_MATH_DEFINES
#include <math.h>
#include "Player.h"
#include <GL/glut.h>

//// MÉTODOS CLASE PLAYER ////
//* Constructores *//
Player::Player() : Character(){
	this->score = 0;
	this->mouseX = 0;
	this->mouseY = 0;
	this->kills = 0;
}

Player::Player(const Vector3D& position, const Color& color, const Vector3D& speed,
	const Vector3D& orientation, int health, Weapon& weapon, float size, int score)
	: Character(position, color, speed, orientation, health, weapon, size) {
	this->score = score;
}

//* Getters *//
int Player::getScore() const {
	return this->score;
}

float Player::getMouseX() const {
	return this->mouseX;
}

float Player::getMouseY() const {
	return this->mouseY;
}

int Player::getKills() const {
	return this->kills;
}

//* Setters *//
void Player::setScore(const int& s) {
	this->score = s;
}

void Player::setMouseY(const int& mouseY) {
	this->mouseY = mouseY;
}

void Player::setMouseX(const int& mouseX) {
	this->mouseX = mouseX;
}

void Player::setKills(const int& k) {
	this->kills = k;
}

//* Movimiento *//
void Player::processMouseMovement(const int& x, const int& y)
{
	this->setOrientation(this->getOrientation() + Vector3D(0.0, -x + this->getMouseX(), 0.0));
	this->setMouseX(x);
	this->setMouseY(y);
}

void Player::processMouseClick(const int& button, const int& state, const int& x, const int& y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		this->setMouseX(x);
		this->setMouseY(y);
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		this->setMouseX(0);
		this->setMouseY(0);
	}
}

void Player::processKeyPressed(unsigned char key, int px, int py) {
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
	case 'r':
	case 'R':
		this->reload();
		break;
	}
}

//* Otros *//
//Renderizado
void Player::render() const {
	glPushMatrix();
	glTranslatef(getPosition().getX(), getPosition().getY(), getPosition().getZ());
	glRotatef(getOrientation().getX(), 1.0, 0.0, 0.0);
	glRotatef(getOrientation().getY(), 0.0, 1.0, 0.0);
	glRotatef(getOrientation().getZ(), 0.0, 0.0, 1.0);
	glColor3f(getColor().getRed(), getColor().getGreen(), getColor().getBlue());
	glutSolidCube(this->getSize());
	glPopMatrix();
}

//Actualización
void Player::update(const float& time, const Vector3D& direction) {
	//Cálculo de los nuevos ejes en función de la orientación
	float yOrientationInRadians = this->getOrientation().getY() * M_PI / 180;
	float xOrientationInRadians = this->getOrientation().getX() * M_PI / 180;
	float xComponent = -cos(xOrientationInRadians) * sin(yOrientationInRadians);
	float yComponent = sin(xOrientationInRadians);
	float zComponent = -cos(xOrientationInRadians) * cos(yOrientationInRadians);
	Vector3D velocity(xComponent, yComponent, zComponent);

	//Si se mueve en el eje X
	if (direction.getX() == 1.0) {
		this->setPosition(this->getPosition() - velocity * time);
	}
	//Si se mueve en el eje Z
	else {
		//Vector perpendicular al X (Z)
		velocity = Vector3D(zComponent, yComponent, -xComponent);
		this->setPosition(this->getPosition() - velocity * time);
	}
}

