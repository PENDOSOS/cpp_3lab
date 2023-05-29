#pragma once

#include <SFML/Graphics.hpp>

#include "scene.h"
#include "gem.h"
#include "marker.h"
#include "bomb.h"

class Game 
{
private:
	int width_;
	int height_;

public:
	Game(int width, int height);
	Scene CreateBoard();
	void Run(Scene& board);
};

