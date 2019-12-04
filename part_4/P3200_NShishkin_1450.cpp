#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdbool.h>

using namespace std;

int n, m, a, b, c, s, f;

struct edge
{
	int a, b, pr;
};

vector<edge> v(124751);

vector<int> d(501, 1);

void steal();

int main()
{	
	scanf("%d %d\n", &n, &m);

	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &a, &b, &c);
		v[i].a = a;
		v[i].b = b;
		v[i].pr = -c;
	}

	scanf("%d %d", &s, &f);

	steal();

	return 0;
}

void steal()
{
	d[s] = 0;
	for (int i = 0; i < n-1; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (d[v[j].a] < 1)
				d[v[j].b] = min(d[v[j].b], d[v[j].a]+v[j].pr);
		}
	}
	if (d[f] == 1)
		printf("No solution\n");
	else
		printf("%d\n", -d[f]);
}