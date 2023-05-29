#include <SFML/Graphics.hpp>
#include "gem.h"


Gem::Gem() {}

Gem::Gem(int x, int y, sf::Color color, const sf::Texture* texture)
{
	x_ = x;
	y_ = y;
	color_ = color;
	texture_ = *texture;
}

void Gem::SetX(int newX) 
{
	x_ = newX;
}

void Gem::SetY(int newY) 
{
	y_ = newY;
}

void Gem::SetColor(sf::Color newColor) 
{
	color_ = newColor;
}

void Gem::SetTexture(sf::Texture newTexture)
{
	texture_ = newTexture;
}

void Gem::SetSelectedColor()
{
	isSelected_ = true;
	originalColor_ = color_;
	color_ = sf::Color(color_.r, color_.g, color_.b, 200);
}

void Gem::SetSelectedTexture()
{
	isSelected_ = true;
	originalTexture_ = texture_;
	texture_.loadFromFile("gems_assets/white.png");
}

void Gem::SetDeselectedColor()
{
	isSelected_ = false;
	color_ = originalColor_;
}

void Gem::SetDeselectedTexture()
{
	isSelected_ = false;
	texture_ = originalTexture_;
}

void Gem::SetBomb(bool isBomb) 
{
	isBomb_ = isBomb;
}

void Gem::SetMarker(bool isMarker) 
{
	isMarker_ = isMarker;
}

int Gem::GetX() 
{
	return x_;
}

int Gem::GetY() 
{
	return y_;
}

sf::Color Gem::GetColor() 
{
	return color_;
}

const sf::Texture* Gem::GetTexture()
{
	return &texture_;
}

bool Gem::GetSelected() const { return isSelected_; }

bool Gem::GetBomb() 
{
	return isBomb_;
}

bool Gem::GetMarker() 
{
	return isMarker_;
}

sf::Color Gem::ChoiceColor() 
{
	switch (std::rand() % 6) 
	{
		case 0:
			return sf::Color::Red;
		case 1:
			return sf::Color::Green;
		case 2:
			return sf::Color::Blue;
		case 3:
			return sf::Color::Yellow;
		case 4:
			return sf::Color::Magenta;
		case 5:
			return sf::Color::Cyan;
	}
}

sf::Texture Gem::ChoiceTexture(sf::Color color)
{
	sf::Texture texture;
	if (color == sf::Color::Red)
	{
		texture.loadFromFile("gems_assets/red.png");
		return texture;
	}
	if (color == sf::Color::Green)
	{
		texture.loadFromFile("gems_assets/green.png");
		return texture;
	}
	if (color == sf::Color::Blue)
	{
		texture.loadFromFile("gems_assets/blue.png");
		return texture;
	}
	if (color == sf::Color::Magenta)
	{
		texture.loadFromFile("gems_assets/orange.png");
		return texture;
	}
	if (color == sf::Color::Yellow)
	{
		texture.loadFromFile("gems_assets/yellow.png");
		return texture;
	}
	if (color == sf::Color::Cyan)
	{
		texture.loadFromFile("gems_assets/cyan.png");
		return texture;
	}
}


