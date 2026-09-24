#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
	char* first_name; // Dynamically allocated, support any size name
	char* last_name; // Same
};

// Frees an array of people and their first_name and last_name character arrays
void free_people(struct person* people, int n_people) {
	int i;
	// Free their names
	for (i = 0; i < n_people; i++) {
		free(people[i].first_name);
		free(people[i].last_name);
	}
	// Free the array of people itself
	free(people);
}

// Reads the next person from the file. If it fails to read a person, returns
// a person structure with first_name == last_name == NULL
struct person read_person(FILE* data_file) {
	char* line_of_text = NULL;
	size_t buffer_size = 0;
	ssize_t line_length = getline(&line_of_text, &buffer_size, data_file);
	
	struct person p;

	// feof() only returns a nonzero value after FAILING to
	// read any more characters at least once. So the loop runs
	// one extra time, reading no characters on the last iteration.
	// This if statement handles that.
	if (line_length > 0) {
		// Remove line feed (\n) from end of line
		line_of_text[line_length - 1] = '\0';
		line_length--;
		
		// Use strtok to get first and last names. Remember
		// that strtok modifies the tokenized string.
		char* last_name = strtok(line_of_text, ",");
		char* first_name = strtok(NULL, ",");

		// Initialize p's members (add 1 to strlen for null terminators)
		p.last_name = (char*) malloc(
			sizeof(char) * (strlen(last_name) + 1)
		);
		strcpy(p.last_name, last_name);
		p.first_name = (char*) malloc(
			sizeof(char) * (strlen(first_name) + 1)
		);
		strcpy(p.first_name, first_name);
	} else {
		p.first_name = NULL;
		p.last_name = NULL;
	}

	free(line_of_text);

	return p;
}

int main(int argc, char** argv) {
	FILE* data_file = fopen(argv[1], "r"); // argv[0] is the exe path
	if (!data_file) { // i.e., if it's NULL (NULL == 0 == false)
		printf("Error opening file %s\n", argv[1]);
		return 1;
	}

	// Dynamically allocated person array
	struct person* people = NULL;
	int n_people = 0;

	// Skip first line since it's the header. Just use a dummy getline()
	// call for this (there are better ways, but this is simplest)
	char* dummy_line = NULL;
	size_t dummy_buffer_size;
	getline(&dummy_line, &dummy_buffer_size, data_file);
	free(dummy_line);

	// While we haven't failed to read a person due to end-of-file
	while (!feof(data_file)) {
		// Try to read the next person
		struct person p = read_person(data_file);
		if (p.first_name) { // i.e., if not NULL, a person was read
			// Append them to the array
			n_people++;
			people = realloc(people, sizeof(struct person) * n_people);
			people[n_people - 1] = p; // Shallow copy (that's fine)
		}
	}

	// Print people in format First_Name Last_Name
	int i;
	for(i = 0; i < n_people; i++) {
		printf("%d. %s %s\n",
			i + 1,
			people[i].first_name,
			people[i].last_name);
	}

	free_people(people, n_people);
	people = NULL; // Good practice :)

	fclose(data_file); // Don't forget, or valgrind will report a leak!

	return 0;
}
