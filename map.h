#pragma once

#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Map{
    int width;
    int height;
    int maxWidth;
    int maxHeight;
    vector<string> rain;
public:
    void showText(int x, int y, string text);
    void rect(int width, int height);
    void line(int x1, int y1, int x2, int y2);
    void moveRain();
};