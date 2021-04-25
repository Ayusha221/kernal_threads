
//#include<stdio.h>
#include"types.h"
#include"user.h"
#include"mmu.h"
//#include"x86.h"
//#include"fs.h
#include"stat.h"
//#define PGSIZE (4096)
void test_clone(void*arg1){

printf(1,"%d ",*(int*)arg1);
exit();

}




int main(){

int ppid;
ppid = getpid();
	 printf(1, "%d   \n",ppid);
   void *stack = malloc(PGSIZE*2);
   //int a=2,b=3;
   //printf(2,"heyyy youu\n");
   //printf(2,"%d\n",(uint)stack);
   //if((uint)stack % PGSIZE){
     //stack = stack + (4096 - (uint)stack % PGSIZE);
     //}
     int arg1=4;
     int r = clone(&test_clone,&arg1,stack);
     printf(1, "%d   \n",r);
     //printf(1,"foool\n");

exit();







}
