#include <SFML/Graphics.hpp>
#include "Game.h"
//#include "Menu.h"


int main()
{
    unsigned int windowWidth{1280};
    unsigned int windowHeight(720);

    Game* game = new Game();
    game->loadAll();

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Escape from Office");

    game->Loop(window, windowWidth, windowHeight);

    return 0;    

}
