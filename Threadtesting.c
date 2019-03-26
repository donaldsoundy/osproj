#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define BUFFER_SIZE 80
int inv = 0;
pthread_mutex_t mute;
pthread_cond_t conc, conp;

void *producer(void *ptr){
	int item;
	
	while(item <= BUFFER_SIZE){
		pthread_mutex_lock(&mute);
		while(inv != 0) pthread_cond_wait(&conp, &mute);
		inv = item;
		pthread_cond_signal(&conc);
		pthread_mutex_unlock(&mute);
		
		pid = pthread_self();
		printf("producer %d has created 1 item.", (int) pid);
		
		item++;
	}
	pthread_exit(0);
}

void *consumer(void *ptr){
	int item;
	
	while(item <=  BUFFER_SIZE){
		pthread_mutex_lock(&mute);
		while(inv==0) pthread_cond_wait(&conc, &mute);
		inv = 0;
		pthread_cond_signal(&conp);
		pthread_mutex_unlock(&mute);
		
		pid = pthread_self();
		printf("consumer %d has created 1 item.", (int) pid);
		
		item++;
	}
	pthread_exit(0);
}

int main(int argc, char **argv)
{
	pthread_t pro, con;
	pthread_mutex_init(&mute, 0);
	pthread_cond_init(&conc, 0);
	pthread_cond_init(&conp, 0);
	pthread_create(&con, 0, consumer, 0);
	pthread_create(&pro, 0, producer, 0);
	pthread_join(pro, 0);
	pthread_join(con, 0);
	pthread_cond_destroy(&conc);
	pthread_cond_destroy(&conp);
	pthread_mutex_destroy(&mute);
	
	return 0;
}