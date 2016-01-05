#include<stdio.h>
#include<stdlib.h>
#include<sched.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>



void *t1(){

	int i=3;
	while(i>0){
		i--;
		printf("Thread 1 is running.\n");
		usleep(1000);
	}
}


void *t2(){

	int i =3;
	while(i>0){
		i--;
		printf("Thread 2 is running.\n");
		usleep(1000);
	}
}


int main(int argc,char *argv[]){

	pthread_attr_t custom;
	struct sched_param p1,p2;
	pthread_t tid1,tid2;
	
	pthread_attr_init(&custom);
	p1.sched_priority=5;
	p2.sched_priority=1;
	
	if(argv[1]!=NULL){
		if(strcmp(argv[1],"SCHED_FIFO")==0){
			pthread_attr_setschedpolicy(&custom,SCHED_FIFO);	
		}
		else{
			pthread_attr_setschedpolicy(&custom,SCHED_OTHER);		
		}
	}
	else{
			pthread_attr_setschedpolicy(&custom,SCHED_OTHER);	
	}
	printf("Thread 1 was created.\n");
	pthread_attr_setschedparam(&custom,&p1);
	pthread_create(&tid1,&custom,t1,NULL);

	printf("Thread 2 was created.\n");
	pthread_attr_setschedparam(&custom,&p2);
	pthread_create(&tid2,&custom,t2,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	return 0;
}
