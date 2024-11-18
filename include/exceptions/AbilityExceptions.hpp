#include <exception>
#include <string>

class AbilityException : public std::exception {
public:
  explicit AbilityException(const std::string &arg_message)
      : message(arg_message) {}

  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message; // The error message
};
