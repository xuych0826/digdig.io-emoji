#include <windows.h>
#include <stdio.h>

const int brakeKey = 'Z';
const int circleKey = 'X';
const int centerCompensate = 0;

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
            const double PI = 3.14159265358979323846;
            const int radius = 10; // 设置旋转半径
            const int clicks = 1; // 设置点击次数
            const int stepsPerRound = 10; // 设置旋转的步数，现在是两圈
            const int nRounds = 1;

            int stepTot = stepsPerRound * nRounds;
            int stepsPerClick = stepTot / clicks;

            SHORT rightButtonState = GetAsyncKeyState(VK_RBUTTON);
            HANDLE hThread;

            for (int roundIdx = 0; roundIdx < nRounds; roundIdx++) {
                for (int stepIdx = 0; stepIdx < stepsPerRound; stepIdx++) {
                    double angle = ((double)stepIdx / stepsPerRound) * (2.0 * PI);
                    int x = centerX + radius * cos(angle);
                    int y = centerY + radius * sin(angle);
                    SetCursorPos(x, y);

                    int stepTotCur = stepsPerRound * nRounds;
                    if (stepTotCur % stepsPerClick == 0) {
                        // 模拟鼠标右键点击
                        int pos[2] = {x, y};
                        hThread = CreateThread(NULL, 0, ClickThread, pos, 0, NULL);
                    }

                    Sleep(20); // 延迟以便在1秒内完成旋转
                }
            }

            end:
                WaitForSingleObject(hThread, INFINITE);
                // move the cursor to the center
                SetCursorPos(centerX, centerY);
                // Restore the state of the right button
                if (rightButtonState & 0x8000) {
                    // If the right button was down before, simulate a right button down event
                    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                    // printf("right button down\n");
                }
        }
    }

    return 0;
}