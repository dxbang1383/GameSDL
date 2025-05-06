#include "game.h"

void Entity::update(float deltaTime) {
    vel.y += 500 * deltaTime;// trọng lực 
    pos.x += vel.x * deltaTime;// cập nhật x , y 
    pos.y += vel.y * deltaTime;
    // kiểm tra rơi xuống mặt đất
    if (pos.y > 400) {
        //neu roi qua thi tro lai mat dat
        pos.y = 400;
        vel.y = 0;
        onGround = true;
    }

    else {
        onGround = false;
    }if (pos.x < 0) {
        pos.x = 0;
    }
    if (pos.x > 800 - 32) {
        pos.x = 800 - 32;
    }
    // cập nhật hình chữ nhật va chạm 
    hitbox = { (int)pos.x, (int)pos.y, 32, 32 };
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
    // kiểm tra va chạm giữa 2 hcn 
    return SDL_HasIntersection(&a, &b);
}
bool checkCollisionFloat(SDL_FRect a, SDL_FRect b) {
    return !(a.x + a.w <= b.x || a.x >= b.x + b.w ||
        a.y + a.h <= b.y || a.y >= b.y + b.h);
}

