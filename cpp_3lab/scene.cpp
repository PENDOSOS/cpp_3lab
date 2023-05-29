#include <SFML/Graphics.hpp>

#include <typeinfo>

#include "scene.h"
#include "gem.h"	


Scene::Scene(int width, int height) 
{
	rows_ = height / sizeGem_;
	columns_ = width / sizeGem_;
	width_ = width;
	height_ = height;
}

void Scene::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < gems_.size(); i++)
	{
		for (int j = 0; j < gems_[i].size(); j++)
		{
			sf::RectangleShape square(sf::Vector2f(sizeGem_, sizeGem_));
			square.setTexture(gems_[i][j]->GetTexture());
			square.setPosition(j * sizeGem_, i * sizeGem_);
			window.draw(square);
		}
	}
}

void Scene::CreateGems() 
{
	for (int i = 0; i < rows_; i++) 
	{
		std::vector<Gem*> row;
		for (int j = 0; j < columns_; j++) 
		{
			sf::Color color = Gem::ChoiceColor();
			sf::Texture texture = Gem::ChoiceTexture(color);
			row.push_back(new Gem(i, j, color, &texture));
		}
		gems_.push_back(row);
	}
	if (IsFoundCombinatioins()) {
		for (vector<Gem*> row_gem : gems_) 
		{
			row_gem.clear();
		}
		gems_.clear();
		CreateGems();
	}
}

int Scene::GetSizeGem() 
{
	return sizeGem_;
}

vector<vector<Gem*>> Scene::GetGems() 
{
	return gems_;
}

Gem& Scene::GetGemAt(int x, int y) 
{
	return *gems_[y][x];
}

void Scene::SwapGems(int x1, int y1, int x2, int y2) 
{
	int temp_x = gems_[x1][y1]->GetX();
	int temp_y = gems_[x1][y1]->GetY();
	gems_[x1][y1]->SetX(gems_[x2][y2]->GetX());
	gems_[x1][y1]->SetY(gems_[x2][y2]->GetY());
	gems_[x2][y2]->SetX(temp_x);
	gems_[x2][y2]->SetY(temp_y);
	std::swap(gems_[x1][y1], gems_[x2][y2]);
}

bool Scene::IsFoundCombinatioins() 
{
	const int num_rows = gems_.size();
	const int num_cols = gems_[0].size();

	for (int i = 0; i < num_rows; i++) 
	{
		for (int j = 0; j < num_cols - 2; j++) 
		{
			if (gems_[i][j]->GetColor() == gems_[i][j + 1]->GetColor() && gems_[i][j + 1]->GetColor() == gems_[i][j + 2]->GetColor())
			{
				return true;
			}
		}
	}

	for (int i = 0; i < num_rows - 2; i++) 
	{
		for (int j = 0; j < num_cols; j++) 
		{
			if (gems_[i][j]->GetColor() == gems_[i + 1][j]->GetColor() && gems_[i + 1][j]->GetColor() == gems_[i + 2][j]->GetColor())
			{
				return true;
			}
		}
	}

	return false;
}

std::set<std::tuple<int, int>> Scene::SearchCombinations() 
{
	std::set<std::tuple<int, int>> coordinates_combinations;
	const int num_rows = gems_.size();
	const int num_cols = gems_[0].size();

	for (int i = 0; i < num_rows; i++) 
	{
		for (int j = 0; j < num_cols - 2; j++) 
		{
			if (gems_[i][j]->GetColor() == gems_[i][j + 1]->GetColor() && gems_[i][j + 1]->GetColor() == gems_[i][j + 2]->GetColor())
			{
				coordinates_combinations.insert(std::make_tuple(i, j));
				coordinates_combinations.insert(std::make_tuple(i, j + 1));
				coordinates_combinations.insert(std::make_tuple(i, j + 2));
			}
		}
	}

	for (int i = 0; i < num_rows - 2; i++) 
	{
		for (int j = 0; j < num_cols; j++) 
		{
			if (gems_[i][j]->GetColor() == gems_[i + 1][j]->GetColor() && gems_[i + 1][j]->GetColor() == gems_[i + 2][j]->GetColor())
			{
				coordinates_combinations.insert(std::make_tuple(i, j));
				coordinates_combinations.insert(std::make_tuple(i + 1, j));
				coordinates_combinations.insert(std::make_tuple(i + 2, j));
			}
		}
	}

	return coordinates_combinations;
}

