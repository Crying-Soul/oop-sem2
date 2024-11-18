#include <string>
#include <exception>
class ShipPlacementException : public std::exception {
public:
    explicit ShipPlacementException(const std::string& arg_message)
        : message(arg_message) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};

class ShipIntersectionException : public ShipPlacementException {
public:
    explicit ShipIntersectionException(const std::string& arg_message)
        : ShipPlacementException(arg_message) {}
};

class ShipProximityException : public ShipPlacementException {
public:
    explicit ShipProximityException(const std::string& arg_message)
        : ShipPlacementException(arg_message) {}
};
