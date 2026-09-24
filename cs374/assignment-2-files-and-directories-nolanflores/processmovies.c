/* Nolan Flores
 * Oregon State University
 * College of Engineering
 * CS 374
 * 10/31/2025
 */

#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void print_options(){
	printf("1. Select file to process\n");
	printf("2. Exit the program\n\n");
	printf("Enter a choice 1 or 2: ");
}

void print_file_options(){
	printf("\nWhich file do you want to process?\n");
	printf("Enter 1 to pick the largest file\n");
	printf("Enter 2 to pick the smallest file\n");
	printf("Enter 3 to specify the name of a file\n\n");
	printf("Enter a choice 1 to 3: ");
}

int get_option(){
	int option;
	scanf("%d", &option);
	return option;
}

//wraps the fopen function with a printf message
//returns a read only FILE pointer
FILE* open_file(char* file_name){
	printf("Now Processing the chosen file named %s\n", file_name);
	FILE* movies = fopen(file_name, "r");
	return movies;
}

//compares two off_t values, which I believe are signed integers
//returns 1 if the first parameter is larger than the second
int larger(off_t value, off_t compare_to){
	if(value > compare_to)
		return 1;
	return 0;
}

//compares two off_t values
//returns 1 if the first parameter is smaller or the second parameter is 0
//This is dependant on my belief that a valid movies_.csv file can't be 0 bytes
int smaller(off_t value, off_t compare_to){
	if(value < compare_to || compare_to == 0)
		return 1;
	return 0;
}

//Finds the smallest or largest file in a directory
//Parses through a DIR, and compares files with the prefix movies_ and suffix .csv
//Takes a DIR pointer, and a function pointer that compares two off_t values
//I am happy with the implementation of a function pointer, I never get to use that
FILE* extrema_file(DIR* wd, int (*compare)(off_t, off_t)){
	struct dirent* file = readdir(wd);
	off_t current_size = 0;
	char file_name[50];
	while(file != NULL){
		if(strncmp(file->d_name, "movies_",7) == 0 && strcmp(file->d_name+(strlen(file->d_name)-4), ".csv") == 0){
			struct stat file_stats;
			stat(file->d_name, &file_stats);
			if(compare(file_stats.st_size, current_size)){
				strcpy(file_name, file->d_name);
				current_size = file_stats.st_size;
			}
		}
		file = readdir(wd);
	}
	return open_file(file_name);
}

//Takes user input for the name of a file
//searches through the working directory for a file with that name
//Returns a FILE pointer, returns NULL if the file isn't found
FILE* name_file(DIR* wd){
	printf("Enter the complete file name: ");
	char file_name[50];
	scanf("%s", file_name);
	FILE* movies = NULL;
	struct dirent* file = readdir(wd);
	while(file != NULL){
		if(strcmp(file->d_name, file_name) == 0){
			movies = open_file(file_name);
			break;
		}
		file = readdir(wd);
	}
	if(movies == NULL)
		printf("The file %s was not found. Try again\n", file_name);
	return movies;
}

struct movie{
	char* title;
	int year;
};

//Singly Linked List Node
struct node{
	struct movie* mv;
	struct node* next;
};

//Singly Linked List
struct linked_list{
	struct node* head;
	struct node* tail;
};

//Reads a line from a FILE and allocates and initializes a movie struct
//Each line of the CSV file is: Title,Year,[Languages],Rating
//We only care about the Title and Year
struct movie* create_movie(FILE* csv){
	//read the line from the file
	char* line = NULL;
	size_t buffer_size = 0;
	ssize_t line_length = getline(&line, &buffer_size, csv);
	if(line_length <= 0){
		free(line);
		return NULL;
	}
	line[line_length - 1] = '\0';
	line_length--;
	
	struct movie* new_movie = (struct movie*)malloc(sizeof(struct movie));

	//tokenize the line
	char* saveptr = NULL;
	char* title = strtok_r(line, ",", &saveptr);
	new_movie->title = (char*)malloc(sizeof(char) * (strlen(title)+1));
	strcpy(new_movie->title, title);
	new_movie->year = (int)strtol(strtok_r(NULL, ",", &saveptr), NULL, 10);
	free(line);
	
	return new_movie;
}

//Frees a movie struct from the stack
//Also frees the title C string
void free_movie(struct movie* mv){
	if(mv != NULL)
		free(mv->title);
	free(mv);
}

//Allocates and Initializes an empty linked list
struct linked_list* create_linked_list(){
	struct linked_list* ll = (struct linked_list*)malloc(sizeof(struct linked_list));
	ll->head = NULL;
	ll->tail = NULL;
	return ll;
}

//Appends a new node to the end of a linked list
//stores a pointer to an existing movie struct in the new node
void ll_add_movie(struct linked_list* ll, struct movie* mv){
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node->next = NULL;
	new_node->mv = mv;
	if(ll->head == NULL)
		ll->head = new_node;
	else
		ll->tail->next = new_node;
	ll->tail = new_node;
}

//Frees linked_list struct, and all nodes associated
//Also frees all movies pointed to in the nodes
void free_linked_list(struct linked_list* ll){
	struct node* current = ll->head;
	while(current != NULL){
		free_movie(current->mv);
		struct node* temp = current;
		current = current->next;
		free(temp);
	}
	free(ll);
}

//Reads and immediately frees a line from a FILE
//This is intended to deal with the header of the CSV files
void read_dummy_line(FILE* csv){
	char* a = NULL;
	size_t b = 0;
	getline(&a, &b, csv);
	free(a);
}

//Creates a directory in the working directory with rwxr-x---
//The new directory has random numbers in it's name from 0 to 99999
//Parses through the passed linked_list, creating year.txt files with rw-r-----
//Appends the name of each movie to it's corresponding year .txt file
void process_data(struct linked_list* ll){
	char dir[22];
	int num = random() % 100000;
	int dir_len = sprintf(dir, "florenol.movies.%d", num);
	mkdir(dir, 0750);
	printf("Created directory with name %s\n\n", dir);
	
	struct node* current = ll->head;
	while(current != NULL){
		char file_title[dir_len+12];
		sprintf(file_title, "./%s/%d.txt", dir, current->mv->year);
		FILE* year_file = fopen(file_title, "a");
		fprintf(year_file, "%s\n", current->mv->title);
		fclose(year_file);
		current = current->next;
	}
}


int main(){
	umask(0026);//set the umask once ----w-rw-
	srandom(time(NULL));//seed random with time

	while(1){
		print_options();
		int choice = get_option();
		if(choice == 2){
			//exit the program
			break;
		}else if(choice == 1){
			//user chose to process file
			FILE* csv = NULL;
			while(1){
				//loops until user selects valid file
				DIR* wd = opendir(".");
				print_file_options();
				int file_choice = get_option();
				if(file_choice == 1)
					csv = extrema_file(wd, larger);//largest movies_.csv
				else if(file_choice == 2)
					csv = extrema_file(wd, smaller);//smallest movies_.csv
				else if(file_choice == 3)
					csv = name_file(wd);//user inputed file name
				closedir(wd);
				if(csv != NULL)
					break;//file with valid name found
			}
			//read data from the csv
			read_dummy_line(csv);
			struct linked_list* ll = create_linked_list();
			while(!feof(csv)){
				struct movie* mv = create_movie(csv);
				if(mv != NULL)
					ll_add_movie(ll, mv);
			}
			//create directory and txt files
			process_data(ll);
			
			free_linked_list(ll);
			fclose(csv);
		}
	}
	return 0;
}
