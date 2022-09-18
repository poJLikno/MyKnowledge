#pragma once

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <gdiplus.h>

using namespace Gdiplus;

POINT Cursor_point;
RECT Display;
double PI = 3.14159265359;
const int map_x = 9, map_y = 9;

const char map[map_y][map_x + 1] =
{"wwwwwwwww",
 "w.......w",
 "w..www..w",
 "w....w..w",
 "w.......w",
 "w..w....w",
 "w..www..w",
 "w.......w",
 "wwwwwwwww"};

class World
{
private:
    void IntersectionsAndDepth(HDC hdc, int x_x, int x_y, int x_d, int y_x, int y_y, int y_d, float Cur_angle, int p_pos_x, int p_pos_y, int p_FOV_depth, float p_angle)
    {
        //Set color
        SetDCBrushColor(hdc, RGB(0, 255, 0));
        SetDCPenColor(hdc, RGB(0, 255, 0));

        //Intersection dote
        if (x_d == 0 && y_d != 0) Rectangle(hdc, y_x / 4 - 4, y_y / 4 - 4, y_x / 4 + 4, y_y / 4 + 4);
        else if (y_d == 0 && x_d != 0) Rectangle(hdc, x_x / 4 - 4, x_y / 4 - 4, x_x / 4 + 4, x_y / 4 + 4);
        else if (x_d < y_d) Rectangle(hdc, x_x / 4 - 4, x_y / 4 - 4, x_x / 4 + 4, x_y / 4 + 4);
        else if (y_d < x_d) Rectangle(hdc, y_x / 4 - 4, y_y / 4 - 4, y_x / 4 + 4, y_y / 4 + 4);
        else if (x_d == y_d && x_d != 0 && y_d != 0) Rectangle(hdc, x_x / 4 - 4, x_y / 4 - 4, x_x / 4 + 4, x_y / 4 + 4);
        //------

        //FOV_depth range dote
        float Dote_pos_x = (float)p_pos_x + (float)p_FOV_depth * cos(Cur_angle * PI / 180);
        float Dote_pos_y = (float)p_pos_y + (float)p_FOV_depth * sin(Cur_angle * PI / 180);
        Rectangle(hdc, Dote_pos_x / 4 - 2, Dote_pos_y / 4 - 2, Dote_pos_x / 4 + 2, Dote_pos_y / 4 + 2);

        /*float Dote_pos_x1 = (float)p_pos_x + (float)p_FOV_depth * cos(p_angle * PI / 180);
        float Dote_pos_y1 = (float)p_pos_y + (float)p_FOV_depth * sin(p_angle * PI / 180);
        SetDCPenColor(hdc, RGB(255, 255, 0));
        SetDCBrushColor(hdc, RGB(255, 255, 0));
        Rectangle(hdc, Dote_pos_x1 / 4 - 2, Dote_pos_y1 / 4 - 2, Dote_pos_x1 / 4 + 2, Dote_pos_y1 / 4 + 2);*/
        //------
    }
public:
    void BackgroundDraw(HDC hdc, bool p_ctrl)
    {
        //Sky
        //Set color
        SetDCBrushColor(hdc, RGB(5, 116, 129));
        SetDCPenColor(hdc, RGB(5, 116, 129));
        //Draw sky
        if (p_ctrl) Rectangle(hdc, 0, 0, Display.right, Display.bottom / 2 - 50);
        else Rectangle(hdc, 0, 0, Display.right, Display.bottom / 2);
        //------

        //Floor
        //Set color
        SetDCBrushColor(hdc, RGB(93, 93, 93));
        SetDCPenColor(hdc, RGB(93, 93, 93));
        //Draw floor
        if (p_ctrl) Rectangle(hdc, 0, Display.bottom / 2 - 50, Display.right, Display.bottom);
        else Rectangle(hdc, 0, Display.bottom / 2, Display.right, Display.bottom);
        //------
    }

