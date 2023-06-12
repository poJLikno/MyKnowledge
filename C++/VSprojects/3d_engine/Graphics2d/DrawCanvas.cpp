#include "Graphics2d.h"

extern Player *player;
extern Rect *my_rect;

void Graphics2d::DrawCanvas(HWND *hWnd, PAINTSTRUCT *ps)
{
    ps->hdc = BeginPaint(*hWnd, ps);
    CreateBuffer(ps);
    SetBrushColor(RED);
    SetPenColor(BLACK);

    float cof_y = 1.f / (float)WinHeight;
    float cof_x = 1.f / (float)WinWidth;

    float old_xy = player->GetAngleXY();
    float old_xz = player->GetAngleXZ();

    player->SetAngleXY(player->GetAngleXY() + 50.f);
    player->SetAngleXZ(player->GetAngleXZ() + 40.f);
    for (float i = 0.5f; i > -0.5f; i -= cof_y)
    {
        for (float j = -0.5f; j < 0.5f; j += cof_x)
        {
            if (j == 0.f) DrawPixel(j, i, BLUE);
            player->SetFacingByAngle();
            if (my_rect->FindIntersection(player->GetFacing(), player->GetX(), player->GetY(), player->GetZ()))
                DrawPixel(j, i, GREEN);//RGB(int(255.f * (j + 0.5f)), int(255.f * (i + 0.5f)), 0));
            player->SetAngleXY(player->GetAngleXY() - cof_x * 100.f);
        }
        player->SetAngleXY(old_xy + 50.f);
        player->SetAngleXZ(player->GetAngleXZ() - cof_y * 80.f);
    }

    player->SetAngleXY(old_xy);
    player->SetAngleXZ(old_xz);
    player->SetFacingByAngle();

    // Test
    DrawPixel(player->GetX(), player->GetY(), GREEN);

    float cx = 0.3f, cy = 0.2f, r = 0.1f;
    DrawRect(cx, cy, r, r);
    DrawPixel(cx, cy, GREEN);

    SetPenColor(BLUE);
    DrawLine(player->GetX(), player->GetY(), player->GetFacing().get_x() + player->GetX(), player->GetFacing().get_y() + player->GetY());

    if (my_rect->FindIntersection(player->GetFacing(), player->GetX(), player->GetY(), player->GetZ()))
        DrawCircle(-0.1f, 0.1f, 0.05f);
    DrawPixel(-0.1f - 0.05f, 0.1f + 0.05f, GREEN);
    DrawPixel(-0.1f + 0.05f, 0.1f - 0.05f, GREEN);

    SetBuffer(ps);
    EndPaint(*hWnd, ps);
}

//Gdiplus::Graphics graphics(ps->hdc);
//Gdiplus::Image image(L"image.jpg");
//graphics.DrawImage(&image, 0, 0);


    /*DrawPixel(player->GetX(), player->GetY(), GREEN);

    float cx = 0.3f, cy = 0.2f, r = 0.1f;
    DrawRect(cx, cy, r, r);
    DrawPixel(cx, cy, GREEN);

    SetPenColor(BLUE);
    DrawLine(player->GetX(), player->GetY(), player->GetFacing().get_x() + player->GetX(), player->GetFacing().get_y() + player->GetY());

    if (my_rect->FindIntersection(player->GetFacing(), player->GetX(), player->GetY(), player->GetZ()))
        DrawCircle(-0.1f, 0.1f, 0.05f);
    DrawPixel(-0.1f - 0.05f, 0.1f + 0.05f, GREEN);
    DrawPixel(-0.1f + 0.05f, 0.1f - 0.05f, GREEN);*/