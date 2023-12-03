#include <iostream>
using namespace std;

const int row = 10;
const int col = 20;

class Coordintate
{
public:
    int distance;
    int x, y;

    Coordintate()
    {
        x = 0;
        y = 0;
        distance = 0;
    }
    Coordintate(int d, int a, int b)
    {
        distance = d;
        x = a;
        y = b;
    }
    bool operator<(Coordintate &other)
    {
        return distance < other.distance;
    }
};

bool isValid(int x, int y)
{

    if (x >= 0 && x < row && y >= 0 && y < col)
    {
        return 1;
    }
    return 0;
}

