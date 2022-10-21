#include "map.h"
#include <ctime>
#include <cstdlib>
#include <atomic>
// #ifndef LINUX_KBHIT_H_
// #define LINUX_KBHIT_H_
// #include <stdio.h>
// #include <termios.h>
// #include <atomic>
// //#include <unistd.h>



// int linux_kbhit(void)
// {
//     struct termios oldt, newt; 
//     int ch;
//     tcgetattr( STDIN_FILENO, &oldt ); 
//     newt = oldt;
//     newt.c_lflag &= ~( ICANON | ECHO ); 
//     tcsetattr( STDIN_FILENO, TCSANOW, &newt );    
//     ch = getchar();
//     tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
//     return ch;
// }
// #endif

//atomic<int> rainCnt(0);
int rainCnt;
pthread_mutex_t mutexid;
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

    VerticalLine vLine1(origin_x + width/2, origin_y + height-2*gap, gap*2, ch);
    vLine1.show();

    // VerticalLine vLine1(origin_x + width/2, origin_y + height-gap, gap, ch);
    // vLine1.show();

    Text tName(origin_x + gap + 1, origin_y + height-gap, "이름 : ");
    tName.show();
    
    Text tLevel(origin_x + width/2 + gap, origin_y + height-2*gap, "난이도 : ");
    tLevel.show();   

    Text tScore(origin_x + width/2 + gap, origin_y + height-gap, "총점 : ");
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

    VerticalLine vLine1(origin_x + width/2, origin_y + height-2*gap, gap*2, ch);
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

void Map::showLevel(int level)
{    
    int x = origin_x + width/2 + 11;
    int y = origin_y + height - 4;
    textLevel.set(x, y, to_string(level));
    textLevel.show();
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
    int x = origin_x + 12;
    int y = origin_y + height - 4;
    textAnswer.set(x, y, ans);
    textAnswer.show();
}

void Map::showAnswerResult(string ans)
{
    //.origin_x + gap + 1, origin_y + height - 2*gap
    int x = origin_x + 25;
    int y = origin_y + height - 4;
    textAnswerResult.set(x, y, ans);
    textAnswerResult.show();
}

void Map::showRain(vector<string> answers, int fallingTime)
{
    int n = answers.size();    
    nThreads = n;
    int rainX = (width - 2)/n;
    
    vThreads = new pthread_t[n];
    sr = new StringRain[n];

    for(int i = 0; i < n; ++i){
        double ratio = 1 + (rand()%201 - 100)*0.001;
        int s_x = rainX*i + 3;
        int s_y = origin_y + 3;

        sr[i].set(s_x, s_y, height-4, answers[i], fallingTime*ratio);    
        pthread_create(&vThreads[i], NULL, rain_thread, &sr[i]);            
    }       
    //getAnswer();    
}    

void Map::resetForWriteAnswer()
{
    strAnswer = "NULL";
    rainCnt = 0;
    pthread_mutex_init(&mutexid, NULL);
}

void Map::showText(int x, int y, string text)
{
    int s_x = origin_x + x;
    int s_y = origin_y + y;
    textShow.set(s_x, s_y, text);
    textShow.show();
}

void Map::showResultInfo(PlayerManager& pm)
{
    int s_x = origin_x + width/2 - 15;
    int s_y = origin_y + 5;
    int rank = 1;
    gotoxy(s_x, s_y);
    while(pm.showInfoByRank(rank++)) {gotoxy(s_x, ++s_y);}  

    s_x = origin_x + width/2 - 7;
    s_y = origin_y -1; 
    gotoxy(s_x, s_y);
    showText(s_x, s_y, "R  A  N  K");
}

void Map::showWarning(){
    int s_x = origin_x + width/2 - 7;
    int s_y = origin_y -1; 
    gotoxy(s_x, s_y);
    showText(s_x, s_y, "I  N  F  O");

    s_x = origin_x + width/2 - 17;
    s_y = origin_y +5; 
    gotoxy(s_x, s_y);
    showText(s_x, s_y, "This game is Quiz Rain");

    s_x = origin_x + width/2 - 17;
    s_y = origin_y +6; 
    gotoxy(s_x, s_y);
    showText(s_x, s_y, "문제 유형은 OX/객관식/주관식 입니다.");

    s_x = origin_x + width/2 - 17;
    s_y = origin_y +7; 
    gotoxy(s_x, s_y);
    showText(s_x, s_y, "보기가 땅에 닿을때까지 엔터를 치지 않으면");

    s_x = origin_x + width/2 - 17;
    s_y = origin_y +8; 
    gotoxy(s_x, s_y);
    showText(s_x, s_y, "작성중인 답안이 자동으로 제출됩니다.");

    s_x = origin_x + width/2 - 17;
    s_y = origin_y +9; 
    gotoxy(s_x, s_y);
    showText(s_x, s_y, "오답 입력시 게임 오버됩니다.");

    s_x = origin_x + width/2 - 17;
    s_y = origin_y +10; 
    gotoxy(s_x, s_y);
    showText(s_x, s_y, "한글 오입력 시 backspace 3번 눌러야 지워집니다.");
}


void showMenu();


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

void Map::removeAnswerResult()
{
    textAnswerResult.hide();
}

void Map::removeRain()
{    
    for(int i = 0; i < nThreads; ++i)
        pthread_cancel(vThreads[i]);
}

// void Map::getAnswer()
// {
//     string res;
//     char c;    

//     while(c != '\n'){        
//         c = linux_kbhit();           
//         if(c == '\n') break;
//         res += (char)c;
//         showAnswer(res);
//     }    
//     //res[res.length() - 1] = '\0';
//     strAnswer = res;     
// }

string Map::waitAnswer()
{
    usleep(500000);    
    
    while(strAnswer == "NULL" && rainCnt != 0){        
        usleep(5000);       
    }    
    
    return strAnswer;
}

void* rain_thread(void *arg)
{
    StringRain* tmp = (StringRain*)arg; 
    pthread_mutex_lock(&mutexid);
    ++rainCnt;
    pthread_mutex_unlock(&mutexid);

    tmp->show();

    pthread_mutex_lock(&mutexid);
    --rainCnt;;
    pthread_mutex_unlock(&mutexid);
    
    return NULL;
}

Map::~Map()
{    
    for(int i = 0; i < nThreads; ++i)
        pthread_join(vThreads[i], (void **)NULL);

    delete [] vThreads; 
    delete [] sr;
}