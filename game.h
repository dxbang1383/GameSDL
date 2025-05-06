    #ifndef GAME_H
    #define GAME_H

    #include <SDL.h>
    #include <SDL_image.h>
    #include <vector>
    #include <iostream>
    #include <SDL_ttf.h>

    enum GameState {
        MAIN_MENU,
        OPTIONS,
        PLAYING,
        PAUSED,
        EXIT, PLAYING2, PLAYING1, PLAYING3
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
    bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
    struct Entity {
        Vector2 pos;// vị trí trên màn 
        Vector2 vel;// vận tốc
        SDL_Rect hitbox;// hcn kiểm tra va chạm 
        bool onGround;// đánh dấu vật có trên mặt đất không
        bool directionR = 1;// 1 là phải , 0 là trái 
        void update(float deltaTime);// cập nhật vị trí
        void update2(float deltaTime, const std::vector<SDL_Rect>& platforms);
        void jump();// nhảy (nếu trên mặt đất )
    };// vạt thể khả dụng j
    bool checkCollisionFloat(SDL_FRect a, SDL_FRect b);

    #endif
