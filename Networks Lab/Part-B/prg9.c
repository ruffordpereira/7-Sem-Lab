//Socket_Server.c :

#include<stdio.h>

#include<fcntl.h>

#include<sys/types.h>

#include<sys/socket.h>

#include<netinet/in.h>

#include<string.h>

#define PORT_ID 8000

int main()
{
	char buf[300];

	int fd1,fd2,n,size;

	struct sockaddr_in s;

	system("clear");

	printf("Server is getting ready........\n");

	/*setting socket attributes*/

              s.sin_family=AF_INET;

              s.sin_port=htons(PORT_ID);

              s.sin_addr.s_addr=inet_addr("127.0.0.1");

              /*creating socket*/

              fd1=socket(AF_INET,SOCK_STREAM,0);

	 /*Binding socket*/

	 if((bind(fd1,(struct sockaddr *)&s,sizeof(struct sockaddr)))==-1)

                            printf("Error in socket binding!!!!\n");

	/*Listening for client connection request*/

	if((listen(fd1,5))==-1)

	               printf("Error in listening!!!!\n");

	printf("Waiting for client request......\n");

	size=sizeof(struct sockaddr);

	/*Accepting the client request*/

	fd2=accept(fd1,(struct sockaddr *)&s,&size);

	/*Recieving the client sent data*/

	size=recv(fd2,buf,sizeof(buf),0);

	buf[size]='\0';

	printf("File Name Received is:%s\n",buf);

	if((fd1=open(buf,O_RDONLY))!=-1)

	{

		while((n=read(fd1,buf,sizeof(buf)))>0)

		/*sending the contents*/

		send(fd2,buf,n,0);

	}
	else

		send(fd2,"File not found!!!!!!!",20,0);

	close(fd1);

	close(fd2);

	printf("Server terminated......");

	return 0;

}
                            Socket_Client.c :

#include<stdio.h>

#include<fcntl.h>

#include<sys/types.h>

#include<sys/socket.h>

#include<netinet/in.h>

#include<string.h>

#define PORT_ID 8000

int main()

{

	char buf[30000];

	int fd1,n;

	struct sockaddr_in s;

	system("clear");

	printf("Enter the filename to be sent to the server\n");

	scanf("%s",buf);

	/*setting socket attributes*/

	s.sin_family=AF_INET;

	s.sin_port=htons(PORT_ID);

	s.sin_addr.s_addr=inet_addr("127.0.0.1");

	/*creating socket*/

	fd1=socket(AF_INET,SOCK_STREAM,0);

	/*connecting to socket*/

	if((connect(fd1,(struct sockaddr *)&s,sizeof(struct sockaddr)))==-1)

		printf("Error in socket binding!!!!\n");

	/*sending filename to server*/

	send(fd1,buf,strlen(buf),0);

	printf("*****************Contents of the requested file is************\n\n");

	while((n=recv(fd1,buf,sizeof(buf),0))>0)

	{

		buf[n]='\0';

		printf("%s",buf);

	}

	printf("\n");

	close(fd1);

	return 0;

}
