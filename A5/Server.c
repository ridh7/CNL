#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#define maxlen 70000
#define mlen 100000
int main()
{
  	char fileName[100];
  	char filebuffer[2000],caufile[maxlen];
  	char *vfilep;
  	int aufile[70000],vfile[mlen];
  	int sd,connfd,len;
	for(int i=0;i<=100;i++)
	{
		fileName[i]='\0';
	}
  	struct sockaddr_in servaddr,cliaddr;
  	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd==-1)
    {
      printf(" socket not created in server\n");
      exit(0);
    }
  	else
    {
      printf("socket created in  server\n");
    }
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
  	servaddr.sin_addr.s_addr = INADDR_ANY;
  	servaddr.sin_port = htons(6666);
  	memset(&(servaddr.sin_zero),'\0',8);
  	if ( bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0 )
    	printf("Not binded\n");
  	else
    	printf("Binded\n");
  	len=sizeof(cliaddr);

	// Receive text file

  	recvfrom(sd,fileName,1024,0,(struct sockaddr *)&cliaddr, &len);
  	printf("NAME OF TEXT FILE RECEIVED : %s\n",fileName);
	FILE *fp;
  	printf("Contents in the received text file : \n");
  	recvfrom(sd,filebuffer,1024,0,(struct sockaddr *)&cliaddr, &len);
  	printf("%s\n",filebuffer);
  	int fsize=strlen(filebuffer);
	fp=fopen(fileName,"w");
  	if(fp)
	{
 		fwrite(filebuffer, fsize, 1, fp);
  		printf("File received successfully.\n");
  	}
  	else
		printf("Cannot create to output file.\n");
  	memset(fileName, '\0', sizeof(fileName));
  	fclose(fp);

	// Receiving audio file
  	
	recvfrom(sd,fileName,1024,0,(struct sockaddr *)&cliaddr, &len);
   	printf("NAME OF AUDIO FILE RECEIVED : %s\n",fileName);
   	FILE *afp;
   	int numbytes;
    afp=fopen(fileName,"w");
    size_t  afsize;
    afsize=recvfrom(sd,aufile,70000,0,(struct sockaddr *)&cliaddr, &len);
    if(afp)
	{
    	fwrite(aufile, afsize, 1, afp);
    	printf("File received successfully.\n");
    }
    else
   		printf("Cannot open output file.\n");
     	memset(fileName, '\0', sizeof(fileName));
     	fclose(afp);
     	
	// Receiving video file

    recvfrom(sd,fileName,1024,0,(struct sockaddr *)&cliaddr, &len);
    printf("VIDEO FILE NAME RECEIVED : %s\n",fileName);
    FILE *vfp;
    vfp=fopen(fileName,"w");
    size_t  vfsize;
    vfsize=recvfrom(sd,vfile,100000,0,(struct sockaddr *)&cliaddr, &len);
    if(vfp)
	{
        fwrite(vfile, vfsize, 1, vfp);
        printf("File received successfully.\n");
    }
    else
        printf("Cannot open output file.\n");
    fclose(vfp);
	close(sd);
  	return(0);
}

