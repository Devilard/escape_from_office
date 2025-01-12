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
}

sf::Sprite& Player::getExMark()
{
    sf::Sprite sp;

    return sp;
}

void Player::control(float time)
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

void Player::shoot(std::list<Entity*>& entities, sf::Vector2f pos, sf::Image* bulletImg, TileMap* currentLevel)
{
    sound.play();
    entities.push_back(new Bullet(*bulletImg, "Bullet", *currentLevel, x, y, 16, 16, pos));
}

void Player::action(std::list<Entity*>& entities)
{
    std::vector<Object>::iterator it;
    std::list<Entity*>::iterator it2;
    if (state == stateObject::stay)
    {
        for (it = action_objects.begin(); it != action_objects.end(); it++)
        {

            if (getRect().intersects(it->rect))
            {
                if (it->properties["class"] == "door")
                {
                    if (it->properties["to"] != "")
                    {
                        Object To = levelCopy.getObjectById(std::stoi(it->GetPropertyString("to")));

                        y = To.rect.top;
                        x = To.rect.left;

                        break;
                    }
                }

                if (it->properties["class"] == "npc")
                {
                    for (it2 = entities.begin(); it2 != entities.end(); it2++)
                    {
                        if ((*it2)->id == it->id)
                        {
                            if ((*it2)->isHaveQuest)
                            {
                                std::cout << "i can take the quest " << static_cast<NPC&>(*(*it2)).questName << " NPC ID " << (*it2)->id << "\n";
                                questList[static_cast<NPC&>(*(*it2)).getQuest().questName] = static_cast<NPC&>(*(*it2)).getQuest();
                                questList[static_cast<NPC&>(*(*it2)).getQuest().questName].status = statuses::taken;
                                (*it2)->isHaveQuest = false;

                                break;
                            }
                        }
                    }

                }

            }
        }
    }

}