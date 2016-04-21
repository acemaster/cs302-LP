#include <bits/stdc++.h>
using namespace std;

map< string, vector< vector< string > > > prodmap;

void addtoprodmap(string lprod,vector<string> prod)
{
	if(prodmap.count(lprod) > 0)
		prodmap[lprod].push_back(prod);
	else
	{
		vector< vector< string > > temp;
		prodmap[lprod]=temp;
		prodmap[lprod].push_back(prod);
	}
}


class Production
{
	int index;
	string lprod;
	vector<string> production;
	public:
		Production()
		{
			index=-1;
		}
		void addForProd(int index1,string lprod1,vector<string> production1)
		{
			cout<<"\n\t\t\tCreating new production .....";
			index = index1;
			lprod = ""+lprod1;
			for(int i=0;i<production1.size();i++)
			{
				production.push_back(production1[i]);
			}
			cout<<"\n\t\t\tDone production\n";
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
			addtoprodmap(lprod,production);
			index=0;
		}
		int getindex()
		{
			return index;
		}
		
		string getdotstring()
		{
			if(index < production.size())
				return production[index];
			else
				return "";
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
			cout<<"\t index: "<<index;
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
		
		Production newprod(string a)
		{
			cout<<"\tCreating new production for string "<<a;
			Production p;
			if(production[index].compare(a) == 0)
				{
					cout<<"\n\t\tNew production ....";
					Production p;
					p.addForProd(index+1,lprod,production);
					p.viewproduction();
					return p;
		
				}
			return p;
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
			cout<<"\nNew csi being created............\n";
			for(int i=0;i<prods.size();i++)
			{
				cout<<"\nfor prod ......"<<i<<endl;
				Production p=prods[i].newprod(s);
				string nlprod= p.getdotstring();
				if(p.getindex() != -1)
			    	c.prods.push_back(p);
			    if(prodmap.count(nlprod) > 0)
			    {
			    	for(int j=0;j<prodmap[nlprod].size();i++)
			    	{
			    		Production temp;
			    		temp.addForProd(0,nlprod,prodmap[nlprod][j]);
			    		c.prods.push_back(temp);
			    	}
			    }
			}
			return c;
		}
		
		void viewcsi()
		{
			cout<<"\n===========View csi===============\n";
			for(int i=0;i<prods.size();i++)
			{
				prods[i].viewproduction();
				cout<<endl;
			}
		}
		
		vector<string> startstrings()
		{
			vector<string> sstrings;
			for(int i=0;i<prods.size();i++)
			{
				int flag=0;
				for(int j=0;j<sstrings.size();j++)
					if(sstrings[j].compare(prods[i].getdotstring()) == 0)
						{
							flag=1;
							break;
						}
				if(flag == 0)
				{
					cout<<"Pushing string: "<<prods[i].getdotstring()<<endl;
					sstrings.push_back(prods[i].getdotstring());
				}
			}
			return sstrings;
		}
};

class CSIMap
{
	int s1;
	int s2;
	int state;
	string movingvariable;
public:
	void addCSIMap(int i,int j,int st,string mv)
	{
		s1=i;
		s2=j;
		state=st;
		movingvariable=""+mv;
	}
	void viewCSIMap()
	{
		cout<<s1<<"\t"<<s2<<"\t"<<state<<"\t"<<movingvariable<<"\n";
	}

};

vector<CSIMap> csimap;


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
			int k=0;
			cout<<"\n=======Getting the starting strings======\n";
			vector<string> sstrings=csis[i].startstrings();
			for(int j=0;j<sstrings.size();j++)
				cout<<sstrings[j]<<" : ";
			cout<<endl;
			vector<CSI> temp;
			for(int j=0;j<sstrings.size();j++)
			{
				cout<<sstrings[j]<<endl;
				cout<<"\nCreating new collection for the start string: "<<sstrings[j]<<endl;
				CSI temp2 = csis[i].newcsi(sstrings[j]);
				cout<<endl<<"Got new csi .....\n";
				temp2.viewcsi();
				cout<<endl;
				temp.push_back(temp2);
				CSIMap temp;
				if(islower(sstrings[j][0]) == 0)
					temp.addCSIMap(i,csis.size()+k,0,sstrings[j]);
				else
					temp.addCSIMap(i,csis.size()+k,1,sstrings[j]);
				k++;
				csimap.push_back(temp);
			}
			for(int j=0;j<temp.size();j++)
					csis.push_back(temp[j]);

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
		cout<<"continue? 0 or 1";
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
	for(int i=0;i<csimap.size();i++)
		csimap[i].viewCSIMap();
	return 0;
}

