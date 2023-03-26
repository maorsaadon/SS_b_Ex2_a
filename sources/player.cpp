#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "player.hpp"
#include "card.hpp"

namespace ariel{
	
	int Player::playersCounter =0;

	Player::Player(string name){
		 if (name == "")
        {
            throw invalid_argument("put a name player");
        }
        this->name = name;
        this->ownCardCount = 0;
        this->counterTurnWin = 0;
        this->id = Player::playersCounter++;
    }
	
	string Player::getName()
	{
		return this->name;
	}

	int Player::getId()
	{
		return this->id;
	}

	bool Player::isEqual(Player other)
	{
		if(this->name.compare(other.getName()) == 0 && this->id == other.getId()) return true;
		return false;
	}

	bool Player::pileIsEmpty(){
		return this->myPile.empty();
	}

	void Player::incOwnCardCount(int size)
	{
		this->ownCardCount += size;
	}

	void Player::placeBottom(Card card){
		this->myPile.push_back(card);
	}

	int Player::cardesTaken()
	{
		return this->ownCardCount;
	} 

	int Player::stacksize()
	{
		return this->myPile.size();
	}

	int Player::getCounterTurnWin()
	{
		return this->counterTurnWin;
	}

	int Player::incCounterTurnWin()
	{
		return this->counterTurnWin++;
	}
	
	Card Player::play()
	{
		Card drawnCard = this->myPile.at(0);
		this->myPile.erase(this->myPile.begin());
		return drawnCard;
	}

};		
 



