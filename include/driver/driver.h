#pragma once

#include <SFML/Graphics.hpp>

#include "driver/events.h"
// #include "graph/node.h"

#include <algorithm>
#include <iostream>
#include <ranges>

using sf::Color;
using sf::RenderWindow;
// using std::views;

namespace driver {
/// @brief The main update function for the driver
auto update(unique_ptr<RenderWindow>& window) -> void {
    process_events(window);

    window->clear(Color::White);
    window->display();
}

}  // namespace driver