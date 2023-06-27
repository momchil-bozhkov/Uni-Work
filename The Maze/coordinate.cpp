#include "coordinate.h"

Coordinate::Coordinate() {
    xCoordinate = 0;
    yCoordinate = 0;
}

Coordinate::Coordinate(int x, int y) {
    xCoordinate = x;
    yCoordinate = y;
}

bool operator==(Coordinate& point1, Coordinate& point2) {
    return ((point1.getX() == point2.getX()) && (point1.getY() == point2.getY()));
}