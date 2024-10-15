#include "game.h"
#include "square.h"

int main(int argc, char **argv)
{
    Game::start(800, 600, "float");

    Game::add(new Square(glm::ivec2(100, 100), 50, glm::vec3(1.0, 0.0, 0.0)));
    
    Game::loop();
    
    Game::end();
    return 0;
}
