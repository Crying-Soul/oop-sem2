#include "abilities/RandomStrike.hpp"
#include <iostream>
#include <vector>

void RandomStrike::use(Game &game) const {
  ShipManager enemyManager = game.getEnemyShipManager();
  auto enemyFleet = enemyManager.getAllShips();

  if (enemyFleet.empty()) {
    std::cout << "No enemy ships available." << std::endl;
    return;
  }

  // ??????? ????????? ?????? ?????? Random
  Random randomGenerator;

  std::vector<std::shared_ptr<ShipSegment>> validSegments;

  for (auto &ship : enemyFleet) {
    auto &segments = ship->getSegments();
    for (auto &segment : segments) {
      if (segment->getStatus() == ShipSegment::SegmentStatus::Intact ||
          segment->getStatus() == ShipSegment::SegmentStatus::Damaged) {
        // segment->hit();
        validSegments.push_back(segment);
      }
    }
  }

  size_t randomSegmentIndex =
      randomGenerator.getRandomValue<int>(0, validSegments.size() - 1);
  auto randomSegment = validSegments[randomSegmentIndex];

  // ??????? ???? ?????????? ????????
  if (randomSegment->getStatus() == ShipSegment::SegmentStatus::Intact) {
    randomSegment->hit(); // ???? ?? ????????

  } else {
    std::cout << "The selected segment was already damaged." << std::endl;
  }
}

std::string RandomStrike::getName() const { return "Random Strike"; }

Ability::AbilityType RandomStrike::getType() const {
  return AbilityType::RANDOM_STRIKE;
}
