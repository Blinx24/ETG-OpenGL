#include "Triangle.h"

void Triangle::render() const
{
	glBegin(GL_TRIANGLES);
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vertex1.getX(), vertex1.getY(), vertex1.getZ());
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vertex2.getX(), vertex2.getY(), vertex2.getZ());
	glNormal3f(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(vertex3.getX(), vertex3.getY(), vertex3.getZ());
	glEnd();
}
