#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
int main(){
	int pid,ppid,i,num1,num2;
	pid=getpid();
	if(fork()==0){
		pid=getpid();
		ppid=getppid();
		printf("Child process starts\n");
		printf("Process id of child process= %d\n",pid);
		printf("Process id of parent process from child process = %d\n",ppid);
		printf("Enter any two numbers :- ");
		scanf("%d%d",&num1,&num2);
		printf("sum = %d\n",num1+num2);
		printf("Child process end \n");
		
	}
	else{	
		pid=getpid();
		printf("Parent process starts\n");
		printf("Process id of parent process= %d\n",pid);
		wait(NULL);
		printf("Ten numbers are :- \n");
		for(i=1;i<=10;i++){
			printf("%d\n",i);
		}
		printf("Parent process end \n");
	}
	return 0;
}
