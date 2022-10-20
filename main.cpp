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

    //////게임 시작////////
    PlayerManager p_manager;
    while(true){
        string name;
        string ans;
        int choice;
        Map map;
        cout << "게임" << endl;
        cout << "1. 사용자 정보 입력" << endl;
        cout << "2. 랭크 확인" << endl;        
        cout << "3. 게임 시작" << endl;
        cout << "4. 종료" << endl;

        cin >> choice;

        switch(choice){
            case 1:                
                cout << "이름 ->";
                cin >> name;
                break;
            
            case 2:
                p_manager.showAllPlayer();
                break;    
            case 3:
                
                p_manager.addPlayer(make_shared<Player>(name,0));
                                
                map.showFrame('*');
                map.showQuiz(q_manager.getQuiz(1));
                map.showRain(q_manager.sendGetAnswers(), 1000000);
                
                cin >> ans;
                q_manager.callCheckAnswer(1,ans);
                break;
              
                
            case 4:
                return 0;
                
            default :
                break;
        }
    }

    


    
	return 0;
}