#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Cell.h"
#include <vector>
#include <iostream>

class TileMap{

  public:
    TileMap(int row, int col);
    TileMap();
    virtual ~TileMap();

    void update();
    void render(sf::RenderTarget& target);
    void changeState();

    std::string toString();

  private:
    int m_rows;
    int m_cols;

    std::vector<std::vector<Cell>> m_Map;
    sf::VertexArray m_vetices;
};
