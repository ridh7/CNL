//============================================================================
// Name        : Assignment2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <math.h>
using namespace std;

int main() {
	cout<<"DATA SIZE: 8 bits\n";
	cout<<"CODEWORD SIZE: 11 bits\n";
	cout<<"GENERATOR SIZE: 11-8+1 = 4 bits\n";
	cout<<"REDUNDANCY BITS: 4-1 = 3\n";
	char a;
	cout<<"Enter input character: ";
	cin>>a;
	int d = (int)a;
	cout<<"ASCII Value: "<<d<<endl;
	int i = 7, dw[11] = {0,0,0,0,0,0,0,0,0,0,0};
	while(d != 0)
	{
		dw[i] = d%2;
		d /= 2;
		i--;
	}
	cout<<"Data to be sent: ";
	for(int i=0;i<8;i++)
		cout<<dw[i];
	cout<<endl;
	int g[4];
	label1:
	cout<<"Enter generator of size 4(bit-by-bit):\n";
	for(int i=0;i<4;i++)
	{
		cin>>g[i];
		if(g[i] == 0 || g[i] == 1)
			continue;
		else
		{
			cout<<"Input can be 0 or 1 only!\n";
			goto label1;
		}
	}
	int temp[11];
	for(int i=0;i<11;i++)
		temp[i]=dw[i];
	int j,k;
	for(int i=0;i<8;i++)
	{
		if(temp[i] == 1)
		{
			for(j=0,k=i;j<4;j++,k++)
			{
				temp[k] = temp[k] ^ g[j];
			}
		}
	}
	cout<<"\n\n----------SENDER SIDE----------\n\n";
	cout<<"Remainder: ";
	for(int i=8;i<11;i++)
	{
		dw[i] = temp[i];
		cout<<temp[i];
	}
	cout<<"\nData after appending redundancy bits: ";
	for(int i=0;i<11;i++)
		cout<<dw[i];
	char c;
	int e;
	cout<<"\nWould you like to change any bits? (Y/N): ";
	cin>>c;
	if(c == 'Y' || c == 'y')
	{
		label:
		cout<<"\nEnter position of bit to be changed (0-7): ";
		cin>>e;
		if(e >= 0 && e <= 7)
			dw[e] = !dw[e];
		else
		{
			cout<<"Please enter valid position!\n";
			goto label;
		}
	}
	cout<<"\n\n----------RECEIVER SIDE----------\n\n";
	int temp2[11],rw[11];
	for(int i=0;i<11;i++)
	{
		temp2[i] = dw[i];
		rw[i] = temp2[i];
	}
	for(int i=0;i<8;i++)
	{
		if(temp2[i] == 1)
		{
			for(j=0,k=i;j<4;j++,k++)
			{
				temp2[k] = temp2[k] ^ g[j];
			}
		}
	}
	int flag = 0;
	cout<<"Remainder: ";
	for(int i=8;i<11;i++)
	{
		rw[i] = temp2[i];
		cout<<temp2[i];
		if(temp2[i] == 1)
			flag = 1;
	}
	if(flag == 1)
		cout<<"\nSyndrome is not zero, hence data received is incorrect\n";
	else
		cout<<"\nSyndrome is zero, hence data received is correct\n";
	cout<<"\nReceived data: ";
	for(int i=0;i<11;i++)
		cout<<rw[i];
	int num = 0;
	for(int i=7,j=0;i>=0;i--,j++)
	{
		num += rw[i] * pow(2,j);
	}
	cout<<"\nCharacter received: "<<char(num);
	return 0;
}
