#include <iostream>
#include <pthread.h>
#include <vector>
#include "map.h"
using namespace std;

void * rain_thread(void *);
void * score_thread(void *);
pthread_mutex_t mutexid;
int main()
{   
    Map map(100, 25);

    map.showFrame('*');
    map.showQuiz("test");
    map.showScore(100);
    map.showName("jpg");

    // map.removeName();
    // map.removeQuiz();
    // map.removeScore();

    // pthread_mutex_init(&mutexid, NULL);
    // string strAnswer;  

    

    

    // StringRain sr1(5, 5, 19, "Quiz Answer1", 1);
    // //sr1.show();
    // StringRain sr2(25, 5, 19, "Quiz Answer2", 1);
    // //sr2.show();
    // StringRain sr3(45, 5, 19, "Quiz Answer3", 1);
    // //sr3.show();
    // StringRain sr4(65, 5, 19, "Quiz Answer4", 1);
    // //sr4.show();

    // pthread_t vThreads[4];
    // pthread_create(&vThreads[0], NULL, rain_thread, &sr1);
    // pthread_create(&vThreads[1], NULL, rain_thread, &sr2);
    // pthread_create(&vThreads[2], NULL, rain_thread, &sr3);
    // pthread_create(&vThreads[3], NULL, rain_thread, &sr4);

    // pthread_join(vThreads[0], (void **)NULL);
    // pthread_join(vThreads[1], (void **)NULL);
    // pthread_join(vThreads[2], (void **)NULL);
    // pthread_join(vThreads[3], (void **)NULL);    

    // pthread_mutex_destroy(&mutexid);
}

void* rain_thread(void *arg)
{
    //pthread_mutex_lock(&mutexid);
    ((StringRain*)arg)->show();
    //pthread_mutex_unlock(&mutexid);

    return NULL;
}

void * score_thread(void *arg)
{
    int score = 0;
    while(true){
        score++;
        if(score == 100) score = 0;
        ((Text*)arg)->setText(to_string(score));
        pthread_mutex_lock(&mutexid);
        ((Text*)arg)->show();            
        ((Text*)arg)->hide();   
        pthread_mutex_unlock(&mutexid);
    }
    return NULL;
}