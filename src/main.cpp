#include <iostream>
#include <raylib.h>
#include <vector>
using namespace std;

int main() {
    InitWindow(800, 600, "raylib");
    SetTargetFPS(60);
    int screenWidth = GetScreenWidth();
    Vector2 center = {GetScreenWidth()/2, GetScreenHeight()/2};
    vector<Rectangle> redRectangles;
    float rotation = 0;
    Rectangle box = { GetScreenWidth() / 2.0f - 30, GetScreenHeight() / 2.0f - 30, 60, 60 };
    SetWindowOpacity(0.8f);

    while (!WindowShouldClose()) {
        // Updates
        box.x = GetMouseX() - box.width / 2;
        box.y = GetMouseY() - box.height / 2;

        if (IsMouseButtonPressed(0))
            redRectangles.push_back({ GetMouseX() - 25, GetMouseY() - 25, 50, 50 });

        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        DrawFPS(10, 10);
        for (const auto& redRect : redRectangles)
            DrawRectangleRec(redRect, RED);
            
        DrawRectangleRec(box, BLUE);
        DrawPoly(center, 5, 50, rotation, GRAY);

        rotation += 2;

        EndDrawing();
    }

    return 0;
}
