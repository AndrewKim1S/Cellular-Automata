#include "Automata.h"


// To draw graph based on windows specifications
sf::VertexArray ResizeWindow(sf::RenderWindow& window, int r, int c)
{  
  int rows = r;
  int cols = c;
  int numLines = rows + cols - 2;
  
  sf::VertexArray grid(sf::Lines, 2*(numLines));
  window.setView(window.getDefaultView());
  sf::Vector2u size = window.getSize();

  float rowHeight = size.y / rows;
  float colWidth = size.x / cols;

  // Draw rows
  for(int i = 0; i < rows -1; i++){
    int k = i+1;
    float rowY = rowHeight * k;
    grid[i*2].position = {0.f, rowY};
    grid[i*2+1].position = {static_cast<float>(size.x), rowY};
  }

  // Draw cols
  for(int i = rows-1; i < numLines; i++){
    int c = i-rows+2;
    float colX = colWidth * c;
    grid[i*2].position = {colX, 0.f};
    grid[i*2+1].position = {colX, static_cast<float>(size.y)};
  }

  return grid;
}


// main
int main()
{
  sf::RenderWindow window(sf::VideoMode(800,720), "Grid");
  window.setPosition(sf::Vector2i(180,50));
  window.setFramerateLimit(60);

  int rows = 18;
  int cols = 20;

  sf::VertexArray grid;
  grid = ResizeWindow(window, rows, cols);

  Automata automata(grid, window, rows, cols);
  automata.setState(Automata::State::SETUP);

  std::cout << "-----Conway's Game Of Life-----" << std::endl;
  std::cout << "Press r to run, p to pause, and escape to setup!" << std::endl;

  sf::Clock clock;
  clock.restart();

  // Main Loop
  while(window.isOpen()){
    sf::Event event;

    // Poll Events
    while(window.pollEvent(event)){
      switch(event.type){
        
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::MouseButtonPressed:
          if(event.mouseButton.button == sf::Mouse::Left &&
            automata.getState() == Automata::State::SETUP){
            float x = static_cast<float>(sf::Mouse::getPosition(window).x);
            float y = static_cast<float>(sf::Mouse::getPosition(window).y);
            sf::Vector2f posM(x, y);
            automata.SetCell(posM);
          }
          break;

        case sf::Event::KeyPressed:
          if(event.key.code == sf::Keyboard::R){
            automata.setState(Automata::State::RUN);
          } else if(event.key.code == sf::Keyboard::P){
            automata.setState(Automata::State::PAUSE);
          } else if(event.key.code == sf::Keyboard::Escape){
            automata.setState(Automata::State::SETUP);
          }
          break;

        default:
          break;
      }
    }

    if(clock.getElapsedTime().asSeconds() >= 0.15 && 
      (automata.getState() == Automata::State::RUN)){
      clock.restart();
      automata.update();
    }

    window.clear();
    automata.render(window);
    window.display();
  }

  return 0;
}
