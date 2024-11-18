#include "ui/CLIParser.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>

std::string CLIParser::askString(const std::string &prompt) const {
  std::string input;
  std::cout << prompt;
  std::getline(std::cin, input);
  return input;
}

std::pair<int, int> CLIParser::askTwoInts(const std::string &prompt) const {
  int x, y;
  std::cout << prompt;
  while (!(std::cin >> x >> y)) {
    std::cin.clear();  // Clear the error flag
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
    std::cout << "Invalid input. Please enter two integers: ";
  }
  return std::make_pair(x, y);
}

bool CLIParser::askUser(const std::string &prompt) const {
  char answer;
  std::cout << prompt << " (y/n): ";
  std::cin >> answer;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer
  return (answer == 'y' || answer == 'Y');
}

std::vector<uint8_t> CLIParser::askShipSizes() const {
  std::string shipSizesStr = askString("Enter ship sizes (comma separated): ");
  std::vector<uint8_t> shipSizes;
  std::stringstream ss(shipSizesStr);
  std::string size;

  while (std::getline(ss, size, ',')) {
    // Trim leading and trailing spaces
    size.erase(0, size.find_first_not_of(" \t"));
    size.erase(size.find_last_not_of(" \t") + 1);

    // Validate and convert size to integer
    try {
      int parsedSize = std::stoi(size);
      if (parsedSize > 0) {
        shipSizes.push_back(static_cast<uint8_t>(parsedSize));
      } else {
        std::cerr << "Invalid ship size: " << size << " (must be greater than 0)" << std::endl;
      }
    } catch (const std::invalid_argument &) {
      std::cerr << "Invalid input: '" << size << "' is not a valid number." << std::endl;
    } catch (const std::out_of_range &) {
      std::cerr << "Invalid input: '" << size << "' is out of range." << std::endl;
    }
  }

  if (shipSizes.empty()) {
    std::cerr << "No valid ship sizes entered. Please try again." << std::endl;
    return askShipSizes();  // Retry if no valid sizes were entered
  }

  // Sort the ship sizes in descending order
  std::sort(shipSizes.begin(), shipSizes.end(), std::greater<uint8_t>());
  return shipSizes;
}
int CLIParser::askSingleInt(const std::string &prompt) const {
    int input;
    std::cout << prompt;

    while (true) {
        std::cin >> input;
        
        // Check if the input was valid (a number)
        if (std::cin.fail()) {
            // Clear the error flag
            std::cin.clear();
            // Discard the invalid input from the buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid number: ";
        } else {
            // If input was valid, break out of the loop
            break;
        }
    }

    return input;
}