void Scene::DestroyGems(std::set<std::tuple<int, int>>& coordinates_combinations, sf::RenderWindow& window) 
{
	for (auto& coordinate : coordinates_combinations) 
	{
		int x = std::get<0>(coordinate);
		int y = std::get<1>(coordinate);
		gems_[x][y]->SetColor(sf::Color::Black);
		sf::Texture tempTex;
		gems_[x][y]->SetTexture(tempTex);

		switch (std::rand() % 15) 
		{
			case 0: 
			{
				std::tuple<int, int> positionBomb = SetBonusPosition(x, y);
				gems_[std::get<0>(positionBomb)][std::get<1>(positionBomb)]->SetBomb(true);
				gems_[x][y]->SetColor(sf::Color::Black);
				gems_[x][y]->SetTexture(tempTex);
			}
				  break;
			case 1: 
			{
				std::tuple<int, int> positionMarker = SetBonusPosition(x, y);
				gems_[std::get<0>(positionMarker)][std::get<1>(positionMarker)]->SetMarker(true);
				gems_[x][y]->SetColor(sf::Color::Black);
				gems_[x][y]->SetTexture(tempTex);
			}
		}
	}
}

void Scene::AddGems(sf::RenderWindow& window) 
{
	for (int j = 0; j < gems_[0].size(); ++j) 
	{
		for (int i = 0; i < gems_.size(); ++i) {
			if (gems_[i][j]->GetColor() == sf::Color::Black) 
			{
				for (int k = i; k > 0; --k) 
				{
					SwapGems(gems_[k][j]->GetX(), gems_[k][j]->GetY(), gems_[k - 1][j]->GetX(), gems_[k - 1][j]->GetY());
				}
				gems_[0][j]->SetColor(Gem::ChoiceColor());
				gems_[0][j]->SetTexture(Gem::ChoiceTexture(gems_[0][j]->GetColor()));
			}
		}
	}
}

std::tuple<int, int> Scene::SetBonusPosition(int x, int y) 
{
	std::vector<std::tuple<int, int>> candidates;
	for (int i = x - 3; i <= x + 3; ++i) 
	{
		for (int j = y - 3; j <= y + 3; ++j) 
		{
			if (i >= 0 && i < rows_ && j >= 0 && j < columns_) 
			{
				candidates.push_back({ i, j });
			}
		}
	}

	int indexPositionBonus = rand() % candidates.size();
	return candidates[indexPositionBonus];
}

sf::VertexArray Scene::CreateLines() 
{
	sf::VertexArray lines(sf::Lines);
	for (int i = 0; i <= width_; i += sizeGem_) 
	{
		lines.append(sf::Vertex(sf::Vector2f(static_cast<float>(i), 0), sf::Color::Black));
		lines.append(sf::Vertex(sf::Vector2f(static_cast<float>(i), static_cast<float>(height_)), sf::Color::Black));
	}
	for (int i = 0; i <= height_; i += sizeGem_) 
	{
		lines.append(sf::Vertex(sf::Vector2f(0, static_cast<float>(i)), sf::Color::Black));
		lines.append(sf::Vertex(sf::Vector2f(static_cast<float>(width_), static_cast<float>(i)), sf::Color::Black));
	}
	return lines;
}

void Scene::Update(sf::RenderWindow& window) 
{
	std::set<std::tuple<int, int>> coordinates_combinations;
	do 
	{
		coordinates_combinations = SearchCombinations();
		DestroyGems(coordinates_combinations, window);
		Draw(window);
		window.draw(CreateLines());
		window.display();
		sf::sleep(sf::seconds(0.3f));
		AddGems(window);
		Draw(window);
		window.draw(CreateLines());
		window.display();
		sf::sleep(sf::seconds(0.3f));
	} while (!coordinates_combinations.empty());
}