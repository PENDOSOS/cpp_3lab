#pragma once

#include <SFML/Graphics.hpp>

#include "gem.h"
#include "scene.h"

class Bomb : public Gem 
{
public:
	Bomb(int x, int y);
	void Draw(sf::RenderWindow& window, int sizeGem);
	void ActionBomb(sf::RenderWindow& window, Scene& board);
};