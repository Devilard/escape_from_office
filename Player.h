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
   
    
   

    Player(sf::Image& image, sf::String Name, TileMap& lev, float X, float Y, int W, int H) : Entity(image, Name, X, Y, W, H)
    {
        
        
        playerScore = 0; state = stateObject::stay; obj = lev.getAllObjects();
        if (name == "Player1")
        {
            sprite.setTextureRect(sf::IntRect(64, 0, w, h));
        }
        buffer.loadFromFile("sound/otskok-myacha.ogg");
        sound.setBuffer(buffer);
    }


    void control(float time) {
        
        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
            state = stateObject::left;
            speed = 0.1f;
            currentFrame += 0.005f * time;
            if (currentFrame > 5) currentFrame -= 4;
            sprite.setTextureRect(sf::IntRect(((64 * (int)currentFrame)+64) , 0, -64, 64));
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
            state = stateObject::right;
            speed = 0.1f;
            	currentFrame += 0.005f * time;
            	if (currentFrame > 5) currentFrame -= 4;
            	sprite.setTextureRect(sf::IntRect((64 * (int)currentFrame), 0, 64, 64));
        }

        if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) && (onGround)) {
            state = stateObject::jump; dy = -0.5; onGround = false;
            //currentFrame += 0.005*time;
            //if (currentFrame > 3) currentFrame -= 3;
            //p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 307, 96, 96));
        }

        if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
            state = stateObject::down;

            //currentFrame += 0.005*time;
            //if (currentFrame > 3) currentFrame -= 3;
            //p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 0, 96, 96));
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
        case stateObject::stay: break;
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

    /*
    void interactionWithMap()
    {
        for (int i = y / 32; i < (y + h) / 32; i++)
        {
            for (int j = x / 32; j < (x + w) / 32; j++)
            {
                if (TileMap[i][j] == '0')
                {
                    if (dy > 0) { y = i * 32 - h; }

                    if (dy < 0) { y = i * 32 + 32; }

                    if (dx > 0) { x = j * 32 - w; }

                    if (dx < 0) { x = j * 32 + 32; }

                }

                if (TileMap[i][j] == 's')
                {
                    player_score++;
                    TileMap[i][j] = ' ';
                }

                if (TileMap[i][j] == 'f')
                {
                    health -= 40;
                    TileMap[i][j] = ' ';
                }

                if (TileMap[i][j] == 'h')
                {
                    health += 20;
                    TileMap[i][j] = ' ';
                }

            }
        }
    }
    */

    void checkCollisionWithMap(float Dx, float Dy)
    {
        /*
        for (int i = y / 32; i < (y + h) / 32; i++)
        {
            
            for (int j = x / 32; j < (x + w) / 32; j++)
            {
                
                if (TileMap[i][j] == '0')
                {
                    
                    if (Dy > 0) { y = i * 32 - h;  dy = 0; onGround = true; }//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
                    if (Dy < 0) { y = i * 32 + 32;  dy = 0; }//столкновение с верхними краями карты(может и не пригодиться)
                    if (Dx > 0) { x = j * 32 - w; }//с правым краем карты
                    if (Dx < 0) { x = j * 32 + 32; }// с левым краем карты
                }
                else {  onGround = false; }
            }
        }

        */
        
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
    
};

#endif
