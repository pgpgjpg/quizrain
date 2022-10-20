#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "quiz.h"
#include "quizmanager.h"
#include "map.h"

int main(void)
{
	// 퀴즈관리를 목적으로 설계된 컨트롤 클래스의 객체생성
	QuizManager manager;

	// 퀴즈 등록
	vector<string> wordVector;
    ifstream fin("quizlist.txt");
    if(!fin){
        cout << "quizlist.txt 파일을 열수 없습니다" << endl;
        return 0;
    }
    manager.fileRead(fin);
    fin.close();
	//cout << "quizlist.txt 파일을 읽었습니다." << endl;

	//manager.showQuizList();
    //cout << manager.getNumQuiz() << endl;
   // cout << manager.getQuiz(1) << endl;

   // cout << (manager.callCheckAnswer(1, "3");
   


    Map map;
    map.showFrame('*');
    map.showQuiz(manager.getQuiz(1));
    map.showRain(manager.sendGetAnswers(), 1000000);

    vector<string> tmp = manager.sendGetAnswers();
    string ans;
    cin >> ans;
    manager.callCheckAnswer(1,ans);


    
	return 0;
}