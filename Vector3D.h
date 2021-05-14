#ifndef VECTOR3D_H
#define VECTOR3D_H
class Vector3D {
public:
	double x, y, z;

	Vector3D();
	Vector3D(double x, double y, double z);
	double* getArray();
};
#endif // !VECTOR3D_H
