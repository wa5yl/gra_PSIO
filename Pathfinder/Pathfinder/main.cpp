
#include <iostream>

#include "game.h"

int main()
{
    srand(static_cast<unsigned>(time(NULL)));



    sf::Clock timer;
    
    double delta;

    game game;

    while (game.runnin()) {
       

         delta = timer.getElapsedTime().asSeconds();

        timer.restart();

        game.upadete(delta);
   
        game.render();
        
    }
        
    

}

