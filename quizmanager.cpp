#include "quizmanager.h"
#include <exception>
#include <memory>
#include <iomanip>
#include <random>

struct NotOX : exception {
  const char* what() const noexcept {return "O나 X를 입력하세요.\n";}
};

struct Minus : exception {
  const char* what() const noexcept {return "양수를 입력하세요.\n";}
};

struct NoQuizType : exception {
  const char* what() const noexcept {return "퀴즈 텍스트파일에 타입이 정의되있지 않습니다. 퀴즈파일을 확인해주세요.\n";}
};

void QuizManager:: fileRead(ifstream &fin){
	string line;

	while(getline(fin,line)){
		vector<string> partName;
		int start = 0;
		while(1){
			int k = line.find('|', start);
			if(k==-1){
				//k = line.size();
				break;
			}
			string temp = line.substr(start,k-start);
			partName.push_back(temp);
			start = k + 1;
			if(k==line.size())break;
			
		}
		
		try{
			if(partName[0] != "OX" && partName[0] != "multi" && partName[0] != "short")
				throw NoQuizType();
			if(partName[0] == "OX"){ //OX퀴즈일때
				try{
					if (partName[4][0] != 'O' && partName[4][0] != 'X')
						throw NotOX();
					quizList.push_back(new OX(partName[1], stoi(partName[2]), stoi(partName[3]), partName[4][0]));
				}
				catch(exception& e){
        			cout << partName[0] << ": " << e.what();
				}
			}
			else if(partName[0] == "multi"){ //객관식퀴즈일때
				try{
					if (stoi(partName[2]) < 0)
						throw Minus();
					if (stoi(partName[3]) < 0)
						throw Minus();
					if(partName.size()==7)
						quizList.push_back(new MultiChoice(partName[1], stoi(partName[2]), stoi(partName[3]),stoi(partName[4]), partName[5], partName[6]));
					if(partName.size()==8)
						quizList.push_back(new MultiChoice(partName[1], stoi(partName[2]), stoi(partName[3]),stoi(partName[4]), partName[5], partName[6], partName[7]));
					if(partName.size()==9)
						quizList.push_back(new MultiChoice(partName[1], stoi(partName[2]), stoi(partName[3]),stoi(partName[4]), partName[5], partName[6], partName[7], partName[8]));
				}
				catch(exception& e){
        			cout << partName[0] << ": " << e.what();
				}
			}
			else if(partName[0] == "short"){ //주관식퀴즈일때
				try{
					if (stoi(partName[2]) < 0)
						throw Minus();
					if (stoi(partName[3]) < 0)
						throw Minus();
					quizList.push_back(new ShortAnswer(partName[1], stoi(partName[2]), stoi(partName[3]), partName[4]));
				}
				catch(exception& e){
        			cout << partName[0] << ": " << e.what();
				}
			}
		}
		catch(exception& e){
        	cout << e.what();
		}
	}
}

void QuizManager:: showQuizList() const{
	vector<Quiz*>::const_iterator it;
	for(it = quizList.begin(); it != quizList.end(); it++)
		cout << (*it)->getQuestion() << endl;

}

int QuizManager::getNumQuiz(){
	return quizList.size();
}

string QuizManager::getQuiz(int n){
	return (quizList.at(n))->getQuestion();
}

bool QuizManager::callCheckAnswer(int n, string choice_answer){
	if(quizList[n]->checkAnswer(choice_answer) == true){
		totalScore += quizList[n]->getQuestionScore(); //정답이면 토탈스코어에 배점 추가
		return true;
	}
	else
		return false;
}

vector<string> QuizManager::sendGetAnswers(int n){
	vector<string> tm =	quizList[n]->getAnswers();
	return tm;
}

int QuizManager::getQuizLevel(int n){
	return quizList[n]->getLevel();
}

void QuizManager::setTotalSocre(){
	totalScore = 0;
}

void QuizManager::randomQuiz(){
	Quiz* temp;
    random_device rd;
    mt19937 gen(rd());
	int num = getNumQuiz();
    uniform_int_distribution<int> dis(0,99);
	int idx1, idx2;
    for (int i = 0; i < 100; i++){
		idx1 = dis(gen)%num;
		idx2 = dis(gen)%num;

    	temp = quizList[idx1];
		quizList[idx1] = quizList[idx2];
		quizList[idx2] = temp;

    }
}