#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "absl/status/statusor.h"
#include "driver/driver.h"
#include "driver/env.h"
#include "driver/events.h"
#include "driver/window.h"
#include "utils/config.h"
#include "utils/tracing.h"

using std::cout;
using std::endl;

using absl::OkStatus;
using absl::Status;
using fmt::format;
using sf::Color;
using sf::Event;
using sf::Keyboard;
using sf::RenderWindow;
using sf::VideoMode;
using std::unique_ptr;

auto Main() -> Status {
  // unique_ptr<RenderWindow> window;
  // driver::init_window(window);

  tracing::init();

  // -- OLD START --

  // Initialize the environment (e.g. create nodes, edges, etc.)
  // auto environment = env::init();
  // Texture texture;

  // if (!texture.loadFromFile("assets/high_res_boid.png")) {
  //     fmt::print("Failed to load node texture from file\n");
  // }

  // // create a line object to display the range
  // sf::RectangleShape line;

  // RenderWindow window(VideoMode(1920, 1080), "SFML works!");

  // // set the position to the middle of the screen
  // line.setPosition(window.getSize().x / 2, window.getSize().y / 2);
  // line.setSize(sf::Vector2f(30, 30));
  // line.setFillColor(sf::Color::Black);

  // vector<unique_ptr<graph::Node>> nodes;

  // for (int i = 0; i < 10; i++) {
  //     nodes.push_back(make_unique<graph::Node>(window, texture,
  //                                              Vector2f(i * 100, i *
  //                                              100)));
  // }

  // // auto node =

  // auto node = make_unique<graph::Node>(window, texture, Vector2f(1200,
  // 500)); node->set_color(sf::Color(0, 255, 0));

  // auto node2 =
  //     std::make_unique<graph::Node>(window, texture, Vector2f(200, 200));

  // -- OLD END --

  // Initialize the driver (e.g. create the game state - nodes, edges, etc.)
  // auto driver2 = make_unique<driver2::GameState>(window);
  // auto driver2 = driver::GameState::build();
  auto simulation_driver = driver::init();

  simulation_driver->main_loop();

  // -- OLD MAIN LOOP --
  // Process events
  // driver::process_events(window);

  // window.clear(Color::White);

  // window.draw(line);
  // node->render();

  // for (auto& node : nodes) {
  //     node->render();
  // }

  // window.display();

  return OkStatus();
}

auto main() -> int { return Main().raw_code(); }
