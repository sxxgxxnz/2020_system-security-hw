#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#define 	BUF_SIZE 	1024
#define READ 0
#define WRITE 1

int sum=0,i;

int main(){
	char buffer[BUF_SIZE];
	int fds1[2],fds2[2];
	pid_t pid;
	int len,status;
	
	if(pipe(fds1)==-1){
		perror("pipe error\n");
		exit(1);
	}
	if(pipe(fds2)==-1){
		perror("pipe error\n");
		exit(1);
		}
		
	switch(pid=fork()){
	
	case -1 :
		perror("fork error\n");
		exit(1);
		break;
	
	
	case 0 :	//child process
		close(fds1[WRITE]);
		close(fds2[READ]);	
		
		len=read(fds1[READ],buffer,BUF_SIZE);	//read parent
			
		sum=atoi(buffer);
		for(i=51;i<=100;i++){
			sum+=i;
		}
		
		
		sprintf(buffer,"%d",sum);
			
		write(fds2[WRITE],buffer,strlen(buffer));	//child to parent
		break;
		
	default:	//parent process	
		close(fds1[READ]);	//write
		close(fds2[WRITE]);	//read
		buffer[0]='\0';
		
		for(i=1;i<=50;i++)
		{
			sum+=i;
		}						
			
		sprintf(buffer,"%d",sum);	//int to char
	
		write(fds1[WRITE],buffer,BUF_SIZE);	//parent to child
		sleep(2);
		write(1,"sum= ",15);
		len=read(fds2[READ],buffer,BUF_SIZE);	//read child
		write(1,buffer,len);
		waitpid(pid,&status,0);
		break;	
	 
}	
return 0;
	}	
