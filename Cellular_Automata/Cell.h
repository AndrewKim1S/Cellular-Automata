#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


class Cell{
  public:
    Cell();
    Cell(float posX, float posY, sf::Vector2f& size);
    ~Cell();

    void setAliveState(bool alive);
    void switchAliveState();
    void render(sf::RenderWindow& window);

    bool getAliveState() const; 

    sf::FloatRect getGlobalBounds() const;
    bool nextAlive;

  private:
    bool alive;
    sf::RectangleShape shape;
  
};
