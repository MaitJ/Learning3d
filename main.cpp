#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <cmath>
#include "GuiEngine.h"
#include "MatrixManipulations.h"
#include "Transformations3D.h"
#define UNICODE
#define _UNICODE
#define M_PI 3.141592653589793238463




int main(){
    GuiEngine gui(60, 30);
    COORD screenCenter = { 20, 15 };

    Vector3D points[8] = {
        {15, 20, -5},
        {25, 20, -5},
        {15, 10, -5},
        {25, 10, -5},
        {15, 20, 10},
        {25, 20, 10},
        {15, 10, 10},
        {25, 10, 10},
    };

    gui.ConstructConsole();
    gui.toggleCursor();
    gui.clearBuffer();

    Vector3D* translatedPoints = new Vector3D[8];


    short angle = 0;
    while(true) {
        gui.clearBuffer();
		for (int i = 0; i < 8; ++i) {

            Vector3D currentPoint = points[i];
            currentPoint.x = currentPoint.x - screenCenter.X;
            currentPoint.y = currentPoint.y - screenCenter.Y;
            Transformations3D::rotateX(&currentPoint, angle);
            Transformations3D::rotateY(&currentPoint, angle);
            Transformations3D::rotateZ(&currentPoint, angle);
            currentPoint.x += screenCenter.X;
            currentPoint.y += screenCenter.Y;
            translatedPoints[i] = currentPoint;

            //Translate points and assign them to an array
            //On translated array connect the points using Gui.DrawLine()
		}

        for (int i = 0; i < 8; ++i) {
            gui.DrawChar((short)round(translatedPoints[i].x), (short)round(translatedPoints[i].y), L'@');
        }

        gui.DrawLine(translatedPoints[0], translatedPoints[1], L'@');
        gui.DrawLine(translatedPoints[0], translatedPoints[2], L'@');
        gui.DrawLine(translatedPoints[1], translatedPoints[3], L'@');
        gui.DrawLine(translatedPoints[2], translatedPoints[3], L'@');

        gui.DrawLine(translatedPoints[4], translatedPoints[5], L'@');
        gui.DrawLine(translatedPoints[4], translatedPoints[6], L'@');
        gui.DrawLine(translatedPoints[6], translatedPoints[7], L'@');
        gui.DrawLine(translatedPoints[5], translatedPoints[7], L'@');

        gui.DrawLine(translatedPoints[3], translatedPoints[7], L'@');
        gui.DrawLine(translatedPoints[1], translatedPoints[5], L'@');
        gui.DrawLine(translatedPoints[2], translatedPoints[6], L'@');
        gui.DrawLine(translatedPoints[0], translatedPoints[4], L'@');

		gui.render();
        if (angle >= 180) {
            angle = 0;
        }
        angle += 5;
        Sleep(500);
    }


    return 0;
}