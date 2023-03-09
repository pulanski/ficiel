#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "utils/config.h"

#define FMT_HEADER_ONLY
#include "fmt/color.h"

using fmt::color;
using fmt::emphasis;
using fmt::format;
using std::cout;
using std::endl;
using std::string;
using std::string_view;
using std::vector;

/// @brief Collection of utilities for logging and tracing
///        within the application.
namespace tracing {

/// @brief The **verbosity level**. This is used to control the
/// **amount of logging** emitted.
/// defaults to `LogLevel::LVL_INFO`
///
/// In general, when setting the log level of interest (e.g.
/// `LogLevel::LVL_DEBUG`), this will cause all less important log levels to
/// be ignored.
///
/// The following diagram illustrates how this works.
///
/// `Error` <- `Warn` <- `Info` <- `Debug` <- `Trace`
///
/// Example:
///
/// So, if the log level is set to `LogLevel::LVL_DEBUG`, then only
/// `LogLevel::LVL_DEBUG`, `LogLevel::LVL_INFO`, `LogLevel::LVL_WARN`, and
/// `LogLevel::LVL_ERROR` messages will be emitted, but not
/// `LogLevel::LVL_TRACE` messages.
///
/// ```cpp
/// // Set the log level to `LVL_DEBUG`
/// setLogLevel(LogLevel::LVL_DEBUG);
///
/// // This will be logged
/// debug("This is a debug message");
///
/// // This will not be logged
/// trace("This is a trace message");
/// ```
enum LogLevel {
    /// @brief The most verbose level. This is used for **debugging**.
    LVL_TRACE,
    /// @brief The second most fine-grained level for logging (e.g. less
    /// granular than `LVL_TRACE`).
    LVL_DEBUG,
    /// @brief The default log level. This is used for **informational**
    /// messages.
    LVL_INFO,
    /// @brief The second least verbose level. This is used for **warning**
    /// messages.
    LVL_WARN,
    /// @brief The least verbose level. This is used for **error** messages.
    LVL_ERROR
};

/// @brief The **log level**. This is used to control the **amount of
/// logging** emitted.
static LogLevel log_level = LVL_INFO;

/// Comparison operators for LogLevel
inline bool operator==(LogLevel a, LogLevel b) { return (int)a == (int)b; }

inline bool operator!=(LogLevel a, LogLevel b) { return (int)a != (int)b; }

inline bool operator<(LogLevel a, LogLevel b) { return (int)a < (int)b; }

/// @brief The log prefix
class LogPrefix {
   public:
    LogPrefix(LogLevel level) {
        switch (level) {
            case LVL_TRACE:
                prefix = format(fg(color::blue) | emphasis::bold, "TRACE");
                break;
            case LVL_DEBUG:
                prefix = format(fg(color::cyan) | emphasis::bold, "DEBUG");
                break;
            case LVL_INFO:
                prefix = format(fg(color::green) | emphasis::bold, "INFO");
                break;
            case LVL_WARN:
                prefix =
                    format(fg(fmt::color::yellow) | emphasis::bold, "WARN");
                break;
            case LVL_ERROR:
                prefix = format(fg(fmt::color::red) | emphasis::bold, "ERROR");
                break;
        }
    }
    string to_string() { return prefix; }

   private:
    string prefix;
};

/// @brief Log a message to the console
/// @param level The log level
/// @param strings The strings to log
inline void log(LogLevel level, vector<string_view> strings) {
    cout << format(fg(color::black) | emphasis::bold, "[")
         << LogPrefix{level}.to_string()
         << format(fg(color::black) | emphasis::bold, "]: ");
    for (auto s : strings) {
        cout << s << ", ";
    }
    cout << endl;
}

/// @brief Log a message to the console
/// @param level  The log level
/// @param str   The string to log
inline void log(LogLevel level, string_view str) {
    cout << format(fg(color::black) | emphasis::bold, "[")
         << LogPrefix{level}.to_string()
         << format(fg(color::black) | emphasis::bold, "]: ") << str << endl;
}

/// @brief Get the current log level (defaults to `LogLevel::LVL_INFO`)
/// @return The current log level
inline auto getLogLevel() { return log_level; }

/// @brief Set the log level
/// @param level The log level
inline auto set_log_level(LogLevel level) { log_level = level; }

/// @brief Initialize the log level
/// @param level The log level
inline auto initLogLevel(LogLevel level) { set_log_level(level); }

/// @brief Check if the log level allows for trace messages
/// @return `true` if the log level allows for trace messages
inline auto trace_enabled() { return LVL_TRACE >= getLogLevel(); }

/// @brief Check if the log level allows for debug messages
/// @return `true` if the log level allows for debug messages
inline auto debug_enabled() { return LVL_DEBUG >= getLogLevel(); }

/// @brief Check if the log level allows for info messages
/// @return `true` if the log level allows for info messages
inline auto info_enabled() { return LVL_INFO >= getLogLevel(); }

/// @brief Check if the log level allows for warn messages
/// @return `true` if the log level allows for warn messages
inline auto warn_enabled() { return LVL_WARN >= getLogLevel(); }

/// @brief Check if the log level allows for error messages
/// @return `true` if the log level allows for error messages
inline auto error_enabled() { return LVL_ERROR >= getLogLevel(); }

/// @brief Log a trace message to the console
/// @param str The string to log
inline auto trace(string_view str) {
    if (trace_enabled()) log(LVL_TRACE, str);
}

/// @brief Log a debug message to the console
/// @param str The string to log
inline auto debug(string_view str) {
    if (debug_enabled()) log(LVL_DEBUG, str);
}

/// @brief Log an info message to the console
/// @param str The string to log
inline auto info(string_view str) {
    if (info_enabled()) log(LVL_INFO, str);
}

/// @brief Log a warning message to the console
/// @param str The string to log
inline auto warn(string_view str) {
    if (warn_enabled()) log(LVL_WARN, str);
}

/// @brief Log an error message to the console
/// @param str The string to log
inline auto error(string_view str) {
    if (error_enabled()) log(LVL_ERROR, str);
}

/// @brief Log a debug message to the console
/// @param strings The strings to log
inline auto debug(vector<string_view> strings) {
    if (debug_enabled()) log(LVL_DEBUG, strings);
}

/// @brief Log an info message to the console
/// @param strings The strings to log
inline auto info(vector<string_view> strings) {
    if (info_enabled()) log(LVL_INFO, strings);
}

/// @brief Log a warning message to the console
/// @param strings The strings to log
inline auto warn(vector<string_view> strings) {
    if (warn_enabled()) log(LVL_WARN, strings);
}

/// @brief Log an error message to the console
/// @param strings The strings to log
inline auto error(vector<string_view> strings) {
    if (error_enabled()) log(LVL_ERROR, strings);
}

/// @brief Log system initialization information (window size, map size, etc.)
auto init() -> void {
    info(format("Initializing {}", config::WINDOW_TITLE));
    debug(format("Window size: {}x{}", config::WINDOW_WIDTH,
                 config::WINDOW_HEIGHT));
    debug(format("Map size: {}x{}", config::MAP_WIDTH, config::MAP_HEIGHT));
    debug(format("Max FPS: {}", config::MAX_FPS));
    debug(format("Debug mode: {}", config::DEBUG_MODE));

    trace("Starting main loop...");
}

}  // namespace tracing