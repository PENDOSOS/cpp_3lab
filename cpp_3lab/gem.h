#pragma once

#include <SFML/Graphics.hpp>


class Gem 
{
protected:
	sf::Color color_;
	sf::Color originalColor_;
	sf::Texture texture_;
	sf::Texture originalTexture_;
	int x_;
	int y_;
	bool isSelected_ = false;
	bool isBomb_ = false;
	bool isMarker_ = false;

public:
	Gem();
	
	Gem(int x, int y, sf::Color color, const sf::Texture* texture);
	static sf::Color ChoiceColor();
	static sf::Texture ChoiceTexture(sf::Color color);

	void SetX(int newX);
	void SetY(int newY);
	void SetColor(sf::Color newColor);
	void SetTexture(sf::Texture newTexture);
	void SetSelectedColor();
	void SetDeselectedColor();
	void SetSelectedTexture();
	void SetDeselectedTexture();
	void SetBomb(bool isBomb);
	void SetMarker(bool isMarker);

	int GetX();
	int GetY();
	sf::Color GetColor();
	const sf::Texture* GetTexture();
	bool GetSelected() const;
	bool GetBomb();
	bool GetMarker();
};