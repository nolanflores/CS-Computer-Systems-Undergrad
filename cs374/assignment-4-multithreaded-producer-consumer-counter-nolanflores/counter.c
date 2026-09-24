#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t my_cond_1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t my_cond_2 = PTHREAD_COND_INITIALIZER;

struct shared_state {
	int my_count;
	int producer_ready;
	int consumer_ready;
	int consumer_started;
};

void* consumer_thread_function(void* arg) {
	printf("CONSUMER THREAD CREATED\n");
	struct shared_state* state_ptr = (struct shared_state*)arg;
	int prev_count = 0;

	pthread_mutex_lock(&my_mutex);
	printf("CONSUMER: MUTEX LOCKED\n");

	state_ptr->consumer_started = 1;
	pthread_cond_signal(&my_cond_2);

	pthread_mutex_unlock(&my_mutex);
	printf("CONSUMER: MUTEX UNLOCKED\n");

	while(1){
		pthread_mutex_lock(&my_mutex);
		printf("CONSUMER: MUTEX LOCKED\n");

		if(state_ptr->my_count >= 10){
			printf("CONSUMER: MUTEX UNLOCKED\n");
			pthread_mutex_unlock(&my_mutex);
			break;
		}

		printf("CONSUMER: WAITING ON CONDITION VARIABLE 1\n");
		while(!state_ptr->consumer_ready)
			pthread_cond_wait(&my_cond_1, &my_mutex);
		state_ptr->consumer_ready = 0;

		printf("Count updated: %d -> %d\n", prev_count, state_ptr->my_count);
		prev_count = state_ptr->my_count;

		state_ptr->producer_ready = 1;
		printf("CONSUMER: SIGNALING CONDITION VARIABLE 2\n");
		pthread_cond_signal(&my_cond_2);

		printf("CONSUMER: MUTEX UNLOCKED\n");
		pthread_mutex_unlock(&my_mutex);
	}
	return NULL;
}

int main() {
	printf("PROGRAM START\n");

	struct shared_state state;
	state.my_count = 0;
	state.producer_ready = 0;
	state.consumer_ready = 0;
	state.consumer_started = 0;

	pthread_t consumer_thread;
	pthread_create(&consumer_thread, NULL, consumer_thread_function, &state);

	pthread_mutex_lock(&my_mutex);
	printf("PRODUCER: MUTEX LOCKED\n");

	while(!state.consumer_started)
		pthread_cond_wait(&my_cond_2, &my_mutex);

	while(state.my_count < 10){
		state.my_count++;

		state.consumer_ready = 1;
		printf("PRODUCER: SIGNALING CONDITION VARIABLE 1\n");
		pthread_cond_signal(&my_cond_1);

		printf("PRODUCER: WAITING ON CONDITION VARIABLE 2\n");
		while(!state.producer_ready)
			pthread_cond_wait(&my_cond_2, &my_mutex);
		state.producer_ready = 0;
	}

	printf("PRODUCER: MUTEX UNLOCKED\n");
	pthread_mutex_unlock(&my_mutex);

	pthread_join(consumer_thread, NULL);
	printf("PROGRAM END\n");

	return 0;
}

