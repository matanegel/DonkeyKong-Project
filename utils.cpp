#include <iostream>

#include "utils.h"
#include <cstdlib>
#include <ctime>

void gotoxy(int x, int y) {
    std::cout.flush();
    COORD coord; // Create a COORD structure 
    coord.X = x; // Set the X coordinate 
    coord.Y = y; // Set the Y coordinate 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor 
}

void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}



int random39Or42() {
    // Generate a random number (0 or 1) and map it to 39 or 42
    return (rand() % 2 == 0) ? 39 : 43;
}