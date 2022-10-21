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
    int totalScore; //각 플레이어가 문제 풀때 토탈스코어 저장해서 플레이어쪽에 보내줘야함.
//    Music m_music
public:
	void playQuiz();
    void fileRead(ifstream &fin);
    void showQuizList() const;
    int getNumQuiz(); // 문제의 개수 리턴
    string getQuiz(int n);  //문제 리턴
    bool callCheckAnswer(int n, string choice_answer); //n번 문제의 choice_answer 정답 입력 받아서 정답/오답 메시지 리턴
    vector<string> sendGetAnswers(int n); //n번 문제 보기 map에 띄워줌
    int getTotalScore(){return totalScore;};
    void setTotalSocre();
    int getQuizLevel(int n); //n번 문제의 난이도 int로 리턴
    void randomQuiz(); //퀴즈리스트 랜덤 정렬
};