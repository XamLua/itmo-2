#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

set<long long int> h;
set<long long int> v;

unsigned int m, n, k;
long long int answer = 0, x, y;

void count();

int main() 
{	
	scanf("%d %d %d", &m, &n, &k);

	for (int i = 0; i < m; ++i)
	{
		h.insert(i*(n+2));
		h.insert((i+1)*(n+2) - 1);
	}

	for (int i = 0; i < n; ++i)
	{
		v.insert(i*(m+2));
		v.insert((i+1)*(m+2) - 1);
	}

	for (int i = 0; i < k; i++)
	{
		scanf("%llu %llu", &x, &y);
		h.insert((x-1)*(n+2) + y);
		v.insert((y-1)*(m+2) + x);
	}

	count();

	return 0;
}

void count()
{
	set<long long int>::iterator it = h.begin();
	long long int cur, prev = *it++;
	while(it != h.end())
	{
		cur = *it++;
		if (cur - prev > 2)
			answer++;
		prev = cur;
	}
	it = v.begin();
	prev = *it++;
	while(it != v.end())
	{
		cur = *it++;
		if (cur - prev > 2)
			answer++;
		else if (cur - prev == 2)
		{
			y = ((cur-1) / (m+2)) + 1;
			x = (cur-1) % (m+2);
			if (h.find(((x-1)*(n+2) + y + 1)) != h.end() &&
				h.find(((x-1)*(n+2) + y - 1)) != h.end())
			{
				answer++;
			}
		}
		prev = cur;
	}
	printf("%llu\n", answer);
}