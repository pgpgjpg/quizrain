#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "quiz.h"
#include "quizmanager.h"

/*
void fileRead(vector<string> &v, ifstream &fin){
    string line;
    while(getline(fin,line)){
        v.push_back(line);
    }
}
*/

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
	cout << "quizlist.txt 파일을 읽었습니다." << endl;

	manager.showQuizList();
    cout << manager.getNumQuiz() << endl;
    cout << manager.getQuiz(1) << endl;

    if (manager.callCheckAnswer(1, "3") == true)
        cout << "정답입니다." << endl;
    else cout << "오답입니다." << endl;
	return 0;
}