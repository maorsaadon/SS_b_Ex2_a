#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "card.hpp"
#include <vector>
using namespace std;

namespace ariel{
  class Player {
    private:
      // Private members
      string name;
      vector<Card> myPile;
      int ownCardCount;
      int counterTurnWin;
      int id;
      

    public:

      static int playersCounter;

      // Constructor
      Player(string name);

      string getName();
      int getId();
      bool isEqual(Player other);
      bool pileIsEmpty();
      void incOwnCardCount(int size);
      void placeBottom(Card card);
      int cardesTaken();
      int stacksize(); 
      int getCounterTurnWin();
      int incCounterTurnWin(); 
      Card play();

  };
};

#endif // PLAYER_HPP
