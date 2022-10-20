#include <iostream>
#include <pthread.h>
#include <vector>
#include "map.h"
using namespace std;

int main()
{   
    Map map(100, 25);

    map.showFrame('*');
    map.showQuiz("test");
    map.showScore(100);
    map.showName("jpg");
    fflush(stdout);

    vector<string> as = {"abcd", "dasewqe", "qweqwr", "qwewqe", "qwe12312"};
    map.showRain(as, 1000000);
    
    
    string tmp = map.waitAnswer();
    map.showAnswer(tmp);
    
    
    fflush(stdout);
    sleep(10);
    // while(true){
    //     //usleep(10000);
    //     vector<string> as = {"abcd", "dasewqe", "qweqwr", "qwewqe", "qwe12312"};
    //     map.showRain(as, 500000);
    //     //string answer = map.getAnswer();
    //     //cout << answer << endl;
    // }

  

    // map.removeName();
    // map.removeQuiz();
    // map.removeScore();

    //usleep(300000);
    //map.removeRain();

}