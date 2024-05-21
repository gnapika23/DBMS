#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
#include<map>
#include <time.h>
#include<stdlib.h>
using namespace std;

struct sales_record 
{
	int region_no;
	int salesman_no;
	int product_id;
	int units;
};

int parse_sales_data(char *s, sales_record &sr)
{
	int i = 0;
	char *rest = s;
	char *token = strtok_r(rest, ", \n", &rest);
	while(token != NULL)
	{
		if(i == 0)
		{
			sr.region_no = atoi(token);
		}
		else if(i == 1)
		{
			sr.salesman_no = atoi(token);
		}
		else if(i == 2)
		{
			sr.product_id = atoi(token);
		}
		else
		{
			sr.units = atoi(token);
		}
		i++;
		token = strtok_r(rest, ", ", &rest);
	}
	return 0;
}

int product[8][2] = {{1,25}, {2,32}, {3,172}, {4,457}, {5,500}, {6,38}, {7,85}, {8,35}};

int read_file(vector<sales_record> &vs)
{
	FILE *fp = fopen("sales.txt", "r");
	if(fp == NULL)
	{
		cout << "File not found" << endl;
		return -1;
	}
	char l[100];
	while(fgets(l, 100, fp) != NULL)
	{
		sales_record s;
		parse_sales_data(l, s);
		vs.push_back(s);
	}
	fclose(fp);
	return 0;
}

struct rsales
{
	map<int, double> sales;
	double cost;
};

void populate_sales_by_region(vector<sales_record> &vs, map<int, rsales> &m)
{
	for(int i = 0; i < vs.size(); i++)
	{
		sales_record &s1 = vs[i];
		map<int, rsales>::iterator itr = m.find(s1.region_no);
		if(itr == m.end())
		{
			rsales r;
			r.sales[s1.salesman_no] = s1.units * product[s1.product_id-1][1];
			r.cost = r.sales[s1.salesman_no];
			m[s1.region_no] = r;
		}
		else
		{
			rsales &r = itr->second;
			if(r.sales.find(s1.salesman_no) == r.sales.end())
			{
				r.sales[s1.salesman_no] = s1.units * product[s1.product_id-1][1];
			}
			else
			{
				r.sales[s1.salesman_no] += (s1.units * product[s1.product_id-1][1]);
			}
			r.cost += r.sales[s1.salesman_no];
		}
	}
}
 
void print_sales(map<int, rsales> &m)
{
    time_t my_time = time(NULL);
	ofstream g;
	g.open("output.txt");
	g << "\t\t\t\t" << "ABC Company" << endl;
	g << "\t\t\t\t" << "___________" << endl;
	for(map<int, rsales>::iterator i = m.begin(); i != m.end(); i++) {
		g << "Region" << i->first << endl;
		g << "__" << endl;
		for(map<int, double>::iterator j = i->second.sales.begin(); j != i->second.sales.end(); j++)
		{
			g << "Salesman" << j->first << "\t\t\tRs " << j->second << "/-" << endl;
		}
	    g << "\nTotal sale at region " <<  i->first << ":\t\tRs " << i->second.cost << "/-\n" << endl;
        g<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        g<<ctime(&my_time)<< "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t "<< " Page: "<<i->first<<endl;
        g<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	}

}
int main()
{
	vector<sales_record> vs;
	read_file(vs);
	map<int, rsales> m;
	populate_sales_by_region(vs, m);
	print_sales(m);
    time_t my_time = time(NULL);
    cout<<"\t\t\t\t\t\t"<<"ABC Company" <<endl;
    cout<<"\t\t\t\t" << "___________" << endl;
    for(map<int, rsales>::iterator i = m.begin(); i != m.end(); i++) {
		cout << "Region" << i->first << endl;
		cout << "__" << endl;
		for(map<int, double>::iterator j = i->second.sales.begin(); j != i->second.sales.end(); j++)
		{
			cout << "Salesman" << j->first << "\t\t\tRs " << j->second << "/-" << endl;
		}
	    cout << "\nTotal sale at region " <<  i->first << ":\t\tRs " << i->second.cost << "/-\n" << endl;
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout<<ctime(&my_time)<< "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t "<< " Page: "<<i->first<<endl;
	}
	return 0;
}