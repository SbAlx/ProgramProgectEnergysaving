/*Program project EnergySaving*/

/*System calls*/
#include <windows.h>
#include "Resource.h"

/*World's handle instance application*/
HINSTANCE g_hInst;

/*Frame window procedure*/
LRESULT CALLBACK FrameWndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    HWND hwndFrame, hwndClient;
    MSG msg;
    WNDCLASSEX wndclass;

    /*Save hInstance*/
    g_hInst = hInstance;

    /*string app name, window caption*/
    char szFrameClassName[STR_MAX_LENGTH];
    char szFrameWindowCaption[STR_MAX_LENGTH];

    /*Load string*/
    LoadString(g_hInst,IDS_FRAMECLASSNAME,szFrameClassName,STR_MAX_LENGTH);
    LoadString(g_hInst,IDS_FRAMEWINDOWCAPTION,szFrameWindowCaption,STR_MAX_LENGTH);

    if(!hPrevInstance)
    {
        /*Register the frame window class*/

        wndclass.cbSize = sizeof(wndclass);
        wndclass.style = CS_HREDRAW | CS_VREDRAW;
        wndclass.lpfnWndProc = FrameWndProc;
        wndclass.cbClsExtra = 0;
        wndclass.cbWndExtra = 0;
        wndclass.hInstance = hInstance;
        wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
        wndclass.hbrBackground =(HBRUSH) (COLOR_APPWORKSPACE+1);
        wndclass.lpszMenuName = NULL;
        wndclass.lpszClassName = szFrameClassName;
        wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

        RegisterClassEx(&wndclass);
    }

    hwndFrame = CreateWindow(
                        szFrameClassName, // window class name
                        szFrameWindowCaption, // window caption
                        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, // window style
                        CW_USEDEFAULT, // initial x position
                        CW_USEDEFAULT, // initial y position
                        CW_USEDEFAULT, // initial x size
                        CW_USEDEFAULT, // initial y size
                        NULL, // parent window handle
                        NULL, // window menu handle
                        hInstance, // program instance handle
                        NULL
                        ); // creation parameters

    hwndClient = GetWindow(hwndFrame, GW_CHILD);

    /*Show maximized window*/
    ShowWindow(hwndFrame, SW_MAXIMIZE);
    UpdateWindow(hwndFrame);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

/*Main frame window procedure */
LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    static HWND hwndClient;
    CLIENTCREATESTRUCT clientstruct;
    HDC hdc;
    RECT rect;
    int cxScreen, cyScreen;
    char szTempClassName[STR_MAX_LENGTH];

    switch(iMsg)
    {
    case WM_CREATE:

        /*Create the client window*/
        LoadString(g_hInst, IDS_MDICLIENT, szTempClassName, STR_MAX_LENGTH);

        clientstruct.hWindowMenu = NULL;
        clientstruct.idFirstChild = 0;

        hwndClient = CreateWindow(szTempClassName,
                                  NULL,
                                  WS_CHILD|WS_CLIPCHILDREN|WS_VISIBLE,
                                  0,0,0,0,
                                  hwnd,
                                  (HMENU) 1,
                                  g_hInst,
                                  (LPSTR) &clientstruct);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    /*Pass unprocessed messages to DefFrameProc*/
    return DefFrameProc(hwnd, hwndClient, iMsg, wParam, lParam);
}
