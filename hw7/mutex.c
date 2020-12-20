#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
int num;
pthread_mutex_t mutex;

void* thr1(void *data){
	int i;
	pthread_mutex_lock(&mutex);	//create lock
	for(i=1;i<=50;i++){
		
		num+=i;
		
		}
		pthread_mutex_unlock(&mutex);
}
void* thr2(void *data){
	int i;
	pthread_mutex_lock(&mutex);	//create lock
	for(i=51;i<=100;i++){
		num+=i;
		
		}
		pthread_mutex_unlock(&mutex);
}
int main(){
	int thr_id;
	pthread_t p_thread[2];
	int status;
	int a=1;
	
	num=0;
	thr_id=pthread_create(&p_thread[0],NULL,thr1,(void *)&a);
	sleep(1);
	thr_id=pthread_create(&p_thread[1],NULL,thr2,(void *)&a);
	
	pthread_join(p_thread[0],(void*)&status);
	pthread_join(p_thread[1],(void*)&status);
	
	status=pthread_mutex_destroy(&mutex); //0 is done
	
	printf("num=%d\n",num);
	return 0;
}
