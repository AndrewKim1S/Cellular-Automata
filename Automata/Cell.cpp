#include "Cell.h"

Cell::Cell(){
  m_state = State::DEAD;
  m_NextState = State::ALIVE;
}


Cell::~Cell(){

}


Cell::State
Cell::getState(){
  return m_state;
}


void
Cell::setState(Cell::State state){
  m_state = state;
}
