#include "shortanswer.h"
#include <cstring>

ShortAnswer::ShortAnswer(string question, int level, int score, string answer) : Quiz(question, level, score){
    this->answer = answer;
}

string ShortAnswer::choiceAnswer(string ans){ return ans; }

string ShortAnswer::getAnswer(){ return answer ;}

void ShortAnswer::showAnswer(){
    cout << "정답은 " << getAnswer() << " 입니다." << endl;
}

bool ShortAnswer::checkAnswer(string choosen_ans){
    if (strcasecmp((this->answer.c_str()),(choosen_ans.c_str())) == 0)
    //if (this->answer == choosen_ans)
        return true;
    else   
        return false;
}

vector<string> ShortAnswer::getAnswers(){
    vector<string> res;
    res.push_back("정답을 입력하세요(단답형)");
    
    return res;
}