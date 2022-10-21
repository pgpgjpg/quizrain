// Control(Handler) Class : 사원 객체의 처리 기능을 위한 클래스  
#include "playerManager.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

struct  CheckError : exception {
    string message;    
    CheckError(string msg) : message(msg) {}    
    ~CheckError() {}    
    virtual const char* what() const noexcept {
        cout << message << endl;          
        return 0;
    }
};

PlayerManager::PlayerManager() {}

void PlayerManager::addPlayer(shared_ptr<Player> player)
{	
	playerList.push_back(player);
    updateRank();
}

void PlayerManager::showAllPlayer() const
{	    
	vector<shared_ptr<Player>> sortedV = playerList;
	sort(sortedV.begin(), sortedV.end(), [](const shared_ptr<Player> i, const shared_ptr<Player> j){return (i->getRank() < j->getRank());});
	for_each(sortedV.begin(), sortedV.end(), [](const shared_ptr<Player> i){ i->showInfo();});
}

void PlayerManager::searchByName(string name)
{	    
	auto it = find_if(playerList.begin(), playerList.end(), [name](shared_ptr<Player> i){return (i->getName() == name);});

	try {
		if(it != playerList.end()) (*it)->showInfo();
		else throw CheckError(("error : " + name + " is not in DB").c_str());
	}
	catch(exception &e){
		const char *c_str = e.what();  		
	}
}

bool PlayerManager::showInfoByRank(int rank)
{	    
	auto it = find_if(playerList.begin(), playerList.end(), [rank](shared_ptr<Player> i){return (i->getRank() == rank);});

	
	if(it != playerList.end()){
		(*it)->showInfo();
		return true;
	}else
		return false;
	
	
}

void PlayerManager::updateRank()
{
    int cnt = 0;
    vector<shared_ptr<Player>> sortedV = playerList;
	sort(sortedV.begin(), sortedV.end(), [](const shared_ptr<Player> i, const shared_ptr<Player> j){return (i->getScore() > j->getScore());});
    for_each(sortedV.begin(), sortedV.end(), [&cnt](const shared_ptr<Player> i){ i->setRank(++cnt);});
}

void PlayerManager::setScoreByName(string name, int score)
{
	auto it = find_if(playerList.begin(), playerList.end(), [name](shared_ptr<Player> i){return (i->getName() == name);});

	try {
		if(it != playerList.end()) (*it)->setScore(score);
		else throw CheckError(("error : " + name + " is not in DB").c_str());
	}
	catch(exception &e){
		const char *c_str = e.what();  		
	}
	updateRank();
}

PlayerManager::~PlayerManager() {}