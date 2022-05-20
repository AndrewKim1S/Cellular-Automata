#include "CellularAutomata.h"


// Initialization Functions
void 
CellularAutomata::initWindow(){
  m_videoMode = sf::VideoMode(800, 600);
  m_window = new sf::RenderWindow(m_videoMode, "Cellular Automata",
    sf::Style::Close | sf::Style::Titlebar);
  m_window->setPosition(sf::Vector2i(180, 50));
  m_window->setFramerateLimit(60);
}


void 
CellularAutomata::initVariables(){
  m_endGame = false;
  m_state = simulationState::RUN;
}


// Constructor and Deconstructors
CellularAutomata::CellularAutomata(){
  initVariables();
  initWindow();
}


CellularAutomata::~CellularAutomata(){
  delete m_window;
}

// Functions
void
CellularAutomata::run(){
  //Check if we have exited the window
  pollEvents();

  switch(m_state){
    // Run the simulation
    case simulationState::RUN:
      update();
      break;

    // Pause the simulation
    case simulationState::PAUSE:
      break;

    // Setup the board
    case simulationState::SETUP:
      break;

    default:
      break;
  }
  render();
}


void
CellularAutomata::pollEvents(){
  
  while(m_window->pollEvent(m_ev)){

    switch(m_ev.type){
      case sf::Event::Closed:
        m_window->close();
        break;
      case sf::Event::KeyPressed:
        if(m_ev.key.code == sf::Keyboard::Escape){
          m_window->close();
        }
        break;
      default:
        break;
    }
  }

}


void
CellularAutomata::update(){

}


void
CellularAutomata::render(){
  m_window->clear();
}


// Accessors
const bool
CellularAutomata::running() const{
  return m_window->isOpen();
}
