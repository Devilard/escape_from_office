#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <list>

#include "view.h"
#include "Player.h"
#include "mission.h"
#include "Enemy.h"
#include "level.h"
#include "Bullet.h"

#include "Game.h"


int main()
{
    std::string str_path{ "tiled_prod/map.tmx" };
    TileMap* lvl = new TileMap();
    lvl->load(str_path);

    Game* game = new Game(lvl);
    
    
    sf::RenderWindow window(sf::VideoMode(640, 480), "Escape from Office");

    view.reset(sf::FloatRect(0, 0, 640, 480));



    sf::Font font;
    font.loadFromFile("CyrilicOld.TTF");
    sf::Text text("", font, 20);
    sf::Color redColor;
    
    text.setFillColor(sf::Color::Red);


    /////////////////////
    //Quest
    /////////////////////
    sf::Image image_quest;
    image_quest.loadFromFile("layouts/img/missionbg.jpg");
    image_quest.createMaskFromColor(sf::Color(0, 0, 0));

    sf::Texture texture_quest;
    texture_quest.loadFromImage(image_quest);
    sf::Sprite sprite_quest;
    sprite_quest.setTexture(texture_quest);
    sprite_quest.setTextureRect(sf::IntRect(0, 0, 340, 510));
    sprite_quest.setScale(0.6f, 0.6f);
    bool showMissionText = true;


    
    std::list<Entity*>::iterator it;
    float currentFrame{ 0.0f };
    sf::Clock clock;

    while (window.isOpen())
    {
        float time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
        clock.restart();

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f pos = window.mapPixelToCoords(pixelPos);


        time = time / 800;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                delete game;
                game = nullptr;
                window.close();
            }
                

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Tab)
                {
                    switch (showMissionText) {

                    case true: {
                        
                        std::ostringstream playerHealthString;
                        playerHealthString << game->getPlayer().health;

                        std::ostringstream task;
                        task << getTextMission(getCurrentMisson(game->getPlayer().getPlayerCoordinateX()));
                        text.setString("Здоровье: " + playerHealthString.str() + "\n" + task.str());
                        text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);
                        sprite_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);
                        showMissionText = false;
                        break;
                        
                    }
                    case false: {
                        text.setString("");
                        showMissionText = true;
                        break;

                    }
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.key.code == sf::Mouse::Left)
                {

                    game->getPlayer().shoot(game->getEntities(), pos, game->bulletImg, game->currentLevel);
                }
            }


        }


        game->update(time);
       
        window.setView(view);

        viewMap(time);
        
        window.clear();

        window.draw(game->getCurrentLevel());
        
        for (it = game->getEntities().begin(); it != game->getEntities().end(); it++)
        {

            window.draw((*it)->sprite);
        }
        window.draw(game->getPlayer().sprite);

        

        //std::ostringstream playerScoreString;
        //playerScoreString << p.health;


        //text.setString("Собранно камней " + playerScoreString.str());
        //text.setPosition(view.getCenter().x - 200, view.getCenter().y - 200);

        if (!showMissionText)
        {
            window.draw(sprite_quest);
            window.draw(text);
            text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);
            sprite_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);
        }

        //window.draw(text);

        window.display();
    }

    return 0;
    
}