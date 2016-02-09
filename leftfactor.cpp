#include <bits/stdc++.h>

using namespace std;
void display_prod(string start,vector< vector< string > > main)
{
	cout<<start<<"   ->  ";
	for(int i=0;i<main.size();i++)
	{
		for(int j=0;j<main[i].size();j++)
			cout<<main[i][j];
		cout<<" | ";
	}
	cout<<endl;
}

int main()
{
	vector< vector< string > > main;
	vector<int> clear;
	string start;
	int maxno;
	cout<<"Insert max productions in one: ";
	cin >>maxno;
	cout<<"Start string: ";
	cin>>start;
	string temp;
	for(int i=0;i<maxno;i++)
	{
		vector<string> temp2;
		while(1){
			cin>>temp;
			if(temp.compare("-1")==0)
				break;
			temp2.push_back(temp);
		}
		main.push_back(temp2);
		clear.push_back(0);
	}
	string sec(start);
	sec.append("\'");
	display_prod(start,main);
	vector< vector< string > > prod1;
	vector< vector< string > > prod2;
	int minequal=999;
	vector<string> minstring;
	for(int i=0;i<main.size();i++)
		for(int j=i+1;j<main.size();j++)
		{
			int min=main[i].size() < main[j].size() ? main[i].size():main[j].size();
			int localmin=0;
			vector<string> temp4;
			for(int k=0;k<min;k++)
			{
				if(main[i][k].compare(main[j][k]) == 0)
				{
					localmin++;
					temp4.push_back(main[j][k]);
				}
				else
					break;
			}	
			if(localmin!=0 && minequal > localmin)
			{
				minequal=localmin;
				minstring.clear();
				for(int l=0;l<minequal;l++)
					minstring.push_back(temp4[l]);
			}
		}
	for(int i=0;i<main.size();i++)
		if(main[i][0].compare(minstring[0]) != 0)
		{
			clear[i]=1;
			prod1.push_back(main[i]);
		}	
	minstring.push_back(sec);
	prod1.push_back(minstring);
	vector<string> temp6;
	for(int i=0;i<main.size();i++)
		if(clear[i]==0)
		{
			for(int j=minequal;j<main[i].size();j++)
				temp6.push_back(main[i][j]);
			prod2.push_back(temp6);
			temp6.clear();
		}
	cout<<minequal;
	display_prod(start,prod1);
	display_prod(sec,prod2);
			
	return 0;
}
		
		
		  
