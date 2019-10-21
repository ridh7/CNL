#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include<netinet/in.h>
#include<sys/types.h>
#include <stdlib.h>
#include<string.h>
#include <unistd.h>
#define maxlen 300000
int main()
{
	char fileName[2000],afileName[2000],vfileName[2000],file_buffer[2000],c,caufile[70000];
    int sockfd,connfd,len,aufile[70000],vfile[100000];
	struct sockaddr_in servaddr,cliaddr;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd==-1)
	{
    	printf(" socket not created in client\n");
    	exit(0);
	}
	else
    	printf("socket created in  client\n");

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(6666);
	memset(&(servaddr.sin_zero),'\0',8);
	
	// Transfering text file
	
	printf("Enter text file name to send : \n");
    scanf("%s",fileName);
    sendto(sockfd, fileName, strlen(fileName), 0, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));
    FILE *fp;
    fp=fopen(fileName,"r");
    if(fp)
	{
    	printf("Reading file contents.\n");
    	fseek(fp,0,SEEK_END);
    	size_t file_size=ftell(fp);
    	fseek(fp,0,SEEK_SET);
    	if(fread(file_buffer,file_size,1,fp)<=0)
        {
           printf("Unable to copy file into buffer or empty file.\n");
           exit(1);
        }
    }
	else
	{
    	printf("Cannot open file.\n");
    	exit(0);
    }
    printf("FILE CONTENTS TO SEND : %s\n",file_buffer);
    if(sendto(sockfd, file_buffer,strlen(file_buffer), 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr))<0)
    	printf("FILE WAS NOT SENT\n");
    else
    	printf("FILE SENT\n");
    fclose(fp);

	// Transfering audio file

    printf("Enter audio file name to send : \n");
    scanf("%s",afileName);
    sendto(sockfd, afileName, strlen(afileName), 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr));
	FILE *afp;
	afp=fopen(afileName,"r");
	fseek(afp,0,SEEK_END);
	size_t  afsize=ftell(afp);		
	fseek(afp,0,SEEK_SET);
	if(afp)
	{
		printf("Reading file contents.\n");
		if(fread(aufile,afsize,1,afp)<=0)
		{
	    	printf("Unable to copy file into buffer or empty file.\n");
	        exit(1);
	    }
	}
	else
	{
		printf("Could not read audio file.\n");
		exit(0);
	}

	if(sendto(sockfd, aufile, afsize, 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr))<0)
		printf("FILE WAS NOT SENT\n");
	else
	    printf("FILE SENT\n");
	fclose(afp);
	
	// Transfering video file

	printf("Enter video file name to send : \n");
    scanf("%s",vfileName);
    sendto(sockfd, vfileName, strlen(vfileName), 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr));
	FILE *vfp;
	vfp=fopen(vfileName,"r");
	fseek(vfp, 0, SEEK_END);
	size_t vfsize = ftell(vfp);
	fseek(vfp, 0, SEEK_SET);

	if(vfp)
	{
		if(fread(vfile, 1, vfsize, vfp)<=0)
			printf("No contents or error reading file \n");
	}
	else
	{
		printf("Could not read audio file.\n");
		exit(0);
	}
	if(sendto(sockfd, vfile, vfsize, 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr))<0)
		printf("FILE WAS NOT SENT\n");
	else
		printf("FILE SENT\n");
	fclose(vfp);
    close(sockfd);
	return(0);
}
