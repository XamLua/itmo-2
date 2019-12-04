#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <vector>
#include <functional>

using namespace std;

int n;

int d = 0;

const int T = 20000;	

struct Node
{
	vector<int> childs;
	long long hash;
	string value;
};

Node r[T+1];

int sz;

hash<string> str_hash;

int add_to(string s, int node_number);

void print_result(int node_number);

int cmp_value(const int &a, const int &b);

int main() 
{
	memset(&r[0].childs, 0, sizeof r[0].childs);
	sz = 1;
	r[0].value = "/";
	scanf("%d\n", &n);
	char temp_char;
	string path;
	int temp_node = 0;

	for (int i = 0; i < n; i++)
	{
		scanf("%c", &temp_char);
		while (temp_char != '\n' && temp_char != -1)
		{	
			if (temp_char == '\\')
			{
				temp_node = add_to(path, temp_node);
				path = "";
			}
			else
				path.push_back(temp_char);

			scanf("%c", &temp_char);
		}
		add_to(path, temp_node);
		path = "";
		temp_node = 0;
	}
	
	for (int i = 0; i < r[0].childs.size(); i++)
	{
		print_result(r[0].childs[i]);
	}

	return 0;
}

int cmp_value(const int &a, const int &b){
	return lexicographical_compare(r[a].value.begin(), r[a].value.end(),
								   r[b].value.begin(), r[b].value.end());
}

int add_to(string s, int node_number)
{
	long long s_hash = str_hash(s);
	r[sz].value = s;
	vector<int>::iterator temp_node = lower_bound(r[node_number].childs.begin(), r[node_number].childs.end(),
		sz, cmp_value);
	if (temp_node != r[node_number].childs.end())
		{ 
			if(r[*temp_node].hash == s_hash)
				return *temp_node;
		}
	r[node_number].childs.insert(temp_node, sz);
	r[sz].hash = s_hash;
	return sz++;
}

void print_result(int node_number){
	for (int i = 0; i < d; i++)
	{
		printf(" ");
	}
	printf("%s\n", r[node_number].value.c_str());
	d++;
	for (int i = 0; i < r[node_number].childs.size(); i++)
	{
		print_result(r[node_number].childs[i]);
	}
	d--;
}