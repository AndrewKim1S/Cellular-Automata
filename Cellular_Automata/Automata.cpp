#include "Automata.h"

// Constructor
Automata::Automata(sf::VertexArray& grid, sf::RenderWindow& window,
  int rows, int cols){
  this->grid = grid;
  sf::Vector2u size = window.getSize();
  this->cellWidth = static_cast<float>(size.x / cols);
  this->cellHeight = static_cast<float>(size.y / rows);
  state = State::SETUP;

  cells.resize(static_cast<size_t>(cols));
  for(size_t i = 0; i < cells.size(); i++){
    cells[i].resize(static_cast<size_t>(rows));
  }
  
  CreateCells(rows, cols);
}

// Deconstructor
Automata::~Automata(){}

// Create Wall objects and place them into 2d vector
void Automata::CreateCells(int rows, int cols){

  sf::Vector2f size(cellWidth, cellHeight);
  
  for(int i = 0; i < cols; i++){
    for(int k = 0; k < rows; k++){
      Cell cell(static_cast<float>(i * cellWidth),
        static_cast<float>(k * cellHeight), size);
      cells[i][k] = cell;
    }
  }
}

// Change the state of Wall the mouse clicked
void Automata::SetCell(sf::Vector2f& mouse){
  for(size_t i = 0; i < cells.size(); i++){
    for(size_t k = 0; k < cells[i].size(); k++){
      if(cells[i][k].getGlobalBounds().contains(mouse.x +5.f , mouse.y +5.f)){
        cells[i][k].switchAliveState();
        return;
      }
    }
  }

}

// Update simulation
void Automata::update(){
  /*
  1 or 0 Dead
  2 or 3 Neighbors Alive - and Alive -> Alive
  3 Neighbors Alive - and Dead -> Alive
  4 Neighbors Alive - Always Dead
  */

  for(size_t i = 0; i < cells.size(); i++){
    for(size_t k = 0; k < cells[i].size(); k++){
      int numAlive = 0;
    
      // Game Logic
      if(inBounds(i-1, k-1) && 
        cells[i-1][k-1].getAliveState()){
        numAlive++;
      }
      if(inBounds(i-1, k) &&
        cells[i-1][k].getAliveState()){
        numAlive++;
      }
      if(inBounds(i-1, k+1) && 
        cells[i-1][k+1].getAliveState()){
        numAlive++;
      }
      if(inBounds(i, k-1) &&
        cells[i][k-1].getAliveState()){
        numAlive++;
      }
      if(inBounds(i, k+1) &&
        cells[i][k+1].getAliveState()){
        numAlive++;
      }
      if(inBounds(i+1, k-1) &&
        cells[i+1][k-1].getAliveState()){
        numAlive++;
      }
      if(inBounds(i+1, k) && 
        cells[i+1][k].getAliveState()){
        numAlive++;
      }
      if(inBounds(i+1, k+1) &&
        cells[i+1][k+1].getAliveState()){
        numAlive++;
      }

      // Game Rules
      if(cells[i][k].getAliveState() && numAlive < 2){
        cells[i][k].nextAlive = false;
      } 
      else if(cells[i][k].getAliveState() && (
        numAlive == 2 || numAlive == 3)){
        cells[i][k].nextAlive = true;
      } 
      else if(cells[i][k].getAliveState() &&
        numAlive > 3){
        cells[i][k].nextAlive = false;
      } 
      else if((!cells[i][k].getAliveState()) &&
        numAlive == 3){
        cells[i][k].nextAlive = true;
      }

    }
  }
  changeState();

}

// Render objects 
void Automata::render(sf::RenderWindow& window){
  for(size_t i = 0; i < cells.size(); i++){
    for(size_t j = 0; j < cells[i].size(); j++){
      //std::cout << "Index: " << i << ", " << j << "\n";
      cells[i][j].render(window);
    }
  }
  window.draw(grid);
}

// Change the state of the Cells
void Automata::changeState(){
 for(size_t i = 0; i < cells.size(); i++){
    for(size_t k = 0; k < cells.size(); k++){
      cells[i][k].setAliveState(cells[i][k].nextAlive);
    }
  }
}

// Check if index is within range
bool Automata::inBounds(size_t i, size_t k){
  if(i >= 0 && i < cells.size()){
    if(k >= 0 && k < cells[i].size()){
      return true;
    }
    return false;
  }
  return false;
}

void Automata::setState(State state){
  this->state = state;
}

Automata::State Automata::getState() const{
  return state;
}
