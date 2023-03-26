#ifndef GAME_HPP
#define GAME_HPP


#include "player.hpp"
using namespace std;

namespace ariel{
  class Game {
    
    private:
      // Private members
      Player* player1; 
      Player* player2;
      vector<stringstream> log;
      bool gameOn;
      

      vector<Card> fullPile();
      void shuffle(vector<Card> pile);
      void deal();

    public:

      static vector<Player> players;
      
      // Constructor
      Game(Player& player1, Player& player2);
    
      // Public methods
      void playTurn();
      void printLastTurn();                                             
      void playAll();
      void printWiner();
      void printLog();
      void printStats();
                      
  };
};

  #endif // GAME_HPP
