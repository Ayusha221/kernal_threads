#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"



void multiply(void* argp){
	printf(1,"%d *\n",*(int*)argp);
    printf(1,"Multiplication is %d\n", *(int*)argp * 2);
    exit();
}


int main(int argc, char* argv[]){
    int argp = 22;
    char *stack = malloc(PGSIZE*1);
    if((uint)stack%PGSIZE!=0){
  		return -1;
  	}
    //int c = clone(&multiply,&argp,stack);
    sleep(5);
    int thkid = thread_create(&multiply,&argp);
    int jpid = thread_join();
    printf(1,"tc return value is %d\n", thkid);
    printf(1,"Join pid is %d\n", jpid);
    //free(stack);
    exit();

}
