#ifndef SHIP_HPP
#define SHIP_HPP

#include <iostream>
#include <algorithm>

class Ship {
private:
    int* segments;  
    int size;       

public:
    Ship(int size);
    ~Ship();

    void printState() const;        
    void updateSegment(int segmentId, int value);  
    bool isDestroyed() const;       
    int getSize() const;
    int getSegment( int segmentId) const;
};


#endif
