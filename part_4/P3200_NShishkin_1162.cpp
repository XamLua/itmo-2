#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdbool.h>
#include <cfloat>
#include <cmath>

using namespace std;

int n, m, a, b, c, s, f;

float sum, r1, r2, c1, c2;

struct edge
{
	int a, b;
	float rate, com;
};

vector<edge> v(203);

vector<float> d(101, 1);

void cheat();

int main()
{	
	scanf("%d %d %d %f\n", &n, &m, &s, &sum);

	for (int i = 1; i <= 2*m; i+=2)
	{
		scanf("%d %d %f %f %f %f", &a, &b, &r1, &c1, &r2, &c2);
		v[i] = {a, b, r1, c1};
		v[i+1] = {b, a, r2, c2};
	}

	cheat();

	return 0;
}

void cheat()
{
	bool res = 0;
	d[s] = -sum;
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j <= 2*m; j++)
		{
			if (d[v[j].a] != 1)
			{
				if(d[v[j].b] - (d[v[j].a]+v[j].com)*v[j].rate > 0.000001
					&& ((d[v[j].a]+v[j].com)*v[j].rate < 0))
				{
					d[v[j].b] = (d[v[j].a]+v[j].com)*v[j].rate;
					if (i == n-1)
						res = 1;
				}
			}
		}
	}	

	if (res)
		printf("YES\n");
	else
		printf("NO\n");
}
