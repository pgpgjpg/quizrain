#include "quiz.h"

class MultiChoice : public Quiz{
    int answer;
    string s1, s2, s3, s4;
public:
    MultiChoice(string question, int level, int sore, int answer, string s1, string s2, string s3, string s4);
    int choiceAnswer(int n);
    int getAnswer();
    void showAnswer();
};