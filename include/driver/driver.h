#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <ranges>

#include "driver/events.h"
#include "graph/graph.h"

using fmt::format;
using sf::Color;
using sf::Event;
using sf::Keyboard;
using sf::RenderWindow;
using sf::VideoMode;
using std::cout;
using std::endl;
using std::unique_ptr;
using tracing::debug;
using tracing::error;
using tracing::info;
using tracing::init;
using tracing::trace;
using tracing::warn;

namespace driver {

const static auto TEXTURE_PATH = "assets/ball0.png";
// const static auto TEXTURE_PATH = "assets/high_res_boid.png";

class GameState {
 public:
  GameState() {
    tracing::trace("Initializing window...");
    if (config::DEBUG_MODE) {
      tracing::info("Debug mode enabled");
      window_ = std::make_unique<RenderWindow>(
          VideoMode(config::DEBUG_WINDOW_WIDTH, config::DEBUG_WINDOW_HEIGHT),
          config::WINDOW_TITLE);
      window_->setFramerateLimit(config::MAX_FPS);
    } else {
      window_ = std::make_unique<RenderWindow>(
          VideoMode(config::PROD_WINDOW_WIDTH, config::PROD_WINDOW_HEIGHT),
          config::WINDOW_TITLE);
      window_->setFramerateLimit(config::MAX_FPS);
    }
    // digraph_ = std::make_unique<graph::DirectedAcyclicGraph>();
    texture_ = std::make_unique<sf::Texture>();

    if (!texture_->loadFromFile(TEXTURE_PATH)) {
      tracing::error("Failed to load node texture from file");
    } else {
      tracing::info("Loaded node texture from file");
    }

    // Initialize the digraph...
    // if (generate_random_graph) {
    //     // Generate a random graph (random number of nodes and edges
    //     // within the window)
    //     digraph_->generate(num_nodes, num_edges);
    // } else {
    //     digraph_->empty_graph();
    // }

    // under the hood... we're just creating a bunch of nodes and edges
    nodes_ = std::vector<std::unique_ptr<graph::Node>>();

    for (int i = 0; i < 10; i++) {
      nodes_.push_back(make_unique<graph::Node>(
          *(window_.get()), *(texture_.get()), graph::random_position()));
      //   nodes_.push_back(make_unique<graph::Node>(
      //       *(window_.get()), *(texture_.get()), Vector2f(i * 100, i *
      //       100)));
    }

    debug("Initialized game state");
    debug(format("Created {} nodes", nodes_.size()));
  }

  /// @brief Process events from the user (e.g. keyboard, mouse, window
  /// events)
  auto process_events() {
    // Only log events processing header every 1000 events
    static int eventCount = 0;
    if (eventCount++ % 1000 == 0) trace("Processing events");
    eventCount++;

    Event event;
    while (window_->pollEvent(event)) {
      switch (event.type) {
        case Event::Closed:
          trace("Closing window");
          window_->close();
          break;

        case Event::Resized:
          debug(format("Window resized to {}x{}", event.size.width,
                       event.size.height));
          break;

        case Event::LostFocus:
          warn("Window lost focus");
          break;

        case Event::GainedFocus:
          info("Window gained focus");
          break;

        case Event::TextEntered:
          if (event.text.unicode < 128) {
            debug(format("ASCII character typed: {}",
                         static_cast<char>(event.text.unicode)));
          }
          break;

        // Window movement
        case Event::MouseMoved:
          if (eventCount % 10 == 0)
            trace(format("Mouse moved to ({}, {})", event.mouseMove.x,
                         event.mouseMove.y));
          break;

        case Event::MouseButtonPressed:
          debug(format("Mouse button pressed: {}", event.mouseButton.button));
          break;

        case Event::MouseButtonReleased:
          debug(format("Mouse button released: {}", event.mouseButton.button));
          break;

        case Event::MouseWheelScrolled:
          trace(
              format("Mouse wheel scrolled: {}", event.mouseWheelScroll.delta));
          break;

          // Keyboard events
        case Event::KeyPressed:
          if (event.key.code == Keyboard::Escape) {
            trace("Closing window");
            window_->close();
          }

          if (event.key.code == Keyboard::F1) {
            set_log_level(tracing::LogLevel::LVL_TRACE);
            trace(
                "F1 pressed - setting log level to "
                "LVL_TRACE");
          }

          if (event.key.code == Keyboard::F2) {
            set_log_level(tracing::LogLevel::LVL_DEBUG);
            debug(
                "F2 pressed - setting log level to "
                "LVL_DEBUG");
          }

          if (event.key.code == Keyboard::F3) {
            set_log_level(tracing::LogLevel::LVL_INFO);
            info(
                "F3 pressed - setting log level to "
                "LVL_INFO");
          }

          if (event.key.code == Keyboard::F4) {
            set_log_level(tracing::LogLevel::LVL_WARN);
            warn(
                "F4 pressed - setting log level to "
                "LVL_WARN");
          }

          if (event.key.code == Keyboard::F5) {
            set_log_level(tracing::LogLevel::LVL_ERROR);
            error(
                "F5 pressed - setting log level to "
                "LVL_ERROR");
          }

          // Fullscreen TODO: Fix this
          // if (event.key.code == Keyboard::F) {
          //     // Toggle fullscreen mode
          //     if (window.isOpen() &&
          //         !sf::VideoMode::getFullscreenModes().empty())
          //         { debug("Toggling fullscreen mode");
          //         sf::VideoMode fullscreenMode =
          //             sf::VideoMode::getFullscreenModes()[0];
          //         window.create(fullscreenMode, "SFML
          //         Window",
          //                       sf::Style::Fullscreen);
          //     } else {
          //         debug("Toggling windowed mode");
          //         window.create(sf::VideoMode(800, 600),
          //         "SFML Window");
          //     }
          // }

          break;

        default:
          break;
      }
    }
  }

  auto tick() {
    // auto update(unique_ptr<RenderWindow>& window) -> void {
    // process_events(window);
    process_events();

    // Update the game state...
    // update();

    // Render the game state
    render();
  }

  /// @brief The main game loop
  auto main_loop() -> void {
    // continuously update the game state until the window is closed
    while (window_->isOpen()) {
      tick();
    }
  }

  auto render() -> void {
    window_->clear(Color::Black);
    // window_->clear(Color::White); // Light mode

    // for (auto& node : nodes_) {
    //   window_->draw(*node->sprite());
    // }

    // Render the nodes
    for (auto& node : nodes_) {
      node->render();
    }

    window_->display();
  }

  static auto build() { return make_unique<GameState>(); }

 private:
  unique_ptr<RenderWindow> window_;
  unique_ptr<Texture> texture_;
  vector<unique_ptr<graph::Node>> nodes_;

  //   unique_ptr<graph::DirectedAcyclicGraph> digraph_;
};

auto init() -> unique_ptr<driver::GameState> {
  srand(time(NULL));
  trace("Initializing game state...");
  return GameState::build();
}

}  // namespace driver

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
