#include <raylib.h>
#include <cmath>
#include <string>

void resetBall(Vector2 &ball_position, Vector2 &ball_velocity, float ball_speed) {
    ball_position = {
            .x = (float)GetScreenWidth() / 2,
            .y = (float)GetScreenHeight() / 2
    };
    // Generate random direction for ball
    ball_velocity = {
            .x = (float)GetRandomValue(-100, 100),
            .y = (float)GetRandomValue(-50, 50)
    };
    float ball_velocity_magnitude = sqrt(ball_velocity.x * ball_velocity.x + ball_velocity.y * ball_velocity.y);
    ball_velocity.x /= ball_velocity_magnitude;
    ball_velocity.y /= ball_velocity_magnitude;
    ball_velocity.x *= ball_speed;
    ball_velocity.y *= ball_speed;
}

int main() {
    InitWindow(800, 400, "Pong");
    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Configs
    static const float ball_radius = 5.0f;
    static const float collider_width = 6.0f;
    static const float collider_height = 48.0f;
    static const float divider_width = 1.0f;
    static const float divider_separation = 12.0f;
    static const float ball_speed = 10.0f;
    static const float score_font_size = 40.0f;

    // Params
    Vector2 ball_position;
    Vector2 ball_velocity;
    resetBall(ball_position, ball_velocity, ball_speed);
    /**/

    int user_points = 0, computer_points = 0;

    float collider_left = (GetScreenHeight() - collider_height) / 2;
    float collider_right = (GetScreenHeight() - collider_height) / 2;

    while(!WindowShouldClose()) {

        //Game Logic

        collider_right = GetMouseY() - collider_height / 2;
        collider_left = ball_position.y - collider_height / 2;

        ball_position.x += ball_velocity.x;
        ball_position.y += ball_velocity.y;

        if(ball_position.y < ball_radius) {
            ball_velocity.y = abs(ball_velocity.y);
        }
        if(ball_position.y > GetScreenHeight() - ball_radius) {
            ball_velocity.y = -abs(ball_velocity.y);
        }

        if(CheckCollisionCircleRec(ball_position, ball_radius, Rectangle(0, collider_left, collider_width, collider_height))) {
            ball_velocity.x = abs(ball_velocity.x);
        }
        if(CheckCollisionCircleRec(ball_position, ball_radius, Rectangle(GetScreenWidth() - collider_width, collider_right, collider_width, collider_height))) {
            ball_velocity.x = -abs(ball_velocity.x);
        }

        if(ball_position.x < -2 * ball_radius) {
            //player point
            user_points++;

            resetBall(ball_position, ball_velocity, ball_speed);
        }
        if(ball_position.x > GetScreenWidth() + 2 * ball_radius + 100) {
            //computer point
            computer_points++;

            resetBall(ball_position, ball_velocity, ball_speed);
        }

        // Drawing
        BeginDrawing();

        ClearBackground(BLACK);

        DrawRectangle(0, collider_left, collider_width, collider_height, WHITE);
        DrawRectangle(GetScreenWidth() - collider_width, collider_right, collider_width, collider_height, WHITE);
        for(int i = 0, l = 0; l < GetScreenHeight(); i++, l += 2 * divider_separation) {
            DrawRectangle((GetScreenWidth() - divider_width) / 2, l, divider_width, divider_separation, WHITE);
        }
        DrawCircle(ball_position.x, ball_position.y, ball_radius, WHITE);

        DrawText(std::to_string(computer_points).c_str(), GetScreenWidth() / 2 - 2 * score_font_size, 2, score_font_size, WHITE);
        DrawText(std::to_string(user_points).c_str(), GetScreenWidth() / 2 + score_font_size, 2, score_font_size, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
