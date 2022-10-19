#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Quiz{
protected:
    string question;
    int level;  //난이도
    int score;  //문제 당 배점
public:
    Quiz(string question, int level, int score);
    string getQuestion();
    string setQuestion();
    void fileRead(ifstream &fin);
    virtual bool checkAnswer(string choice_answer) = 0;
};