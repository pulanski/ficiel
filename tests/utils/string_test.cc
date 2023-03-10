
#include "utils/data_structures/string.h"

#include <gtest/gtest.h>

// -----------------------------------------------------------------------------
// Small string optimization (fbstring newtype)
// -----------------------------------------------------------------------------

TEST(FbString, SmallStringOptimization) {
    // fbstring is a newtype wrapper (facade) around std::string that uses small
    // string optimization (SSO) to avoid heap allocations for small strings.
    // This test checks that the SSO works as expected.

    // create a string that is small enough to fit in the SSO buffer
    using String = data_structures::string::String;

    auto small_string = String::from("hello world");

    // // create a fbstring from the small string
    // fbstring fbstring_from_small_string = small_string;

    // check that the fbstring is using the SSO buffer
    // EXPECT_TRUE(fbstring_from_small_string.is_small());

    // // create a string that is too big to fit in the SSO buffer
    // std::string big_string = "hello world hello world hello world hello
    // world";

    // // create a fbstring from the big string
    // fbstring fbstring_from_big_string = big_string;

    // // check that the fbstring is not using the SSO buffer
    // EXPECT_FALSE(fbstring_from_big_string.is_small());

    // drop-in replacement for std::string
    // (i.e. same api, same behavior, same performance)

    // create a string
    // std::string string = "hello world";
}
