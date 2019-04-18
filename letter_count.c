#include<stdio.h>
#include<pthread.h>
#include<string.h>
#define NTHREADS 6


void* count_letter(void*);

static const char filename[]="books/ClarissaV1Ascii.txt";
long unsigned int letters[26];
pthread_t thread[NTHREADS];
pthread_mutex_t flag_mutex[26];
FILE *file;

void* count_letter(void *arg){
	int letter;
	char err;
	int ind = (int) arg;
	if(file!=NULL){
		char line[128];
		while(fgets(line,sizeof(line),file)!=NULL){/*readaline*/
			for(int i=0;i<128 && line[i]>0;i++){
				if(line[i]<=90 && line[i] >= 65){
					letter = ((int) line[i]) - 65;
					pthread_mutex_lock(&flag_mutex[letter]);
					letters[letter]++;
					pthread_mutex_unlock(&flag_mutex[letter]);
				}else if(line[i]>=141 && line[i]<=172){
					letter = ((int) line[i]) - 141;
					pthread_mutex_lock(&flag_mutex[letter]);
					letters[letter]++;
					pthread_mutex_unlock(&flag_mutex[letter]);
				}
			}
		}
	}else{
		perror(filename);
	}
		
	return NULL;
}

int main(void){
	int a;
	file=fopen (filename,"r");
	for(int i=0; i < 25 ; i++){
		pthread_mutex_init(&flag_mutex[i],NULL);
		letters[i]=0;
	}
	for(int i=0; i < NTHREADS; i++)
		pthread_create(&thread[i], NULL, count_letter, (void *)i);
	for(int i=0; i < NTHREADS; i++){
		pthread_join(thread[i], NULL);
	}
	printf("LETRA : TOTAL\n");
	for(int i=0;i<26;i++)
		printf("%c : %lu\n",i+65,letters[i]);
	fclose (file);
	return 0;
}
