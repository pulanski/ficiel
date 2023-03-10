#pragma once

// #include <folly/FBString.h>
#include <string>
#include <utility>

// #include "llvm/ADT/SmallString.h"

/// @brief Data structures used throughout the codebase
namespace data_structures {

/// @brief A drop-in replacement for `std::string` that uses
/// small string optimization (SSO) to avoid heap allocations
/// for small strings.
namespace string {

// using llvm::SmallString; // TODO

/// @brief The size of the small string optimization buffer
/// @details This is the size of the buffer that is used for
/// small string optimization. If the string is smaller than
/// this size, it will be stored in the buffer instead of
/// being allocated on the heap.
static constexpr size_t kSmallStringSize = 32;

/// @brief A newtype wrapper for `llvm::SmallString` that
/// represents a string with a small size optimization.
/// This is used as a stand-in replacement for `std::string`
/// in the codebase.
/// A **newtype** wrapper for `llvm::SmallString`
class String {
   public:
    // Constructors
    String() = default;
    // SmallString(const char* str) : data_(str) {}
    // SmallString(const std::string& str) : data_(str) {}
    // SmallString(std::string&& str) : data_(std::move(str)) {}

    // Conversion operators
    // operator const std::string&() const { return data_; }
    // operator std::string() const { return data_; }
    // operator const llvm::SmallString<kSmallStringSize>&() const {
    //     return data_;
    // }

    // operator llvm::SmallString<kSmallStringSize>() const { return data_; }

    // Comparison operators
    bool operator==(const String& other) const { return data_ == other.data_; }
    bool operator!=(const String& other) const { return data_ != other.data_; }

    // Accessors
    const char* c_str() const { return data_.c_str(); }

    // static method to create a new instance of SmallString from a given string
    // literal
    static String from(const char* str) {
        String string;
        string.data_ = str;
        return string;
    }

    /// @brief Create a new instance of SmallString from a given string
    /// @param str The string to create a new instance of SmallString from
    /// @return A new instance of SmallString
    static String from(const std::string& str) {
        String string;
        string.data_ = str;
        return string;
    }

    static String from(std::string&& str) {
        String string;
        string.data_ = std::move(str);
        return string;
    }

    static String from(const char* str, size_t size) {
        String string;
        string.data_ = str;
        return string;
    }

    static String from(std::string& str, size_t size) {
        String string;
        string.data_ = str;
        return string;
    }

    static String from(std::string&& str, size_t size) {
        String string;
        string.data_ = std::move(str);
        return string;
    }

    // size_t size() const { return data_.size(); }
    // size_t length() const { return data_.length(); }

    // from(&str) is a static method that returns a SmallString
    // from a string
    // static SmallString from(const std::string& str) { return
    // SmallString(str); }

   private:
    std::string data_;  // TODO: temp
    // SmallString<kSmallStringSize> data_;
};
}  // namespace string

}  // namespace data_structures
