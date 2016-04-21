#include <bits/stdc++.h>


class Production
{
	int index;
	string lprod;
	vector<string> production;
	public:
		Production(){
		}
		Production(int index,string lprod,vector<string> &production)
		{
			this->index=index;
			this->lprod=lprod;
			for(int i=0;i<production.size();i++)
				this->production[i]=production[i];
		}
		
		void insertprod()
		{
			cout<<"===========Insert============\n";
			cout<<"Enter left side\n";
			cin>>lprod;
			cout<<"Enter right side.... -1 to stop\n";
			int i=0;
			string temp;
			while(1)
			{
				cin>>temp;
				if(temp.compare("-1") == 0)
					break;
				production.push_back(temp);
			}
			index=0;
		}
		int getindex()
		{
			return index;
		}
		
		string getdotstring()
		{
			return production[index];
		}
		string getlprod()
		{
			return lprod;
		}
		string getprod(int i)
		{
			return production[i];
		}
		void viewproduction()
		{
			cout<<lprod<<" --> ";
			for(int i=0;i<production.size();i++)
				cout<<production[i];
		}
		void incrementdot()
		{
			index++;
		}
		bool checkprod(Production p)
		{
			if(index == p.getindex())
			{
				if(lprod.compare(p.getlprod()) == 0)
				{
					for(int i=0;i<production.size();i++)
						if(production[i].compare(p.getprod(i))!=0)
							return false;
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
		
		Production* newprod(string a)
		{
			if(production[index].compare(a) == 0)
				{
					Production p(index+1,lprod,production);
					return &p;
		
				}
			return NULL;
		}
};