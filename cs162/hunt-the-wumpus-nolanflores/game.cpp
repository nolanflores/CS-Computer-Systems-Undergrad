#include <cstdlib>
#include <ncurses.h>
#include <string>

#include "game.hpp"

Game::Game(int width, int height, int depth, bool debug) :
		cave(width,height,depth),
		debug(debug){
	cave.populate_cave(this->gs);
}

void Game::display_game(){
	printw("Lives remaining: %d\n",this->gs.lives);
	if(gs.armor > 0)
		mvprintw(0,20,"Armor: %d\n",gs.armor);
	printw("Arrows remaining: %d\n", this->gs.arrows);
	if(cave.get_depth() > 1)
		printw("Level %d\n", -gs.z);
	else
		printw("\n");
	std::string row_border = "--";
	for (int i = 0; i < cave.get_width(); i++) {
		row_border += "-----";
	}
	printw("%s\n",row_border.c_str());
	for (int y = 0; y < cave.get_height(); y++) {
		printw("||");
		for (int x = 0; x < cave.get_width(); x++) {
			if(!this->debug){
				printw(" ");
			}
			if(this->gs.x == x && this->gs.y == y){
				printw("*");
			}else{
				printw(" ");
			}
			if(debug && this->cave.get_room(x,y,this->gs.z).get_event()){
				this->cave.get_room(x,y,this->gs.z).get_event()->print_char();
			}else if(debug){
				printw(" ");
			}
			printw(" ||");
		}
		printw("\n");
		printw("%s\n",row_border.c_str());
	}
}

void Game::display_precepts(){
	char dir[4] = {'a','w','d','s'};
	for(int i = 0; i < 4; i++){
		int dx = this->gs.x+((i-1)%2), dy = this->gs.y+((i-2)%2);
		if(this->can_move_in_direction(dir[i]) && this->cave.get_room(dx,dy,this->gs.z).get_event()){
			this->cave.get_room(dx,dy,this->gs.z).get_event()->print_precept();
		}
	}
}

bool Game::check_win() const{
	return this->gs.win;
}

bool Game::check_lose() const{
	return gs.lives <= 0;
}

bool Game::is_direction(char c) {
	return c == 'w' ||
		c == 'a' ||
		c == 's' ||
		c == 'd';
}

char Game::to_lower(char direction) {
	if (direction >= 'A' && direction <= 'Z') {
		return direction + ('a' - 'A');
	}
	return direction;
}

bool Game::can_move_in_direction(char direction) const{
	if(direction == 'w'){
		return this->gs.y > 0;
	}else if(direction == 'a'){
		return this->gs.x > 0;
	}else if(direction == 's'){
		return this->gs.y < this->cave.get_height()-1;
	}else{
		return this->gs.x < this->cave.get_width()-1;
	}
}

bool Game::is_valid_action(char action) {
	if (this->is_direction(action)) {
		char direction = action;
		return this->can_move_in_direction(direction);
	} else if (action == 'f') {
		return this->gs.arrows > 0;
	}
	return false;
}

void Game::print_action_error(char action) {
	mvprintw(2*this->cave.get_height()+8,0,"\n");
	if (this->is_direction(action)) {
		mvprintw(2*this->cave.get_height()+8,0,"You can't move in that direction!");
	} else if (action == 'f') {
		mvprintw(2*this->cave.get_height()+8,0,"You're out of arrows!");
	} else {
		mvprintw(2*this->cave.get_height()+8,0,"That's an invalid input!");
	}
}

char Game::get_player_action() {
	char action;
	bool first = true;
	mvprintw(2*this->cave.get_height()+8,0,"\nWhat would you like to do?\n\n");
	printw("w: move up\n");
	printw("a: move left\n");
	printw("s: move down\n");
	printw("d: move right\n");
	printw("f: fire an arrow\n");
	do {
		if (!first) {
			char previous_action = action;
			this->print_action_error(previous_action);
		}
		first = false;

		action = getch();
		action = this->to_lower(action);
	} while (!this->is_valid_action(action));

	return action;
}

char Game::get_arrow_fire_direction() {
	char direction;
	bool first = true;
	do {
		if (!first) {
			printw("\nThat's an invalid input!\n\n");
		}
		first = false;

		printw("\n\nWhat direction would you like to fire the arrow?\n\n");
		printw("w: up\n");
		printw("a: left\n");
		printw("s: down\n");
		printw("d: right\n");

		direction = getch();
		direction = this->to_lower(direction);
	} while (!this->is_direction(direction));

	return direction;
}

