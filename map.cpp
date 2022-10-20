#include "map.h"

#ifndef LINUX_KBHIT_H_
#define LINUX_KBHIT_H_
#include <stdio.h>
#include <termios.h>
//#include <unistd.h>
int linux_kbhit(void)
{
    struct termios oldt, newt; int ch;
    tcgetattr( STDIN_FILENO, &oldt ); 
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO ); 
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
     return ch;
}
#endif


void* rain_thread(void *arg);

void Map::showFrame(char ch)
{
    clearTerminal();
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

    Text tAnswer(origin_x + gap + 1, origin_y + height - 2*gap, "입력값 : ");
    tAnswer.show();
}

void Map::showResultFrame()
{
    clearTerminal();
    char ch = '*';
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

void Map::showAnswer(string ans)
{
    //.origin_x + gap + 1, origin_y + height - 2*gap
    int x = origin_x + 10;
    int y = origin_y + height - 4;
    textAnswer.set(x, y, ans);
    textAnswer.show();
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
    getAnswer();    
}   

void Map::showText(int x, int y, string text)
{
    int s_x = origin_x + x;
    int s_y = origin_y + y;
    textScore.set(s_x, s_y, text);
    textScore.show();
}

void Map::showResultInfo(PlayerManager& pm)
{
    int s_x = origin_x + width/2 - 15;
    int s_y = origin_y + 5;
    gotoxy(s_x, s_y);
    pm.showAllPlayer();    
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

void Map::removeAnswer()
{
    textAnswer.hide();
}

void Map::removeRain()
{    
    for(int i = 0; i < nThreads; ++i)
        pthread_cancel(vThreads[i]);
}

void Map::getAnswer()
{
    string res;
    char c;    

    while(c != '\n'){
        c = linux_kbhit();           
        res += (char)c;
        showAnswer(res);
    }    
    
    strAnswer = res;     
}

string Map::waitAnswer()
{
    while(strAnswer == "NULL"){
        usleep(5000);       
    }    
    
    return strAnswer;
}

void* rain_thread(void *arg)
{
    StringRain* tmp = (StringRain*)arg; 
    
    tmp->show();

    return NULL;
}

Map::~Map()
{    
    for(int i = 0; i < nThreads; ++i)
        pthread_join(vThreads[i], (void **)NULL);

    delete [] vThreads; delete [] sr;
}