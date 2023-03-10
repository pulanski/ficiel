#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "utils/config.h"
#include "utils/tracing.h"

using sf::RenderWindow;
using sf::VideoMode;
using std::unique_ptr;

namespace driver {

// ----------------------------------------
// Utility functions
// ----------------------------------------

// auto init_window(RenderWindow* window) -> void {
//     tracing::trace("Initializing window");
//     if (config::DEBUG_MODE) {
//         tracing::info("Debug mode enabled");
//         window = std::make_unique<RenderWindow>(
//             VideoMode(config::DEBUG_WIDTH, config::DEBUG_HEIGHT),
//             config::WINDOW_TITLE);
//         window->setFramerateLimit(config::MAX_FPS);
//     } else {
//         window = std::make_unique<RenderWindow>(
//             VideoMode(config::WINDOW_WIDTH, config::WINDOW_HEIGHT),
//             config::WINDOW_TITLE);
//         window->setFramerateLimit(config::MAX_FPS);
//     }
// }

// unique_ptr solve

// auto init_window(unique_ptr<RenderWindow>& window) -> void {
//     tracing::trace("Initializing window");
//     if (config::DEBUG_MODE) {
//         tracing::info("Debug mode enabled");
//         window = std::make_unique<RenderWindow>(
//             VideoMode(config::DEBUG_WIDTH, config::DEBUG_HEIGHT),
//             config::WINDOW_TITLE);
//         window->setFramerateLimit(config::MAX_FPS);
//     } else {
//         window = std::make_unique<RenderWindow>(
//             VideoMode(config::WINDOW_WIDTH, config::WINDOW_HEIGHT),
//             config::WINDOW_TITLE);
//         window->setFramerateLimit(config::MAX_FPS);
//     }
// }

}  // namespace driver
