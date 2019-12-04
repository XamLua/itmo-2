#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdbool.h>
#include <climits>
#include <cmath>
#include <set>

using namespace std;

long int max_edge, mass;

int n, m, a, b;

vector<pair<long int, pair<int, int>>> e;

vector<int> parent(1002);
vector<int> r(1002);

vector<pair<int, int>> answer;

void connect();

int find_set(int x);

void union_sets(int a, int b);

int main()
{	
	scanf("%d %d", &n, &m);

	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %ld", &a, &b, &mass);
		e.push_back({mass, {a, b}});
	}

	connect();

	return 0;
}

int find_set(int x)
{
	if(x == parent[x])
		return x;
	else
		return parent[x] = find_set(parent[x]);
}

void union_sets(int a, int b)
{
	a = find_set(a);
	b = find_set(b);
	if(a != b)
	{
		if (r[a] < r[b])
			parent[a] = b;
		else
			parent[b] = a;

		if (r[a] == r[b])
			r[a]++;
	}
}

void connect()
{

	for (int i = 1; i <= n; i++)
	{
		parent[i] = i;
		r[i] = 0;
	}

	sort(e.begin(), e.end());

	for (int i = 0; i < m; i++)
	{
		a = e[i].second.first;
		b = e[i].second.second;
		mass = e[i].first;
		if(find_set(a) != find_set(b))
		{
			max_edge = mass;
			answer.push_back({a, b});
			union_sets(a, b);
		}
	}

	printf("%ld\n", max_edge);

	printf("%lu\n", answer.size());

	for (int i = 0; i < answer.size(); i++)
		printf("%d %d\n", answer[i].first, answer[i].second);
}
