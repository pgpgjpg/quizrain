#include <iostream>
#include <string>
#include <fstream>
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

	// 퀴즈 등록
	vector<string> wordVector;
    ifstream fin("quizlist.txt");
    if(!fin){
        cout << "quizlist.txt 파일을 열수 없습니다" << endl;
        return 0;
    }
    q_manager.fileRead(fin);
    fin.close();

	//manager.showQuizList();
    //cout << manager.getNumQuiz() << endl;
   // cout << manager.getQuiz(1) << endl;

   // cout << (manager.callCheckAnswer(1, "3");
   
    ////게임 시작////////
    PlayerManager p_manager;
    while(true){
        system("clear");
        string ans;
        int choice;
        Map map;
        cout << "게임" << endl;
        cout << "1. 사용자 정보 입력" << endl;
        cout << "2. 랭크 확인" << endl;        
        cout << "3. 게임 시작" << endl;
        cout << "4. 종료" << endl;

        cin >> choice;
        cin.ignore();
        switch(choice){
            case 1:                
                
                cout << "이름 ->";
                cin >> name;
                cin.ignore();
                p_manager.addPlayer(make_shared<Player>(name,0));
                break;            
            case 2:
                map.showResultFrame();
                map.showResultInfo(p_manager);
                getchar();
                break;    
            case 3:{
                
                for (int i = 0; i < q_manager.getNumQuiz(); i++){
                    system("clear");
                    
                    map.showFrame('*');
                    //map.showName(name);
                    map.showName(name);
                    map.showQuiz(q_manager.getQuiz(1));
                    map.showRain(q_manager.sendGetAnswers(), 1000000);
                    string quizans = map.waitAnswer();
                    map.showAnswer(quizans);
                
                    if (q_manager.callCheckAnswer(1,quizans) == true){
                        p_manager.setScoreByName(name, q_manager.getTotalScore());
                        map.showScore(q_manager.getTotalScore());
                        map.removeRain();
                        map.showAnswer("정답입니다.");                      
                        sleep(2);
                        continue;
                    }
                    else{
                        map.showAnswer("오답입니다.");
                        map.removeRain();
                        sleep(2);                        
                        break;
                    }
                }
                
                map.removeRain();
                
                map.showResultFrame();
                map.showResultInfo(p_manager);

                sleep(5);

                break;
                    
            }
                
            case 4:
                return 0;
                
            default :
                break;
        }
        
        
    }

    

	return 0;
}