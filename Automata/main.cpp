#include "CellularAutomata.h"
#include "TileMap.h"
#include <iostream>
#include <ctime>


int main(){
  srand((unsigned)time(0));
  
  CellularAutomata simulation;

  while(simulation.running()){
    simulation.run();
  }


  // For terminal step simulation
  /*std::string input = "n";
  TileMap m_Test(50,50);
  while(input == "n"){ 
    std::cout << m_Test.toString() << "\n";
    m_Test.update();
    std::cin >> input;
  }*/

  return 0;

}
