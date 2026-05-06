#pragma once

#include <iostream>
#include <string>

namespace algobox {
    struct SizeLimitException;
    struct NoAlgoModeSelected;
    struct OutOfRange;
}

struct algobox::SizeLimitException : public std::exception {
    size_t current_size;
    size_t expected_size;
    std::string message;
    SizeLimitException(const size_t cur, const size_t exp);

    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

inline algobox::SizeLimitException::SizeLimitException(const size_t cur, const size_t exp):
    current_size(cur), expected_size(exp){
        message = "[SizeLimitException]: Expected a vector of size: " + std::to_string(exp) +
                " but current size is: " + std::to_string(cur);
}

struct algobox::NoAlgoModeSelected : public std::exception {
    const char* message;
    NoAlgoModeSelected();

    virtual const char* what() const noexcept override {
        return message;
    }
};

inline algobox::NoAlgoModeSelected::NoAlgoModeSelected() :
    message ("[NoAlgoModeSelected]: No algorithm mode has been chosen for this vector {search, sort, etc.}") {}

struct algobox::OutOfRange : public std::exception {
    size_t wanted_index;
    size_t valid_index;
    std::string message;
    OutOfRange(const size_t wanted_index, const size_t valid_index);

    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

inline algobox::OutOfRange::OutOfRange(const size_t wanted, const size_t valid):
    wanted_index(wanted), valid_index(valid){
        message = "[OutOfRange]: The accessed index is out of range of this vector: " + std::to_string(wanted) +
                " current size is: " + std::to_string(valid);
}
