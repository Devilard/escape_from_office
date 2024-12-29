#include <SFML/Graphics.hpp>

#include "level.h"
#include "Game.h"


int main()
{
    std::string str_path{ "tiled_prod/map.tmx" };
    TileMap* lvl = new TileMap();
    lvl->load(str_path);
    unsigned int windowWidth{1280};
    unsigned int windowHeight(720);
    Game* game = new Game(lvl);
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Escape from Office");
    game->Loop(window, windowWidth, windowHeight);

    return 0;    
}