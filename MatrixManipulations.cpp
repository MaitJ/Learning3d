#include "MatrixManipulations.h"

#include <Windows.h>

Vector2D MatrixManipulations::threeDToTwoD(double** translationMatrix, Vector3D point) {
    double* pointArr = point.getArray();

    double* twodPoint = (double*)malloc(2 * sizeof(double));


    for (int i = 0; i < 2; ++i) {
        twodPoint[i] = 0;
        for (int j = 0; j < 3; j++) {
            twodPoint[i] += translationMatrix[i][j] * pointArr[j];
        }
    }

    Vector2D twodVector = { twodPoint[0], twodPoint[1] };
    return twodVector;
}

double** MatrixManipulations::matrixMultiply(double** firstMatrix, double** secondMatrix) {
    double** matrix = (double**)malloc(3 * sizeof(double));

    for (int i = 0; i < 3; ++i) {
        matrix[i] = (double*)malloc(3 * sizeof(double));
        for (int j = 0; j < 3; ++j) {
            matrix[i][j] = 0;
        }
    }

    for (int x = 0; x < 3; ++x) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                matrix[x][i] += firstMatrix[x][j] * secondMatrix[j][i];
            }
        }
    }
    return matrix;
}

Vector3D MatrixManipulations::matrixMultiplyPoint(double translationMatrix[3][3], Vector3D point) {
    double* pointArr = point.getArray();

    double* threedPoint = (double*)malloc(3 * sizeof(double));

    for (int i = 0; i < 3; ++i) {
        threedPoint[i] = 0;
        for (int j = 0; j < 3; ++j) {
            threedPoint[i] += translationMatrix[i][j] * pointArr[j];
        }
    }

    Vector3D newPoint = { threedPoint[0], threedPoint[1], threedPoint[2] };
    return newPoint;
}

double** MatrixManipulations::translate(double x, double y) {
    double** translationMatrixPtr = (double**)malloc(3 * sizeof(double));
    for (int i = 0; i < 3; ++i) {
        translationMatrixPtr[i] = (double*)malloc(3 * sizeof(double));
    }

    short translationMatrix[3][3] = {
        { 1, 0, x },
        { 0, 1, y },
        { 0, 0, 1 }
    };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            translationMatrixPtr[i][j] = translationMatrix[i][j];
        }
    }
    return translationMatrixPtr;
}