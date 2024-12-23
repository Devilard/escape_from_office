#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <list>

#include "map.h"
#include "view.h"
#include "Player.h"
#include "mission.h"
#include "Enemy.h"
#include "level.h"
#include "Bullet.h"






int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Escape from Office");

    view.reset(sf::FloatRect(0, 0, 640, 480));

    std::string str_path{ "tiled_prod/map.tmx" };
    TileMap lvl;
    lvl.load(str_path);

    sf::Font font;
    font.loadFromFile("CyrilicOld.TTF");
    sf::Text text("", font, 20);

    /////////////////////
    //Ёксперимент
    /////////////////////


    sf::Image image_tower_ico;
    image_tower_ico.loadFromFile("layouts/img/tower_1.jpg");

    sf::Texture texture_tower_ico;
    texture_tower_ico.loadFromImage(image_tower_ico);

    sf::Sprite sprite_tower_ico;
    sprite_tower_ico.setTexture(texture_tower_ico);

    /*
    /////////////////////
    //MAP
    /////////////////////
    sf::Image image_map;
    image_map.loadFromFile("layouts/img/map.png");

    sf::Texture texture_map;
    texture_map.loadFromImage(image_map);

    sf::Sprite sprite_map;
    sprite_map.setTexture(texture_map);

    */

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
    /////////////////////
    //Hero
    /////////////////////

    std::list<Entity*> entities;
    std::list<Entity*>::iterator it;
    std::list<Entity*>::iterator it2;



    Object player = lvl.getObject("Player");
    //Object easyEnemyObject = lvl.getObject("easyEnemy");

    sf::Image hero_img;
    hero_img.loadFromFile("layouts/img/hero.png");
    Player p(hero_img, "Player1", lvl, player.rect.left, player.rect.top, 64.0f, 64.0f);

    bool showMissionText = true;

    //enemy
    sf::Image easyEnemyImage;
    easyEnemyImage.loadFromFile("layouts/img/shamaich.png");
    easyEnemyImage.createMaskFromColor(sf::Color(255, 0, 0));
    //Enemy easyEnemy(easyEnemyImage, "EasyEnemy", lvl, easyEnemyObject.rect.left, easyEnemyObject.rect.top, 200, 97);

    //bullet
    sf::Image bullet_image;
    bullet_image.loadFromFile("layouts/img/bullet.png");


    std::vector<Object> e = lvl.getObjectsByName("easyEnemy");

    for (int i = 0; i < e.size(); i++)
        entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 200, 97));


    float currentFrame{ 0.0f };
    sf::Clock clock;

    while (window.isOpen())
    {
        float time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
        clock.restart();

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f pos = window.mapPixelToCoords(pixelPos);


        time = time / 800;

        sf::Sprite towers[10];

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Tab)
                {
                    switch (showMissionText) {

                    case true: {
                        std::ostringstream playerHealthString;
                        playerHealthString << p.health;

                        std::ostringstream task;
                        task << getTextMission(getCurrentMisson(p.getPlayerCoordinateX()));
                        text.setString("«доровье: " + playerHealthString.str() + "\n" + task.str());
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

                if (event.key.code == sf::Keyboard::R)
                {
                    for (int i = 0; i < e.size(); i++)
                        entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 200, 97));
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.key.code == sf::Mouse::Left)
                {
                    
                    std::cout << "pos_x " << pos.x  << "\n";
                    std::cout << "pos_y " << pos.y  << "\n";
                    entities.push_back(new Bullet(bullet_image, "Bullet", lvl, p.x, p.y, 16,16, pos));
                }
            }


        }



        p.update(time);
        //easyEnemy.update(time);
        /*
        for (it = entities.begin(); it != entities.end(); it++)
        {
            (*it)->update(time);
        }
        */
        for (it = entities.begin(); it != entities.end();)
        {
            Entity* b = *it;
            b->update(time);
            if (b->life == false && b->isAnimationDeathEnd == true)
            {
                it = entities.erase(it); delete b;
            }
            else { it++; }
        }

        for (it = entities.begin(); it != entities.end(); it++)//проходимс€ по эл-там списка
        {
            if ((*it)->getRect().intersects(p.getRect()))//если пр€моугольник спрайта объекта пересекаетс€ с игроком
            {
                if ((*it)->name == "EasyEnemy") {//и при этом им€ объекта EasyEnemy,то..

                    if ((p.dy > 0) && (p.onGround == false)) { (*it)->dx = 0; p.dy = -0.2; (*it)->health = 0; }//если прыгнули на врага,то даем врагу скорость 0,отпрыгиваем от него чуть вверх,даем ему здоровье 0
                    else {
                        p.health -= 5;	//иначе враг подошел к нам сбоку и нанес урон
                    }
                }
            }

            for (it2 = entities.begin(); it2 != entities.end(); it2++)
            {
                if ((*it)->getRect() != (*it2)->getRect())
                {
                    if ((*it)->getRect().intersects((*it2)->getRect()) && (*it)->name == "EasyEnemy" && (*it2)->name == "Bullet")
                    {
                        (*it)->health = 0;
                        (*it2)->life = false;
                        (*it2)->isAnimationDeathEnd = true;
                        break;
                    }
                }
            }
        }

        window.setView(view);
        viewMap(time);
        

        window.clear();
        /*
        for (int i = 0; i < HEIGHT_MAP; i++)
        {
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == ' ') { sprite_map.setTextureRect(sf::IntRect(0, 0, 32, 32)); }
                if (TileMap[i][j] == 's') { sprite_map.setTextureRect(sf::IntRect(32, 0, 32, 32)); }
                if (TileMap[i][j] == '0') { sprite_map.setTextureRect(sf::IntRect(64, 0, 32, 32)); }
                if (TileMap[i][j] == 'f') { sprite_map.setTextureRect(sf::IntRect(96, 0, 32, 32)); }
                if (TileMap[i][j] == 'h') { sprite_map.setTextureRect(sf::IntRect(128, 0, 32, 32)); }

                sprite_map.setPosition(j * 32, i * 32);
                window.draw(sprite_map);
            }
        }
        */

        //std::ostringstream playerScoreString;
        //playerScoreString << p.health;


        //text.setString("—обранно камней " + playerScoreString.str());
        //text.setPosition(view.getCenter().x - 200, view.getCenter().y - 200);

        if (!showMissionText)
        {
            window.draw(sprite_quest);
            window.draw(text);
            text.setPosition(view.getCenter().x + 125, view.getCenter().y - 130);
            sprite_quest.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);
        }

        //window.draw(text);


        window.draw(sprite_tower_ico);
        sprite_tower_ico.setPosition(view.getCenter().x, view.getCenter().y + 200);

        window.draw(lvl);
        //window.draw(easyEnemy.sprite);
        for (it = entities.begin(); it != entities.end(); it++)
        {
            window.draw((*it)->sprite);
        }
        window.draw(p.sprite);
        window.display();
    }

    return 0;
    
}