void Game::move_up(){
	this->gs.y--;
}

void Game::move_down(){
	this->gs.y++;
}

void Game::move_left(){
	this->gs.x--;
}

void Game::move_right(){
	this->gs.x++;
}

void Game::move(char direction) {
	if (direction == 'w') {
		this->move_up();
	} else if (direction == 'a') {
		this->move_left();
	} else if (direction == 'd') {
		this->move_right();
	} else {
		this->move_down();
	}
}

void Game::move_random(){
	char dir[4] = {'w','a','s','d'};
	int i;
	do{
		i = std::rand()%4;
	}while(!this->can_move_in_direction(dir[i]));
	this->move(dir[i]);
}

void Game::fire_arrow_up() {
	bool hit = false;
	if(this->gs.z == this->gs.wumpus_z && this->gs.x == this->gs.wumpus_x){
		for(int dy = 1; dy <= 3; dy++){
			if(this->gs.y-dy == this->gs.wumpus_y){
				hit = true;
				break;
			}
		}
	}
	if(hit){
		gs.win = true;
	}else{
		mvprintw(2*this->cave.get_height()+8,0,"You missed.");
		cave.move_wumpus(gs);
	}
}

void Game::fire_arrow_down() {
	bool hit = false;
	if(this->gs.z == this->gs.wumpus_z && this->gs.x == this->gs.wumpus_x){
		for(int dy = 1; dy <= 3; dy++){
			if(this->gs.y+dy == this->gs.wumpus_y){
				hit = true;
				break;
			}
		}
	}
	if(hit){
		gs.win = true;
	}else{
		mvprintw(2*this->cave.get_height()+8,0,"You missed.");
		cave.move_wumpus(gs);
	}
}

void Game::fire_arrow_left() {
	bool hit = false;
	if(this->gs.z == this->gs.wumpus_z && this->gs.y == this->gs.wumpus_y){
		for(int dx = 1; dx <= 3; dx++){
			if(this->gs.x-dx == this->gs.wumpus_x){
				hit = true;
				break;
			}
		}
	}
	if(hit){
		gs.win = true;
	}else{
		mvprintw(2*this->cave.get_height()+8,0,"You missed.");
		cave.move_wumpus(gs);
	}
}

void Game::fire_arrow_right() {
	bool hit = false;
	if(this->gs.z == this->gs.wumpus_z && this->gs.y == this->gs.wumpus_y){
		for(int dx = 1; dx <= 3; dx++){
			if(this->gs.x+dx == this->gs.wumpus_x){
				hit = true;
				break;
			}
		}
	}
	if(hit){
		gs.win = true;
	}else{
		mvprintw(2*this->cave.get_height()+8,0,"You missed.");
		cave.move_wumpus(gs);
	}
}

void Game::fire_arrow(char direction) {
	mvprintw(2*this->cave.get_height()+8,0,"\n");
	if (direction == 'w') {
		this->fire_arrow_up();
	} else if (direction == 'a') {
		this->fire_arrow_left();
	} else if (direction == 'd') {
		this->fire_arrow_right();
	} else {
		this->fire_arrow_down();
	}
	this->gs.arrows--;
}

bool Game::play_game(){
	while (!this->check_win() && !this->check_lose()) {
		clear();

		// Print game board
		this->display_game();

		// TODO Display precepts around player's location
		this->display_precepts();

		refresh();

		// Ask player for their action
		char action = this->get_player_action();

		// Process action
		if (this->is_direction(action)) {
			// W/A/S/D = move player
			char direction = action;
			if(this->gs.is_confused){
				this->move_random();
				this->gs.is_confused = false;
			}
			else
				this->move(direction);
		} else {
			// F = prompt for arrow fire direction and fire arrow
			char direction = this->get_arrow_fire_direction();
			this->fire_arrow(direction);
		}

		// TODO If the user is on a space with an event, trigger its encounter
		if(this->cave.get_room(this->gs.x,this->gs.y,this->gs.z).get_event()){
			if(this->cave.get_room(this->gs.x,this->gs.y,this->gs.z).get_event()->encounter(this->gs)){
				this->cave.get_room(this->gs.x,this->gs.y,this->gs.z).set_event(nullptr);
			}
		}
	}
	return this->check_win();
}
