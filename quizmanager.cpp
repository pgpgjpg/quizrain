#include "quizmanager.h"
#include <exception>
#include <memory>

struct NotOX : exception {
  const char* what() const noexcept {return "O나 X를 입력하세요.\n";}
};

struct Minus : exception {
  const char* what() const noexcept {return "양수를 입력하세요.\n";}
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
}

void QuizManager:: showQuizList() const{
	vector<Quiz*>::const_iterator it;
	for(it = quizList.begin(); it != quizList.end(); it++)
		cout << (*it)->getQuestion() << endl;
}