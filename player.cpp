
#include "player.h"

void player1_shot(SDL_Event& event, Entity& player, std::vector<Bullet>& bullets) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_SPACE && player.directionR == 1) {
            bullets.push_back({ {player.pos.x + 32, player.pos.y + 16}, 500, true }); // tạo đạn 
        }
        if (event.key.keysym.sym == SDLK_SPACE && player.directionR == 0) {
            bullets.push_back({ {player.pos.x - 10  , player.pos.y + 16}, -500, true }); // tạo đạn 
        }

    }
}
void player1_input(SDL_Event& event, Entity& player, std::vector <Bullet>& bullets) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_w) player.jump();
    }
}
void player1_input2(Entity& player) {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    player.vel.x = 0;
    if (keystate[SDL_SCANCODE_A]) {
        player.vel.x = -200;
        player.directionR = 0;
    }
    if (keystate[SDL_SCANCODE_D]) {
        player.vel.x = 200;
        player.directionR = 1;
    }
    if (keystate[SDL_SCANCODE_W]) {
        player.jump();
    }
}
void player_1_input(SDL_Event& event, Entity& player, std::vector <Bullet>& bullets) {
    player1_input(event, player, bullets);
    player1_input2(player);
    player1_shot(event, player, bullets);
}

void player2_shot(SDL_Event& event, Entity& player, std::vector<Bullet>& bullets) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_RETURN && player.directionR == 1) {
            bullets.push_back({ {player.pos.x + 32, player.pos.y + 16}, 500, true }); // tạo đạn 
        }
        else if (event.key.keysym.sym == SDLK_RETURN && player.directionR == 0) {
            bullets.push_back({ {player.pos.x - 10, player.pos.y + 16}, -500, true }); // tạo đạn 
        }
    }
}
void player2_input(SDL_Event& event, Entity& player, std::vector <Bullet>& bullets) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_UP) player.jump();
    }
}
void player2_input2(Entity& player) {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    player.vel.x = 0;
    if (keystate[SDL_SCANCODE_LEFT]) {

        player.vel.x = -200;
        player.directionR = 0;
    }
    if (keystate[SDL_SCANCODE_RIGHT]) {
        player.vel.x = 200;
        player.directionR = 1;
    }
    if (keystate[SDL_SCANCODE_UP]) {
        player.jump();
    }
}
void player_2_input(SDL_Event& event, Entity& player, std::vector <Bullet>& bullets) {
    player2_input(event, player, bullets);
    player2_input2(player);
    player2_shot(event, player, bullets);
}

void check_renderBullet(Entity& player, Entity& player2, std::vector <Bullet>& bullets, int& c1 , int &c2) {

    for (auto& b : bullets) {
        if (!b.active) continue;

        SDL_Rect bRect = b.getRect();

        // cơ chế khiên và tử vong ;
        if (b.speed > 0) {
            // đạn đi  từ trái sang phải 
            if (checkCollision(bRect, player.hitbox)) {
                // nếu directtionR =1 tức là nhân vật hướng mặt về bên phải , nên sẽ đỡ đc đòn đánh ;
                if (player.directionR == 1) {
                    b.active = 0;
                }
                else if (player.directionR == 0) {
                    b.active = 0;
                    std::cout << "Player 1 tu vong" << std::endl;
                    c2 = c2 + 1;
                    player.pos.y = 0;

                }
            }
            // Nếu đạn chạm player2
            if (checkCollision(bRect, player2.hitbox)) {
                if (player2.directionR == 0) {
                    std::cout << "Player 2 tu vong!" << std::endl;
                    c1 = c1 + 1;
                    player2.pos.y = 0;
                    b.active = false;
                }
                else if (player2.directionR == 1) {
                    b.active = 0;
                }
            }
        }
        if (b.speed < 0) {
            // đạn đi  từ pahi sang trai
            if (checkCollision(bRect, player.hitbox)) {
                // nếu directtionR = 0 tức là nhân vật hướng mặt về bên trai , nên sẽ đỡ đc đòn đánh ;
                if (player.directionR == 0) {
                    b.active = 0;
                }
                else if (player.directionR == 1) {
                    b.active = 0;
                    std::cout << "Player 1 tu vong" << std::endl;
                    c2 = c2 + 1;
                    player.pos.y =0;

                }
            }
            // Nếu đạn chạm player2
            if (checkCollision(bRect, player2.hitbox)) {
                if (player2.directionR == 1) {
                    std::cout << "Player 2 tu vong!" << std::endl;
                    c1 = c1 + 1;
                    player2.pos.y = 0;
                    b.active = false;
                }
                else if (player2.directionR == 0) {
                    b.active = 0;
                }
            }
        }
    }
}





