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
	}
	string sec(start);
	sec.append("\'");
	display_prod(start,main);
	vector< vector< string > > prod1;
	vector< vector< string > > prod2;
	for(int i=0;i<main.size();i++)
	{
		if(main[i][0].compare(start) == 0){
			prod1.push_back(main[i+1]);
			prod1[0].push_back(sec);
			vector<string> temp3;
			for(int j=1;j<main[i].size();j++)
				temp3.push_back(main[i][j]);
			temp3.push_back(sec);
			prod2.push_back(temp3);
		}
	}

	display_prod(start,prod1);
	display_prod(sec,prod2);
			
	return 0;
}
		
		
		  
