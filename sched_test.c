#include<stdio.h>
#include<stdlib.h>
#include<sched.h>
#include<pthread.h>
#include<string.h>
#include<time.h>

void *t1(){

	int i=3;
	while(i>0){
		time_t end =time(NULL)+1;
		i--;
		printf("Thread 1 is running.\n");
		while(time(NULL)<end){}
	}
}


void *t2(){

	int i =3;
	while(i>0){
		time_t end =time(NULL)+1;
		i--;
		printf("Thread 2 is running.\n");
		while(time(NULL)<end){}
	}
}


int main(int argc,char *argv[]){

	pthread_attr_t s1,s2;
	struct sched_param p1,p2;
	pthread_t tid1,tid2;
	int policy;	

	pthread_attr_init(&s1);
	pthread_attr_init(&s2);

	p1.sched_priority=5;
	p2.sched_priority=1;
	
	if(argv[1]!=NULL){
		if(strcmp(argv[1],"SCHED_FIFO")==0){
			policy=SCHED_FIFO;	
		}
		else{
			policy=SCHED_OTHER;
		}
	}
	else{
			policy=SCHED_OTHER;
			//pthread_attr_setschedpolicy(&s2,SCHED_OTHER);	
	}
	printf("Thread 1 was created.\n");
	sched_setscheduler(0,policy,&p1);
	pthread_attr_setschedparam(&s1,&p1);
	pthread_create(&tid1,&s1,t1,NULL);

	printf("Thread 2 was created.\n");
	sched_setscheduler(0,policy,&p2);
	pthread_attr_setschedparam(&s2,&p2);
	pthread_create(&tid2,&s2,t2,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	return 0;
}
