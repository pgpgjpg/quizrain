#include "map.h"

void* rain_thread(void *arg);

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
    int n = answers.size();    
    nThreads = n;
    int rainX = (width - 2)/n;
    
    vThreads = new pthread_t[n];
    sr = new StringRain[n];

    for(int i = 0; i < n; ++i){
        int s_x = rainX*i + 3;
        int s_y = origin_y + 3;

        sr[i].set(s_x, s_y, height-4, answers[i], fallingTime);    
        pthread_create(&vThreads[i], NULL, rain_thread, &sr[i]);            
    }       
    for(int i = 0; i < n; ++i)
        pthread_join(vThreads[i], (void **)NULL);
}   

void Map::showText(int x, int y, string text)
{
    int s_x = origin_x + x;
    int s_y = origin_y + y;
    textScore.set(s_x, s_y, text);
    textScore.show();
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
    // 미완성
    for(int i = 0; i < nThreads; ++i)
        pthread_cancel(vThreads[i]);
}

string Map::getAnswer()
{
    string res;
    // char c;
    // int cnt = 0;
    // while(c != '\n'){
    //     c = getchar();
    //     gotoxy(origin_x + 6 + cnt, origin_y + height - 4);
    //     putchar(c);
    //     ++cnt;
    //     res += c;        
    // }
    return res;
}

void* rain_thread(void *arg)
{
    StringRain* tmp = (StringRain*)arg; 
    
    tmp->show();

    return NULL;
}