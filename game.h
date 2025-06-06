﻿    #ifndef GAME_H
    #define GAME_H

    #include <SDL.h>
    #include <SDL_image.h>
    #include <vector>
    #include <iostream>
    #include <SDL_ttf.h>
    #include <string>
    #include <random> 

    enum GameState {
        MAIN_MENU,
        OPTIONS,
        PLAYING,
        PAUSED,
        EXIT, PLAYING3, PLAYING4,PLAYING3_end
    };
    struct Vector2 {
        float x, y;
    };
    struct Bullet {
        Vector2 pos;
        float speed;
        bool active;
        SDL_Rect getRect() const {
            return { (int)pos.x, (int)pos.y, 10, 5 };
        }
    };// thông số đạn 
    struct BulletB {
        Vector2 pos;
        float speedX, speedY;
        bool active;

        SDL_Rect getRect() const {
            return { (int)pos.x, (int)pos.y, 5, 5 };
        }
    };
    bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
    struct Entity {
        Vector2 pos;// vị trí trên màn 
        Vector2 vel;// vận tốc
        SDL_Rect hitbox;// hcn kiểm tra va chạm 
        bool onGround;// đánh dấu vật có trên mặt đất không
        bool directionR = 1;// 1 là phải , 0 là trái 

        void update2(float deltaTime, const std::vector<SDL_Rect>& platforms);
        void jump();// nhảy (nếu trên mặt đất )
        void renderEntity(SDL_Renderer* renderer);
        void renderEntity2(SDL_Renderer* renderer);
    };// vạt thể khả dụng j


    #endif
