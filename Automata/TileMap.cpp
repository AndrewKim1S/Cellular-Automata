#include "TileMap.h"


// Constructor
TileMap::TileMap(int rows, int cols){
  m_rows = rows;
  m_cols = cols;

  m_Map.resize(m_rows+2);

  // Resizing the 2D Vector
  // When generating the vector add extra column and row
  for(int i = 0; i < m_rows+2; i++){
    
    m_Map[i].resize(m_cols+2);
    for(int k = 0; k < m_cols+2; k++){
      m_Map[i][k] = Cell();
      if(i == 0 || i == m_rows+1 || k == 0 || k == m_cols+1){
        m_Map[i][k].setState(Cell::State::DEAD);
      } else {
        if(rand()%2){
          m_Map[i][k].setState(Cell::State::ALIVE);
        }
      }
    }
  } 
}


TileMap::~TileMap(){

}


// Functions
void 
TileMap::update(){

  /*
  1 or 0 Dead
  2 or 3 Neighbors Alive - and Alive -> Alive
  3 Neighbors Alive - and Dead -> Alive
  4 Neighbors Alive - Always Dead
  */

  // Traverse through the 2D Cell Vector
  // i and k = 1 i++, k++
  for(int i = 1; i < m_rows+1; i+=1){
    for(int k = 1; k < m_cols+1; k+=1){
      
      // Game Logic
      int numAlive = 0;
      if(m_Map[i-1][k-1].getState() == Cell::ALIVE){
        numAlive++;
      }
      if(m_Map[i-1][k].getState() == Cell::ALIVE){
        numAlive++;
      }
      if(m_Map[i-1][k+1].getState() == Cell::ALIVE){
        numAlive++;
      }
      if(m_Map[i][k-1].getState() == Cell::ALIVE){
        numAlive++;
      }
      if(m_Map[i][k+1].getState() == Cell::ALIVE){
        numAlive++;
      }
      if(m_Map[i+1][k-1].getState() == Cell::ALIVE){
        numAlive++;
      }
      if(m_Map[i+1][k].getState() == Cell::ALIVE){
        numAlive++;
      }
      if(m_Map[i+1][k+1].getState() == Cell::ALIVE){
        numAlive++;
      }

      // std::cout << "x: " << i  << " y: " << k << " Alive: "<< numAlive << "\n";

      // Game Rules
      if(m_Map[i][k].getState() == Cell::State::ALIVE && 
        numAlive < 2){
        //m_Map[i][k].setState(Cell::State::DEAD);
        m_Map[i][k].m_NextState = Cell::State::DEAD;
      } else if((m_Map[i][k].getState() == Cell::State::ALIVE) && (
        numAlive == 2 || numAlive == 3)){
        //m_Map[i][k].setState(Cell::State::ALIVE);
        m_Map[i][k].m_NextState = Cell::State::ALIVE;
      } else if(m_Map[i][k].getState() == Cell::State::ALIVE &&
        numAlive > 3){
        //m_Map[i][k].setState(Cell::State::DEAD);
        m_Map[i][k].m_NextState = Cell::State::DEAD;
      } else if(m_Map[i][k].getState() == Cell::State::DEAD &&
        numAlive == 3){
        //m_Map[i][k].setState(Cell::State::ALIVE);
        m_Map[i][k].m_NextState = Cell::State::ALIVE;
      }
    }
  }
  changeState();
}


void
TileMap::render(sf::RenderTarget& target){

}


void
TileMap::changeState(){
  for(int i = 1; i < m_rows+1; i+=1){
    for(int k = 1; k < m_cols+1; k+=1){
      m_Map[i][k].setState(m_Map[i][k].m_NextState);
    }
  }
}


// Tester Function to check logic of the board
std::string
TileMap::toString(){
  std::string result = "";
  for(size_t i = 0; i < m_Map.size(); i++){
    for(size_t k = 0; k < m_Map[i].size(); k++){
      if(m_Map[i][k].getState() == Cell::State::DEAD){
        result += "0 ";
      }
      else if(m_Map[i][k].getState() == Cell::State::ALIVE){
        result += "1 ";
      }
    }
    result += "\n";
  }
  return result;
}
