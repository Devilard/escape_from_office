#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"
#include "level.h"
#include "Bullet.h"
#include "GameView.h"
#include "Enemy.h"
#include "NPC.h"
#include "Mission.h"

using sf::Keyboard;

class Player : public Entity
{
public:
    enum class stateObject {left, right, up, down, jump, stay};
    stateObject state;
    int playerScore;
    float currentFrame{ 1.0f };
    sf::SoundBuffer buffer;
    sf::Sound sound;
    std::vector<Object> action_objects;
    bool isActionKeyPressed;
    TileMap levelCopy;
    std::vector<Quest> questList;
    
    Player(sf::Image& image, sf::String Name, TileMap& lev, float X, float Y, float W, float H);
    sf::Sprite& getExMark();
    void control(float time);
    void update(float time) override;
    float getPlayerCoordinateX() { return x; }
    float getPlayerCoordinateY() { return y; }
    void checkCollisionWithMap(float Dx, float Dy);
    void shoot(std::list<Entity*>& entities, sf::Vector2f pos, sf::Image* bulletImg, TileMap* currentLevel);
    void action(std::list<Entity*>& entities);
};

#endif
