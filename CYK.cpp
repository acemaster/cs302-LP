/*
 *
 * Input:
 * 2
 * ab
 * A
 * B
 * C
 * 1
 * 3
 * A
 * B
 * C
 * B
 * a
 * C
 * b
 * 1
 * 1
 * A
 * B
 * C
 * 1
 * 1
 *
 *
 * Output:
 * True Done
 *
 * Actual input is A->BC B->a C->b
 * string: ab
 *
*/



#include <bits/stdc++.h>
using namespace std;
//productions will be of the Chomsky normal form r->a or r->r1r2 


int main(){
	vector<char> nonterminal;
	map<char, vector<char> > unit;
	map<char, vector<char> > nonunit;
	map<char,vector< vector<int> > > p;
	vector<char> starts;
	int nstarts=0;
	printf("Please enter the number of characters in grammar\n");
	int ngrammar;
	cin>>ngrammar;
	cout<<"\nEnter the string: ";
	string word;
	cin>>word;
	cout<<"\nEnter the starting symbols:";
	char tempstart;
	while(1){
		cin>>tempstart;
		if(tempstart == '1')
			break;
		starts.push_back(tempstart);
		nstarts++;
	}
	printf("Please enter the number of non terminal symbols\n");
	int nnts;
	scanf("%d",&nnts);
	char temp;
	for(int i=0;i<nnts;i++){
		cin>>temp;
		nonterminal.push_back(temp);
	}
	printf("Set the unit productions: \n");
	printf("R->a form: \n");
	char a,b;
	while(1){
		cin>>a;
		cin>>b;
		if(a == '1' && b == '1')
			break;
		if(unit.count(a) >0)
		unit[a].push_back(b);
		else{
		vector<char> tempu;
		tempu.push_back(b);
		unit[a]=tempu;
		tempu.clear();
		}
		cout<<"\nInserted < "<<a<<" , "<<b<<"> into map\n";
	}
	map<char, vector<char> >::iterator it;
	for(it=unit.begin();it!=unit.end();it++){
		cout<<it->first<<"->";
		for(int i=0;i<it->second.size();i++)
			cout<<it->second[i];
		cout<<endl;
	}
	cout<<"\nSet non unit productions:\n";
	vector<char> v;
	while(1){
		cin>>a;
		cin>>b;
		if(a == '1' && b == '1')
			break;
		v.push_back(b);
		cin>>b;
		v.push_back(b);
		nonunit[a]=v;
		cout<<"\ninserted "<<a<<"->";
		cout<<v[0]<<v[1]<<endl;
		v.clear();
	}
			
	map<char, vector<char> >::iterator it2;
	for(it2=nonunit.begin();it2!=nonunit.end();it2++){
		cout<<it2->first<<"->"<<it2->second[0]<<it2->second[1];
		cout<<endl;
	}
	vector< vector<int> > tempv;
	for(int k=0;k<nnts;k++){
		for(int i=0;i<ngrammar;i++){
			vector<int> tempv1;
			for(int j=0;j<ngrammar;j++)
				tempv1.push_back(0);
			tempv.push_back(tempv1);
		}
		p[nonterminal[k]]=tempv;
		tempv.clear();
	}
	for(int i=0;i<nnts;i++){
		cout<<endl<<nonterminal[i];
		for(int j=0;j<ngrammar;j++){
			for(int k=0;k<ngrammar;k++)
				cout<<p[nonterminal[i]][j][k]<<"\t";
		cout<<"\n";
		}
	}
	
	for(int i=0;i<ngrammar;i++)
		for(int j=0;j<nnts;j++)
			if(unit.count(nonterminal[j])>0 )
				for(int k=0;k<unit[nonterminal[j]].size();k++)
					if(unit[nonterminal[j]][k] == word[i])
						p[nonterminal[j]][0][i]=1;
	cout<<"\nAfter unit production: ";
	for(int i=0;i<nnts;i++){
		cout<<endl<<nonterminal[i];
		for(int j=0;j<ngrammar;j++){
			for(int k=0;k<ngrammar;k++)
				cout<<p[nonterminal[i]][j][k]<<"\t";
		cout<<"\n";
		}
	}
	for(int i=1;i<ngrammar;i++)
		for(int j=0;j<=ngrammar-i+1;j++)
			for(int k=0;k<=i-1;k++)
				for(int l=0;l<nnts;l++)
					if(nonunit.count(nonterminal[l]) > 0){
						if(p[nonunit[nonterminal[l]][0]][k][j] == 1 && p[nonunit[nonterminal[l]][1]][i-k-1][j+k+1] == 1)
							{
								p[nonterminal[l]][i][j]=1;
								cout<<"Worked for "<<i<<" , "<<j;
							}
					}
	cout<<"\nAfter non terminating production: ";
	for(int i=0;i<nnts;i++){
		cout<<endl<<nonterminal[i];
		for(int j=0;j<ngrammar;j++){
			for(int k=0;k<ngrammar;k++)
				cout<<p[nonterminal[i]][j][k]<<"\t";
		cout<<"\n";
		}
	}

	for(int i=0;i<nstarts;i++)
		if(p[starts[i]][ngrammar-1][0] == 1){
			cout<<"True";
			break;
		}			
	cout<<"Done";	
}

