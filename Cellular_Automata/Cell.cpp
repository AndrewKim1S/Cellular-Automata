#include "Cell.h"


Cell::Cell(){}

Cell::Cell(float posX, float posY, sf::Vector2f& size){
  shape.setPosition(posX+2.5f, posY+2.5f);
  shape.setSize(size);
  shape.setOutlineThickness(5.f);
  shape.setOutlineColor(sf::Color::Black);
  alive = false;
}

Cell::~Cell(){}

void Cell::render(sf::RenderWindow& window){
  if(alive){
    shape.setFillColor(sf::Color::White);
  } else {
    shape.setFillColor(sf::Color::Black);
  }
  //std::cout << "Draw" << "\n";
  window.draw(shape);
}

void Cell::switchAliveState(){
  this->alive = !alive;
}

void Cell::setAliveState(bool alive){
  this->alive = alive;
}

bool Cell::getAliveState() const{
  return alive;
}

sf::FloatRect Cell::getGlobalBounds() const{
  return shape.getGlobalBounds();
}
