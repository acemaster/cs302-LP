#include <bits/stdc++.h>


using namespace std;

vector< vector< string > > precedence_t;
vector<string> opmap;
int n;

vector< string > terminals;
vector< string > nonterminals;
map< string, vector< vector< string > > > prods;


void printv(string message,vector<string> a)
{
	cout<<message<<endl;
	for(int i=0;i<a.size();i++)
		cout<<a[i]<<" , ";
	cout<<endl;
}



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

int containsE(string a)
{
	for(int i=0;i<prods[a].size();i++)
		for(int j=0;j<prods[a][i].size();j++)
		if(prods[a][i][j].compare("E") == 0)
			return 1;
	return 0;
}
void viewallprods()
{
	map<string , vector< vector< string > > >::iterator it;
	for(it=prods.begin();it!=prods.end();it++)
		viewprod((string)it->first);
}

void printprecedencetable(vector< vector<string> > p)
{
	cout<<"\n  \t";
	for(int i=0;i<n;i++)
		cout<<opmap[i]<<"\t";
	cout<<"\n";
	for(int i=0;i<n;i++)
		for(int j=0;j<8;j++)
			cout<<"=";
	cout<<endl;
	for(int i=0;i<p.size();i++)
		{
			cout<<opmap[i]<<"\t";
			for(int j=0;j<p[i].size();j++)
				cout<<p[i][j]<<"\t";
			cout<<endl;
		}
}

int isrightprod(string a,string &leftprod)
{
	string fprod="";
	cout<<"\nChecking if right production...........";
	map<string , vector< vector< string > > >::iterator it;
	for(it=prods.begin();it!=prods.end();it++)
		{
			string temp=((string)it->first);
			cout<<temp<<endl;
			viewprod(temp);
			for(int i=0;i<prods[temp].size();i++)
				for(int j=0;j<prods[temp][i].size();j++)
					fprod.append(prods[temp][i][j]);
			cout<<"Production..........\n";
			if(fprod.compare(a)==0)
			{
				cout<<"Found............\n";
				leftprod=temp;
				return 1;
			}
			else
				fprod="";	
		}
	return 0;
	
}

int checkprecedence(string input)
{
	if(isnonterminal(input))
			return 1;
	else
	{
		int i;
		int flag=0;
		for(i=0;i<input.size();i++)
			if(input[i]=='>')
			{
				flag=1;
				break;
			}
		if(flag == 0)
			return 0;
		flag=0;
		cout<<"Found i : "<<i;
		int j;
		for(j=i;j>=0;j--)
			if(input[j] == '<')
			{
				flag=1;
				break;	
			}
		if(flag == 0)
			return 0;
		//Both i and j have been found
		string substring;
		substring=input.substr(j,i-j+1);
		string substringbefore=input.substr(j-1,1);
		string substringafter=input.substr(i,1);
		cout<<"Substring: "<<substring<<endl;
		string::iterator it;
		it=substring.begin();
		substring.erase(it);
		substring.erase(it+substring.size()-1);
		cout<<"Modified substring: "<<substring;
		string newsubstring;
		if(isnonterminal(substringbefore))
		{
			j--;
			newsubstring=substringbefore;
		}
		newsubstring=newsubstring+substring;
		if(isnonterminal(substringafter))
		{
			i++;
			newsubstring=newsubstring+substringafter;
		}
		string leftprod;
		if(isrightprod(newsubstring,leftprod) == 1)
		{
			string newinput=input.substr(0,j)+leftprod+input.substr(i+1,input.size()-i-1);
			cout<<"Modified input: "<<newinput;
			return checkprecedence(newinput);
		}
		else
		{
			cout<<"Not matching..........\n";\
			return 0;
		}
	}
}
int main()
{
	cout<<"\t\t\tOperator Table\n";
	cout<<"\t\t\t+++++++++++++\n";
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
	cout<<"\nEnter the number of operators";
	cin>>n;
	string temp;
	for(int i=0;i<n;i++)
	{
		cout<<"Terminal sym: ";
		cin>>temp;
		opmap.push_back(temp);
	}
	string prec;
	for(int i=0;i<n;i++)
	{
		vector<string> temp2;
		cout<<"Precedence of "<<opmap[i];
		for(int j=0;j<n;j++)
			{
				cout<<"Enter the precedence: ( "<<opmap[i]<<" : "<<opmap[j];
				cin>>prec;
				temp2.push_back(prec);
			}
		precedence_t.push_back(temp2);
		temp2.clear();
	}
	printprecedencetable(precedence_t);
	vector<string> input;
	string tempin;
//	input.push_back("$");
	while(1)
	{
		cin>>tempin;
		if(tempin.compare("-1"))
			break;
		else
			input.push_back(tempin);
	}
	string finalinput="";
	for(int i=0;i<size();i++)
	{
		finalinput=finalinput+input[i];
		//find the symbol and get the precedence value
	}
	finalinput=finalinput+input[input.size()-1];
	checkprecedence(finalinput);
	return 0;
}
