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
	//cout << "quizlist.txt 파일을 읽었습니다." << endl;

	//manager.showQuizList();
    //cout << manager.getNumQuiz() << endl;
   // cout << manager.getQuiz(1) << endl;

   // cout << (manager.callCheckAnswer(1, "3");
   
    //////게임 시작////////
    PlayerManager p_manager;
    while(true){
        string name;
        int choice;
        cout << "게임" << endl;
        cout << "1. 사용자 정보 입력" << endl;
        cout << "2. 랭크 확인" << endl;        
        cout << "3. 게임 시작" << endl;
        cout << "4. 종료" << endl;

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
                
                break;
            
            case 4:
                return 0;
            default :
        }
    }

    Map map;
    map.showFrame('*');
    map.showQuiz(q_manager.getQuiz(1));
    map.showRain(q_manager.sendGetAnswers(), 1000000);

    vector<string> tmp = q_manager.sendGetAnswers();
    string ans;
    cin >> ans;
    q_manager.callCheckAnswer(1,ans);


    
	return 0;
}