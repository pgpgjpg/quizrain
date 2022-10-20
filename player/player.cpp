#include "player.h"
#include <iostream>

void Player::setName(string name)
{
    this->name = name;
}

void Player::setScore(int score)
{
    this->score = score;
}

void Player::setRank(int rank)
{
    this->rank = rank;
}

string Player::getName()
{
    return name;
}

int Player::getScore()
{
    return score;
}

int Player::getRank()
{
    return rank;
}

void Player::showInfo()
{
    cout<< "Rank " << rank << "   " << name << "   " << score << endl;	
}