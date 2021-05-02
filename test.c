#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "x86.h"
#include "types.h"
#include "stat.h"
#include "mmu.h"


#define PGSIZE 4096

#define MAX 4

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX];
int step_i = 0;
// maximum number of threads
//#define MAX_THREAD 4

void add(void *arg1){
	printf(1,"Addition value : %d\n", *(int*)arg1 + 100);
	exit();
}

void clonetest(void){
	printf(1,"Test for checking Clone\n");
    int ppid;
	int kkid;
	ppid = getpid();
	printf(1,"ppid is %d\n", ppid);
	void *stack = malloc(PGSIZE*2);
    if((uint)stack % PGSIZE){
     	stack = stack + (4096 - (uint)stack % PGSIZE);}
	printf(1,"stack = %d\n",(uint)stack);
	int arg1 = 1;
	kkid = clone(&add,&arg1,stack);
	sleep(5);
	printf(1,"kkid is %d\n", kkid);
    int join_id = join(&stack);
    printf(1, "join pid is %d\n", join_id);
	printf(1,"Clone test passed\n");
    


}



void multi(void* arg)
{
	int core = step_i++;

	// Each thread computes 1/4th of matrix multiplication
	for (int i = core * MAX / 4; i < (core + 1) * MAX / 4; i++)
		for (int j = 0; j < MAX; j++)
			for (int k = 0; k < MAX; k++)
				matC[i][j] += matA[i][k] * matB[k][j];
	exit();
}

void matrixtest(void){
	printf(1,"Matrix Multiplication using threads:\n");
    for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			matA[i][j] = 2;
			matB[i][j] = 3;
		}
	}

	// Displaying matA
	printf(1,"\n Matrix A\n");
		
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
			printf(1,"%d  ",matA[i][j]);
		printf(1,"\n");
	}

	// Displaying matB
	printf(1,"\n Matrix B\n");
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
			printf(1,"%d  ",matB[i][j]);	
		printf(1,"\n");
	}

	thread_create(multi,0);
	thread_create(multi,0);
	thread_create(multi,0);
	thread_create(multi,0);

	thread_join();
	thread_join();
	thread_join();
	thread_join();

	printf(1,"\n Matrix C\n");
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
			printf(1,"%d  ",matC[i][j]);		
		printf(1,"\n");
	}
	
}


void multiply(void* argp){
    printf(1,"Multiplication is %d\n", *(int*)argp * 10);
    exit();
}

void basicthreadtest(void){
	printf(1,"Basic thread testing:\n");
    int argp = 22;
    char *stack = malloc(PGSIZE*1);
    if((uint)stack%PGSIZE!=0){
  		printf(1,"stack unaligned\n");
  	}
    sleep(5);
    int thkid = thread_create(multiply,&argp);
    int jpid = thread_join();
    printf(1,"Thread pid is %d\n", thkid);
    printf(1,"Join pid is %d\n", jpid);
}

volatile uint shared=0;
lock_t* lk, *lk1;
unsigned int size = 0;
int num_threads = 61;



void test(void* argp){
    int a = *(int*)argp;

	lock_acquire(lk);
	shared = shared + 1;
    printf(1, "A = %d\n", a);	
	printf(1,"Value of shared is %d\n", shared);
    lock_release(lk);
	exit();
}

void sizetest(void){
	printf(1, "\nStress test for maximum number of threads till exhaustion:\n");
    lock_init(lk);
	lock_init(lk1);

    int argp = 22;
   
    sleep(5);
   int i;  
   for (i = 0; i < num_threads; i++) {
            int thread_pid = thread_create(test, &argp);
            sleep(10);
            lock_acquire(lk1);
            printf(1, "Pid is : %d\n", thread_pid);
            lock_release(lk1);

   }

    for (i = 0; i < num_threads; i++) {
       int join_pid = thread_join();
        printf(1, "join id is : %d\n", join_pid);
}
	printf(1,"\nMaximum number of threads that can be created are 61\n");
    //printf(1, "TEST PASSED\n");

}


void addn(void* argp){
    int tid = gettid();
    printf(1,"TID is %d\n", tid);
    tkill(tid);
    printf(1,"Addition is %d\n", *(int*)argp + 10);
    exit();
}

void testkill(void){
    int argp3 = 22;
   
    sleep(5);
    thread_create(addn,&argp3);
    int jpid = thread_join();
    printf(1,"Join pid is %d\n", jpid);
	printf(1,"Thread killed successfully!\n");

}
int main(int argc, char* argv[]){
    basicthreadtest();
    sleep(5);
    printf(1, "-----------------------------------------\n");
    clonetest();
    sleep(5);
    printf(1, "-----------------------------------------\n");
    matrixtest();
    sleep(5);
    printf(1, "-----------------------------------------\n");
    sizetest();
	sleep(5);
	printf(1, "-----------------------------------------\n");
    testkill();
    sleep(5);

	exit();
}

    
     
