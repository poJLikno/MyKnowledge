#include <windows.h>

LRESULT CALLBACK PictViewWndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow){
    HWND hWnd;
    WNDCLASS WndClass;
    MSG Msg;
    char szClassName[] = "PictView";

    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc = PictViewWndProc;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = hInstance;
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WndClass.lpszMenuName = NULL;
    WndClass.lpszClassName = szClassName;

    if ( ! RegisterClass(&WndClass) ){
        MessageBox(NULL, "Can't register class", "Error", MB_OK);
        return 0;
    }

    hWnd = CreateWindow(szClassName, "Picture View", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    if ( ! hWnd ){
        MessageBox(NULL, "Can't create window", "Error", MB_OK);
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while ( GetMessage(&Msg, NULL, 0, 0) ){
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

LRESULT CALLBACK PictViewWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam){
    HDC hDC, hCompatibleDC;
    PAINTSTRUCT PaintStruct;
    HANDLE hBitmap, hOldBitmap;
    RECT Rect;
    BITMAP Bitmap;

    switch ( Message ){
    case WM_PAINT :
        hDC = BeginPaint(hWnd, &PaintStruct);
        hBitmap = LoadImage(NULL, "picture.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
        hCompatibleDC = CreateCompatibleDC(hDC);
        hOldBitmap = SelectObject(hCompatibleDC, hBitmap);
        GetClientRect(hWnd, &Rect);
        StretchBlt(hDC, 0, 0, Rect.right, Rect.bottom, hCompatibleDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);
        SelectObject(hCompatibleDC, hOldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(hCompatibleDC);
        EndPaint(hWnd, &PaintStruct);
        return 0;
    case WM_DESTROY :
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, Message, wParam, lParam);
}
