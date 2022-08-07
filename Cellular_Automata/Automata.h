#pragma once

#include "Cell.h"
#include <vector>


class Automata{
  public:

    enum State{
      RUN,
      PAUSE,
      SETUP
    };

    Automata(sf::VertexArray& grid, sf::RenderWindow& window,
      int rows, int cols);
    ~Automata();
  
    void CreateCells(int rows, int cols);

    void SetCell(sf::Vector2f& mouse);
    void update();
    void render(sf::RenderWindow& window);
    void changeState();

    void setState(State state);
    Automata::State getState() const;

  private:
    State state;

    bool inBounds(size_t i, size_t k);

    std::vector<std::vector<Cell>> cells;
    sf::VertexArray grid;

    float cellWidth;
    float cellHeight;
};
