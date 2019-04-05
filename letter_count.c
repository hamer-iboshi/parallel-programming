#include<stdio.h>
#include<pthread.h>
#define NTHREADS 6

static const char filename[]="books/Pride_and_Prejudice.txt";
long unsigned int letters[25];
pthread_t thread[NTHREADS];
pthread_mutex_t flag_mutex[25];
FILE *file;

void* count_letter(void *arg){
	if(file!=NULL){
		char line[128];
		while(fgets (line,sizeof line,file)!=NULL){/*readaline*/
			fputs (line,stdout );/*writetheline*/
		}
		fclose (file);
	}else{
		perror(filename);
	}
		
	return NULL;
}

int main(void){
	file=fopen (filename,"r");
	for(int i=0;i<25;i++){
		flag_mutex[i]=PTHREAD_MUTEX_INITIALIZER;
		letters[i]=0;
	}
	for(int i=0; i < NTHREADS; i++)
		phtread_create(&thread[i], NULL, count_letter, (void *)i);
	for(int i=0; i < NTHREADS; i++)
		phtread_join(&thread[i], NULL);
	return 0;
}
