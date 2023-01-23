#include <stdio.h>
#include <fstream>
#include "gui.hpp"
#include "runners/steam.hpp"

int main()
{
  Steam *steam = new Steam();
  gui* _gui = new gui();
  _gui->addGames(steam->getAppIds());
  _gui->run();
  int gameId = _gui->getSelectedGame();
  if (gameId != GAME_NOT_SELECTED)
    steam->run(gameId);

  return 0;
}
