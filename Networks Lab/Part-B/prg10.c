/*Program 4:

Using message queues or FIFOs as IPC channels, write a client-server program to make client sending the file name and server to send back the contents of the requested file if present.

Procedure:

//FIFO server
	Create two FIFOs for communication.
	Read the client's request.
	Read the contents of fifo1 that is file requested by client
	Close fifo1
	Open fifo2 to write requested file contents.
	Write the contents of requested file to fifo2
	Close fifo2.

//FIFO client
	Open fifo1.
	Enter the file name to be requested from server to fifo1
	Send file name to server through FIFO.
	Wait for the server reply
	Open fifo2 to receive requested file content from server
	Read the requested file content from fifo2
	Write the file contents to the terminal.

Source Code:
   
                      : FIFO_server.c :*/

#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
        int n,fd1,fd2,file;
        char buf[200];
        system("clear");

	


mkfifo("fifo1",S_IFIFO|0666);
	mkfifo("fifo2",S_IFIFO|0666);
	
printf("Server is online");
	printf("Server is waiting for request....\n\n");

             fd1=open("fifo1",O_RDONLY);

	n=read(fd1,buf,128);
	buf[n]='\0';
	close(fd1);
	
fd2=open("fifo2",O_WRONLY);

	if((file=open(buf,O_RDONLY))<0)
	{
		printf("File not found!!!!!!!!\n\n");
		exit(1);
	}

	printf("Server:%s found \n\n",buf);
	printf("Transfering file contents....\n");
	sleep(2);
          
 while((n=read(file,buf,128))>0)
                     write(fd2,buf,n);

           close(fd2);
           close(file);
           printf("Transfer complete......\n\n");
}

                                       













 FIFO_client.c :

#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int n,fd1,fd2;
	char buf[200];
	system("clear");
	printf("FIFO created......\n");
	fd1=open("fifo1",O_WRONLY);

	


printf("Enter file request to server:\n\n");
	scanf("%s",buf);
	printf("Sending file name to server through FIFO1\n\n");
	write(fd1,buf,strlen(buf));
	close(fd1);
	printf("Waiting for server reply.....\n\n");
	printf("Contents of the requested file %s:\n\n",buf);
	printf("****************************************************\n");
	fd2=open("fifo2",O_RDONLY);
	while((n=read(fd2,buf,128))>0)
		write(1,buf,n);
	close(fd2);
	return 0;
}
