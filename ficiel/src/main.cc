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
    unique_ptr<RenderWindow> window;
    driver::init_window(window);

    // TODO: move to config / args / env
    set_log_level(tracing::LogLevel::LVL_DEBUG);
    tracing::init();

    // Initialize the environment (e.g. create nodes, edges, etc.)
    // auto environment = env::init();

    while (window->isOpen()) {
        driver::update(window);
    }

    return OkStatus();
}

auto main() -> int { return Main().raw_code(); }
