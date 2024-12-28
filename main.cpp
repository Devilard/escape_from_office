#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <list>

#include "GameView.h"
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

    game->getGameView()->view->reset(sf::FloatRect(0, 0, 640, 480));


    
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
                    switch (game->isShowMission) {

                    case true: {
                        game->showMission();
                        break;
                        
                    }
                    case false: {
                        game->hideMission();
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
        window.setView(*(game->getGameView()->view));
        

        game->getGameView()->viewMap(time);
        window.clear();
        window.draw(game->getCurrentLevel());
        for (it = game->getEntities().begin(); it != game->getEntities().end(); it++) { window.draw((*it)->sprite); }
        window.draw(game->getPlayer().sprite);

        
        /*
        std::ostringstream playerScoreString;
        playerScoreString << p.health;

        text.setString("Собранно камней " + playerScoreString.str());
        text.setPosition(view.getCenter().x - 200, view.getCenter().y - 200);
        */

        if (!game->isShowMission)
        {
            window.draw(*game->missionSprite);
            window.draw(*game->missionText);
            game->missionText->setPosition(game->getGameView()->view->getCenter().x + 125, game->getGameView()->view->getCenter().y - 130);
            game->missionSprite->setPosition(game->getGameView()->view->getCenter().x + 115, game->getGameView()->view->getCenter().y - 130);
            
        }

        

        window.display();
    }

    return 0;
    
}