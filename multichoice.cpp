#include "multichoice.h"

MultiChoice::MultiChoice(string question, int level, int score, int answer, string s1, string s2) : Quiz(question, level, score){
    this->answer = answer;
    this->s1 = s1;
    this->s2 = s2;
}

MultiChoice::MultiChoice(string question, int level, int score, int answer, string s1, string s2, string s3) : Quiz(question, level, score){
    this->answer = answer;
    this->s1 = s1;
    this->s2 = s2;
    this->s3 = s3;
}

MultiChoice::MultiChoice(string question, int level, int score, int answer, string s1, string s2, string s3, string s4) : Quiz(question, level, score){
    this->answer = answer;
    this->s1 = s1;
    this->s2 = s2;
    this->s3 = s3;
    this->s4 = s4;
}

int MultiChoice::choiceAnswer(int n){ return n; }

int MultiChoice::getAnswer(){ return answer ;}

void MultiChoice::showAnswer(){
    cout << "정답은 " << getAnswer() << " 입니다." << endl;
}

bool MultiChoice::checkAnswer(string choosen_ans){
    try{
    if (this->answer == stoi(choosen_ans))
        return true;
    else   
        return false;
    }
    catch(invalid_argument){
        return false;
    }
    catch(out_of_range){
        return false;
    }
}

vector<string> MultiChoice::getAnswers()
{
    vector<string> res;

    if(this->s3 == ""){
        res.push_back(this->s1);
        res.push_back(this->s2);
    }
    else if (this->s4 == ""){
        res.push_back(this->s1);
        res.push_back(this->s2);
        res.push_back(this->s3);
    }
    else{
        res.push_back(this->s1);
        res.push_back(this->s2);
        res.push_back(this->s3);
        res.push_back(this->s4);
    }
    return res;
}

