#ifndef PLAYER_H
#define PLAYER_H

#include"game.h"

void player1_shot(SDL_Event& event, Entity& player, std::vector<Bullet>& bullets);
void player1_input(SDL_Event& event, Entity& player, std::vector <Bullet>& bullets);
void player1_input2(Entity& player);
void player_1_input(SDL_Event& event, Entity& player, std::vector <Bullet>& bullets);

void player2_shot(SDL_Event& event, Entity& player, std::vector<Bullet>& bullets);
void player2_input(SDL_Event& event, Entity& player, std::vector <Bullet>& bullets);
void player2_input2(Entity& player);
void player_2_input(SDL_Event& event, Entity& player, std::vector <Bullet>& bullets);
void check_renderBullet(Entity& player, Entity& player2, std::vector <Bullet>& bullets,int &c1 , int &c2);
#endif // !PLAYER_H
