#ifndef MATRIXMANIPULATIONS_H
#define MATRIXMANIPULATIONS_H

#include "Vector2D.h"
#include "Vector3D.h"

class MatrixManipulations {
public:
	static Vector2D threeDToTwoD(double** translationMatrix, Vector3D point);
	static double** matrixMultiply(double** firstMatrix, double** secondMatrix);
	static Vector3D matrixMultiplyPoint(double translationMatrix[3][3], Vector3D point);
	static double** translate(double x, double y);
};
#endif // !MATRIXMANIPULATIONS_H
