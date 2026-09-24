#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){
	if(argc < 2){
		fprintf(stderr, "Too few arguments passed.");
		return 1;
	}
	int len = (int)strtol(argv[1], NULL, 10);	
	char key[len+1];
	srandom(time(NULL));
	for(int i = 0; i < len; i++){
		int num = random()%27;
		if(num < 26)
			key[i] = (char)(num+65);
		else
			key[i] = ' ';
	}
	key[len] = '\0';
	printf("%s\n", key);
}
