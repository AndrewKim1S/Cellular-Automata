#pragma once


class Cell{
  
  public: 
  
    enum State{
      ALIVE,
      DEAD
    };

    Cell();
    virtual ~Cell();

    State getState();
    void setState(State state);
  
    State m_NextState;
  private:
    State m_state;
};
