#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	int i,pid;
	pid=getpid();
	printf("Proces id from program 2:- %d\n",pid);
	for(i=0;i<argc;i++){
		printf("Argument %d :- %s\n",i,argv[i]);
	}
	return 0;
}
