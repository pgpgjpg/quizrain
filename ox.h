#include "quiz.h"

class OX : public Quiz{
    char answer;
public:
    OX(string question, int level, int score, char answer);
    char choiceAnswer(char ox);
    char getAnswer();
    void showAnswer();
    string checkAnswer(string choosen_ans);
    vector<string> getAnswers();
};