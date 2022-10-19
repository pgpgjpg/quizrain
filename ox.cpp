#include "ox.h"

OX::OX(string question, int level, int score, char answer) : Quiz(question, level, score){
    this->answer = answer;
}

char OX::choiceAnswer(char ox){ return ox; }

char OX::getAnswer(){ return answer ;}

void OX::showAnswer(){
    cout << "정답은 " << getAnswer() << " 입니다." << endl;
}