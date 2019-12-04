#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

unsigned int n, counter = 1;

unsigned int order[100001];

stack <int> s;

void check();

int main() 
{

	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &order[i]);
	}

	check();

	return 0;
}

void check()
{
	for (int i = 1; i <= n; i++)
	{
		s.push(i);
		while (!s.empty() && s.top() == order[counter])
		{
			s.pop();
			counter++;
		}
	}
	if (s.empty())
		printf("Not a proof\n");
	else
		printf("Cheater\n");
}