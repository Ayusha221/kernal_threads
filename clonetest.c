
//#include<stdio.h>
#include"types.h"
#include"user.h"
#include"mmu.h"
//#include"x86.h"
//#include"fs.h
#include"stat.h"
//#define PGSIZE (4096)
void test_clone(int arg1){
  int a = arg1; 
 //int a = *
//printf(1,"%d\n",*(int)(*arg1));
printf(1,"%d \n",a);
exit();

}




int main(){

int ppid;
ppid = getpid();
	 printf(1, "pid is %d\n",ppid);
   //void *stack = malloc(PGSIZE*2);
   //int a=2,b=3;
   //printf(2,"heyyy youu\n");
   //printf(2,"%d\n",(uint)stack);
   //if((uint)stack % PGSIZE){
     //stack = stack + (4096 - (uint)stack % PGSIZE);
     //}
     //int arg1=4;
     //int r = thread_create(&test_clone,&arg1);
     //printf(1, "%d\n",r);
     //int jid = thread_join();
      //printf(1, "%d\n",jid);
     //printf(1,"foool\n");

exit();







}
