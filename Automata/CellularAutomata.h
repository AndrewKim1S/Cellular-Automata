#pragma once

#include <iostream>
#include <sstream>
#include "TileMap.h"

// Game Class
class CellularAutomata{

  public:

    enum simulationState{
      RUN,
      PAUSE,
      SETUP
    };

    // Constructor & Deconstructor
    CellularAutomata();
    virtual ~CellularAutomata();

    // Functions
    void run();
    void pollEvents();
    void update();
    void render();

    // Accessors
    const bool running() const;

  private:

    // Variables
    simulationState m_state;

    sf::VideoMode m_videoMode;
    sf::RenderWindow* m_window;
    sf::Event m_ev;

    bool m_endGame;

    // Initialization Functions
    void initWindow();
    void initVariables();
};
