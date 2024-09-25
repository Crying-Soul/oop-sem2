#include "Field.hpp"
#include "ShipManager.hpp"
#include "Game.hpp"


int main() {

  Game game;

  game.createMap(10,10);
  game.createFleet();

  game.userAttack({1,1});

  return 0;
}
