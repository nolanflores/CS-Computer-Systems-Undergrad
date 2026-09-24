#ifndef CAVE_HPP
#define CAVE_HPP

#include <vector>
#include "room.hpp"

class Cave{
private:
    std::vector<std::vector<std::vector<Room>>> floors;     //3D vector containg the game board
    int width, height, depth;                               //side sizes of the game board
public:
    /*
     * Name: Cave (non-default constructor)
     * Description: Instantiates the game board with given sizes
     * Parameters (int): width, height, and depth of the cave
    */
    Cave(int width, int height, int depth);

    /*
     * Name: get_room
     * Description: Accesses the room at a given index in the 3D vector
     * Parameters (int): The x, y, z indexes of the 3D vector
     * Returns (Room&): Reference to the Room object at the given index
    */
    Room& get_room(int x, int y, int z);

    /*
     * Name: move_wumpus
     * Description: Uses the gamestate to remove the wumpus, and place
     *      a new one in a random unoccupied space in the 3D vector,
     *      essentially "moving" the wumpus to a new spot
     * Parameters:
     *      gs (Gamestate&): Reference to the gamestate struct
    */
    void move_wumpus(Gamestate& gs);

    //Getter for the width of the Cave
    int get_width() const;
    //Getter for the hieght of the Cave
    int get_height() const;
    //Getter for the depth of the Cave
    int get_depth() const;

    /*
     * Name: populate_cave
     * Description: Sets up the Gamestate struct and 3D vector
     *      for playing the game. It places an Escape Rope and
     *      Wumpus events in a Room in the 3D vector and stores 
     *      their locations in the Gamestate. It then places a 
     *      Gold event in a random Room. Then for each floor, it
     *      places 2 Arrows, 2 Bats, and 2 Stalactites. If the
     *      Cave is Deeper than 1 floor, it places Up and Down
     *      Ladder events on appropriate floors.
     * Parameters:
     *      gs (Gamestate&): The Gamestate struct to be modified
    */
    void populate_cave(Gamestate& gs);
};

#endif