#include <bits/stdc++.h>
using namespace std;

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


class CSI
{
	public:
		vector<Production> prods;
		CSI()
		{
			cout<<"New CSI";
		}
		CSI(vector<Production> prods)
		{
			for(int i=0;i<prods.size();i++)
				this->prods[i]=prods[i];
		}
		void addproduction(vector<Production> prods)
		{
			for(int i=0;i<prods.size();i++)
				this->prods.push_back(prods[i]);
		}
		void addproduction(string lprod,vector<string> prod)
		{
			Production p(0,lprod,prod);
			prods.push_back(p);
		}
		bool comparecsi(CSI c)
		{
			for(int i=0;i<c.prods.size();i++)
				if(prods[i].checkprod(c.prods[i]) == false)
					return false;
				return true;
		}
		CSI newcsi(string s)
		{
			CSI c;
			for(int i=0;i<prods.size();i++)
				if(prods[i].newprod(s) != NULL)
					c.prods.push_back(*(prods[i].newprod(s)));
			return c;
		}
		
		void viewcsi()
		{
			for(int i=0;i<prods.size();i++)
				prods[i].viewproduction();
		}
		
		vector<string> startstrings()
		{
			vector<string> sstrings;
			for(int i=0;i<prods.size();i++)
			{
				int flag=0;
				for(int j=0;j<sstrings.size();i++)
					if(sstrings[i].compare(prods[i].getdotstring()) == 0)
						{
							flag=1;
							break;
						}
				if(flag == 0)
					sstrings.push_back(prods[i].getdotstring());
			}
			return sstrings;
		}
};


class CSICollection
{
	public:
		vector<CSI> csis;
		int addcsi(CSI c)
		{
			for(int i=0;i<csis.size();i++)
				if(csis[i].comparecsi(c) == true)
					return -1;
			csis.push_back(c);
			return 0;
		}
		
		void createnewcollection(int i)
		{
			cout<<"=======Getting the starting strings======";
			vector<string> sstrings=csis[i].startstrings();
			for(int i=0;i<sstrings.size();i++)
				cout<<sstrings[i]<<endl;
		}
		
		void viewcollection()
		{
			for(int i=0;i<csis.size();i++)
			{
				cout<<"Collection "<<i<<endl;
				csis[i].viewcsi();
			}
		}
		
};


int main()
{
	CSICollection c;
	CSI temp;
	vector<Production> tempprodcoll;
	Production tempprod[10];
	int flag=1;
	int i=0;
	while(flag)
	{
		tempprod[i].insertprod();
		cout<<"Insertion complete...........\n";
		cout<<"continue? ";
		cin>>flag;
		tempprodcoll.push_back(tempprod[i]);
		i++;
		
	}
	cout<<"Production push complete...........\n";
	temp.addproduction(tempprodcoll);
	cout<<"CSI add production complete...........\n";
	c.addcsi(temp);
	c.viewcollection();
	c.createnewcollection(0);
	return 0;
}

