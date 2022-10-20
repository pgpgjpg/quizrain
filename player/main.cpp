#include <iostream>
#include "playerManager.h"
using namespace std;

int main(void)
{
	PlayerManager manager;	
    manager.addPlayer(make_shared<Player>("a", 100));
    manager.addPlayer(make_shared<Player>("b", 98));
    manager.addPlayer(make_shared<Player>("c", 99));
    manager.addPlayer(make_shared<Player>("d", 97));
 
	manager.showAllPlayer();	
	
	manager.searchByName("d");
	manager.searchByName("c");
	manager.searchByName("b");
	manager.searchByName("a");

	return 0;
}