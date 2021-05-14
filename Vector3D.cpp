#include "Vector3D.h"
#include <Windows.h>

Vector3D::Vector3D() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3D::Vector3D(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

double* Vector3D::getArray() {
	double* arr = (double*)malloc(3 * sizeof(double));
	arr[0] = this->x;
	arr[1] = this->y;
	arr[2] = this->z;
	return arr;
}
