
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

// Test case for the playTurn() function    
TEST_CASE("playTurn()")
{
    // Create two players and a game object
    Player p1("p1"); 
    Player p2("p2"); 
    Game game(p1, p2); 
    
    // Test that each player's stack size is less than 26 after playing a turn
    game.playTurn();
    bool playTurnCheck1 = (p2.stacksize() < 26)  && (p1.stacksize() < 26);
    CHECK(playTurnCheck1);

    // Test that at least one player has taken cards after playing a turn
    bool playTurnCheck2 = (p1.cardesTaken() > 0) || (p2.cardesTaken() > 0);
    CHECK(playTurnCheck2);
    
    // Test that an exception is thrown when playing a turn after the game has ended
    game.playAll();
    CHECK_THROWS(game.playTurn());
}

// Test case for the printLastTurn() function 
TEST_CASE("printLastTurn()")
{
     // Create two players and a game object
    Player p1("p1"); 
    Player p2("p2"); 
    Game game(p1, p2); 
     
    // Test that an exception is thrown when trying to print the last turn before a turn has been played
    CHECK_THROWS(game.printLastTurn());
    // Play a turn and test that the last turn can be printed without throwing an exception
    game.playTurn();
    CHECK_NOTHROW(game.printLastTurn());
    // Play all turns and test that the last turn can be printed without throwing an exception
    game.playAll();
    CHECK_NOTHROW(game.printLastTurn());
}      

// Test case for the playAll() function       
TEST_CASE("playAll()")
{
    // Create two players and a new game
    Player p1("p1"); 
    Player p2("p2"); 
    Game game(p1, p2); 
    
    // Play the game until all cards have been taken
    game.playAll();

    // Check that both players have empty stacks and have taken all the cards
    bool playAllCheck1 = (p1.stacksize() == 0) && (p2.stacksize() == 0);
    CHECK(playAllCheck1);
    
    // Check that all 52 cards have been taken
    bool playAllCheck2 = (p1.cardesTaken() + p2.cardesTaken() == 52);
    CHECK(playAllCheck2);
    
    // Check that playing the game again throws an exception
    CHECK_THROWS(game.playAll());
} 

// Test case for the printWiner() function
TEST_CASE("printWiner()")
{
    // Create two players and a new game
    Player p1("p1"); 
    Player p2("p2"); 
    Game game(p1, p2); 
    
    // Check that calling printWiner() before playing any turns throws an exception
    CHECK_THROWS(game.printWiner());
    
    // Play one turn and check that calling printWiner() before playing all turns throws an exception
    game.playTurn();
    if(p1.stacksize() != 0 || p2.stacksize() != 0)
    {
        CHECK_THROWS(game.printWiner());
    }
    // If all turns have been played, check that calling printWiner() does not throw an exception
    else
    {
        // If the two players have taken the same number of cards
        if(p1.cardesTaken() == p2.cardesTaken())
        {
             // Assert that calling printWiner() throws an exception
             CHECK_NOTHROW(game.printWiner());
        }
        else 
        {
            // Assert that calling printWiner() does not throw an exception
            CHECK_NOTHROW(game.printWiner());
            stringstream printcheck;
            streambuf* printbuf = cout.rdbuf(); // save cout buffer
            cout.rdbuf(printcheck.rdbuf()); // redirect cout to print

            game.printWiner(); // call the function 

            string printwin = printcheck.str();
            bool check = (printwin.compare("p1") && printwin.compare("P2"));

            cout.rdbuf(printbuf); // restore cout buffer
            CHECK(check);//check that the name of the winner is one of the playeres that initialize
        }
    }

    

    // Play all turns and check that calling printWiner() does not throw an exception
    game.playAll();
    // If the two players have taken the same number of cards
    if(p1.cardesTaken() == p2.cardesTaken())
    {
            // Assert that calling printWiner() throws an exception
            CHECK_THROWS(game.printWiner());
    }
    else 
    {
        // Assert that calling printWiner() does not throw an exception
        CHECK_NOTHROW(game.printWiner());
    }
}  

// Test case for the printLog function
TEST_CASE("printLog")
{
    // Create two players and a new game
    Player p1("p1"); 
    Player p2("p2"); 
    Game game(p1, p2); 
    
    // Check that calling printLog before playing any turns throws an exception
    CHECK_THROWS(game.printLog());
    // Play one turn and check that calling printLog does not throw an exception
    game.playTurn();
    CHECK_NOTHROW(game.printLog());
    // Play all turns and check that calling printLog does not throw an exception
    game.playAll();
    CHECK_NOTHROW(game.printLog());
}  


