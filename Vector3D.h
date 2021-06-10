//
// Created by rcabido on 25/10/19.
//

#ifndef ENGINE_VECTOR3D_H
#define ENGINE_VECTOR3D_H

///////////////////////////////////////////////////////////////////////////
// CLASE VECTOR 3D //
class Vector3D {
private:
    float x;
    float y;
    float z;

public:
	//Constructores
	Vector3D();
    Vector3D(const float &xCoord, const float &yCoord, const float &zCoord);
    
	//Getters
    float getX() const;
    float getY() const;
    float getZ() const;

	//Setters
    void setX(const float &x);
    void setY(const float &y);
    void setZ(const float &z);

	//Operaciones
    Vector3D add(const Vector3D &b) const;
    Vector3D substract(const Vector3D &b) const;
    Vector3D product(const float &b) const;
    Vector3D product(const Vector3D &b) const;

	//Sobrecarga operadores
    Vector3D operator+(const float &b) const;
    Vector3D operator+(const Vector3D &b) const;
    Vector3D operator-(const float &b) const;
    Vector3D operator-(const Vector3D& b) const;
    Vector3D operator*(const float &b) const;
    Vector3D operator*(const Vector3D &b) const;
	bool operator==(const Vector3D& b) const;

};

#endif //ENGINE_VECTOR3D_H
