#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "GameObject.h"
#include "Triangle.h"

using namespace std;

class Model : public GameObject
{
private:
	vector<Vector3D*> vertexes;
	vector<Vector3D*> textures;
	vector<Vector3D*> normals;

	vector<Triangle*> triangles;

	Vector3D* parseLineToVector3D(string& line);
	Triangle* parseFace(string& line);

public:
	Model() : GameObject() { }

	Model(Vector3D positionToSet, Color colorToSet, Vector3D speedToSet, Vector3D orientationToSet)
		: GameObject(positionToSet, colorToSet, speedToSet, orientationToSet, Vector3D(), false) {}

	void render() const;
	void loadModel(const string& filename);

};

