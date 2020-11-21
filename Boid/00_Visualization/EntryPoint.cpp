#include <raylib.h>
#include <cmath>
#include <ctime>
#include <vector>

int width;
int height;

class Boid
{
private:
    Vector2 mPos;
    Vector2 mVel;
    float mSize;

public:
    Boid(Vector2 pos, Vector2 vel, float size)
    {
        mPos = pos;
        mVel = vel;
        mSize = size;
    }

    void Update()
    {
        if (mPos.x < 0) mPos.x = width;
        if (mPos.y < 0) mPos.y = height;
        if (mPos.x > width) mPos.x = 0;
        if (mPos.y > height) mPos.y = 0;

        mPos.x += mVel.x;
        mPos.y += mVel.y;
    }

    void Render()
    {
        float angleH = std::atan2(mVel.y, mVel.x);
        float angleL = angleH + 0.3 + PI / 2;
        float angleR = angleH - 0.3 - PI / 2;

        Vector2 head = {
            (mSize * 70) * std::cos(angleH) + mPos.x,
            (mSize * 70) * std::sin(angleH) + mPos.y,
        };
        Vector2 tailL = {
            (mSize * 30) * std::cos(angleL) + mPos.x,
            (mSize * 30) * std::sin(angleL) + mPos.y,
        };
        Vector2 tailR = {
            (mSize * 30) * std::cos(angleR) + mPos.x,
            (mSize * 30) * std::sin(angleR) + mPos.y,
        };
        DrawTriangleLines(head, tailR, mPos, WHITE);
        DrawTriangleLines(head, mPos, tailL, WHITE);
    }
};

int main()
{
    srand(time(nullptr));

    width = 580;
    height = 460;

    InitWindow(width, height, "Boid");
    SetTargetFPS(60);

    std::vector<Boid> boids;

    for (int i = 0; i < 20; ++i)
    {
        boids.push_back(Boid(
        {
            (float) GetRandomValue(0, width),
            (float) GetRandomValue(0, height),
        }, {
            (float) GetRandomValue(-5, 5),
            (float) GetRandomValue(-5, 5),
        },
            GetRandomValue(1, 100) / 100.0
        ));
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground({23, 23, 23});

        for (Boid& boid : boids)
        {
            boid.Update();
            boid.Render();
        }

        EndDrawing();
    }

    CloseWindow();
}
