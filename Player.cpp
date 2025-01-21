#include "Player.h"

Player::Player(sf::Image& image, sf::String Name, TileMap& lev, float X, float Y, float W, float H) : Entity(image, Name, X, Y, W, H)
{

    isActionKeyPressed = true;

    levelCopy = lev;
    playerScore = 0; state = stateObject::stay; obj = lev.getAllObjects();
    action_objects = lev.getObjectsByType("action");
    if (name == "Player1")
    {
        sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(w), static_cast<int>(h)));
    }
    buffer.loadFromFile("sound/otskok-myacha.ogg");
    sound.setBuffer(buffer);

    questDialog = new QuestDialog();
    questDialog->init();
}

sf::Sprite& Player::getExMark()
{
    sf::Sprite sp;

    return sp;
}

void Player::control(float time)
{

    if (state != stateObject::cant_move)
    {
        state = stateObject::stay;



        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
            state = stateObject::left;
            speed = 0.1f;
            currentFrame += 0.005f * time;
            if (currentFrame > 5) currentFrame -= 3;
            sprite.setTextureRect(sf::IntRect(((36 * (int)currentFrame)), 0, -36, 74));
        }

        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
            state = stateObject::right;
            speed = 0.1f;
            currentFrame += 0.005f * time;
            if (currentFrame > 4) currentFrame -= 3;
            sprite.setTextureRect(sf::IntRect((36 * (int)currentFrame), 0, 36, 74));
        }

        if ((Keyboard::isKeyPressed(Keyboard::Space)) && (onGround)) {
            state = stateObject::jump; dy = -0.78f; onGround = false;

        }

        if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
            state = stateObject::down;

        }
    }

}

void Player::update(float time)
{
    control(time);

    switch (state)
    {
    case stateObject::right: dx = speed; break;
    case stateObject::left: dx = -speed; break;
    case stateObject::up: break;
    case stateObject::down: break;
    case stateObject::jump: break;
    case stateObject::stay: dx = speed; break;
    case stateObject::cant_move: dx = 0; break;
    }



    y += dy * time;
    checkCollisionWithMap(0, dy);

    x += dx * time;
    checkCollisionWithMap(dx, 0);




    sprite.setPosition(x + w / 2, y + h / 2);
    if (health <= 0) { life = false; }
    dy = dy + 0.0015f * time; //делаем притяжение к земле
    if (!isMove) { speed = 0; }
    if (health <= 0) { life = false; speed = 0; }

}

void Player::checkCollisionWithMap(float Dx, float Dy)
{

    for (int i = 0; i < obj.size(); i++)
    {
        if (getRect().intersects(obj[i].rect))
        {

            if (obj[i].name == "solid")
            {
                if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
                if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
                if (Dx > 0) { x = obj[i].rect.left - w; dx = 0; }
                if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0; }
            }
        }
    }
}

void Player::shoot(EntityHandler* entityHandler, sf::Vector2f pos, sf::Image* bulletImg, TileMap* currentLevel)
{
    sound.play();
    entityHandler->entities.push_back(new Bullet(*bulletImg, "Bullet", *currentLevel, x, y, 16, 16, pos));
}

void Player::action(EntityHandler* entityHandler, GameView* v)
{

    if (state == stateObject::stay || state == stateObject::cant_move)
    {
        for (auto object_it = action_objects.begin(); object_it != action_objects.end(); object_it++)
        {

            if (getRect().intersects(object_it->rect))
            {
                if (object_it->properties["class"] == "door")
                {
                    if (object_it->properties["to"] != "")
                    {
                        Object To = levelCopy.getObjectById(std::stoi(object_it->GetPropertyString("to")));

                        y = To.rect.top;
                        x = To.rect.left;

                        break;
                    }
                }

                if (object_it->properties["class"] == "npc")
                {
                    for (auto entity_it = entityHandler->entities.begin(); entity_it != entityHandler->entities.end(); entity_it++)
                    {
                        if ((*entity_it)->id == object_it->id)
                        {
                            if (!dynamic_cast<NPC*>((*entity_it))->questList.empty())
                            {
                                

                                switch (questDialog->isShowQuestDialog) {

                                    case true: {
                                        questDialog->show(dynamic_cast<NPC*>(*entity_it), v);
                                        state = stateObject::cant_move;
                                        break;

                                    }
                                    case false: {
                                        questDialog->high();
                                        state = stateObject::stay;
                                        break;
                                    }
                                }

                                //std::cout << "i can take the quest \n";
                                //questList.push_back("FuckingMouse");
                                /*
                                std::cout << "i can take the quest " << static_cast<NPC&>(*(*entity_it)).questName << " NPC ID " << (*entity_it)->id << "\n";
                                questList[static_cast<NPC&>(*(*entity_it)).getQuest().questName] = static_cast<NPC&>(*(*entity_it)).getQuest();
                                questList[static_cast<NPC&>(*(*entity_it)).getQuest().questName].status = statuses::taken;
                                (*entity_it)->isHaveQuest = false;
                                */

                                break;
                            }
                        }
                    }

                }

            }
        }
    }

}