#include "multichoice.h"

MultiChoice::MultiChoice(string question, int level, int sore, int answer, string s1, string s2, string s3, string s4) : Quiz(question, level, score){
    this->answer = answer;
    this->s1 = s1;
    this->s1 = s2;
    this->s1 = s3;
    this->s1 = s4;
}

int MultiChoice::choiceAnswer(int n){ return n; }

int MultiChoice::getAnswer(){ return answer ;}

void MultiChoice::showAnswer(){
    cout << "정답은 " << getAnswer() << " 입니다." << endl;
}