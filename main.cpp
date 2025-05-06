#include "game.h"
#include "player.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("SDL2 Game ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    GameState state = MAIN_MENU;// mặc định ở main menu
    bool running = true;
    SDL_Event event;
    std::vector<SDL_Rect> platforms = {
    {0, 500, 800, 100},     // Mặt đất (ground)
    {100, 420, 150, 20},    // Tầng thấp gần mặt đất
    {300, 350, 150, 20},    // Tầng giữa
    {500, 280, 150, 20},    // Tầng cao hơn
    {200, 210, 150, 20},    // Tầng gần đỉnh
    {400, 140, 120, 20},    // Tầng cao nhất
    };


    Entity player = { {100, 100}, {0, 0}, {100, 100, 32, 32}, false , true };
    Entity player2 = { {100, 100}, {0, 0}, {100, 100, 32, 32}, false , false };
    std::vector<Bullet> bullets;
    std::vector<Entity> enemies = { { {600, 400}, {0, 0}, {600, 400, 32, 32}, true , true} };

    Uint32 lastTick = SDL_GetTicks();// lay tg luc bat dau chuong trinh 
    TTF_Font* font = TTF_OpenFont("Tagesschrift-Regular.ttf", 24);  // Đảm bảo file "arial.ttf" nằm cùng thư mục
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return -1;
    }
    while (running) {
        Uint32 currentTick = SDL_GetTicks(); // lay tg tai day de tinh delta time
        float deltaTime = (currentTick - lastTick) / 1000.0f;
        lastTick = currentTick;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;// thoát

            if (state == MAIN_MENU) {
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
                    state = PLAYING;
                }
            }
            else if (state == PLAYING) {
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_1) state = PLAYING1;
                    if (event.key.keysym.sym == SDLK_2) state = PLAYING2;
                    if (event.key.keysym.sym == SDLK_3) state = PLAYING3;
                }
            }
            else if (state == PLAYING1) {
                player_1_input(event, player, bullets);
            }
            else if (state == PLAYING2) {
                player_1_input(event, player, bullets);
                player_2_input(event, player2, bullets);
            }
            else if (state == PLAYING3) {
                player_1_input(event, player, bullets);
                player_2_input(event, player2, bullets);
            }
            else if (state == PAUSED) {
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                    state = PLAYING;
                }
            }
        }// while
        if (state == PLAYING1) {
            player.update(deltaTime);// cập nhật vị trí hiện tại của player 

            for (auto& b : bullets) {
                if (b.active) b.pos.x += b.speed * deltaTime;
                if (b.pos.x > 800) b.active = false;
            }
            // Check bullet-enemy collision
            for (auto& enemy : enemies) {
                for (auto& b : bullets) {
                    if (b.active && checkCollision(enemy.hitbox, b.getRect())) {
                        b.active = false;
                        enemy.pos.x = -1000; // Move offscreen as simple 'destroy'
                    }
                }
            }

            for (auto& enemy : enemies) {
                enemy.hitbox = { (int)enemy.pos.x, (int)enemy.pos.y, 32, 32 };
            }
        }
        if (state == PLAYING2) {
            player.update(deltaTime);
            player2.update(deltaTime);
            for (auto& b : bullets) {
                if (b.active) b.pos.x += b.speed * deltaTime;
                if (b.pos.x > 800) b.active = false;
                if (b.pos.x < 0) b.active = false;
            }
            // Check bullet-enemy collision
            for (auto& enemy : enemies) {
                for (auto& b : bullets) {
                    if (b.active && checkCollision(enemy.hitbox, b.getRect())) {
                        b.active = false;
                        enemy.pos.x = -1000; // Move offscreen as simple 'destroy'
                    }
                }
            }

            for (auto& enemy : enemies) {
                enemy.hitbox = { (int)enemy.pos.x, (int)enemy.pos.y, 32, 32 };
            }

        }
        if (state == PLAYING3) {
            player.update2(deltaTime, platforms);
            player2.update2(deltaTime, platforms);
            for (auto& b : bullets) {
                if (b.active) b.pos.x += b.speed * deltaTime;
                if (b.pos.x > 800) b.active = false;
                if (b.pos.x < 0) b.active = false;
            }
            // Check bullet-enemy collision
            for (auto& enemy : enemies) {
                for (auto& b : bullets) {
                    if (b.active && checkCollision(enemy.hitbox, b.getRect())) {
                        b.active = false;
                        enemy.pos.x = -1000; // Move offscreen as simple 'destroy'
                    }
                }
            }

            for (auto& enemy : enemies) {
                enemy.hitbox = { (int)enemy.pos.x, (int)enemy.pos.y, 32, 32 };
            }

        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        // phần render hình ảnh 
        if (state == MAIN_MENU) {
            // Render main menu placeholder
            if (state == MAIN_MENU) {
                SDL_Texture* texMain = IMG_LoadTexture(renderer, "img/nengame.png");
                SDL_Color white = { 255, 255, 255 };

                SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Press Enter to Start", white);
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

                SDL_Rect textRect = { 300, 250, textSurface->w, textSurface->h };
                SDL_Rect recMain = { 0 ,0 , 800, 600 };
                SDL_RenderCopy(renderer, texMain, NULL, &recMain);
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(texMain);
                SDL_DestroyTexture(textTexture);
            }
        }
        else if (state == OPTIONS) {
            // Render options menu placeholder
        }
        else if (state == PLAYING1 || state == PAUSED) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_Rect playerRect = { (int)player.pos.x, (int)player.pos.y, 32, 32 };
            SDL_RenderFillRect(renderer, &playerRect);

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            for (const auto& b : bullets) {
                if (b.active) {
                    SDL_Rect bulletRect = b.getRect();
                    SDL_RenderFillRect(renderer, &bulletRect);
                }
            }

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            for (const auto& enemy : enemies) {
                SDL_RenderFillRect(renderer, &enemy.hitbox);
            }
        }
        else if (state == PLAYING2 || state == PAUSED) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_Rect playerRect = { (int)player.pos.x, (int)player.pos.y, 32, 32 };
            SDL_Rect playerRect2 = { (int)player2.pos.x, (int)player2.pos.y, 32, 32 };

            SDL_RenderFillRect(renderer, &playerRect);
            SDL_RenderFillRect(renderer, &playerRect2);

            //render bullet
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            for (const auto& b : bullets) {
                if (b.active) {
                    SDL_Rect bulletRect = b.getRect();
                    SDL_RenderFillRect(renderer, &bulletRect);
                }
            }
            // render enemy
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            for (const auto& enemy : enemies) {
                SDL_RenderFillRect(renderer, &enemy.hitbox);
            }
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
                            player.pos.x = -1000;

                        }
                    }
                    // Nếu đạn chạm player2
                    if (checkCollision(bRect, player2.hitbox)) {
                        if (player2.directionR == 0) {
                            std::cout << "Player 2 tử vong!" << std::endl;
                            player2.pos.x = -1000;
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
                            player.pos.x = -1000;

                        }
                    }
                    // Nếu đạn chạm player2
                    if (checkCollision(bRect, player2.hitbox)) {
                        if (player2.directionR == 1) {
                            std::cout << "Player 2 tử vong!" << std::endl;
                            player2.pos.x = -1000;
                            b.active = false;
                        }
                        else if (player2.directionR == 0) {
                            b.active = 0;
                        }
                    }
                }
            }

        }
        else if (state == PLAYING3 || state == PAUSED) {
            SDL_SetRenderDrawColor(renderer, 150, 75, 0, 255); // Màu nâu
            for (const auto& plat : platforms) {
                SDL_RenderFillRect(renderer, &plat);
            }

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_Rect playerRect = { (int)player.pos.x, (int)player.pos.y, 32, 32 };
            SDL_Rect playerRect2 = { (int)player2.pos.x, (int)player2.pos.y, 32, 32 };

            SDL_RenderFillRect(renderer, &playerRect);
            SDL_RenderFillRect(renderer, &playerRect2);

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            for (const auto& b : bullets) {
                if (b.active) {
                    SDL_Rect bulletRect = b.getRect();
                    SDL_RenderFillRect(renderer, &bulletRect);
                }
            }
            for (auto& b : bullets) {
                if (!b.active) continue;

                SDL_Rect bRect = b.getRect();
                check_renderBullet(player, player2, bullets);
                // cơ chế khiên và tử vong ;
               
            }
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            for (const auto& enemy : enemies) {
                SDL_RenderFillRect(renderer, &enemy.hitbox);
            }

        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
