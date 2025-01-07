#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "level.h"
#include "Bullet.h"
#include "GameView.h"


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
    Player(sf::Image& image, sf::String Name, TileMap& lev, float X, float Y, int W, int H) : Entity(image, Name, X, Y, W, H)
    {
        
        isActionKeyPressed = true;
        levelCopy = lev;
        playerScore = 0; state = stateObject::stay; obj = lev.getAllObjects();
        action_objects = lev.getObjectsByType("door");
        if (name == "Player1")
        {
            sprite.setTextureRect(sf::IntRect(0, 0, w, h));
        }
        buffer.loadFromFile("sound/otskok-myacha.ogg");
        sound.setBuffer(buffer);
    }


    void control(float time)
    {
        state = stateObject::stay;
        
        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
            state = stateObject::left;
            speed = 0.1f;
            currentFrame += 0.005f * time;
            if (currentFrame > 5) currentFrame -= 3;
            sprite.setTextureRect(sf::IntRect(((36 * (int)currentFrame)) , 0, -36, 74));
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
            state = stateObject::right;
            speed = 0.1f;
            	currentFrame += 0.005f * time;
            	if (currentFrame > 4) currentFrame -= 3;
            	sprite.setTextureRect(sf::IntRect((36 * (int)currentFrame), 0, 36, 74));
        }

        if ((Keyboard::isKeyPressed(Keyboard::Space)) && (onGround)) {
            state = stateObject::jump; dy = -0.65; onGround = false;

        }

        if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
            state = stateObject::down;
             
        }


    }

    void update(float time)
    {
        control(time);
        
        switch (state)
        {
        case stateObject::right: dx = speed; break;
        case stateObject::left: dx = -speed; break;
        case stateObject::up: break;
        case stateObject::down: break;
        case stateObject::jump: break;
        case stateObject::stay: dx = 0; break;
        }

        x += dx * time;
        checkCollisionWithMap(dx, 0);
        
        y += dy * time;
        checkCollisionWithMap(0, dy);
        
        sprite.setPosition(x + w / 2, y + h / 2); 
        if (health <= 0) { life = false; }
        dy = dy + 0.0015f * time; //делаем притяжение к земле
        if (!isMove) { speed = 0; }
        if (health <= 0) { life = false; speed = 0; }
        
    }

    float getPlayerCoordinateX() { return x; }

    float getPlayerCoordinateY() { return y; }


    void checkCollisionWithMap(float Dx, float Dy)
    {
        
        for (int i = 0; i < obj.size(); i++)
        {
            if (getRect().intersects(obj[i].rect))
            {
                if (obj[i].name == "solid")
                {
                    if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
                    if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
                    if (Dx > 0) { x = obj[i].rect.left - w; }
                    if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
                }
            }
        }
    }

    
    void shoot(std::list<Entity*>& entities, sf::Vector2f pos, sf::Image* bulletImg, TileMap* currentLevel)
    {
        sound.play();
        entities.push_back(new Bullet(*bulletImg, "Bullet", *currentLevel, x, y, 16, 16, pos));
    }

    void action()
    {
        std::vector<Object>::iterator it;

        if (state == stateObject::stay)
        {
            for (it = action_objects.begin(); it != action_objects.end(); it++)
            {

                if (getRect().intersects(it->rect))
                {
                    if (it->GetPropertyString("to") != "")
                    {
                        Object To = levelCopy.getObjectById(std::stoi(it->GetPropertyString("to")));

                        y = To.rect.top;
                        x = To.rect.left;

                        break;
                    }



                }
            }
        }

    }
    
};

#endif
