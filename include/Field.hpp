#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>
#include <stdexcept>
#include <iostream>

struct Coordinate {
    unsigned int x;
    unsigned int y;
};

struct FieldCell {
    Coordinate cord;
    char value;
};

class Field {
private:
    int rows;
    int columns;
    std::vector<std::vector<FieldCell>> field;  

public:
    Field(int rows, int columns);
    
    bool isValidCoordinate(Coordinate cord) const;

    void create();
    void display() const;

    char getValueAt(Coordinate cord) const;
    void setValueAt(Coordinate cord, char value);

    int getRows() const { return rows; }
    int getColumns() const { return columns; }
};

#endif
