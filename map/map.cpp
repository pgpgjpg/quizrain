#include "map.h"

void Map::showFrame(char ch)
{
    int gap = 2;
    Rect rect(origin_x, origin_y, width, height, ch);
    rect.show();

    HorizontalLine hLline1(origin_x, origin_y + gap, width, ch);
    hLline1.show();

    HorizontalLine hLine2(origin_x, origin_y + height-(gap+1), width, ch);
    hLine2.show();

    HorizontalLine hLine3(origin_x, origin_y + height-(2*gap+1), width, ch);
    hLine3.show();

    VerticalLine vLine1(origin_x + width/2, origin_y + height-gap, gap, ch);
    vLine1.show();

    Text tName(origin_x + gap + 1, origin_y + height-gap, "이름 : ");
    tName.show();

    Text tScore(origin_x + width/2 + gap, origin_y + height-gap, "점수 : ");
    tScore.show();

    Text tAnswer(origin_x + gap + 1, origin_y + height - 2*gap, "정답 : ");
    tAnswer.show();
}

void Map::showQuiz(string text)
{
    int x = origin_x + 3;
    int y = origin_y + 1;
    textQuiz.set(x, y, text);
    textQuiz.show();
}

void Map::showScore(int score)
{    
    int x = origin_x + width/2 + 9;
    int y = origin_y + height - 2;
    textScore.set(x, y, to_string(score));
    textScore.show();
}  

void Map::showName(string name)
{
    int x = origin_x + 10;
    int y = origin_y + height - 2;
    textName.set(x, y, name);
    textName.show();
}

void Map::showRain(vector<string> answers, int fallingTime)
{

}   

void Map::removeQuiz()
{
    textQuiz.hide();
}


void Map::removeScore()
{
    textScore.hide();
}

void Map::removeName()
{
    textName.hide();
}

void Map::removeRain()
{

}

string Map::getAnswer()
{
    return "NULL";
}