#include "game.h"
#include "player.h"
#include "Boss.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("SDL2 Game ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    BossSniper boss(300, 100);
    GameState state = MAIN_MENU;// mặc định ở main menu
    bool running = true;
    SDL_Event event;
    std::vector<SDL_Rect> platforms = {
    {0, 500, 800, 100},     
    {100, 420, 150, 20},    
    {300, 350, 150, 20},    
    {500, 280, 150, 20},    
    {200, 210, 150, 20},    
    {400, 140, 120, 20},    
    };

    Entity player = { {700, 100}, {0, 0}, {100, 100, 32, 32}, false , true };
    Entity player2 = { {100, 100}, {0, 0}, {100, 100, 32, 32}, false , false };
    std::vector<Bullet> bullets;
    std::vector<Entity> enemies = { { {600, 400}, {0, 0}, {600, 400, 32, 32}, true , true} };

    Uint32 lastTick = SDL_GetTicks();// lay tg luc bat dau chuong trinh 
    TTF_Font* font = TTF_OpenFont("PixelifySans-VariableFont_wght.ttf", 32);  

    int frameCount = 0;
    float fpsTimer = 0.0f;
    int currentFPS = 0;

    int count = 0;

    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return -1;
    }
    while (running) {
        Uint32 currentTick = SDL_GetTicks(); // lay tg tai day de tinh delta time
        float deltaTime = (currentTick - lastTick) / 1000.0f;
        lastTick = currentTick;
        frameCount++;
        fpsTimer += deltaTime;
        if (fpsTimer >= 1.0f) {
            currentFPS = frameCount;
            frameCount = 0;
            fpsTimer = 0.0f;
        }

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
                    if (event.key.keysym.sym == SDLK_4) state = PLAYING4;
                }
            }
            else if (state == PLAYING1) {
                player_1_input(event, player, bullets);
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_ESCAPE)state = MAIN_MENU;
                }
            }
            else if (state == PLAYING2) {
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_ESCAPE)state = MAIN_MENU;
                }
                player_1_input(event, player, bullets);
                player_2_input(event, player2, bullets);
            }
            else if (state == PLAYING3) {
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        state = MAIN_MENU;
                        player = { {700, 100}, {0, 0}, {100, 100, 32, 32}, false , true };
                        player2 = { {100, 100}, {0, 0}, {100, 100, 32, 32}, false , false };
                    }
                }
                player_1_input(event, player, bullets);
                player_2_input(event, player2, bullets);
            }
            else if (state == PLAYING4) {
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        state = MAIN_MENU;
                        player = { {700, 100}, {0, 0}, {100, 100, 32, 32}, false , true };
                    }
               }
                player_1_input(event, player, bullets);
            }

            else if (state == PAUSED) {
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                    state = PLAYING;
                }
            }
            
        }// while event

        //update vi tri 
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
            
            for (auto& enemy : enemies) {
                for (auto& b : bullets) {
                    if (b.active && checkCollision(enemy.hitbox, b.getRect())) {
                        b.active = false;
                        enemy.pos.x = -1000;
                    }
                }
            }

            for (auto& enemy : enemies) {
                enemy.hitbox = { (int)enemy.pos.x, (int)enemy.pos.y, 32, 32 };
            }

        }
        if (state == PLAYING4) {
            player.update2(deltaTime, platforms);
            boss.update(deltaTime, player);

            for (auto& b : bullets) {
                if (b.active) b.pos.x += b.speed * deltaTime;
                if (b.pos.x > 800 || b.pos.x < 0) b.active = false;
            }

            for (auto& b : boss.bullets) {
                if (b.active && checkCollision(player.hitbox, b.getRect())) {
                    b.active = false;
                    player.pos.x = 0;
                    player.pos.y = 0;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        // phần render hình ảnh 

        if (state == MAIN_MENU) {
                SDL_Texture* texMain = IMG_LoadTexture(renderer, "img/white.jpg");
                SDL_Color white = { 0, 0,0 };

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
        else if (state == PLAYING) {
            SDL_Texture* texMain = IMG_LoadTexture(renderer, "img/white.jpg");
            SDL_Color white = { 0, 0, 0 };

            SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Press 3 to PvP ", white);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_Rect textRect = { 300, 250, textSurface->w, textSurface->h };

            SDL_Surface* textSurface2 = TTF_RenderText_Solid(font, "Press 4 to PvE ", white);
            SDL_Texture* textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
            SDL_Rect textRect2 = { 300, 300, textSurface2->w, textSurface2->h }; // đặt dưới dòng trên

            SDL_Rect recMain = { 0, 0, 800, 600 };
            SDL_RenderCopy(renderer, texMain, NULL, &recMain);

            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);

            SDL_FreeSurface(textSurface);
            SDL_FreeSurface(textSurface2);
            SDL_DestroyTexture(texMain);
            SDL_DestroyTexture(textTexture);
            SDL_DestroyTexture(textTexture2);

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
                check_renderBullet(player, player2, bullets);
                // cơ chế khiên và tử vong ;
                
            }

        }
        else if (state == PLAYING3 || state == PAUSED) {
            SDL_SetRenderDrawColor(renderer, 150, 75, 0, 255); // Màu nâu
            for (const auto& plat : platforms) {
                SDL_RenderFillRect(renderer, &plat);
            }

            SDL_SetRenderDrawColor(renderer, 255, 0 , 0, 255);
            SDL_Rect playerRect = { (int)player.pos.x, (int)player.pos.y, 32, 32 };
            
            SDL_RenderFillRect(renderer, &playerRect);
            SDL_SetRenderDrawColor(renderer, 0 , 255, 0, 255);
            SDL_Rect playerRect2 = { (int)player2.pos.x, (int)player2.pos.y, 32, 32 };
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
                
                // cơ chế khiên và tử vong ;
               
            }check_renderBullet(player, player2, bullets);


        }
        else if (state == PLAYING4 || state == PAUSED) {
            // render nền và platform
            SDL_SetRenderDrawColor(renderer, 150, 75, 0, 255);
            for (const auto& plat : platforms) SDL_RenderFillRect(renderer, &plat);

            // render player
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_Rect playerRect = { (int)player.pos.x, (int)player.pos.y, 32, 32 };
            SDL_RenderFillRect(renderer, &playerRect);

            // render bullet của player
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            for (const auto& b : bullets) {
                std::string pointText = "POINT: " + std::to_string(count);
                if (b.active) {
                    SDL_Rect bulletRect = b.getRect();
                    SDL_RenderFillRect(renderer, &bulletRect);
                    if (checkCollision(b.getRect(), boss.hitbox) == 1) {
                        std::random_device rd;
                        std::mt19937 gen(rd());
                        std::uniform_int_distribution<> distX(50, 750);
                        std::uniform_int_distribution<> distY(50, 450);

                        int x = distX(gen);
                        int y = distY(gen);
                        boss.pos.x = x;
                        boss.pos.y = y;
                        count = count + 1;
                    }
                }
            }
            // render boss sniper
            boss.draw(renderer);
            }
            SDL_Color fpsColor = { 255, 255, 255 };

            std::string fpsText = "FPS: " + std::to_string(currentFPS);
            std::string pointText = "POINT: " + std::to_string(count);

            SDL_Surface* fpsSurface = TTF_RenderText_Solid(font, fpsText.c_str(), fpsColor);
            SDL_Texture* fpsTexture = SDL_CreateTextureFromSurface(renderer, fpsSurface);
            SDL_Rect fpsRect = { 10, 10, fpsSurface->w, fpsSurface->h };

            SDL_Surface* pointSurface = TTF_RenderText_Solid(font, pointText.c_str(), fpsColor);
            SDL_Texture* pointTexture = SDL_CreateTextureFromSurface(renderer, pointSurface);
            SDL_Rect pointRect = { 10, 10 + fpsSurface->h + 5, pointSurface->w, pointSurface->h };

            SDL_RenderCopy(renderer, fpsTexture, NULL, &fpsRect);
            SDL_RenderCopy(renderer, pointTexture, NULL, &pointRect);

            SDL_FreeSurface(fpsSurface);
            SDL_DestroyTexture(fpsTexture);
            SDL_FreeSurface(pointSurface);
            SDL_DestroyTexture(pointTexture);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}