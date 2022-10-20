#include "ox.h"

OX::OX(string question, int level, int score, char answer) : Quiz(question, level, score){
    this->answer = answer;
}

char OX::choiceAnswer(char ox){ return ox; }

char OX::getAnswer(){ return answer ;}

void OX::showAnswer(){
    cout << "정답은 " << getAnswer() << " 입니다." << endl;
}

bool OX::checkAnswer(string choosen_ans){
    if (this->answer == choosen_ans[0])
        return true;
    else   
        return false;
}

vector<string> OX::getAnswers(){
    vector<string> res;
    res.push_back("O(대문자)");
    res.push_back("X(대문자)");
    return res;
}