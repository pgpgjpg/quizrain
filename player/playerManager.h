#pragma once
#include <string>
#include <vector>
#include <memory>
#include "player.h"
using namespace std;

class PlayerManager
{
private:	
	vector<shared_ptr<Player>> playerList;	
public:
	PlayerManager();
    ~PlayerManager();
	void addPlayer(shared_ptr<Player> player);
	void setScoreByName(string name, int score);
	void showAllPlayer() const;	
	void searchByName(string name);	
    void updateRank();
};