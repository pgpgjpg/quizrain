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
    string callCheckAnswer(int n, string choice_answer); //n번 문제의 choice_answer 정답 입력 받아서 정답/오답 메시지 리턴
    vector<string> sendGetAnswers(); //보기 map에 띄워줌
};