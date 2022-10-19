#include "quiz.h"

Quiz::Quiz(string question, int level, int score){
    this->question = question;
    this->level = level;
    this->score = score;
}

string Quiz::getQuestion(){ return question; }

string setQuestion();