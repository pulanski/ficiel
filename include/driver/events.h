#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "utils/tracing.h"

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
auto process_events(unique_ptr<RenderWindow>& window) -> void {
    // Only log processing events every 1000 events

    static int eventCount = 0;
    if (eventCount++ % 1000 == 0) trace("Processing events");

    eventCount++;
    Event event;
    while (window->pollEvent(event)) {
        switch (event.type) {
            case Event::Closed:
                trace("Closing window");
                window->close();
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
                trace(format("Mouse button pressed: {}",
                             event.mouseButton.button));
                break;

            case Event::MouseButtonReleased:
                trace(format("Mouse button released: {}",
                             event.mouseButton.button));
                break;

            case Event::MouseWheelScrolled:
                trace(format("Mouse wheel scrolled: {}",
                             event.mouseWheelScroll.delta));
                break;

                // Keyboard events
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Escape) {
                    trace("Closing window");
                    window->close();
                }

                if (event.key.code == Keyboard::F1) {
                    set_log_level(tracing::LogLevel::LVL_TRACE);
                    trace("F1 pressed - setting log level to LVL_TRACE");
                }

                if (event.key.code == Keyboard::F2) {
                    set_log_level(tracing::LogLevel::LVL_DEBUG);
                    debug("F2 pressed - setting log level to LVL_DEBUG");
                }

                if (event.key.code == Keyboard::F3) {
                    set_log_level(tracing::LogLevel::LVL_INFO);
                    info("F3 pressed - setting log level to LVL_INFO");
                }

                if (event.key.code == Keyboard::F4) {
                    set_log_level(tracing::LogLevel::LVL_WARN);
                    warn("F4 pressed - setting log level to LVL_WARN");
                }

                if (event.key.code == Keyboard::F5) {
                    set_log_level(tracing::LogLevel::LVL_ERROR);
                    error("F5 pressed - setting log level to LVL_ERROR");
                }

                // Fullscreen TODO: Fix this
                // if (event.key.code == Keyboard::F) {
                //     // Toggle fullscreen mode
                //     if (window.isOpen() &&
                //         !sf::VideoMode::getFullscreenModes().empty()) {
                //         debug("Toggling fullscreen mode");
                //         sf::VideoMode fullscreenMode =
                //             sf::VideoMode::getFullscreenModes()[0];
                //         window.create(fullscreenMode, "SFML Window",
                //                       sf::Style::Fullscreen);
                //     } else {
                //         debug("Toggling windowed mode");
                //         window.create(sf::VideoMode(800, 600), "SFML
                //         Window");
                //     }
                // }

                break;

            default:
                break;
        }
    }
}
// auto process_events(RenderWindow& window) -> void {
//     // Only log processing events every 1000 events

//     static int eventCount = 0;
//     if (eventCount++ % 1000 == 0) trace("Processing events");

//     eventCount++;
//     Event event;
//     while (window.pollEvent(event)) {
//         switch (event.type) {
//             case Event::Closed:
//                 trace("Closing window");
//                 window.close();
//                 break;

//             case Event::Resized:
//                 debug(format("Window resized to {}x{}", event.size.width,
//                              event.size.height));
//                 break;

//             case Event::LostFocus:
//                 warn("Window lost focus");
//                 break;

//             case Event::GainedFocus:
//                 info("Window gained focus");
//                 break;

//             case Event::TextEntered:
//                 if (event.text.unicode < 128) {
//                     debug(format("ASCII character typed: {}",
//                                  static_cast<char>(event.text.unicode)));
//                 }
//                 break;

//             // Window movement
//             case Event::MouseMoved:
//                 if (eventCount % 10 == 0)
//                     trace(format("Mouse moved to ({}, {})",
//                     event.mouseMove.x,
//                                  event.mouseMove.y));
//                 break;

//             case Event::MouseButtonPressed:
//                 trace(format("Mouse button pressed: {}",
//                              event.mouseButton.button));
//                 break;

//             case Event::MouseButtonReleased:
//                 trace(format("Mouse button released: {}",
//                              event.mouseButton.button));
//                 break;

//             case Event::MouseWheelScrolled:
//                 trace(format("Mouse wheel scrolled: {}",
//                              event.mouseWheelScroll.delta));
//                 break;

//                 // Keyboard events
//             case Event::KeyPressed:
//                 if (event.key.code == Keyboard::Escape) {
//                     trace("Closing window");
//                     window.close();
//                 }

//                 if (event.key.code == Keyboard::F1) {
//                     set_log_level(tracing::LogLevel::LVL_TRACE);
//                     trace("F1 pressed - setting log level to LVL_TRACE");
//                 }

//                 if (event.key.code == Keyboard::F2) {
//                     set_log_level(tracing::LogLevel::LVL_DEBUG);
//                     debug("F2 pressed - setting log level to LVL_DEBUG");
//                 }

//                 if (event.key.code == Keyboard::F3) {
//                     set_log_level(tracing::LogLevel::LVL_INFO);
//                     info("F3 pressed - setting log level to LVL_INFO");
//                 }

//                 if (event.key.code == Keyboard::F4) {
//                     set_log_level(tracing::LogLevel::LVL_WARN);
//                     warn("F4 pressed - setting log level to LVL_WARN");
//                 }

//                 if (event.key.code == Keyboard::F5) {
//                     set_log_level(tracing::LogLevel::LVL_ERROR);
//                     error("F5 pressed - setting log level to LVL_ERROR");
//                 }

//                 // Fullscreen TODO: Fix this
//                 // if (event.key.code == Keyboard::F) {
//                 //     // Toggle fullscreen mode
//                 //     if (window.isOpen() &&
//                 //         !sf::VideoMode::getFullscreenModes().empty()) {
//                 //         debug("Toggling fullscreen mode");
//                 //         sf::VideoMode fullscreenMode =
//                 //             sf::VideoMode::getFullscreenModes()[0];
//                 //         window.create(fullscreenMode, "SFML Window",
//                 //                       sf::Style::Fullscreen);
//                 //     } else {
//                 //         debug("Toggling windowed mode");
//                 //         window.create(sf::VideoMode(800, 600), "SFML
//                 //         Window");
//                 //     }
//                 // }

//                 break;

//             default:
//                 break;
//         }
//     }
// }
}  // namespace driver
