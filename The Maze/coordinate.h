#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate {

    public:
        Coordinate();
        Coordinate(int x, int y);

        int getX() { return xCoordinate; }
        int getY() { return yCoordinate; }
        void setX(int value) { xCoordinate += value; }
        void setY(int value) { yCoordinate += value; }

    private:
        int xCoordinate;
        int yCoordinate;
};

bool operator==(Coordinate& point1, Coordinate& point2);

#endif