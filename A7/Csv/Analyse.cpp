//============================================================================
// Name        : Assignment7.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

int main() {

	ifstream file;
	string fname, sno, time, src, desn, pro, pro_c = "Invalid", len, info, src_p, desn_p, x;
	int c, count, src_p_count;

	do
	{
		file.open("4.csv");
		cout<<"Choose protocol: \n1. TCP\n2. UDP\n3. DNS\n4. IP\n5. HTTP\n6. ARP\n7. Exit\n";
		cin>>c;
		switch(c)
		{
		case 1:
			pro_c = "TCP";
			break;
		case 2:
			pro_c = "UDP";
			break;
		case 3:
			pro_c = "DNS";
			break;
		case 4:
			pro_c = "ICMPv6";
			break;
		case 5:
			pro_c = "HTTP";
			break;
		case 6:
			pro_c = "ARP";
			break;
		case 7:
			exit(0);
		default:
			cout<<"Enter valid choice!\n";
		}

		count = 0;
		src_p_count = 0;
		
		cout<<"Enter source port number whose count is to be displayed: ";
		cin>>x;
		while(!file.eof())
		{
			getline(file, sno, ',');
			getline(file, time, ',');
			getline(file, src, ',');
			getline(file, desn, ',');
			getline(file, pro, ',');
			getline(file, len, ',');
			getline(file, info, ',');
			getline(file, src_p, ',');
			getline(file, desn_p, '\n');
			
			if(sno.length()==0)
				break;
			
			if(src_p.substr(1, src_p.length()-2) == x)
				src_p_count++;
			
			if(pro.substr(1, pro.length()-2) == pro_c || pro.substr(1, pro.length()-2) == "Protocol")
			{
				cout<<setw(5)<<left<<sno.substr(1, sno.length()-2);
				cout<<setw(12)<<left<<time.substr(1, time.length()-2);
				cout<<setw(30)<<left<<src.substr(1, src.length()-2);
				cout<<setw(30)<<left<<desn.substr(1, desn.length()-2);
				cout<<setw(10)<<left<<pro.substr(1, pro.length()-2);
				cout<<setw(8)<<left<<len.substr(1, len.length()-2);
				cout<<setw(14)<<left<<src_p.substr(1, src_p.length()-2);
				cout<<setw(20)<<left<<desn_p.substr(1, desn_p.length()-2);
				cout<<info.substr(1, info.length()-2)<<endl;
				count++;
			}
		}
		cout<<"--------------------Total packets: "<<count<<"--------------------"<<endl;
		cout<<"--------------------Source port count: "<<src_p_count<<"--------------------"<<endl;
		file.close();
	}
	while(1);

	return 0;
}
