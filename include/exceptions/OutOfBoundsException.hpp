#include <exception>
#include <string>

class OutOfBoundsException : public std::exception {
public:
  explicit OutOfBoundsException(const std::string &arg_message)
      : message(arg_message) {}

  const char *what() const noexcept override { return message.c_str(); }

private:
  std::string message;
};
