#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h> 
#include<unistd.h>
#include <string.h>
#include <stdio.h>
#include<fstream>
#include<math.h>
#include<string>
#include<cctype>
#include<sstream>
#include<cstring>
using namespace std;

int main(int argc, char const *argv[])
{
	char choice[2],choice1[2];
	int opt,opt1;
	int sock = socket(AF_INET,SOCK_STREAM,0);
	cout<<"Socket created"<<endl;
	struct sockaddr_in server,client;
	ofstream myfile;

	server.sin_family = AF_INET;
	server.sin_port   = htons(8004);
	server.sin_addr.s_addr = INADDR_ANY;


	char expression1[10],num[7];
	string expression,func,answer_final;
	float number,result;
	stringstream ss;
	char char_ans[20];

	if(bind(sock,(struct sockaddr*)&server,sizeof(server))){
		cout<<"\nBIND ERROR\n";
	}
	cout<<"Socket bound"<<endl;
	if (listen(sock,5)<0){
		cout<<"\nERROR ON LISTEN\n";
	}
	cout<<"Server is listening"<<endl<<endl;

	socklen_t clientlen = sizeof(client);
	int newsock = accept(sock,(struct sockaddr *)&client,&clientlen);

	float number1,number2,answer;
	char _operator[2],num1[20],num2[20],cont[2],fname[20],content[1000],msg_sent[100],msg_recv[100];
	int aud_content[100000],vid_content[100000];
	int numbytes;
bool f;
	FILE *fp;
string r;
	char ans[20];

	//do{  
		recv(newsock,choice,2,0);
		cout<<"Choice received: "<<choice<<endl;
		opt=atoi(choice);
		switch(opt)
		{
		case 1:
			while(true)
			{
				recv(newsock,msg_recv,100,0);
				cout<<"Client: "<<msg_recv<<endl;
				if(msg_recv[0]=='b' && msg_recv[1]=='y' && msg_recv[2]=='e')	
					break;
				cout<<"Server: ";
				cin>>msg_sent;
				send(newsock,msg_sent,100,0);
			}
			break;
		case 2:
			recv(newsock,choice1,2,0);
			opt1=atoi(choice1);
			switch(opt1)
			{
			case 1:
				recv(newsock,fname,20,0);
				cout<<"\nName of the file: "<<fname<<endl;
				myfile.open(fname);
				numbytes=recv(newsock,content,100,0);
				myfile.write(content,numbytes);
				cout<<"Text file has been created"<<endl;
				cout<<"Contents of the file: "<<content<<endl;
				break;
			case 2:
				recv(newsock,fname,20,0);
				cout<<"\nName of the file: "<<fname<<endl;
				numbytes=recv(newsock,aud_content,100,0);
				fp=fopen(fname,"w");
				if(fp)
				{
					fwrite(aud_content, numbytes, 1, fp);
					printf("Creating new output file...\n");
				}
				/*
				myfile.open(fname);
				myfile.write(aud_content,numbytes);  */
				cout<<"Audio file has been created"<<endl;
				break;
			case 3:
				recv(newsock,fname,20,0);
				cout<<"\nName of the file: "<<fname<<endl;
				numbytes=recv(newsock,vid_content,100,0);
				fp=fopen(fname,"w");
				if(fp)
				{
					fwrite(vid_content, numbytes, 1, fp);
					printf("Creating new output file...\n");
				}
				/*
				myfile.open(fname); 
				myfile.write(vid_content,numbytes);  */
				cout<<"Video file has been created"<<endl;
				break;
			case 4:
				break;
			default:
				cout<<"Incorrect Input"<<endl;
			}
			break;
		case 3:
			char res[20];
f=true;
			
			recv(newsock,expression1,6,0);
			cout<<"\nExpression received: "<<expression1<<endl;
			expression=expression1;
			
			func=expression.substr(0,3);
			cout<<"Function: "<<func<<endl;
			for(int i=3,j=0;expression[i]!='\0';i++,j++)
			{
				num[j]=expression[i];
			}
			number=atof(num);
			cout<<"\nAngle : "<<number<<endl;
			number=(number*3.14)/180;
			if(func=="sin")
				result=sin(number);
			else if(func=="cos")
				result=cos(number);
			else if(func=="tan")
				result=tan(number);
			else if(func=="cot")
				result=1/tan(number);
			else if(func=="cosec")
				result=1/sin(number);			
			else if(func=="sec")
				result=1/cos(number);
			else
{
f=false;
				r="Incorrect function";
strcpy(res,r.c_str());
}
			
		/*	ss<<result;
		        answer_final=ss.str();
			strcpy(char_ans,answer_final.c_str());
			send(newsock,char_ans,20,0); */
			if(f==true)
{	
			cout<<"Result: "<<result<<endl;
				sprintf(res,"%f",result);}
			send(newsock,res,20,0);



			break;
		case 4:
			close(sock);
			break;
		default:
			cout<<"Incorrect input"<<endl;
		}
	//}while(opt!=4);
}
