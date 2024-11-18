#include <exception>
#include <string>

class AttackException : public std::exception {
public:
  explicit AttackException(const std::string &arg_message)
      : message(arg_message) {}

  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message; // The error message
};
