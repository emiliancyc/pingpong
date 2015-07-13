#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>



pthread_mutex_t MTX=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t COND=PTHREAD_COND_INITIALIZER;
bool PRINT = false;


void* ping(void* p){
	pthread_mutex_lock(&MTX);
		while(!PRINT){
			pthread_cond_wait(&COND,&MTX);
		}

		printf("PING\n");
		pthread_mutex_unlock(&MTX);
}


void* pong(void* p){
	pthread_mutex_lock(&MTX);
		while(!PRINT){
			pthread_cond_wait(&COND,&MTX);
		}

		printf("PONG\n");
		pthread_mutex_unlock(&MTX);
}

int main(int argc, char **argv){
	printf("START PROGRAMU\n");
	if(argc != 1){
		printf ("Zla liczba argumentow! Podaj tylko jeden!\n");
		return -1;
	}
	else{

	int arg=(int)argv[0];

	pthread_t thread1_id;
	pthread_t thread2_id;

	pthread_create(&thread1_id,0,ping,0);
	sleep(5);
	pthread_mutex_lock(&MTX);
	PRINT=true;
	pthread_cond_signal(&COND);
	pthread_mutex_unlock(&MTX);
	int ret1;
	pthread_join(thread1_id, &ret1);

	return 0;
	}

};
