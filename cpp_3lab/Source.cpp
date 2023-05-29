#include <SFML/Graphics.hpp>

#include "game.h"

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

int main()
{
    sf::Texture tex;
    tex.loadFromFile("gems_assets/yellow");
    tex.getSize().x;
    srand(time(NULL));
    Game game(WINDOW_WIDTH, WINDOW_HEIGHT);
    Scene board = game.CreateBoard();

    game.Run(board);
    return 0;
}