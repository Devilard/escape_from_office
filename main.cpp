#include <SFML/Graphics.hpp>
#include "Game.h"
#include "iconvlite.h"



int main()
{
    unsigned int windowWidth{1280};
    unsigned int windowHeight(720);

    Game* game = new Game();
    game->loadAll();
    

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Escape from Office");
    //window.setFramerateLimit(120);
    game->showMenu(window);

    game->Loop(window, windowWidth, windowHeight);

    return 0;    

}
