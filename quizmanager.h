#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "quiz.h"
#include "ox.h"
#include "multichoice.h"
#include "shortanswer.h"
using namespace std;

class QuizManager
{
private:
	vector<Quiz*> quizList;
//    Music m_music
public:
	void playQuiz();
    void fileRead(ifstream &fin);
    void showQuizList() const;
    int getNumQuiz();
    string getQuiz(int n);
    bool callCheckAnswer(int n, string choice_answer);
    vector<string> sendGetAnswers();
};