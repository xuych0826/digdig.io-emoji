#include <windows.h>
#include <stdio.h>

const int brakeKey = 'Z';
const int circleKey = 'X';
const int centerCompensate = 0;

const double PI = 3.14159265358979323846;
const int radius = 10; // 设置旋转半径
const int clicksPerRound = 1; // 设置点击次数
const int stepsPerRound = 36; // 设置旋转的步数，现在是两圈
const int nRounds = 1;
const int timePerRound = 400; // ms

int rotationStep = 0;

DWORD WINAPI ClickThread(LPVOID lpParam) {
    int* pos = (int*)lpParam;
    mouse_event(MOUSEEVENTF_RIGHTDOWN, pos[0], pos[1], 0, 0);
    Sleep(20); // 延迟0.3秒
    mouse_event(MOUSEEVENTF_RIGHTUP, pos[0], pos[1], 0, 0);
    return 0;
}


int main() {
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int centerX = screenWidth / 2 + centerCompensate;
    int centerY = screenHeight / 2 + centerCompensate;

    // Listen for a key press
    while (1) {
        if (GetAsyncKeyState(brakeKey)) {  // replace 'C' with the key you want
            // printf("The 'C' key is pressed.\n");

            // Set the cursor position to the center of the screen
            SetCursorPos(centerX, centerY);

            // // Wait until the key is released
            // while (GetAsyncKeyState(VK_F8)) {}
        }
        
        if (GetAsyncKeyState(circleKey)) {
            // Increment the rotation step
            rotationStep++;

            // Calculate the new position based on the rotation step
            int x = centerX + radius * cos(2 * PI * rotationStep / stepsPerRound);
            int y = centerY + radius * sin(2 * PI * rotationStep / stepsPerRound);

            // Move the cursor to the new position
            SetCursorPos(x, y);
            Sleep(timePerRound / stepsPerRound);
        }
    }

    return 0;
}