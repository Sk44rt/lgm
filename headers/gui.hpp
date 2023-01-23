#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "utils.hpp"
#include "runners/steam.hpp"

#define GAME_NOT_SELECTED -1

class gui
{
public:
  gui();
  ~gui();
  void run();
  void addGames(std::vector<steamAppManifest> arr);
  int getSelectedGame();
private:
  std::vector<steamAppManifest> games;
  int selectedGame = GAME_NOT_SELECTED;
};
