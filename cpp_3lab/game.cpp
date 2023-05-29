#include <SFML/Graphics.hpp>

#include "game.h"

#include <iostream>
#include <cmath>
#include <cstdlib>


Game::Game(int width, int height) 
{
    width_ = width;
    height_ = height;
}

Scene Game::CreateBoard() 
{
    Scene board(width_, height_);
    board.CreateGems();
    return board;
}

void Game::Run(Scene& board) 
{
    sf::RenderWindow window(sf::VideoMode(width_, height_), "gems");
    window.setFramerateLimit(60);
    sf::VertexArray lines = board.CreateLines();

    Gem* selectable_gem = nullptr;
    bool selected_gem_exists = false;

    while (window.isOpen())
    {
        window.clear(sf::Color::White);
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) 
            {
            case sf::Event::Closed:
                window.close();
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    int x = event.mouseButton.x / board.GetSizeGem();
                    int y = event.mouseButton.y / board.GetSizeGem();

                    if (x >= 0 && x < board.GetGems()[0].size() && y >= 0 && y < board.GetGems().size()) 
                    {
                        Gem& current_gem = board.GetGemAt(x, y);
                        if (selectable_gem != nullptr) 
                        {
                            if (selectable_gem == &current_gem) 
                            {
                                selectable_gem->SetDeselectedColor();
                                selectable_gem->SetDeselectedTexture();
                                selectable_gem = nullptr;
                                break;
                            }
                            else if ((abs(selectable_gem->GetY() - current_gem.GetY()) + abs(selectable_gem->GetX() - current_gem.GetX()) == 1)) 
                            {
                                board.SwapGems(selectable_gem->GetX(), selectable_gem->GetY(), current_gem.GetX(), current_gem.GetY());
                                current_gem.SetSelectedColor();
                                current_gem.SetSelectedTexture();
                                board.Draw(window);

                                selectable_gem->SetDeselectedColor();
                                selectable_gem->SetDeselectedTexture();
                                current_gem.SetDeselectedColor();
                                current_gem.SetDeselectedTexture();

                                if (board.IsFoundCombinatioins()) 
                                {
                                    board.Update(window);
                                }
                                else 
                                {
                                    board.SwapGems(selectable_gem->GetX(), selectable_gem->GetY(), current_gem.GetX(), current_gem.GetY());
                                }
                                selectable_gem = nullptr;
                                board.Draw(window);
                                break;
                            }
                            else 
                            {
                                selectable_gem->SetDeselectedColor();
                                selectable_gem->SetDeselectedTexture();
                            }
                        }
                        selectable_gem = &current_gem;
                        selectable_gem->SetSelectedColor();
                        selectable_gem->SetSelectedTexture();
                        board.Draw(window);
                    }
                }

            }
        }

        for (int i = 0; i < board.GetGems().size(); i++) 
        {
            for (int j = 0; j < board.GetGems()[0].size(); j++) 
            {
                Gem& current_gem = board.GetGemAt(j, i);
                if (current_gem.GetSelected() && (&current_gem != selectable_gem)) 
                {
                    current_gem.SetDeselectedColor();
                    current_gem.SetDeselectedTexture();
                }
            }
        }

        std::vector<Marker> markers;
        for (int i = 0; i < board.GetGems().size(); i++) 
        {
            for (int j = 0; j < board.GetGems()[0].size(); j++) 
            {
                Gem& current_gem = board.GetGemAt(j, i);
                if (current_gem.GetMarker() && !current_gem.GetBomb()) 
                {
                    current_gem.SetMarker(false);
                    Marker marker(j, i, current_gem.GetColor(), current_gem.GetTexture());
                    markers.push_back(marker);
                }
            }
        }

        for (Marker marker : markers) 
        {
            board.Draw(window);
            marker.DrawMarker(window, board.GetSizeGem());
            window.draw(lines);
            window.display();
            sf::sleep(sf::seconds(1.5f));
            marker.ActionMarker(window, board);
        }

        std::vector<Bomb> bombs;
        for (int i = 0; i < board.GetGems().size(); i++) 
        {
            for (int j = 0; j < board.GetGems()[0].size(); j++) 
            {
                Gem& current_gem = board.GetGemAt(j, i);
                if (current_gem.GetBomb() && !current_gem.GetMarker()) 
                {
                    current_gem.SetBomb(false);
                    Bomb bomb(j, i);
                    bombs.push_back(bomb);
                }
            }
        }

        for (Bomb bomb : bombs) 
        {
            board.Draw(window);
            bomb.Draw(window, board.GetSizeGem());
            window.draw(lines);
            window.display();
            sf::sleep(sf::seconds(1.5f));
            bomb.ActionBomb(window, board);
        }

        while (board.IsFoundCombinatioins()) 
        {
            board.Update(window);
        }

        board.Draw(window);
        window.draw(lines);
        window.display();
    }
}