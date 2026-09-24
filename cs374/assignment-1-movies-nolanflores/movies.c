#include <stdio.h>
#include <stdlib.h>


typedef struct Movie{
    char* title;
    int year;
    char* languages;
    float rating;
} Movie;

Movie* createMovie(char* title, int year, char* languages, float rating) {
    Movie* newMovie = (Movie*)malloc(sizeof(Movie));
    if (newMovie == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    newMovie->title = title;
    newMovie->year = year;
    newMovie->languages = languages;
    newMovie->rating = rating;
    return newMovie;
}

void freeMovie(Movie* movie) {
    if (movie != NULL){
        free(movie->title);
        free(movie->languages);
        free(movie);
    }
}

typedef struct Node{
    Movie movie;
    struct Node* next;
} Node;

Node* createNode(Movie movie) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->movie = movie;
    newNode->next = NULL;
    return newNode;
}