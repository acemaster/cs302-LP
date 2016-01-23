#include <bits/stdc++.h>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;
vector<string> v(10);
vector<string> spl(10);
void addtodict(){
	FILE *fp;
	fp=fopen("keywords.txt","r");
	char *line=NULL;
	size_t len=0;
	ssize_t read;
	cout<<"=====Getting keyword dict========\n";
	while((read=getline(&line,&len,fp))!=-1)
	{
		line[read-1]='\0';
		v.push_back(line);
	}
}


void addtodictspl(){
	FILE *fp;
	fp=fopen("special.txt","r");
	char *line=NULL;
	size_t len=0;
	ssize_t read;
	cout<<"=====Getting speical dict========\n";
	while((read=getline(&line,&len,fp))!=-1)
	{
		line[read-1]='\0';
		spl.push_back(line);
	}
}


void gettokens(string test,vector<string> &testtokens,string delimiter)
{
	int pos=0;
	int i=0;
	while((pos= test.find(delimiter)) != string::npos){
		testtokens.push_back(test.substr(0,pos));
		cout<<testtokens[i]<<endl;
		i++;
		test.erase(0,pos+delimiter.length());
	}	
	testtokens.push_back(test);
	cout<<testtokens[i]<<endl;
}

int isidentifier(string token){
	if(isalpha(token[0])){
		for(int i=1;i<token.length();i++)
			if(isalnum(token[i])== 0)
				return 0;
		return 1;
	}
	else
		return 0;
}		

int iskeyword(string token){
	for(int i=0;i<v.size();i++)
		if(v[i] == token)
			return 1;
	return 0;
}

int isintegerorfloat(string token){
	int flag=1;
	for(int i=0;i<token.length();i++)
		if(isdigit(token[i])== 0 && token[i]!='.')
			return 0;
		else if(token[i] == '.')
			flag=2;
	return flag;
}

int isspecial(string token){
	for(int i=0;i<spl.size();i++)
		if(spl[i] == token)
			return 1;
	return 0;
}

int ispreprocessor(string token){
	if(token[0] == '#')
		return 1;
	else
		return 0;
}

int isfunc(string token){
	int flag=0;
	for(int i=0;i<token.length();i++)
		if(token[i] == '(' && flag==0)	
			flag=1;
		else if(token[i] == ')' && flag == 1)
			flag=2;
	return flag;
}

void line(string arr){
	vector<string> tokens;
	string delim=" ";
	cout<<arr;
	cout<<"\nGetting tokens in line\n";
	gettokens(arr,tokens,delim);
	addtodict();
	addtodictspl();
	for(int i=0;i<tokens.size();i++)
	{
		cout<<tokens[i];
		if(ispreprocessor(tokens[i]))
			cout<<": it is a preprocessor\t";
		else if(iskeyword(tokens[i]))
			cout<<": it is a keyword\t";
		else if(isfunc(tokens[i])== 2)
			cout<<": it is a function\t";
		else if(isidentifier(tokens[i]))
			cout<<": it is a identifier\t";
		else if(isintegerorfloat(tokens[i])== 1)
			cout<<": it is a integer\t";
		else if(isintegerorfloat(tokens[i]) == 2)
			cout<<": it is a float\t";
		else if(isspecial(tokens[i]))
			cout<<": it is a special character\t";
		else
			cout<<"\t";
	}
	cout<<endl;
}
int main(int argc, char *argv[]){
	fstream f;
	f.open(argv[1],ios::in);
	while(!f.eof()){
		char arr[200];
		f.getline(arr,200,'\n');
		string arr2=arr;
		line(arr2);
	}

}
