#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdbool.h>
#include <queue>
#include <bitset>

using namespace std;

unsigned int n, d;

vector<vector<int>> v(100);
queue<int> q;
bitset<100> used;
bitset<100> color;

void bfs();

int main()
{	
	scanf("%d\n", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &d);
		while(d != 0)
		{
			v[i].push_back(d);
			v[d].push_back(i);
			scanf("%d", &d);
		}
	}

	bfs();

	return 0;
}

void bfs()
{
	bool res = 1;
	q.push(1);
	used[1] = 1;
	while (!q.empty())
	{
		int i = q.front();
		q.pop();
		for (int j = 0; j < v[i].size(); j++)
		{
			int to = v[i][j];
			if(!used[to])
			{
				used[to] = 1;
				q.push(to);
				color[to] = !color[i];
			}
			else
			{
				if(!color[to]^color[i])
					res = 0;
			}
		}
	}
	if (res)
	{
		for (int i = 1; i <= n; i++)
		{
			printf(color[i] ? "1" : "0");
		}
	}
	else
		printf("-1");
}