#ifndef TRANSFORMATIONS3D_H
#define TRANSFORMATIONS3D_H
#include "Vector3D.h"

class Transformations3D {
public:
	static void rotateX(Vector3D *point, short angle);
	static void rotateY(Vector3D *point, short angle);
	static void rotateZ(Vector3D *point, short angle);

};
#endif // !TRANSFORMATIONS3D_H
