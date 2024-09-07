#ifndef KEYBOARD_H
#define KEYBOARD_H

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

enum ArrowKeys {
    UP_ARROW = 0,
    DOWN_ARROW = 1,
    LEFT_ARROW = 2,
    RIGHT_ARROW = 3
};

int getArrowKey() {
#ifdef _WIN32
    int ch = _getch();
    if (ch == 224) {
        switch (_getch()) {
            case 72: return UP_ARROW;
            case 80: return DOWN_ARROW;
            case 75: return LEFT_ARROW;
            case 77: return RIGHT_ARROW;
        }
    }
#else
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    if (ch == 27) {
        getchar(); // skip the [
        switch (getchar()) {
            case 'A': ch = UP_ARROW; break;
            case 'B': ch = DOWN_ARROW; break;
            case 'D': ch = LEFT_ARROW; break;
            case 'C': ch = RIGHT_ARROW; break;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
    return -1; // No arrow key pressed
}

#endif // KEYBOARD_H
