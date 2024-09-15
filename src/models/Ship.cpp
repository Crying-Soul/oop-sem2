#include "Ship.hpp"

Ship::Ship(int size) : size(size) {
    this->segments = new int[this->size]; 
    std::fill_n(this->segments, this->size, 2);  
}


Ship::~Ship() {
    delete[] this->segments;  
}

int Ship::getSegment(int segmentId) const {
    return this->segments[segmentId];
}

void Ship::printState() const {
    std::cout << "Ship state: ";
    for (int i = 0; i < this->size; i++) {
        std::cout << this->segments[i] << " ";  
    }
    std::cout << std::endl;
}


void Ship::updateSegment(int segmentId, int value) {
    if (segmentId >= 0 && segmentId < this->size) {
        this->segments[segmentId] += value;
    }
}

bool Ship::isDestroyed() const {
    for (int i = 0; i < this->size; i++) {
        if (this->segments[i] > 0) {
            return false;  
        }
    }
    return true;  
}


int Ship::getSize() const {
    return this->size;
}
