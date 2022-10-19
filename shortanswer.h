#include "quiz.h"

class ShortAnswer : public Quiz{
    string answer;
public:
    ShortAnswer(string question, int level, int score, string answer);
    string choiceAnswer(string ans);
    string getAnswer();
    void showAnswer();
};