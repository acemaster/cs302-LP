#include <bits/stdc++.h>

using namespace std;

vector< string > terminals;
vector< string > nonterminals;
map< string, vector< vector< string > > > prods;
map< string, vector< string > > first;
int isterminal(string a)
{
//	cout<<a<<endl;
	for(int i=0;i<terminals.size();i++)
	{
//		cout<<terminals[i]<<" : "<<a<<" : "<<endl;
		if(a.compare(terminals[i])==0)
			return 1;
	}
	return 0;
}

int isnonterminal(string a)
{
	for(int i=0;i<nonterminals.size();i++)
		if(a.compare(nonterminals[i])==0)
			return 1;
	return 0;
}

void printv(string message,vector<string> a)
{
	cout<<message<<endl;
	for(int i=0;i<a.size();i++)
		cout<<a[i]<<" , ";
	cout<<endl;
}
int isEphsilon(string a)
{
	if(a.compare("E")==0)
		return 1;
	return 0;
}


int addprod(string a, vector<string> b)
{
	if(prods.count(a) > 0)
		prods[a].push_back(b);
	else
	{
		vector< vector< string > > temp;
		prods[a]=temp;
		prods[a].push_back(b);
	}
		
}

void viewprod(string a)
{
	cout<<a<<"  -> ";
	for(int i=0;i<prods[a].size();i++)
	{
		for(int j=0;j<prods[a][i].size();j++)
			cout<<prods[a][i][j]<<" ";
		cout<<" | ";
	}	
	cout<<endl;
}

void viewfirst(string a)
{
	cout<<a<<"  -> ";
	for(int i=0;i<first[a].size();i++)
	{
			cout<<first[a][i]<<" ";
		cout<<" | ";
	}	
	cout<<endl;
}


void viewallprods()
{
	map<string , vector< vector< string > > >::iterator it;
	for(it=prods.begin();it!=prods.end();it++)
		viewprod((string)it->first);
}

void viewallfirst()
{
	map<string , vector< string > >::iterator it;
	for(it=first.begin();it!=first.end();it++)
		viewfirst((string)it->first);
}

int containsE(string a)
{
	for(int i=0;i<prods[a].size();i++)
		for(int j=0;j<prods[a][i].size();j++)
		if(prods[a][i][j].compare("E") == 0)
			return 1;
	return 0;
}

int isFirst(string a)
{
	if(first.count(a) > 0)
		return 1;
	else
		return 0;
}

int checkfirst(string a,string b)
{
	for(int i=0;i<first[a].size();i++)
	{
		if(first[a][i].compare(b)==0)
			return 1;
	}
	return 0;
}
void calcfirst(string a,int i,int j)
{
	cout<<a<<" Calulating using "<<i<<" th prod\n"<<"Production string: "<<prods[a][i][j]<<"\n";
	if(first.count(a) == 0)
	{
		vector<string> temp;
		first[a]=temp;
	}
				if(isterminal(prods[a][i][j]) == 1)
				{
					cout<<"Terminal symbol "<<prods[a][i][j]<<endl;
					if(checkfirst(a,prods[a][i][j])==0)
						first[a].push_back(prods[a][i][j]);
				}
				else if(isnonterminal(prods[a][i][j]) == 1 && containsE(prods[a][i][j]) == 0)
				{
					cout<<"Non Terminal symbol "<<prods[a][i][j]<<endl;
					if(first.count(prods[a][i][j]) == 0)
					{
						cout<<"Calculating..........\n";
						calcfirst(prods[a][i][j],0,0);
					}
					cout<<"Adding first of non terminal..........\n";
					for(int k=0;k<first[prods[a][i][j]].size();k++)
						if(checkfirst(a,first[prods[a][i][j]][k])==0)
							first[a].push_back(first[prods[a][i][j]][k]);
				}
				else if(isnonterminal(prods[a][i][j]) == 1 && containsE(prods[a][i][j]) == 1)
				{
					cout<<"Non Terminal symbol with E "<<prods[a][i][j]<<endl;
					if(first.count(prods[a][i][j]) == 0)
						calcfirst(prods[a][i][j],0,0);
					for(int k=0;k<first[prods[a][i][j]].size();k++)
						if(checkfirst(a,first[prods[a][i][j]][k])==0)
							first[a].push_back(first[prods[a][i][j]][k]);
					calcfirst(a,i,j+1);
				}
				if(i != prods[a].size()-1)
					calcfirst(a,i+1,j);
}

int main()
{
	
	cout<<"Enter the non terminals\n";
	string temp;
	while(1)
	{
		cin>>temp;
		if(temp.compare("-1")==0)
			break;
		nonterminals.push_back(temp);
	}
	cout<<"\nEnter the terminal strings: (E for ephsilon) \n";
	
	while(1)
	{
		cin>>temp;
		if(temp.compare("-1")==0)
			break;
		terminals.push_back(temp);
	} 
	printv("Terminals",terminals);
	printv("Non Terminals",nonterminals);
	cout<<"\nEnter the productions: \n";
	string temp2;
	vector<string> temp3;
	while(1)
	{
		cout<<"Left side: ";
		cin>>temp;
		if(temp.compare("-1")==0)
			break;
		cout<<"Right side: ";
		while(1)
		{
			cin>>temp2;
			if(temp2.compare("-1")==0)
			break;
			temp3.push_back(temp2);
		}	
		addprod(temp,temp3);
		temp3.clear();
	}
	cout<<isterminal("id2")<<endl;
	viewallprods();
	calcfirst("A",0,0);
	viewallfirst();
	return 0;
}