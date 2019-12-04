#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

unsigned int k, cnt = 1, temp, z;

pair<unsigned long long int, int> hp[10001];

void restore(int i);

void change(int i, unsigned long long int x);

void order();

int main() 
{

	scanf("%d\n", &k);

	for (int i = 1; i <= k; i++)
	{
		scanf("%d", &temp);
		hp[cnt].second = i;
		change(cnt++, temp);
	}

	order();

	return 0;
}

void order()
{
	while (hp[2].first > 0 || hp[3].first > 0)
	{
		if(hp[2].first != 0)
			z = 2;
		else
			z = 3;

		printf("%d %d ", hp[1].second, hp[z].second);

		change(z, hp[z].first-1);
		change(1, hp[1].first - 1);
	}

	for (int i = 0; i < hp[1].first; i++)
	{
		printf("%d ", hp[1].second);
	}

}

void restore(int i)
{
	pair<unsigned long long int, int> temp;
	int largest = i;
	if(2*i < cnt && hp[2*i].first > hp[largest].first)
		largest = 2*i;
	if(2*i + 1 < cnt && hp[2*i+1].first > hp[largest].first)
		largest = 2*i+1;

	if(largest != i)
	{
		temp = hp[i];
		hp[i] = hp[largest];
		hp[largest] = temp;
		restore(largest);
	}
}

void change(int i, unsigned long long x)
{
	pair<unsigned long long int, int> temp;
	if (x > hp[i].first)
	{
		hp[i].first = x;
		while(i > 1 && hp[i/2].first < hp[i].first)
		{
			temp = hp[i];
			hp[i] = hp[i/2];
			hp[i/2] = temp;
			i/=2;
		}
	}
	else if (x < hp[i].first)
	{
		hp[i].first = x;
		restore(i);
	}
}
