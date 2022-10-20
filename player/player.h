#pragma once
#include <string>
using namespace std;

class Player{
    string name;
    int score;
    int rank;
public:
    Player() : Player("unknown", 0) {}
    Player(string n, int s) : name(n), score(s), rank(-1) {}
    void setName(string);
    void setScore(int);
    void setRank(int);
    string getName();
    int getScore();
    int getRank();    
    void showInfo();
};