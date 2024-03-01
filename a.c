#include <windows.h>
#include <stdio.h>

const int brakeKey = 'Z';
const int circleKey = 'X';
const int centerCompensate = 0;

const double PI = 3.14159265358979323846;
const int radius = 10; // 设置旋转半径
const int clicksPerPeriod = 1; // 设置点击次数
const int stepsPerPeriod = 36; // 设置旋转的步数，现在是两圈
const int nRounds = 1;
const int timePerPeriod = 1600; // ms

int totStep = 0;

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
            totStep++;
            int stepInPeriod = totStep % stepsPerPeriod;
            double stepFraction = (double)stepInPeriod / stepsPerPeriod;

            double angle = 0;
            // double angle = -PI/6 + PI/3*stepFraction 
            //     + (stepFraction < 0.5 ? 0 : PI);
            if (stepFraction < 0.25)
                angle = PI;
            else if (stepFraction < 0.5)
                angle = 0;
            else if (stepFraction < 0.75)
                angle = PI/2;
            else
                angle = -PI/2;

            // Calculate the new position based on the rotation step
            int x = centerX + radius * cos(angle);
            int y = centerY + radius * sin(angle);

            // Move the cursor to the new position
            SetCursorPos(x, y);
            Sleep(timePerPeriod / stepsPerPeriod);
        }
    }

    return 0;
}