// Test case for the printStats function
TEST_CASE("printStats()")
{
    // Create two players and a new game
    Player p1("p1"); 
    Player p2("p2"); 
    Game game(p1, p2); 
    
    // Check that calling printStats before playing any turns throws an exception
    CHECK_NOTHROW(game.printStats());
     // Play one turn and check that calling printStats does not throw an exception
    game.playTurn();
    CHECK_NOTHROW(game.printStats());
    // Play all turns and check that calling printStats does not throw an exception
    game.playAll();
    CHECK_NOTHROW(game.printStats());
}  


// Test case for the Player constructor
TEST_CASE("Player()") 
{
    // Check that creating a player with a valid name does not throw an exception
    CHECK_NOTHROW(Player("p1"));
    //check if you can define player with the same name - yes, like in reality.
    CHECK_NOTHROW(Player("p1"));
    // Check that creating a player with an empty string or null pointer throws an exception
    CHECK_THROWS(Player(""));
    CHECK_THROWS(Player(nullptr));

}

// Test case for the stacksize() function
TEST_CASE("stacksize()") 
{
    // Create two players and a new game
    Player p1("p1"); 
    Player p2("p2"); 
    Game game(p1, p2); 

    // Check that both players start with 26 cards
    bool stacksizeCheck1 = (p1.stacksize() == 26) && (p2.stacksize() == 26);
    CHECK(stacksizeCheck1);  

    // Play one turn and check that both players still have the same number of cards
    game.playTurn();
    bool stacksizeCheck2 = (p1.stacksize() == p2.stacksize());
    CHECK(stacksizeCheck2); 
    
    // to be shore it was only one turn of tie or one turn of card throw
    if(p1.stacksize() > 22 || p2.stacksize() >22)
    {
        // After one turn, we draw on card or multiples of 3 incase it was an even, in that cases stack size will be odd number.
        bool stacksizeCheck2 = (p1.stacksize()%2 == 1) && (p2.stacksize()%2 == 1);
        CHECK(stacksizeCheck2); 
    }

     
    
    // Play five more turns and check that both players still have the same number of cards
    for (int i=0;i<5;i++) {
        game.playTurn();
        bool stacksizeCheck3 = (p1.stacksize() == p2.stacksize());
        CHECK(stacksizeCheck3);
    }
    
    // Check that both players have no more than 20 cards after playing 6 turns
    bool stacksizeCheck4 = (p1.stacksize() <= 20) && (p2.stacksize() <= 20) ;
    CHECK(stacksizeCheck4);

    // Play all turns and check that both players have no cards left
    game.playAll();
    bool stacksizeCheck5 = (p1.stacksize() == 0) && (p2.stacksize() == 0) ;
    CHECK(stacksizeCheck5);

}

// Test case for the cardesTaken() function
TEST_CASE("cardesTaken()") 
{
    // Create two players and a new game
    Player p1("p1"); 
    Player p2("p2"); 
    Game game(p1, p2); 

    // Check that both players start with 0 cards taken
    bool cardesTakenCheck1 = (p1.cardesTaken() == 0) && (p2.cardesTaken() == 0);
    CHECK(cardesTakenCheck1); 

    // Play one turn and check that at least one player has taken a card
    game.playTurn();
    bool cardesTakenCheck2 = (p1.cardesTaken() > 0) || (p2.cardesTaken() > 0);
    CHECK(cardesTakenCheck2);

    // Check that if one player has taken two or more cards, the other player hasn't taken any
    bool cardesTakenCheck3 = (p1.cardesTaken() >= 2) && (p2.cardesTaken() == 0) || (p2.cardesTaken() >= 2) && (p1.cardesTaken() == 0);
    CHECK(cardesTakenCheck3);
    
    // Play five more turns and check that the total number of cards taken is correct
    for (int i=0 ;i<5 ;i++) {
        game.playTurn();
    }
    bool cardesTakenCheck4 = (p1.cardesTaken() + p2.cardesTaken()) == (52 - p1.stacksize() - p2.stacksize());
    CHECK(cardesTakenCheck4);

    // Play all turns and check that at least one player has taken more cards than the other
    game.playAll();
    bool cardesTakenCheck5 = (p1.cardesTaken() > p2.cardesTaken()) || (p2.cardesTaken() > p1.cardesTaken()) || (p2.cardesTaken() == p1.cardesTaken());
    CHECK(cardesTakenCheck5);
     // Check that the total number of cards taken is 52
    bool cardesTakenCheck6 = (p1.cardesTaken() + p2.cardesTaken()) == 52;
    CHECK(cardesTakenCheck6);

}


