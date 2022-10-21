#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;
#include "quiz.h"
#include "quizmanager.h"
#include "map.h"
#include "playerManager.h"


int main(void)
{
    string name;
	// 퀴즈관리를 목적으로 설계된 컨트롤 클래스의 객체생성
	QuizManager q_manager;
    time_t new_time, old_time;

	// 퀴즈 등록
	vector<string> wordVector;
    ifstream fin("quizlist.txt");
    if(!fin){
        cout << "quizlist.txt 파일을 열수 없습니다" << endl;
        return 0;
    }
    q_manager.fileRead(fin);
    fin.close();
   
    ////게임 시작////////
    PlayerManager p_manager;
    Map map;
    while(true){
        system("clear");
        string ans;
        int choice;
        
        cout << "게임" << endl;
        cout << "1. 게임 시작" << endl;
        cout << "2. 랭크 확인" << endl;                
        cout << "3. 종료" << endl;

        cin >> choice;
        cin.ignore();
        switch(choice){
            case 1:{
                q_manager.randomQuiz(); // 퀴즈 셔플

                cout << "이름을 입력해주세요 :";
                getline(cin, name);
                q_manager.setTotalSocre();
                for (int i = 0; i < q_manager.getNumQuiz(); i++){
                    system("clear");

                    old_time = clock();
                    
                    

                    map.showFrame('*');
                    map.showName(name);
                    map.showQuiz(q_manager.getQuiz(i));
                    map.showLevel(q_manager.getQuizLevel(i));
                    p_manager.setScoreByName(name, q_manager.getTotalScore());
                    map.showScore(q_manager.getTotalScore());
                    map.showRain(q_manager.sendGetAnswers(i), 1000000);
                    string quizans = map.waitAnswer();
/*
                    do{
                        quizans=map.waitAnswer();
                        new_time = clock();
                        if(difftime(new_time, old_time) > 15000){
                            quizans = "timeout";
                            break;
                        }
                    }while (quizans == "waiting");
*/

                    if (q_manager.callCheckAnswer(i,quizans) == true){
                        p_manager.setScoreByName(name, q_manager.getTotalScore());
                        map.showScore(q_manager.getTotalScore());
                        map.removeRain();
                        map.removeAnswer();
                        map.showAnswerResult("정답입니다.\n");                 
                        sleep(2);
                        
                        continue;
                    }
                    else{
                        p_manager.setScoreByName(name, q_manager.getTotalScore());
                        map.showScore(q_manager.getTotalScore());
                        map.removeAnswer();
                        map.showAnswerResult("오답입니다.\n");
                        map.removeRain();
                        sleep(2);
                        
                        break;
                    }
                    
                }
                
                map.removeRain();

                p_manager.addPlayer(make_shared<Player>(name,q_manager.getTotalScore()));

                map.showResultFrame();
                map.showResultInfo(p_manager);

                getchar();
                //map.showAnswerResult("                    ");
                break;
            }        
            case 2:
                map.showResultFrame();
                map.showResultInfo(p_manager);
                getchar();
                break;    
            
                
            case 3:
                return 0;
                
            default :
                cout << "잘못 입력하셨습니다 다시 입력해주세요" << endl;
                sleep(3);
                break;
        }
    }
	return 0;
}