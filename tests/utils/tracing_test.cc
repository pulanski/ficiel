#include "utils/tracing.h"

#include <gtest/gtest.h>

using tracing::debug;
using tracing::debug_enabled;
using tracing::error;
using tracing::error_enabled;
using tracing::info;
using tracing::info_enabled;
using tracing::set_log_level;
using tracing::trace;
using tracing::trace_enabled;
using tracing::warn;
using tracing::warn_enabled;

//------------------------------------------------------------------------------
// Tracing
//------------------------------------------------------------------------------

TEST(TracingLevels, Trace) {
    set_log_level(tracing::LVL_INFO);

    // `Error` < - `Warn` < - `Info` < - `Debug` < - `Trace`

    EXPECT_FALSE(trace_enabled());
    EXPECT_FALSE(debug_enabled());
    EXPECT_TRUE(info_enabled());
    EXPECT_TRUE(warn_enabled());
    EXPECT_TRUE(error_enabled());

    // make sure log functions only output when enabled

    testing::internal::CaptureStdout();  // redirect stdout to a string buffer

    trace("trace");  // should not be logged
    debug("debug");  // should not be logged
    info("info");    // should be logged
    warn("warn");    // should be logged
    error("error");  // should be logged

    std::string output =
        testing::internal::GetCapturedStdout();  // get the captured stdout

    EXPECT_EQ(output.find("trace"), std::string::npos)
        << "trace should not be logged";
    EXPECT_EQ(output.find("debug"), std::string::npos)
        << "debug should not be logged";
    EXPECT_NE(output.find("info"), std::string::npos)
        << "info should be logged";
    EXPECT_NE(output.find("warn"), std::string::npos)
        << "warn should be logged";
    EXPECT_NE(output.find("error"), std::string::npos)
        << "error should be logged";
}
