#include "ui/UserInput.hpp"

bool UserInput::askUser(const std::string &message) {
  char choice;
  std::cout << message + " (y/n): ";
  std::cin >> choice;

  if (choice == 'y' || choice == 'Y') {
    return true;
  } else if (choice == 'n' || choice == 'N') {
    return false;
  } else {
    std::cout << "Invalid choice. Please enter 'y' or 'n'.\n";
    return askUser(message);
  }
}

std::string UserInput::askString(const std::string &message) {
  std::string input;
  std::cout << message << ": ";
  std::cin.ignore();
  std::getline(std::cin, input);
  return input;
}

std::pair<int, int> UserInput::askTwoInts(const std::string &message) {
  int num1, num2;
  std::cout << message << " (Enter two integers separated by space): ";
  std::cin >> num1 >> num2;
  return std::make_pair(num1, num2);
}
