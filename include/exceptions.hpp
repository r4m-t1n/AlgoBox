#include <iostream>
#include <string>

namespace algobox {
    struct SizeLimitException;
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

algobox::SizeLimitException::SizeLimitException(const size_t cur, const size_t exp):
    current_size(cur), expected_size(exp){
        message = "[SizeLimitException]: Expected a vector of size: " + std::to_string(exp) +
                " but current size is: " + std::to_string(cur);
}
