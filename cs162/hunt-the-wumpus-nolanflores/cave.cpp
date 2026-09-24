#include "cave.hpp"
#include <cstdlib>

#include "event.hpp"
#include "gold.hpp"
#include "bats.hpp"
#include "stalactites.hpp"
#include "wumpus.hpp"
#include "escape_rope.hpp"
#include "arrow.hpp"
#include "armor.hpp"
#include "ladder.hpp"

Cave::Cave(int width, int height, int depth) :
        width(width),
        height(height),
        depth(depth){
    this->floors = std::vector<std::vector<std::vector<Room>>>(depth,
        std::vector<std::vector<Room>>(width,std::vector<Room>(height)));
}

Room& Cave::get_room(int x, int y, int z){
    return this->floors.at(z).at(x).at(y);
}

void Cave::move_wumpus(Gamestate& gs){
    this->get_room(gs.wumpus_x,gs.wumpus_y,gs.wumpus_z).set_event(nullptr);
    int x, y, z;
    do{
        x = rand()%this->width, y = rand()%this->height, z = rand()%this->depth;
    }while(this->get_room(x,y,z).get_event());
    gs.wumpus_x = x;
    gs.wumpus_y = y;
    gs.wumpus_z = z;
    this->get_room(x,y,z).set_event(new Wumpus);
}

int Cave::get_width() const{
    return this->width;
}

int Cave::get_height() const{
    return this->height;
}

int Cave::get_depth() const{
    return this->depth;
}

void Cave::populate_cave(Gamestate& gs){
    gs.rope_x = rand()%this->width;
    gs.rope_y = rand()%this->height;
    gs.x = gs.rope_x;
    gs.y = gs.rope_y;
    this->get_room(gs.rope_x,gs.rope_y,0).set_event(new Escape_Rope);
    Event* events[3] = {new Wumpus, new Gold, new Armor};
    for(int i = 0; i < 3;){//events in entire cave
        int x = rand()%this->width, y = rand()%this->height, z = rand()%this->depth;
        if(this->get_room(x,y,z).get_event() == nullptr){
            if(i == 0){
                gs.wumpus_x = x;
                gs.wumpus_y = y;
                gs.wumpus_z = z;
            }
            this->get_room(x,y,z).set_event(events[i++]);
        }
    }
    for(int z = 0; z < this->depth; z++){//events on each floor
        Event* events[6] = {new Arrow, new Arrow, new Stalactites,
            new Stalactites, new Bats, new Bats};
        for(int i = 0; i < 6;){
            int x = rand()%this->width, y = rand()%this->height;
            if(this->get_room(x,y,z).get_event() == nullptr)
                this->get_room(x,y,z).set_event(events[i++]);
        }
    }
    for(int z = 0; z < this->depth-1;){//down ladders
        int x = rand()%this->width, y = rand()%this->height;
        if(this->get_room(x,y,z).get_event() == nullptr)
            this->get_room(x,y,z++).set_event(new Ladder(1));
    }
    for(int z = 1; z < this->depth;){//up ladders
        int x = rand()%this->width, y = rand()%this->height;
        if(this->get_room(x,y,z).get_event() == nullptr)
            this->get_room(x,y,z++).set_event(new Ladder(-1));
    }
}