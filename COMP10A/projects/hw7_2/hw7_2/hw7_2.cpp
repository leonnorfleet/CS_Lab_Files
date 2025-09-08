// hw7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class Monster {
private:
    int pos_x = 0, pos_y = 0;
    string name;

public:
    // accessors
    string getName() const {
        return name;
    }
    int getX() const {
        return pos_x;
    }
    int getY() const {
        return pos_y;
    }
    void display() const {
        cout << "Monster: " << name << ", position = (" << pos_x << "," << pos_y << ")" << endl;
    }

    // mutators
    void setName(string aName) {
        name = aName;
    }
    void setXY(int x, int y) {
        if ((x <= 100 && x >= 0) && (y <= 100 && y >= 0)) {
            pos_x = x;
            pos_y = y;

            cout << name << " XY position set to: (" << pos_x << "," << pos_y << ")" << endl;
        }
        else {
            cout << "Error: Illegal Position XY" << endl;
        }
    }
    void setX(int x) {
        if ((x <= 100 && x >= 0)) {
            pos_x = x;
            cout << name << " X position set to: " << pos_x << endl;
        }
        else {
            cout << "Error: Illegal Position X" << endl;
        }
    }
    void setY(int y) {
        if ((y <= 100 && y >= 0)) {
            pos_y = y;
            cout << name << " Y position set to: " << pos_y << endl;
        }
        else {
            cout << "Error: Illegal Position Y" << endl;
        }
    }
    void moveLeft() {
        if (pos_x >= 1) {
            pos_x--;
            cout << name << " Moved to the left. X position set to: " << pos_x << endl;
        }
        else {
            cout << "Error: Illegal Move Left" << endl;
        }
    }
    void moveRight() {
        if (pos_x <= 99) {
            pos_x++;
            cout << name << " Moved to the right. X position set to: " << pos_x << endl;
        }
        else {
            cout << "Error: Illegal Move Right" << endl;
        }
    }
    void moveUp() {
        if (pos_y <= 99) {
            pos_y++;
            cout << name << " Moved upwards. Y position set to: " << pos_y << endl;
        }
        else {
            cout << "Error: Illegal Move Up" << endl;
        }
    }
    void moveDown() {
        if (pos_y >= 1) {
            pos_y--;
            cout << name << " Moved downwards. Y position set to: " << pos_y << endl;
        }
        else {
            cout << "Error: Illegal Move Down" << endl;
        }
    }
};

int main()
{
    Monster monster1;
    monster1.setName("monster1");
    monster1.display();
    monster1.setXY(3, -1);
    monster1.display();
    monster1.setXY(-1, 2);
    monster1.display();
    monster1.setXY(-5, -4);
    monster1.display();
    monster1.setXY(0, 0);
    monster1.display();

    monster1.moveLeft();
    monster1.display();
    monster1.moveDown();
    monster1.display();
    monster1.moveUp();
    monster1.display();
    monster1.moveRight();
    monster1.display();

    cout << endl;

    Monster monster2;
    monster2.setName("monster2");
    monster2.setX(-200);
    monster2.display();
    monster2.setX(101);
    monster2.display();
    monster2.setY(102);
    monster2.display();

    monster2.setX(100);
    monster2.display();
    monster2.setY(100);
    monster2.display();
    monster2.moveUp();
    monster2.display();
    monster2.moveDown();
    monster2.display();
    monster2.moveRight();
    monster2.display();
    monster2.moveLeft();
    monster2.display();
}