#include <pthread.h>
#include <stdlib.h>

#define N 10000
#define NTHREADS  12

double somas[NTHREADS];
int *A,*B,*R;
int size = N/NTHREADS;

void* soma_vec(void *regiao_ptr){
	int region = (int) regiao_ptr;
	int begin=region*size,end=(region+1)*size;
	if(end == N) end += N%NTHREADS;
	for(i=begin;i<end;i++){
		
	}
	somas[region] = soma_parcial;
	return NULL;
}

int main(){
	int partial=NTHREADS/2;
	double soma=0; 
	int i;
	pthread_t thread[NTHREADS];
	A = (*int) malloc(N*sizeof(int));
	B = (*int) malloc(N*sizeof(int));
	R = (*int) malloc(N*sizeof(int));
	for(int i=0;i<N;i++){
		A[i]=i;
		B[i]=i;
		R[i]=0;
	}
	for(int i=0; i < NTHREADS; i++)
		phtread_create(&thread[i], NULL, soma_vec, (void *)i);
	for(int i=0; i < N; i++)
		printf("%d\n",R[i]);
}	


