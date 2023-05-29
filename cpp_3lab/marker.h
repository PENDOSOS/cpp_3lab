#pragma once

#include <SFML/Graphics.hpp>

#include "gem.h"
#include "scene.h"

class Marker : public Gem 
{
public:
	using Gem::Gem;
	void DrawMarker(sf::RenderWindow& window, int sizeGem);
	void ActionMarker(sf::RenderWindow& window, Scene& board);
};