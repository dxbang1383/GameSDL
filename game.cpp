#include "game.h"
#include "player.h"
void Entity::renderEntity(SDL_Renderer* renderer) {

    SDL_Rect backRect;
    if (directionR) {
        backRect = { hitbox.x - 5, hitbox.y, 5, hitbox.h };
    }
    else {
        backRect = { hitbox.x + hitbox.w, hitbox.y, 5,hitbox.h };
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &backRect);

    SDL_SetRenderDrawColor(renderer, 0, 255 , 0, 255);
    SDL_RenderFillRect(renderer,& hitbox );
}
void Entity::renderEntity2(SDL_Renderer* renderer) {
    SDL_Rect backRect;
    if (directionR) {
        backRect = { hitbox.x - 5, hitbox.y, 5, hitbox.h };
    }
    else {
        backRect = { hitbox.x + hitbox.w, hitbox.y, 5,hitbox.h };
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &backRect);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &hitbox);
}

void Entity::update2(float deltaTime, const std::vector<SDL_Rect>& platforms) {
    //tao toc do roi
    vel.y += 500 * deltaTime;

    // tạo hitbox tạm thời để kiểm tra nếu player sắp chạm nền(hit box tương lai

    SDL_Rect predictedHitbox = {
        (int)pos.x,
        (int)(pos.y + vel.y * deltaTime + 1), // +1 để dự đoán một chút phía dưới
        32, 32
    };

    // Mặc định không đứng trên nền
    onGround = false;

    for (const auto& plat : platforms) {
        if (checkCollision(predictedHitbox, plat)) {
            int playerBottom = (int)(pos.y + 32);
            int platformTop = plat.y;

            // Nếu rơi xuống và sắp chạm platform từ trên
            if (vel.y >= 0 && playerBottom <= platformTop + 5) {
                onGround = true;
                break;
            }
        }
    }

    // Cập nhật vị trí
    pos.x += vel.x * deltaTime;
    pos.y += vel.y * deltaTime;

    // Kiểm tra va chạm thực tế và điều chỉnh
    for (const auto& plat : platforms) {
        SDL_Rect currentHitbox = { (int)pos.x, (int)pos.y, 32, 32 };
        if (checkCollision(currentHitbox, plat)) {
            int playerBottom = (int)(pos.y + 32);
            int platformTop = plat.y;

            if (vel.y >= 0 && playerBottom > platformTop && playerBottom - platformTop <= 10) {
                pos.y = plat.y - 32;
                vel.y = 0;
                onGround = true;
                break;
            }
        }
    }

    // Giới hạn biên
    if (pos.x < 0) pos.x = 0;
    if (pos.x > 800 - 32) pos.x = 800 - 32;

    // Cập nhật hitbox cuối cùng
    hitbox = { (int)pos.x, (int)pos.y, 32, 32 };
}
void Entity::jump() {
    if (onGround) {
        vel.y = -300; // nhảy lên (vận tốc để nhảy  ) 
        onGround = false;// không còn trên mặt đất
    }
}

bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return SDL_HasIntersection(&a, &b);
}



