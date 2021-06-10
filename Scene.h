//
// Created by rcabido on 12/11/19.
//

#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

#include <vector>

#include "FlyingCamera.h"
#include "Player.h"
#include "Enemy.h"
#include "Cuboid.h"
#include "Bullet.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
// CLASE SCENE //
class Scene {
private:
    FlyingCamera camera;							//Cámara actual
	Player p;										//Jugador
    vector<Cuboid*> limitsScenario;					//Vector de límites del escenario
	vector<FlyingCamera> cameras;					//Vector de cámaras de la escena
	vector<Bullet*> bullets;						//Vector de balas
	vector<Enemy*> enemies;							//Vector de enemigos
    Vector3D size;									//Tamaño de la escena
    Vector3D gravity;								//Gravedad de la escena
	bool completed;									//Escena completada
	int id;											//ID de la escena

public:
	//Constructor
	Scene(const int& id = 0, const bool& completed = false, const Vector3D& size = Vector3D(50.0, 10.0, 50.0), const Vector3D& cameraPos = Vector3D(5.0, 0.0, 20.0),
		const Vector3D& cameraOr = Vector3D(), const Vector3D& gravity = Vector3D(0.0, -0.01, 0.0), const Player& p = Player());
	
	//Getters
	Vector3D getSize() const;
	Vector3D getGravity() const;
	FlyingCamera getCamera() const;
	Player getPlayer();
	vector<Enemy*> getEnemies() const;
	bool getCompleted() const;
	int getId() const;

	//Setters
	void setCamera(FlyingCamera camera);
	void setPlayer(Player p);
	void setFirstPersonCamera(FlyingCamera fC);
	Player setNewPlayer(Vector3D pos);
	FlyingCamera setNewFirstPersonCamera(Vector3D pos);
	void setId(int i);
	void setCompleted(bool c);

	//Métodos de edición de escena
    void addLimitScenario(Cuboid* obj);
	void addCamera(FlyingCamera cam);
	void addBullet(Bullet* b);
	void addEnemy(Enemy* e);
    void clearScene();

	//Métodos de movimiento
	void processMouseMovement(const int& x, const int& y);
    void processMouseClick(const int& button, const int& state, const int& x, const int& y);
	void playerMovement(unsigned char key, int px, int py);
	void cameraMovement(unsigned char key, int px, int py);
	void firstPersonCameraMovement(unsigned char key, int px, int py);
	void upperCameraMovement(unsigned char key, int px, int py);
    void processKeyPressed(unsigned char key, int px, int py);

	//Métodos de colisiones
	void collisionWithLimits(int& i, float& xP, float& zP, float& xM, float& zM);
	void collisionWithPlayer(int& i, float& xP, float& zP, float& xM, float& zM);
	void collisionWithEnemies(int& i, float& xP, float& zP, float& xM, float& zM);

	//Otros métodos
    void render();
    void update(const float &deltaTime);
	void updateLimits(const float& deltaTime);
	void updateBullets(const float& deltaTime);
	void updateEnemies(const float& deltaTime);	
};

#endif //ENGINE_SCENE_H
