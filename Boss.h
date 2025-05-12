#pragma once
#include"game.h"
#include <vector>

struct BossSniper {
    Vector2 pos;
    Vector2 vel;
    SDL_Rect hitbox;
    Uint32 shootCooldown = 0;
    bool active = 1;
    std::vector<BulletB> bullets;
    int direction = -1;

    BossSniper(float x, float y);
    void update(float deltaTime, const Entity& player);
    void draw(SDL_Renderer* renderer);
};
