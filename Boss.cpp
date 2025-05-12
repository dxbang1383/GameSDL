#include "Boss.h"
#include "player.h"


BossSniper::BossSniper(float x, float y) {
    pos = { x, y };
    vel = { 0, 0 };
    hitbox = { (int)x, (int)y, 32, 32 };
}

void BossSniper::update(float deltaTime, const Entity& player) {
    // Hướng nhìn về phía người chơi
    direction = (player.pos.x < pos.x) ? -1 : 1;

    if (SDL_GetTicks() - shootCooldown > 5000) {
        // Tính toán vector hướng đến người chơi
        float dx = player.pos.x + player.hitbox.w / 2 - (pos.x + 16);
        float dy = player.pos.y + player.hitbox.h / 2 - (pos.y + 16);
        float length = std::sqrt(dx * dx + dy * dy);

        if (length != 0) {
            dx /= length;
            dy /= length;
        }

        float bulletSpeed = 300.0f;

        BulletB bullet;
        bullet.pos = { pos.x + 16, pos.y + 16 };
        bullet.speedX = dx * bulletSpeed;
        bullet.speedY = dy * bulletSpeed;
        bullet.active = true;
        bullets.push_back(bullet);

        shootCooldown = SDL_GetTicks();
    }

    for (auto& b : bullets) {
        if (b.active) {
            b.pos.x += b.speedX * deltaTime;
            b.pos.y += b.speedY * deltaTime;

            if (b.pos.x < 0 || b.pos.x > 800 || b.pos.y < 0 || b.pos.y > 600) {
                b.active = false;
            }
        }
    }

    hitbox = { (int)pos.x, (int)pos.y, 32, 32 };
}

void BossSniper::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 200, 0, 200, 255);
    SDL_RenderFillRect(renderer, &hitbox);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    for (const auto& b : bullets) {
        if (b.active) {
            SDL_Rect r = b.getRect();
            SDL_RenderFillRect(renderer, &r);
        }
    }
}
