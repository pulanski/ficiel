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

/// @brief Whether or not to run in debug mode
static bool DEBUG_MODE = true;

// Window

/// @brief The width of the window in production
const int PROD_WINDOW_WIDTH = 640;
/// @brief The height of the window in production
const int PROD_WINDOW_HEIGHT = 480;

/// @brief The width of the window in debug mode
const int DEBUG_WINDOW_WIDTH = 1920;
/// @brief The height of the window in debug mode
const int DEBUG_WINDOW_HEIGHT = 1080;

/// @brief The width of the window
auto WINDOW_WIDTH = DEBUG_MODE ? DEBUG_WINDOW_WIDTH : PROD_WINDOW_WIDTH;
/// @brief The height of the window
auto WINDOW_HEIGHT = DEBUG_MODE ? DEBUG_WINDOW_HEIGHT : PROD_WINDOW_HEIGHT;

/// @brief The aspect ratio of the window
const float ASPECT_RATIO = 4 / 3;
/// @brief The padding of the window
const float PADDING = 20.0f;
/// @brief The maximum FPS
const float MAX_FPS = 60.0f;
/// @brief The title of the window
const string WINDOW_TITLE = DEBUG_MODE ? "Ficiel (Debug)" : "Ficiel";
// const string WINDOW_TITLE = "Ficiel";

// Map

/// @brief The width of the map (in tiles)
static int MAP_WIDTH = 100;
/// @brief The height of the map (in tiles)
static int MAP_HEIGHT = 100;

}  // namespace config
