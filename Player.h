#ifndef ENGINE_HERENCIA_PLAYER_H
#define ENGINE_HERENCIA_PLAYER_H

#include "Character.h"

class Player : public Character {

private:
	int score;		//Puntuación
	int mouseX;		//Posición X del mouse
	int mouseY;		//Posición Y del mouse
	int kills;		//Asesinatos

public:
	//Constructores
	Player();
	Player(const Vector3D& position, const Color& color, const Vector3D& speed,
		const Vector3D& orientation, int health, Weapon& weapon, float size, int score);

	//Getters
	int getScore() const;
	float getMouseX() const;
	float getMouseY() const;
	int getKills() const;

	//Setters
	void setScore(const int& s);
	void setMouseY(const int& mouseY);
	void setMouseX(const int& mouseX);
	void setKills(const int& k);

	//Métodos de movimiento
	void processMouseMovement(const int& x, const int& y);
	void processMouseClick(const int& button, const int& state, const int& x, const int& y);
	void processKeyPressed(unsigned char key, int px, int py);

	//Otros métodos
	void render() const;
	void update(const float& time, const Vector3D& gravity);
};
#endif //ENGINE_HERENCIA_PLAYER_H

