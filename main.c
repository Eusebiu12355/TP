
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "2048.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    (void)hPrevInstance;
    (void)lpCmdLine;
    
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "2048GUI";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    RegisterClass(&wc);
    HWND hwnd = CreateWindowEx(0, "2048GUI", "2048", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 450, NULL, NULL, hInstance, NULL);

    srand(time(NULL));
    loadHighScore();
    addRandom();
    addRandom();

    ShowWindow(hwnd, nCmdShow);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rect;
            GetClientRect(hwnd, &rect);
            int cellWidth = rect.right / SIZE;
            int cellHeight = (rect.bottom - 50) / SIZE;
            char scorText[50];
            
            sprintf(scorText, "Scor: %d | High Score: %d", score, highScore);
            TextOut(hdc, 10, 10, scorText, strlen(scorText));
            
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    RECT r = { j * cellWidth, 50 + i * cellHeight, (j + 1) * cellWidth, 50 + (i + 1) * cellHeight };
                    Rectangle(hdc, r.left, r.top, r.right, r.bottom);
                    if (board[i][j] != 0) {
                        char numar[10];
                        sprintf(numar, "%d", board[i][j]);
                        DrawText(hdc, numar, -1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                    }
                }
            }
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_KEYDOWN: {
            char input = 0;
            if (wParam == 'W' || wParam == VK_UP) input = 'w';
            else if (wParam == 'S' || wParam == VK_DOWN) input = 's';
            else if (wParam == 'A' || wParam == VK_LEFT) input = 'a';
            else if (wParam == 'D' || wParam == VK_RIGHT) input = 'd';
            
            if (input && move(input)) {
                addRandom();
                if (score > highScore) highScore = score;
                InvalidateRect(hwnd, NULL, TRUE);
                if (checkWin()) MessageBox(hwnd, "Ai castigat!", "2048", MB_OK);
                else if (checkGameOver()) MessageBox(hwnd, "Joc terminat!", "2048", MB_OK);
            }
            return 0;
        }
        case WM_DESTROY:
            saveHighScore();
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}