    void RayCasting(HDC hdc, int p_pos_x, int p_pos_y, float p_angle, float p_delta_angle, int p_FOV, int p_FOV_depth, int p_rays_num, bool p_ctrl, int n_pos_x, int n_pos_y)
    {
        float Cur_angle = p_angle - p_FOV / 2.f;

        for (int i = 0; i < p_rays_num; i++)
        {
            int x_x = 0, x_y = 0, x_d = p_FOV_depth + 1, y_x = 0, y_y = 0, y_d = p_FOV_depth + 1, nx_d = p_FOV_depth + 1, ny_d = p_FOV_depth + 1;

            //Walls d
            for (int x = 0; x <= map_x * 100; x += 100)
            {
                int d = (x - p_pos_x) / cos(Cur_angle * PI / 180);
                if (d <= p_FOV_depth && d > 0)
                {
                    int y = d * sin(Cur_angle * PI / 180) + p_pos_y;

                    for (int y_st = 0; y_st < map_y; y_st++)
                    {
                        for (int x_st = 0; x_st < map_x; x_st++)
                        {
                            if (map[y_st][x_st] == 'w')
                            {
                                if (x >= 100 * x_st - 1 && x <= 100 * x_st + 100 && y >= 100 * y_st - 1 && y <= 100 * y_st + 100)// && y > 0)
                                {
                                    if (x_d == p_FOV_depth + 1 || x_d > d)
                                    {
                                        x_x = x;
                                        x_y = y;
                                        x_d = d;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            for (int y = 0; y <= map_y * 100; y += 100)
            {
                int d = (y - p_pos_y) / sin(Cur_angle * PI / 180);
                if (d <= p_FOV_depth && d > 0)
                {
                    int x = d * cos(Cur_angle * PI / 180) + p_pos_x;

                    for (int y_st = 0; y_st < map_y; y_st++)
                    {
                        for (int x_st = 0; x_st < map_x; x_st++)
                        {
                            if (map[y_st][x_st] == 'w')
                            {
                                if (x >= 100 * x_st - 1 && x <= 100 * x_st + 100 && y >= 100 * y_st - 1 && y <= 100 * y_st + 100)// && y > 0)
                                {
                                    if (y_d == p_FOV_depth + 1 || y_d > d)
                                    {
                                        y_x = x;
                                        y_y = y;
                                        y_d = d;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            //NPC d
            for (int n_x = n_pos_x - 15; n_x <= n_pos_x + 15; n_x += 30)
            {
                int n_d = (n_x - p_pos_x) / cos(Cur_angle * PI / 180);
                if (n_d <= p_FOV_depth && n_d > 0)
                {
                    int n_y = n_d * sin(Cur_angle * PI / 180) + p_pos_y;
                    if (n_x >= n_pos_x - 15 - 1 && n_x <= n_pos_x + 15 && n_y >= n_pos_y - 15 - 1 && n_y <= n_pos_y + 15)
                    {
                        if (nx_d == p_FOV_depth + 1 || n_d < nx_d)
                        {
                            nx_d = n_d;
                        }
                    }

                }
            }
            for (int n_y = n_pos_y - 15; n_y <= n_pos_y + 15; n_y += 30)
            {
                int n_d = (n_y - p_pos_y) / sin(Cur_angle * PI / 180);
                if (n_d <= p_FOV_depth && n_d > 0)
                {
                    int n_x = n_d * cos(Cur_angle * PI / 180) + p_pos_x;

                    if (n_x >= n_pos_x - 15 - 1 && n_x <= n_pos_x + 15 && n_y >= n_pos_y - 15 - 1 && n_y <= n_pos_y + 15)
                    {
                        if (ny_d == p_FOV_depth + 1 || n_d < ny_d)
                        {
                            ny_d = n_d;
                        }
                    }

                }
            }

            //Fish eye fix
            //x_d *= cos((p_angle - Cur_angle) * PI / 180);
            //y_d *= cos((p_angle - Cur_angle) * PI / 180);
            //nx_d *= cos((p_angle - Cur_angle) * PI / 180);
            //ny_d *= cos((p_angle - Cur_angle) * PI / 180);
            //------

            //Walls
            if (x_d == p_FOV_depth + 1 && y_d != p_FOV_depth + 1)
            {
                int h = p_FOV_depth * 100 / y_d;
                if (h > Display.bottom + 100) h = Display.bottom + 100;
                int color = 68 - y_d / 14.705882352941176470588235294118;
                //Set color
                SetDCBrushColor(hdc, RGB(color / 7.5555555555555555555555555555556, color, color / 5.2307692307692307692307692307692));
                SetDCPenColor(hdc, RGB(color / 7.5555555555555555555555555555556, color, color / 5.2307692307692307692307692307692));
                //Draw rect
                if (p_ctrl) Rectangle(hdc, i, (Display.bottom - h) / 2 - 50, i + 1, (Display.bottom + h) / 2 - 50);
                else Rectangle(hdc, i, (Display.bottom - h) / 2, i + 1, (Display.bottom + h) / 2);
            }
            else if (y_d == p_FOV_depth + 1 && x_d != p_FOV_depth + 1)
            {
                int h = p_FOV_depth * 100 / x_d;
                if (h > Display.bottom + 100) h = Display.bottom + 100;
                int color = 68 - x_d / 14.705882352941176470588235294118;
                //Set color
                SetDCBrushColor(hdc, RGB(color / 7.5555555555555555555555555555556, color, color / 5.2307692307692307692307692307692));
                SetDCPenColor(hdc, RGB(color / 7.5555555555555555555555555555556, color, color / 5.2307692307692307692307692307692));
                //Draw rect
                if (p_ctrl) Rectangle(hdc, i, (Display.bottom - h) / 2 - 50, i + 1, (Display.bottom + h) / 2 - 50);
                else Rectangle(hdc, i, (Display.bottom - h) / 2, i + 1, (Display.bottom + h) / 2);
            }
            else if (x_d < y_d && x_d != p_FOV_depth + 1)
            {
                int h = p_FOV_depth * 100 / x_d;
                if (h > Display.bottom + 100) h = Display.bottom + 100;
                int color = 68 - x_d / 14.705882352941176470588235294118;
                //Set color
                SetDCBrushColor(hdc, RGB(color / 7.5555555555555555555555555555556, color, color / 5.2307692307692307692307692307692));
                SetDCPenColor(hdc, RGB(color / 7.5555555555555555555555555555556, color, color / 5.2307692307692307692307692307692));
                //Draw rect
                if (p_ctrl) Rectangle(hdc, i, (Display.bottom - h) / 2 - 50, i + 1, (Display.bottom + h) / 2 - 50);
                else Rectangle(hdc, i, (Display.bottom - h) / 2, i + 1, (Display.bottom + h) / 2);
            }
            else if (y_d < x_d && y_d != p_FOV_depth + 1)
            {
                int h = p_FOV_depth * 100 / y_d;
                if (h > Display.bottom + 100) h = Display.bottom + 100;
                int color = 68 - y_d / 14.705882352941176470588235294118;
                //Set color
                SetDCBrushColor(hdc, RGB(color / 7.5555555555555555555555555555556, color, color / 5.2307692307692307692307692307692));
                SetDCPenColor(hdc, RGB(color / 7.5555555555555555555555555555556, color, color / 5.2307692307692307692307692307692));
                //Draw rect
                if (p_ctrl) Rectangle(hdc, i, (Display.bottom - h) / 2 - 50, i + 1, (Display.bottom + h) / 2 - 50);
                else Rectangle(hdc, i, (Display.bottom - h) / 2, i + 1, (Display.bottom + h) / 2);
            }
            else if (x_d == y_d && x_d != p_FOV_depth + 1 && y_d != p_FOV_depth + 1)
            {
                int h = p_FOV_depth * 100 / x_d;
                if (h > Display.bottom + 100) h = Display.bottom + 100;
                int color = 68 - x_d / 14.705882352941176470588235294118;
                //Set color
                SetDCBrushColor(hdc, RGB(color / 7.5555555555555555555555555555556, color, color / 5.2307692307692307692307692307692));
                SetDCPenColor(hdc, RGB(color / 7.5555555555555555555555555555556, color, color / 5.2307692307692307692307692307692));
                //Draw rect
                if (p_ctrl) Rectangle(hdc, i, (Display.bottom - h) / 2 - 50, i + 1, (Display.bottom + h) / 2 - 50);
                else Rectangle(hdc, i, (Display.bottom - h) / 2, i + 1, (Display.bottom + h) / 2);
            }

            //NPC
            if ((nx_d < x_d && nx_d < y_d) || (ny_d < x_d && ny_d < y_d))
            {
                if (nx_d == p_FOV_depth + 1 && ny_d != p_FOV_depth + 1)
                {
                    int h = p_FOV_depth * 100 / ny_d;
                    if (h > Display.bottom + 100) h = Display.bottom + 100;
                    int color = 201 - ny_d / 5;
                    //Set color
                    SetDCBrushColor(hdc, RGB(color, color / 2.5, 0));
                    SetDCPenColor(hdc, RGB(color, color / 2.5, 0));
                    //Draw rect
                    if (p_ctrl) Rectangle(hdc, i, (Display.bottom - h) / 2 - 50, i + 1, (Display.bottom + h) / 2 - 50);
                    else Rectangle(hdc, i, (Display.bottom - h) / 2, i + 1, (Display.bottom + h) / 2);
                }
                else if (ny_d == p_FOV_depth + 1 && nx_d != p_FOV_depth + 1)
                {
                    int h = p_FOV_depth * 100 / nx_d;
                    if (h > Display.bottom + 100) h = Display.bottom + 100;
                    int color = 201 - nx_d / 5;
                    //Set color
                    SetDCBrushColor(hdc, RGB(color, color / 2.5, 0));
                    SetDCPenColor(hdc, RGB(color, color / 2.5, 0));
                    //Draw rect
                    if (p_ctrl) Rectangle(hdc, i, (Display.bottom - h) / 2 - 50, i + 1, (Display.bottom + h) / 2 - 50);
                    else Rectangle(hdc, i, (Display.bottom - h) / 2, i + 1, (Display.bottom + h) / 2);
                }
                else if (nx_d < ny_d && nx_d != p_FOV_depth + 1)
                {
                    int h = p_FOV_depth * 100 / nx_d;
                    if (h > Display.bottom + 100) h = Display.bottom + 100;
                    int color = 201 - nx_d / 5;
                    //Set color
                    SetDCBrushColor(hdc, RGB(color, color / 2.5, 0));
                    SetDCPenColor(hdc, RGB(color, color / 2.5, 0));
                    //Draw rect
                    if (p_ctrl) Rectangle(hdc, i, (Display.bottom - h) / 2 - 50, i + 1, (Display.bottom + h) / 2 - 50);
                    else Rectangle(hdc, i, (Display.bottom - h) / 2, i + 1, (Display.bottom + h) / 2);
                }
                else if (ny_d < nx_d && ny_d != p_FOV_depth + 1)
                {
                    int h = p_FOV_depth * 100 / ny_d;
                    if (h > Display.bottom + 100) h = Display.bottom + 100;
                    int color = 201 - ny_d / 5;
                    //Set color
                    SetDCBrushColor(hdc, RGB(color, color / 2.5, 0));
                    SetDCPenColor(hdc, RGB(color, color / 2.5, 0));
                    //Draw rect
                    if (p_ctrl) Rectangle(hdc, i, (Display.bottom - h) / 2 - 50, i + 1, (Display.bottom + h) / 2 - 50);
                    else Rectangle(hdc, i, (Display.bottom - h) / 2, i + 1, (Display.bottom + h) / 2);
                }
                else if (nx_d == ny_d && nx_d != p_FOV_depth + 1 && ny_d != p_FOV_depth + 1)
                {
                    int h = p_FOV_depth * 100 / nx_d;
                    if (h > Display.bottom + 100) h = Display.bottom + 100;
                    int color = 201 - nx_d / 5;
                    //Set color
                    SetDCBrushColor(hdc, RGB(color, color / 2.5, 0));
                    SetDCPenColor(hdc, RGB(color, color / 2.5, 0));
                    //Draw rect
                    if (p_ctrl) Rectangle(hdc, i, (Display.bottom - h) / 2 - 50, i + 1, (Display.bottom + h) / 2 - 50);
                    else Rectangle(hdc, i, (Display.bottom - h) / 2, i + 1, (Display.bottom + h) / 2);
                }
            }

            if (i == 719)
            {
                char nx_dc[10] = {};
                char ny_dc[10] = {};
                char x_dc[10] = {};
                char y_dc[10] = {};

                snprintf(nx_dc, 10, "%d", nx_d);
                snprintf(ny_dc, 10, "%d", ny_d);
                snprintf(x_dc, 10, "%d", x_d);
                snprintf(y_dc, 10, "%d", y_d);

                TextOut(hdc, 1400, 0, nx_dc, 5);
                TextOut(hdc, 1400, 30, ny_dc, 5);
                TextOut(hdc, 1400, 60, x_dc, 5);
                TextOut(hdc, 1400, 90, y_dc, 5);
            }

            IntersectionsAndDepth(hdc, x_x, x_y, x_d, y_x, y_y, y_d, Cur_angle, p_pos_x, p_pos_y, p_FOV_depth, p_angle);

            Cur_angle += p_delta_angle;
        }
    }

    World() {}
    ~World() {}
};

class Player
{
public:
    int pos_x = 0, pos_y = 0, static_step_size = 0, FOV, FOV_depth = 0, rays_num = 0, hp = 100;
    float angle = 0.f, delta_angle = 0.f;
    bool ctrl = 0, walk = 0, w_walk = 0, run = 0, lbut = 0, rbut = 0;
    bool previous_walk = 0, previous_w_walk = 0, previous_run = 0, previous_lbut = 0, previous_rbut = 0;

    bool is_alive()
    {
        if (hp > 0) return 1;
    }

    void keyboard()
    {
        int step_size = static_step_size;
        walk = 0;
        w_walk = 0;
        run = 0;

        if (GetKeyState(VK_LCONTROL) < 0)
        {
            step_size -= 3;
            ctrl = 1;
        }
        else if (GetKeyState(VK_LSHIFT) < 0)
        {
            run = 1;
        }

        if (GetKeyState('W') < 0)
        {
            walk = 1;
            w_walk = 1;
            if (run)
            {
                pos_x += (step_size + 5) * cos(angle * PI / 180) + 0.5;
                pos_y += (step_size + 5) * sin(angle * PI / 180) + 0.5;
            }
            else
            {
                pos_x += step_size * cos(angle * PI / 180) + 0.5;
                pos_y += step_size * sin(angle * PI / 180) + 0.5;
            }
        }
        if (GetKeyState('A') < 0)
        {
            walk = 1;
            pos_x += step_size * cos((angle - 90.0) * PI / 180) + 0.5;
            pos_y += step_size * sin((angle - 90.0) * PI / 180) + 0.5;
        }
        if (GetKeyState('S') < 0)
        {
            walk = 1;
            pos_x += step_size * cos((angle + 180.0) * PI / 180) + 0.5;
            pos_y += step_size * sin((angle + 180.0) * PI / 180) + 0.5;
        }
        if (GetKeyState('D') < 0)
        {
            walk = 1;
            pos_x += step_size * cos((angle + 90.0) * PI / 180) + 0.5;
            pos_y += step_size * sin((angle + 90.0) * PI / 180) + 0.5;
        }
        if (GetKeyState('C') < 0)
        {
            hp -= 45;
            Sleep(500);
        }
    }

    void mouse_transition()
    {
        GetCursorPos(&Cursor_point);

        if (Cursor_point.x != Display.right / 2)
        {
            angle += ((float)Cursor_point.x - Display.right / 2.f) / 10;
            SetCursorPos(Display.right / 2, Display.bottom / 2);
        }
    }

    void mouse_buttons()
    {
        lbut = 0, rbut = 0;

        if (GetKeyState(VK_LBUTTON) < 0) lbut = 1;

        if (GetKeyState(VK_RBUTTON) < 0) rbut = 1;
    }

    Player(int x, int y, float angle, int step_size, int FOV, int FOV_depth)
    {
        pos_x = x;
        pos_y = y;
        this->angle = angle;
        this->static_step_size = step_size;
        this->FOV = FOV;
        this->FOV_depth = FOV_depth;
    }
    ~Player() {}
};

class NPC
{
public:
    int pos_x = 0, pos_y = 0, hp = 100;

    NPC(int pos_x, int pos_y)
    {
        this->pos_x = pos_x;
        this->pos_y = pos_y;
    }
    ~NPC() {}
};

class GUI
{
public:
    void HP(HDC hdc, int p_hp)
    {
        SetDCPenColor(hdc, RGB(0, 0, 0));
        SetDCBrushColor(hdc, RGB(50, 50, 50));
        Rectangle(hdc, 10, 860, 312, 890);

        if (p_hp > 66)
        {
            SetDCPenColor(hdc, RGB(0, 255, 0));
            SetDCBrushColor(hdc, RGB(0, 255, 0));
            Rectangle(hdc, 11, 861, 3 * p_hp + 11, 889);
        }
        else if (p_hp > 33)
        {
            SetDCPenColor(hdc, RGB(255, 127, 39));
            SetDCBrushColor(hdc, RGB(255, 127, 39));
            Rectangle(hdc, 11, 861, 3 * p_hp + 11, 889);
        }
        else if (p_hp > 0)
        {
            SetDCPenColor(hdc, RGB(255, 0, 0));
            SetDCBrushColor(hdc, RGB(255, 0, 0));
            Rectangle(hdc, 11, 861, 3 * p_hp + 11, 889);
        }
    }

    void MiniMap(HDC hdc, int p_pos_x, int p_pos_y, int n_pos_x, int n_pos_y)
    {
        //Set color
        SetDCBrushColor(hdc, RGB(0, 255, 0));
        SetDCPenColor(hdc, RGB(0, 255, 0));

        //Walls
        for (int y = 0; y < map_y; y++)
        {
            for (int x = 0; x < map_x; x++)
            {
                if (map[y][x] == 'w')
                {
                    Rectangle(hdc, x * 100 / 4, y * 100 / 4, (x * 100 + 100) / 4, (y * 100 + 100) / 4);
                }
            }
        }
        //------

        //Player
        Rectangle(hdc, (p_pos_x - 10) / 4, (p_pos_y - 10) / 4, (p_pos_x + 10) / 4, (p_pos_y + 10) / 4);
        //------
        
        //NPC
        SetDCBrushColor(hdc, RGB(255, 0, 0));
        SetDCPenColor(hdc, RGB(255, 0, 0));
        Rectangle(hdc, (n_pos_x - 10) / 4, (n_pos_y - 10) / 4, (n_pos_x + 10) / 4, (n_pos_y + 10) / 4);
        //------
    }

    void Crosshair(HDC hdc)
    {
        Image crosshair(L"C:/Users/poJLikno/Documents/C++/VSprojects/ray_casting/x64/Debug/images/crosshair.png");
        Graphics g(hdc);
        g.DrawImage(&crosshair, (int)Display.right / 2 - 20, (int)Display.bottom / 2 - 20, crosshair.GetWidth() / 15, crosshair.GetHeight() / 15);
    }

    GUI() {}
    ~GUI() {}
};

class Weapon
{
private:
    wchar_t* weapon_static = new wchar_t[501];
    wchar_t* weapon_active = new wchar_t[501];
public:
    void DrawWeapon(HDC hdc, float x, float y, float cof, bool l_button)
    {
        if (l_button)
        {
            Image weapon(weapon_active);
            Graphics g(hdc);
            g.DrawImage(&weapon, x, y, (float)weapon.GetWidth() / cof, (float)weapon.GetHeight() / cof);
        }
        else
        {
            Image weapon(weapon_static);
            Graphics g(hdc);
            g.DrawImage(&weapon, (float)x, (float)y, (float)weapon.GetWidth() / cof, (float)weapon.GetHeight() / cof);
        }
    }

    Weapon(const wchar_t* weapon_static, const wchar_t* weapon_active)
    {
        this->weapon_static = (wchar_t*)weapon_static;
        this->weapon_active = (wchar_t*)weapon_active;
    }
    ~Weapon()
    {
        delete[] weapon_static;
        delete[] weapon_active;
    }
};

World world;
Player player(map_x * 50 + 100, map_y * 50, 0.f/*8.f*/, 5, 100, 1000);
NPC npc(map_x * 50, map_y * 50 + 100);
GUI gui;
Weapon ak47(L"C:/Users/poJLikno/Documents/C++/VSprojects/ray_casting/x64/Debug/images/weapon.png",
    L"C:/Users/poJLikno/Documents/C++/VSprojects/ray_casting/x64/Debug/images/weapon fire.png");

void DrawGame(HDC hdc)
{
    world.BackgroundDraw(hdc, player.ctrl);
    world.RayCasting(hdc, player.pos_x, player.pos_y, player.angle, player.delta_angle, player.FOV, player.FOV_depth, player.rays_num, player.ctrl, npc.pos_x, npc.pos_y);
    player.ctrl = 0;

    ak47.DrawWeapon(hdc, (float)Display.right - 900.f / 1.5, (float)Display.bottom - 395.f / 1.5 + 2.f, 1.5f, player.lbut);

    gui.Crosshair(hdc);
    gui.MiniMap(hdc, player.pos_x, player.pos_y, npc.pos_x, npc.pos_y);
    gui.HP(hdc, player.hp);
}