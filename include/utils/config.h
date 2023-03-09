#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using sf::RenderWindow;
using sf::VideoMode;
using std::string;

namespace config {
// ----------------------------------------
// Constants
// ----------------------------------------

/// @brief The time step for the simulation
float dt;

// Window

/// @brief The width of the window
const int WINDOW_WIDTH = 640;
/// @brief The height of the window
const int WINDOW_HEIGHT = 480;
/// @brief The aspect ratio of the window
const float ASPECT_RATIO = 4 / 3;
/// @brief The padding of the window
const float PADDING = 20.0f;
/// @brief The maximum FPS
const float MAX_FPS = 60.0f;
/// @brief The title of the window
const string WINDOW_TITLE = "Ficiel";

// Map

/// @brief The width of the map (in tiles)
static int MAP_WIDTH = 100;
/// @brief The height of the map (in tiles)
static int MAP_HEIGHT = 100;

// Debug

/// @brief Whether or not to run in debug mode
static bool DEBUG_MODE = true;
/// @brief The width of the debug window
const int DEBUG_WIDTH = 1920;
/// @brief The height of the debug window
const int DEBUG_HEIGHT = 1080;

}  // namespace config