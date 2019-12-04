#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdbool.h>
#include <climits>
#include <cmath>
#include <set>
#include <bitset>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

int n, b, cnt_1, cnt_2, current_v, digit, k;
int digit_a_1, digit_a_2, digit_b_1, digit_b_2;

long long int diff, z;

string temp, y, a;

unsigned long long int cost, cur_d;

vector<unsigned long long int> d(50001, ULLONG_MAX);
vector<int> p(50001, -1), costs(10), answer;

priority_queue<pair<unsigned long long int, int>> q;

unordered_map<string, int> phone_numbers;

vector<vector<pair<int, int>>> v(50001);

void v_add(string x);

void phone();

int main()
{	
	cin >> n;

	for (int i = 0; i < 10; ++i)
		cin >> costs[i];

	for (current_v = 0; current_v < n; current_v++)
	{
		cin >> a;
		v_add(a);
	}

	phone();

	return 0;
}

void v_add(string y)
{
	char t_c_1, t_c_2 = '0';
	for (int i = 0; i < 10; i++)
	{
		temp = y;
		t_c_1 = '0';
		for (int j = 0; j < 10; j++)
		{
			temp[i] = t_c_1++;
			auto it = phone_numbers.find(temp); 
			if(it != phone_numbers.end())
			{
				v[it->second].push_back({current_v, costs[i]});
				v[current_v].push_back({it->second, costs[i]});
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = i+1; j < 10; j++)
		{
			temp = y;
			t_c_1 = temp[i];
			t_c_2 = temp[j];
			temp[i] = t_c_2;
			temp[j] = t_c_1;
			auto it = phone_numbers.find(temp); 
			if(it != phone_numbers.end())
			{
				v[it->second].push_back({current_v, costs[i]});
				v[current_v].push_back({it->second, costs[i]});
			}
		}
	}
	phone_numbers.insert({y, current_v});
}

void phone()
{
	d[0] = 0;
	q.push({0, 0});
	while(!q.empty())
	{
		k = q.top().second;
		cur_d = -q.top().first;
		q.pop();

		if(cur_d > d[k])
			continue;

		for (int j = 0; j < v[k].size(); j++)
		{
			b = v[k][j].first;
			cost = v[k][j].second;
			if (d[k] + cost < d[b])
			{
				d[b] = d[k] + cost;
				p[b] = k;
				q.push({-d[b], b});
			}
		}
	}

	if (p[n-1] == -1)
		printf("%d\n", -1);
	else
	{
		printf("%llu\n",d[n-1]);
		for (int i = n-1; i != 0; i=p[i])
			answer.push_back(i+1);
		answer.push_back(1);
		printf("%lu\n", answer.size());
		
		for (int i = answer.size() - 1; i >= 0; i--)
			printf("%d ", answer[i]);

		printf("\n");

	}
}
