#pragma once

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <gdiplus.h>

using namespace Gdiplus;

Player player(720, 500, 0.f, 5, 100, 1000);

int forgmover = 0;

bool menu = 1, gameover = 0;
bool on_pos_play = 0, on_pos_quit = 0;

void LoadButton(HDC hdc, const wchar_t* way, const wchar_t* way_active, bool on_pos_l, int pos_x, int pos_y, int width, int height)
{
    wchar_t *fin = (on_pos_l) ? (wchar_t*)way_active : (wchar_t*)way;
    Image button(fin);
    Graphics g(hdc);
    g.DrawImage(&button, pos_x, pos_y, width, height);

    /*BITMAP BmpInfo{};
    HBITMAP Button = nullptr;

    if (on_pos_l) Button = (HBITMAP)LoadImage(NULL, way_active, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    else Button = (HBITMAP)LoadImage(NULL, way, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    GetObject(Button, sizeof(BmpInfo), &BmpInfo);
    HDC DC = CreateCompatibleDC(hdc);
    SelectObject(DC, Button);

    StretchBlt(hdc, pos_x, pos_y, width, height, DC, 0, 0, BmpInfo.bmWidth, BmpInfo.bmHeight, SRCCOPY);

    DeleteDC(DC);
    DeleteObject(Button);*/
}

void StartMenuLogic(HWND hwnd)
{
    on_pos_play = 0;
    on_pos_quit = 0;

    GetCursorPos(&Cursor_point);
    //ScreenToClient(hwnd, &Cursor_point);

    //Play
    if (Cursor_point.x > Display.right / 4.5 && Cursor_point.x < Display.right / 4.5 + Display.right / 1.8 && Cursor_point.y > Display.bottom / 2.1951219512195121951219512195122 && Cursor_point.y < Display.bottom / 2.1951219512195121951219512195122 + Display.bottom / 11.25)
    {
        on_pos_play = 1;
        if (GetKeyState(VK_LBUTTON) < 0 && GetForegroundWindow() == hwnd)
        {
            menu = 0;
            ShowCursor(FALSE);
        }
    }

    //Quit
    if (Cursor_point.x > Display.right / 4.5 && Cursor_point.x < Display.right / 4.5 + Display.right / 1.8 && Cursor_point.y > Display.bottom / 1.6981132075471698113207547169811 && Cursor_point.y < Display.bottom / 1.6981132075471698113207547169811 + Display.bottom / 11.25)
    {
        on_pos_quit = 1;
        if (GetKeyState(VK_LBUTTON) < 0 && GetForegroundWindow() == hwnd)
        {
            PostQuitMessage(0);
        }
    }
}

void DrawStartMenu(HWND hwnd, HDC hdc)
{
    StartMenuLogic(hwnd);

    Image background(L"C:/Users/poJLikno/Documents/C++/VSprojects/ray_casting/x64/Debug/images/start menu.bmp");
    Graphics g(hdc);
    g.DrawImage(&background, 0, 0, Display.right, Display.bottom);

    /*BITMAP BackBmpInfo{};
    HBITMAP back = (HBITMAP)LoadImage(NULL, "images/start menu.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(back, sizeof(BackBmpInfo), &BackBmpInfo);
    HDC backDC = CreateCompatibleDC(hdc);
    SelectObject(backDC, back);

    StretchBlt(hdc, 0, 0, Display.right, Display.bottom, backDC, 0, 0, BackBmpInfo.bmWidth, BackBmpInfo.bmHeight, SRCCOPY);
    DeleteDC(backDC);
    DeleteObject(back);
    */

    //Play
    LoadButton(hdc, L"C:/Users/poJLikno/Documents/C++/VSprojects/ray_casting/x64/Debug/images/play button.bmp", L"C:/Users/poJLikno/Documents/C++/VSprojects/ray_casting/x64/Debug/images/play button active.bmp", on_pos_play, Display.right / 4.5, Display.bottom / 2.1951219512195121951219512195122, Display.right / 1.8, Display.bottom / 11.25);

    //Quit
    LoadButton(hdc, L"C:/Users/poJLikno/Documents/C++/VSprojects/ray_casting/x64/Debug/images/quit button.bmp", L"C:/Users/poJLikno/Documents/C++/VSprojects/ray_casting/x64/Debug/images/quit button active.bmp", on_pos_quit, Display.right / 4.5, Display.bottom / 1.6981132075471698113207547169811, Display.right / 1.8, Display.bottom / 11.25);
}

/*void DrawSprite(HDC hdc, const wchar_t* way, int pos_x, int pos_y, float cof)
{
    Image sprite(way);
    Graphics g(hdc);
    g.DrawImage(&sprite, (float)pos_x, (float)pos_y, (float)sprite.GetWidth() / cof, (float)sprite.GetHeight() / cof);

    BITMAP BmpInfo;
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, way, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hBitmap, sizeof(BmpInfo), &BmpInfo);
    HDC spriteDC = CreateCompatibleDC(hdc);
    SelectObject(spriteDC, hBitmap);
    TransparentBlt(hdc, pos_x, pos_y, BmpInfo.bmWidth / cof, BmpInfo.bmHeight / cof, spriteDC, 0, 0, BmpInfo.bmWidth, BmpInfo.bmHeight, RGB(255, 0, 255));
    DeleteDC(spriteDC);
    DeleteObject(hBitmap);
}*/




void GameOver(HDC hdc)
{
    Image gmover(L"C:/Users/poJLikno/Documents/C++/VSprojects/ray_casting/x64/Debug/images/gameover.jpg");
    Graphics g(hdc);
    g.DrawImage(&gmover, 0, 0, Display.right, Display.bottom);
    if (forgmover >= 100)
    {
        player.pos_x = 720;
        player.pos_y = 500;
        player.angle = 0.f;
        player.hp = 100;
        gameover = 0;
        forgmover = 0;
    }
    else forgmover += 3;
}



void DrawGame(HDC hdc)//HDC hdc)
{
    if (gameover)
    {
        //GameOver
        GameOver(hdc);
        //------
    }
    else
    {
        //Background
        BackgroundDraw(hdc);
        //------

        //Ray casting func
        //RayCasting(hdc, Cur_angle);

        player.ctrl = 0;

        //Map
        MiniMap(hdc);
        //------

        //Crosshire
        DrawSprite(hdc, L"C:/Users/poJLikno/Documents/C++/VSprojects/ray_casting/x64/Debug/images/crosshair.png", Display.right / 2 - 20, Display.bottom / 2 - 20, 15.f);
        //------

        //Weapoon
        if (player.lbut) DrawSprite(hdc, L"C:/Users/poJLikno/Documents/C++/VSprojects/ray_casting/x64/Debug/images/weapon fire.png", Display.right - 900.f / 1.5, Display.bottom - 395.f / 1.5 + 2.f, 1.5f);
        else DrawSprite(hdc, L"C:/Users/poJLikno/Documents/C++/VSprojects/ray_casting/x64/Debug/images/weapon.png", Display.right - 900.f / 1.5, Display.bottom - 395.f / 1.5 + 2.f, 1.5f);
        //------

        //HP
        HP(hdc);
        //------
    }
}
