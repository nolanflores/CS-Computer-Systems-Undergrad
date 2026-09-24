#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

struct Gamestate{
    int x, y, z = 0;                    //The location of the Player in the Cave
    int wumpus_x, wumpus_y, wumpus_z;   //The location of the Wumpus in the Cave
    int rope_x, rope_y;                 //The location of the Escape Rope on the first floor
    int arrows = 0;                     //The number of Arrows the Player has left
    int lives = 3;                      //The ammount of lives the Player has left
    int armor = 0;                      //The ammount of armor the Player has left
    bool is_confused = false;           //Whether or not the Player's next move should be random
    bool have_gold = false;             //The Player has collected the gold or not
    bool win = false;                   //The Wumpus is dead or the Player has escaped with the gold
};

#endif