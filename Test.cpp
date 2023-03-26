#include "doctest.h"
#include <stdexcept>
#include <iostream>
#include <stddef.h>

#include "game.hpp"
#include "player.hpp"
#include "card.hpp"

using namespace ariel;

TEST_CASE("Game()")
{

    Player p1("p1"); // Create player 1 with the name "p1"
    Player p2("p2"); // Create player 2 with the name "p2"
    Player p3("p3"); // Create player 3 with the name "p3"
    Player p4("p4"); // Create player 4 with the name "p4"
    Player p5("p5"); // Create player 5 with the name "p5"
    Player p6("p6"); // Create player 6 with the name "p6"
    
    Game game(p1, p2); // Create a game with the two players.

    //check if p1, p2 that play in game can play in parallel in otherGame.
    CHECK_THROWS(Game(p1, p2));

    //check if p1 that play in game can play in parallel in otherGame with new player p3.
    CHECK_THROWS(Game(p1, p3));

    CHECK_NOTHROW(Game otherGame(p3,p4));

    //check if p5 can play with himself.
    CHECK_THROWS(Game(p5, p5));

    //check if p1 that finish to play in game can play in otherGame with new player p6.
    game.playAll();
    CHECK_NOTHROW(Game(p1, p6));

}

    
TEST_CASE("playTurn()")
{
    Player p1("p1"); 
    Player p2("p2"); 
    Game game(p1, p2); 
    
    game.playTurn();
    bool playTurnCheck1 = (p2.stacksize() < 26)  && (p1.stacksize() < 26);
    CHECK(playTurnCheck1);
    
    game.playAll();
    CHECK_THROWS(game.playTurn());
}
    
TEST_CASE("printLastTurn()")
{
    Player p1("p1"); 
    Player p2("p2"); 
    Game game(p1, p2); 
     
    CHECK_THROWS(game.printLastTurn());
    game.playTurn();
    CHECK_NOTHROW(game.printLastTurn());
    game.playAll();
    CHECK_NOTHROW(game.printLastTurn());
}      
       
TEST_CASE("playAll()")
{
    Player p1("p1"); 
    Player p2("p2"); 
    Game game(p1, p2); 
    
    
    game.playAll();

    bool playAllCheck1 = (p1.stacksize() == 0) && (p2.stacksize() == 0);
    CHECK(playAllCheck1);
    
    bool playAllCheck2 = (p1.cardesTaken() + p2.cardesTaken() == 52);
    CHECK(playAllCheck2);
    
    CHECK_THROWS(game.playAll());
} 

TEST_CASE("printWiner()")
{
    Player p1("p1"); 
    Player p2("p2"); 
    Game game(p1, p2); 
    
    CHECK_THROWS(game.printWiner());
    game.playTurn();
    CHECK_THROWS(game.printWiner());
    game.playAll();
    CHECK_NOTHROW(game.printWiner());
}  

TEST_CASE("printLog")
{
    Player p1("p1"); 
    Player p2("p2"); 
    Game game(p1, p2); 
    
    CHECK_THROWS(game.printLog());
    game.playTurn();
    CHECK_NOTHROW(game.printLog());
    game.playAll();
    CHECK_NOTHROW(game.printLog());
}  

TEST_CASE("printStats()")
{
    Player p1("p1"); 
    Player p2("p2"); 
    Game game(p1, p2); 
    
    CHECK_THROWS(game.printStats());
    game.playTurn();
    CHECK_NOTHROW(game.printStats());
    game.playAll();
    CHECK_NOTHROW(game.printStats());
}  


TEST_CASE("Player()") 
{
    
    CHECK_THROWS(Player (""));
    
    CHECK_THROWS(Player(nullptr));

}

TEST_CASE("stacksize()") 
{
    Player p1("p1"); 
    Player p2("p2"); 
    Game game(p1, p2); 

    bool stacksizeCheck1 = (p1.stacksize() == 26) && (p2.stacksize() == 26);
    CHECK(stacksizeCheck1);  

    game.playTurn();
    bool stacksizeCheck2 = (p1.stacksize()%2 == 1) && (p2.stacksize()%2 == 1) && (p1.stacksize() == p2.stacksize());
    CHECK(stacksizeCheck2);  
    
    bool stacksizeCheck3 = (p1.cardesTaken() > 0) || (p2.cardesTaken() > 0);
    CHECK(stacksizeCheck3);
    
    for (int i=0;i<5;i++) {
        game.playTurn();
    }
    bool stacksizeCheck4 = (p1.stacksize()<=20) && (p2.stacksize()<=20) && (p1.stacksize() == p2.stacksize());
    CHECK(stacksizeCheck4);

}
TEST_CASE("cardesTaken()") 
{
    Player p1("p1"); 
    Player p2("p2"); 
    Game game(p1, p2); 

    bool cardesTakenCheck1 = (p1.cardesTaken() == 0) && (p2.cardesTaken() == 0);
    CHECK(cardesTakenCheck1); 

    game.playTurn();
    bool cardesTakenCheck2 = (p1.cardesTaken() >= 2) && (p2.cardesTaken() == 0) || (p2.cardesTaken() >= 2) && (p1.cardesTaken() == 0);
    CHECK(cardesTakenCheck2);
    
    for (int i=0 ;i<5 ;i++) {
        game.playTurn();
    }
    bool cardesTakenCheck3 = (p1.cardesTaken()%2 == 0) && (p2.cardesTaken()%2 == 0);
    CHECK(cardesTakenCheck3);
    bool cardesTakenCheck4 = (p1.cardesTaken() + p2.cardesTaken()) == ((26 - p2.stacksize())*2);
    CHECK(cardesTakenCheck4);

    game.playAll();
    bool cardesTakenCheck5 = (p1.cardesTaken() > p2.cardesTaken()) || (p2.cardesTaken() > p1.cardesTaken());
    CHECK(cardesTakenCheck5);

}



