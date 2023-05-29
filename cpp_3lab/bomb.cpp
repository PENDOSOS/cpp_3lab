#include <SFML/Graphics.hpp>

#include "bomb.h"

Bomb::Bomb(int x, int y) 
{
	x_ = x;
	y_ = y;
}

void Bomb::Draw(sf::RenderWindow& window, int sizeGem) 
{
	sf::RectangleShape body(sf::Vector2f(65, 65));
	sf::Texture bomb;
	bomb.loadFromFile("Gems_assets/bomb.png");
	body.setTexture(&bomb);
	body.setPosition((x_)*sizeGem + 5, y_ * sizeGem + 5);

	window.draw(body);
}

void Bomb::ActionBomb(sf::RenderWindow& window, Scene& board) 
{
	for (int i = 0; i < 4; i++) 
	{
		int x = rand() % board.GetGems()[0].size();
		int y = rand() % board.GetGems().size();
		std::cout << x << std::endl;
		std::cout << y << std::endl;
		Gem& gem = board.GetGemAt(x, y);
		gem.SetColor(sf::Color::Black);
		std::cout << x << std::endl;
		std::cout << y << std::endl;
	}
	Gem& gem_with_bomb = board.GetGemAt(x_, y_);
	gem_with_bomb.SetColor(sf::Color::Black);
	board.Draw(window);
	board.AddGems(window);
}
