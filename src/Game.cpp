#include "Game.hpp"

Game::Game() : userField(0, 0), enemyField(0, 0) {}

void Game::createMap(uint8_t rowsCount, uint8_t columnsCount) noexcept {
    this->userField = Field(rowsCount, columnsCount);
    this->enemyField = Field(rowsCount, columnsCount);
}

void Game::createFleet(const std::vector<uint8_t> &sizes) {
    this->userManager = ShipManager(sizes);
    this->enemyManager = ShipManager(sizes);

    for (const auto &ship : this->userManager.getAllShips()) {
        this->userField.placeShipByRandCoords(ship);
    }

    for (const auto &ship : this->enemyManager.getAllShips()) {
        this->enemyField.placeShipByRandCoords(ship);
    }
}

void Game::userAttack(Coordinate coords) {
    this->enemyField.attack(coords);
    SegmentStatus status = this->enemyManager.attack(coords);
    this->update();

    switch (status) {
    case SegmentStatus::Intact:
        std::cout << "Missed!" << std::endl;
        break;
    case SegmentStatus::Damaged:
        std::cout << "Damaged!" << std::endl;
        break;
    case SegmentStatus::Destroyed:
        std::cout << "Destroyed!" << std::endl;
        break;
    default:
        break;
    }
}

void Game::enemyAttack(Coordinate coords) {
    this->userField.attack(coords);
    SegmentStatus status = this->userManager.attack(coords);
    this->update();

    switch (status) {
    case SegmentStatus::Intact:
        std::cout << "Missed!" << std::endl;
        break;
    case SegmentStatus::Damaged:
        std::cout << "Damaged!" << std::endl;
        break;
    case SegmentStatus::Destroyed:
        std::cout << "Destroyed!" << std::endl;
        break;
    default:
        break;
    }
}

void Game::display() const noexcept {
    std::cout << "User's Field:" << std::endl;
    this->userField.display();
    
    std::cout << "Enemy's Field (Hidden):" << std::endl;
    this->enemyField.display(true);
}

void Game::update() const noexcept {
    system("clear");
    this->userField.display();
    
    std::cout << "             ------ ENEMY ------" << std::endl;
    this->enemyField.display(true);
}
