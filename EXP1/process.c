#include <stdio.h>
#include<unistd.h>
int main(){
int pid;
	pid=getpid();
	printf("Process id of parent process= %d\n",pid);
	if(fork()==0){
		pid=getpid();
		printf("Process id of child process= %d\n",pid);
	}
	return 0;
}
