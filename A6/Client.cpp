#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<fstream>
#include<cmath>
using namespace std;

void clear(char* a)
{
for(int i=0;i<100;i++)
	a[i]=' ';
}

int main(int argc, char const *argv[])
{
	
	int i;
	char a[20],b[20],c[20],ans[20],cont[20],fname[20],choice[2],content[100],msg_sent[100],msg_recv[100],opt[2];
	int aud_content[100000],vid_content[100000];
	ifstream myfile;
	string line;

	char expression[10];				//sin30

	int sock = socket(AF_INET,SOCK_STREAM,0);
	cout<<"Socket created"<<endl;
	struct sockaddr_in server;

	server.sin_family = AF_INET;
	server.sin_port   = htons(8004);
	server.sin_addr.s_addr = INADDR_ANY;
	//server.sin_addr.s_addr = inet_addr("10.10.15.111"); this is for multiple machines
	//cout<<ntohl(server.sin_addr.s_addr);

	connect(sock,(struct sockaddr *)&server,sizeof(server));
	cout<<"Connecting"<<endl<<endl;
	size_t fsize;
	FILE *fp;
	//do{  
	
		cout<<"Menu\n1.Chat\n2.File transfer\n3.Calculator\n4.Exit\nChoice: ";
		cin>>choice;
		send(sock,choice,2,0);
		switch(choice[0])
		{
		
		case '1':
			while(true)
			{
				cout<<"Client: ";
				cin>>msg_sent;
				send(sock,msg_sent,100,0);
				if(msg_sent[0]=='b' && msg_sent[1]=='y' && msg_sent[2]=='e')
					break;
				recv(sock,msg_recv,100,0);
				cout<<"Server: "<<msg_recv<<endl;
			}
			break;
		case '2':
			
			cout<<"1.Text File\n2.Audio File\n3.Video File\nChoice: ";
			cin>>opt;
			send(sock,opt,strlen(opt),0);
			
			switch(opt[0])
			{
			case '1':
				cout<<"Enter the name of the file: ";
				cin>>fname;
				i=0;
				send(sock,fname,20,0);	
				myfile.open(fname);			
				clear(content);
			 	if (myfile.is_open())
				{
				
					myfile.seekg(0,ios::end);
					fsize=myfile.tellg();
					myfile.seekg(0,ios::beg);
					myfile.read(content,fsize);
				}
				cout<<"Size: "<<fsize<<endl;
				cout<<"Contents: "<<content<<endl;
				send(sock,content,100,0);
				break;
			case '2':
				cout<<"Enter the name of the file: ";
				cin>>fname;
				i=0;
				send(sock,fname,20,0);
				
				fp=fopen(fname,"r");
				if(fp)
				{
					fseek(fp,0,SEEK_END);
					fsize=ftell(fp);
					fseek(fp,0,SEEK_SET);
					if(fread(aud_content,fsize,1,fp)<=0)
					{
						printf("File copying error\n");
						exit(1);
					}

				}
				else
				{
					printf("Cannot open file\n");
					exit(0);
				}
				fclose(fp);
				
				
			/*	
			 	if (myfile.is_open())
				{
				
					myfile.seekg(0,ios::end);
					fsize=myfile.tellg();
					myfile.seekg(0,ios::beg);
					myfile.read(aud_content,fsize);
				} */
				cout<<"Size: "<<fsize<<endl;
				//cout<<"Contents: "<<aud_content<<endl;
				send(sock,aud_content,fsize,0);
				break;
				break;
			case '3':
				cout<<"Enter the name of the file: ";
				cin>>fname;
				i=0;
				send(sock,fname,20,0);
								
				fp=fopen(fname,"r");
				if(fp)
				{
					fseek(fp,0,SEEK_END);
					fsize=ftell(fp);
					fseek(fp,0,SEEK_SET);
					if(fread(vid_content,fsize,1,fp)<=0)
					{
						printf("File copying error\n");
						exit(1);
					}

				}
				else
				{
					printf("Cannot open file\n");
					exit(0);
				}
				fclose(fp);
				/*
			 	if (myfile.is_open())
				{
				
					myfile.seekg(0,ios::end);
					fsize=myfile.tellg();
					myfile.seekg(0,ios::beg);
					myfile.read(vid_content,fsize);
				}  */
				cout<<"Size: "<<fsize<<endl;
				//cout<<"Contents: "<<vid_content<<endl;
				send(sock,vid_content,fsize,0);
				break;
			default:
				cout<<"Incorrect Input"<<endl;
			}
			break;
		case '3':

			cout<<"\nEnter the expression (For eg. sin45): ";
			cin>>expression;
			send(sock,expression,10,0);


			recv(sock,ans,20,0);
			if(isinf((float)atof(ans)))
				cout<<"Infinity"<<endl;
			else  
				cout<<expression<<"= "<<ans<<endl;
			bzero((char*)ans,sizeof(ans));	
			
			break;
		case '4':
			close(sock);
			break;
		default:
			cout<<"Incorrect Input"<<endl;
			
			
		}

//	}while(choice[0]!='4');
}
