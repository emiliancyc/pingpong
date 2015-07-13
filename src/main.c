#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



pthread_mutex_t MTX=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t COND=PTHREAD_COND_INITIALIZER;
bool IS_PING = true;
int count = 0;



void* ping(void* p){


	int i = count;
	for (; i > 0; --i) {
	pthread_mutex_lock(&MTX);

		while(!IS_PING){
			pthread_cond_wait(&COND,&MTX);
		}

		printf("PING\n");
		IS_PING = false;
		pthread_cond_signal(&COND);
		pthread_mutex_unlock(&MTX);
	}



}


void* pong(void* p){
	int i = count;
		for (; i > 0; --i) {
	pthread_mutex_lock(&MTX);
		while(IS_PING){
			pthread_cond_wait(&COND,&MTX);
		}


		printf("\tPONG\n");
		IS_PING = true;
		pthread_cond_signal(&COND);
		pthread_mutex_unlock(&MTX);
		//PRINT=true;

		}

}

int main(int argc, char **argv){
	printf("START PROGRAMU\n");

	if(argc != 2){
		printf ("Zla liczba argumentow! Podaj tylko jeden!\n");
		return -1;
	}
	else{

	int arg=atoi(argv[1]);
	printf("Ilosc powtorzen: %d\n\n", arg);
	count=arg;

	pthread_t thread1_id;
	pthread_t thread2_id;

	pthread_create(&thread1_id,0,ping,0);
	pthread_create(&thread2_id,0,pong,0);
	pthread_join(thread1_id, 0);
	pthread_join(thread2_id, 0);
	//count--;
	//}

	return 0;
	}

};
