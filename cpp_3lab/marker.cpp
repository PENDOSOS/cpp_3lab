#include <SFML/Graphics.hpp>

#include "marker.h"

#include <algorithm> 
#include <random>


void Marker::DrawMarker(sf::RenderWindow& window, int sizeGem) 
{
	sf::RectangleShape body(sf::Vector2f(55, 55));
	sf::Texture pencil;
	pencil.loadFromFile("Gems_assets/pencil.png");
	body.setTexture(&pencil);
	body.setPosition((x_) * sizeGem + 10, y_ * sizeGem + 10);
	
	window.draw(body);
}

void Marker::ActionMarker(sf::RenderWindow& window, Scene& board) 
{
	std::vector<std::tuple<int, int>> candidates_painted_gems;
	std::vector<std::tuple<int, int>> painted_gems;
	candidates_painted_gems.push_back({ x_ - 1, y_ - 1 });
	candidates_painted_gems.push_back({ x_ + 1, y_ - 1 });
	candidates_painted_gems.push_back({ x_ - 1, y_ + 1 });
	candidates_painted_gems.push_back({ x_ + 1, y_ + 1 });

	for (std::tuple<int, int> candidate : candidates_painted_gems) 
	{
		int x = std::get<0>(candidate);
		int y = std::get<1>(candidate);
		if (x > 0 && x < board.GetGems()[0].size() && y > 0 && y < board.GetGems().size()) 
		{
			painted_gems.push_back(candidate);
		}

	}

	std::mt19937 rng(std::random_device{}());
	std::shuffle(painted_gems.begin(), painted_gems.end(), rng);

	switch (painted_gems.size()) 
	{
		case 4: case 3: case 2: 
		{
			Gem& first_painted = board.GetGemAt(std::get<0>(painted_gems[0]), std::get<1>(painted_gems[0]));
			Gem& second_painted = board.GetGemAt(std::get<0>(painted_gems[1]), std::get<1>(painted_gems[1]));
			first_painted.SetColor(color_);
			first_painted.SetTexture(texture_);
			second_painted.SetColor(color_);
			second_painted.SetTexture(texture_);
			break; 
		}
		case 1: 
		{
			Gem& painted = board.GetGemAt(std::get<0>(painted_gems[0]), std::get<1>(painted_gems[0]));
			painted.SetColor(color_);
			painted.SetTexture(texture_);
			break; 
		}
	}
	board.Draw(window);
}