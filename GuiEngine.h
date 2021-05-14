#ifndef GUIENGINE_H
#define GUIENGINE_H

#include <Windows.h>
#include <vector>
#include <string>
#include "Vector2D.h"
#include "Vector3D.h"

class GuiEngine {
protected:
    int m_nScreenWidth;
    int m_nScreenHeight;
    int screenSize_Y;
    HANDLE hStdOut;
    DWORD written;
    SMALL_RECT windowRect;
    wchar_t* screenBuf;
    short errorCount;
    short lineCounter;
    std::vector<std::wstring> errorList;

public:
    GuiEngine(int screenSize_X, int screenSize_Y);
    void ConstructConsole();
    void toggleCursor();
    void clearBuffer();
    void DrawPoint(Vector2D* point, wchar_t charToWrite);
    void DrawLine(Vector3D point1, Vector3D point2, wchar_t charToWrite);
    void DrawChar(short x, short y, wchar_t charToWrite);
    void DrawString(std::wstring str, COORD pos);
    void Error(std::wstring err);
    void render();
    int getScreenWidth();
    int getScreenHeight();

};

#endif
