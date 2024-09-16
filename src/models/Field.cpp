#include "Field.hpp"

Field::Field(int rowCount, int colCount) : rows(rowCount), columns(colCount) {
    field.resize(rows, std::vector<FieldCell>(columns));
}

void Field::create() {
    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < columns; ++y) {
            field[x][y].cord = {x, y};
            field[x][y].value = '~';  
        }
    }
}

void Field::display() const {
    std::cout << "+";
    for (int y = 0; y < columns; y++) {
        std::cout << "---+";
    }
    std::cout << std::endl;

    for (int x = 0; x < rows; ++x) {
        std::cout << "|";
        for (int y = 0; y < columns; ++y) {
            std::cout << " " << field[x][y].value << " |";
        }
        std::cout << std::endl;

        std::cout << "+";
        for (int y = 0; y < columns; ++y) {
            std::cout << "---+";
        }
        std::cout << std::endl;
    }
}

void Field::setValueAt(Coordinate cord, char value) {
    if (!isValidCoordinate(cord)) {
        throw std::out_of_range("Coordinate out of range");
    }
    field[cord.x][cord.y].value = value;
}

char Field::getValueAt(Coordinate cord) const {
    if (!isValidCoordinate(cord)) {
        throw std::out_of_range("Coordinate out of range");
    }
    return field[cord.x][cord.y].value;
}

bool Field::isValidCoordinate(Coordinate cord) const {
    return cord.x < rows && cord.y < columns;  
}
