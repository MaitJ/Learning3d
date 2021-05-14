#include "GuiEngine.h"
#include <iostream>

GuiEngine::GuiEngine(int screenSize_X, int screenSize_Y) {
    this->m_nScreenWidth = screenSize_X;
    this->m_nScreenHeight = screenSize_Y;
    this->written = 0;
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    this->lineCounter = 0;
}

void GuiEngine::ConstructConsole() {


    windowRect = { 0, 0, 1, 1 };
    SetConsoleWindowInfo(hStdOut, TRUE, &windowRect);

    COORD coord = { (short)m_nScreenWidth, (short)m_nScreenHeight };
    if (!SetConsoleScreenBufferSize(hStdOut, coord)) {
        std::cout << "SetConsoleScreenBufferSize: " << GetLastError() << std::endl;
        return;
    }

    // Assign screen buffer to the console
    if (!SetConsoleActiveScreenBuffer(hStdOut))
    {
        std::cout << "SetConsoleActiveScreenBuffer: " << GetLastError() << std::endl;
        return;
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        std::cout << "GetCSBI: " << GetLastError() << std::endl;
        return;
    }
    if (m_nScreenHeight > csbi.dwMaximumWindowSize.Y) {
        std::cout << "Screen Height / Font Height Too Big" << std::endl;
        return;
    }
    if (m_nScreenWidth > csbi.dwMaximumWindowSize.X) {
        std::cout << "Screen Width / Font Width Too Big" << std::endl;
        return;
    }


    windowRect = { 0, 0, (short)m_nScreenWidth - 1, (short)m_nScreenHeight - 1 };
    if (!SetConsoleWindowInfo(hStdOut, TRUE, &windowRect)) {
        std::cout << "SetConsoleWindowInfo" << std::endl;
        return;
    }

    this->screenBuf = new wchar_t[m_nScreenWidth * m_nScreenHeight];


}

void GuiEngine::toggleCursor() {
    CONSOLE_CURSOR_INFO cci;

    if (!GetConsoleCursorInfo(hStdOut, &cci)) {
        std::cout << "GetConsoleCursorInfo: " << GetLastError() << std::endl;
        return;
    }

    cci.bVisible = !cci.bVisible;

    if (!SetConsoleCursorInfo(hStdOut, &cci)) {
        std::cout << "SetConsoleCursorInfo: " << GetLastError() << std::endl;
        return;
    }

}

void GuiEngine::clearBuffer() {
    for (int i = 0; i < (m_nScreenWidth * m_nScreenHeight); ++i) {
        this->screenBuf[i] = L' ';
    }
}

void GuiEngine::DrawChar(short x, short y, wchar_t charToWrite) {
    if (x > 0 && x < (short)m_nScreenWidth && y > 0 && y < (short)m_nScreenHeight) {
        this->screenBuf[x + (y * m_nScreenWidth)] = charToWrite;
    }
    else {
        if (x < 0 || x > m_nScreenWidth) {
            Error(L"X pos is too small/big");
        }
        if (y < 0 || y > m_nScreenHeight) {
            Error(L"Y pos is too small/big");
        }
        return;
    }

}

void GuiEngine::DrawPoint(Vector2D* point, wchar_t charToWrite) {
    DrawChar(point->x, point->y, charToWrite);
}

void GuiEngine::DrawLine(Vector3D point1, Vector3D point2, wchar_t charToWrite) {
    short dx = point1.x - point2.x;
    short dy = point1.y - point2.y;

    short steps = 0;

    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
    }
    else {
        steps = abs(dy);
    }

    double xFraction = (double)dx / (double)steps;
    double yFraction = (double)dy / (double)steps;

    Vector2D currentPoint(point2.x, point2.y);
    for (int i = 0; i < (int)steps; ++i) {
        currentPoint.x = currentPoint.x + xFraction;
        currentPoint.y = currentPoint.y + yFraction;
        this->DrawChar((short)round(currentPoint.x), (short)round(currentPoint.y), charToWrite);
    }
}

void GuiEngine::DrawString(std::wstring str, COORD pos) {
    if (pos.X > 0 && pos.X < m_nScreenWidth && pos.Y > 0 && pos.Y < m_nScreenHeight) {
        for (int i = 0; i < (int)str.size(); ++i) {
            DrawChar(pos.X + i, pos.Y, str[i]);
        }
    }
    else {
        if (pos.X < 0 || pos.X > m_nScreenWidth) {
            Error(L"X pos is too small/big");
        }
        if (pos.Y < 0 || pos.Y > m_nScreenHeight) {
            Error(L"Y pos is too small/big");
        }
        return;
    }
}

//Implement chance to display multiple errors | doesn't work with upper function errors
void GuiEngine::Error(std::wstring err) {
    std::wstring errMsg = L"[ERROR] " + err;
    errorList.push_back(errMsg);
    lineCounter = (short)errorList.size();
    for (int i = 0; i < (int)errorList.size(); ++i) {
        short lineToAdd = (short)ceil(errorList[i].size() / m_nScreenWidth);
        lineCounter += lineToAdd;
    }
    for (int i = 0; i < (int)errorList.size(); ++i) {
        short xCount = 0;
        for (int j = 0; j < (int)errorList[i].size(); ++j) {
            DrawChar(xCount, m_nScreenHeight - lineCounter, errorList[i][j]);
            ++xCount;
            if (xCount == m_nScreenWidth - 1) {
                xCount = 0;
                --lineCounter;
            }
        }
        --lineCounter;
    }
}

void GuiEngine::render() {
    WriteConsoleOutputCharacterW(this->hStdOut, this->screenBuf, (m_nScreenWidth * m_nScreenHeight), { 0, 0 }, &this->written);
}

int GuiEngine::getScreenWidth() {
    return this->m_nScreenWidth;
}

int GuiEngine::getScreenHeight() {
    return this->m_nScreenHeight;
}
