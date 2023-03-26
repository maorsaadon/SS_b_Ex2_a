#include "doctest.h"
#include <stdexcept>
#include <iostream>
#include <stddef.h>

#include "game.hpp"
#include "player.hpp"
#include "card.hpp"

using namespace ariel;

// This is a test case for the Game class
TEST_CASE("Game()")
{
    // Create six players
    Player p1("p1"); 
    Player p2("p2"); 
    Player p3("p3"); 
    Player p4("p4"); 
    Player p5("p5"); 
    Player p6("p6"); 
    
    // Create a game with player 1 and player 2
    Game game(p1, p2); 

    // Test that creating a game with the same players throws an exception
    CHECK_THROWS(Game(p1, p2));
    // Test that creating a game with a player not in the game and player in the game throws an exception
    CHECK_THROWS(Game(p1, p3));
    // Test that creating a game with two players not already in a game does not throw an exception
    CHECK_NOTHROW(Game otherGame(p3,p4));
    // Test that creating a game with the same player twice throws an exception
    CHECK_THROWS(Game(p5, p5));
    // Test that creating a game with a player in a finished game does not throw an exception
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

    bool playTurnCheck2 = (p2.cardesTaken() > 0) || (p1.cardesTaken() > 0);
    CHECK(playTurnCheck2);
    
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
    //check if you can define player with the same name - yes, like in reality.
    CHECK_NOTHROW(Player("p1"));
    CHECK_NOTHROW(Player("p1"));

    CHECK_THROWS(Player(""));
    
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
    
    for (int i=0;i<5;i++) {
        game.playTurn();
        bool stacksizeCheck3 = (p1.stacksize() == p2.stacksize());
        CHECK(stacksizeCheck3);
    }
    bool stacksizeCheck4 = (p1.stacksize() <= 20) && (p2.stacksize() <= 20) ;
    CHECK(stacksizeCheck4);

    game.playAll();
    bool stacksizeCheck5 = (p1.stacksize() == 0) && (p2.stacksize() == 0) ;
    CHECK(stacksizeCheck5);


}
TEST_CASE("cardesTaken()") 
{
    Player p1("p1"); 
    Player p2("p2"); 
    Game game(p1, p2); 

    bool cardesTakenCheck1 = (p1.cardesTaken() == 0) && (p2.cardesTaken() == 0);
    CHECK(cardesTakenCheck1); 

    game.playTurn();
    bool cardesTakenCheck2 = (p1.cardesTaken() > 0) || (p2.cardesTaken() > 0);
    CHECK(cardesTakenCheck2);

    bool cardesTakenCheck3 = (p1.cardesTaken() >= 2) && (p2.cardesTaken() == 0) || (p2.cardesTaken() >= 2) && (p1.cardesTaken() == 0);
    CHECK(cardesTakenCheck3);
    
    for (int i=0 ;i<5 ;i++) {
        game.playTurn();
    }
    bool cardesTakenCheck4 = (p1.cardesTaken()%2 == 0) && (p2.cardesTaken()%2 == 0);
    CHECK(cardesTakenCheck4);
    bool cardesTakenCheck5 = (p1.cardesTaken() + p2.cardesTaken()) == ((26 - p2.stacksize())*2);
    CHECK(cardesTakenCheck5);

    game.playAll();
    bool cardesTakenCheck6 = (p1.cardesTaken() >= p2.cardesTaken()) || (p2.cardesTaken() >= p1.cardesTaken());
    CHECK(cardesTakenCheck6);
    bool cardesTakenCheck7 = (p1.cardesTaken() + p2.cardesTaken()) == 52;
    CHECK(cardesTakenCheck7);

}



