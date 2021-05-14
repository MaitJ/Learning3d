#ifndef LINEEQUATIONS_CPP
#define LINEEQUATIONS_CPP

#include "Vector3D.cpp"

class LineEquations {
protected:
    double y1, x1, m;
public:
    LineEquations(Vector3D pointOnLine, double m) {
        this->x1 = (double)pointOnLine.x;
        this->y1 = (double)pointOnLine.y;
        this->m = m;
    }
    static double findM(Vector3D point1, Vector3D point2) {
        return (point1.y - point2.y) / (point1.x - point2.x);
    }

    double getY(double x) {
        return (m * (x - x1)) + y1;
    }

};

#endif // !LINEEQUATIONS_CPP
