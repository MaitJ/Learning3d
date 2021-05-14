#include "Transformations3D.h"
#include "MatrixManipulations.h"
#include "Vector3D.h"
#include <cmath>

void Transformations3D::rotateX(Vector3D *point, short angle) {

	double rotationMatrixX[3][3] = {
				{1, 0, 0},
				{0, cos(angle), -sin(angle)},
				{0, sin(angle), cos(angle)}
	};

	*point = MatrixManipulations::matrixMultiplyPoint(rotationMatrixX, *point);
}

void Transformations3D::rotateY(Vector3D *point, short angle) {

	double rotationMatrixY[3][3] = {
			{cos(angle), 0, sin(angle)},
			{0, 1, 0},
			{-sin(angle), 0, cos(angle)}
	};

	*point = MatrixManipulations::matrixMultiplyPoint(rotationMatrixY, *point);
}

void Transformations3D::rotateZ(Vector3D *point, short angle) {

	double rotationMatrixZ[3][3] = {
				{cos(angle), -sin(angle), 0},
				{sin(angle), cos(angle), 0},
				{0, 0, 1}
	};

	*point = MatrixManipulations::matrixMultiplyPoint(rotationMatrixZ, *point);
}
