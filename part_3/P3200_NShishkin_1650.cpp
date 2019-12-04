#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <unordered_map>
#include <stdbool.h>
#include <map>
using namespace std;

int m, n, k, cnt = 1, current_day, day_cnt = 0;
unsigned long long int money, check_1, check_2;

pair<unsigned long long int, string> hp[50001];

string person = "", city = "";

string current_person, current_city;

unordered_map<string, pair<string, unsigned long long int>> rich_p;
unordered_map<string, pair<int, int>> city_heap;

void restore(int i);

void change(int i, unsigned long long int x);

void read_day();

int main() 
{	
	scanf("%d\n", &n);

	for (int i = 0; i < n; i++)
	{
		char temp_char;
		scanf("%c", &temp_char);
		while (temp_char != ' ')
		{
			person.push_back(temp_char);
			scanf("%c", &temp_char);
		}
		scanf("%c", &temp_char);
		while (temp_char != ' ')
		{
			city.push_back(temp_char);
			scanf("%c", &temp_char);
		}
		scanf("%llu", &money);
		scanf("%c", &temp_char);
		if(city_heap.find(city) == city_heap.end())
		{
			city_heap.insert({city, {cnt, 0}});
			hp[cnt++].second = city;
		}
		rich_p.insert({person, {city, money}});
		change(city_heap[city].first, hp[city_heap[city].first].first + money);
		person="";
		city="";
	}

	scanf("%d %d", &m, &k);

	if (day_cnt < k)
		read_day();

	for (int i = 1; i <= m; i++)
	{
		if (cnt > 2)
			check_1 = hp[2].first;
		else
			check_1 = 0;

		if (cnt > 3)
			check_2 = hp[3].first;
		else
			check_2 = 0;

		if (hp[1].first != check_1 && hp[1].first != check_2)
			city_heap[hp[1].second].second++;
		
		while(current_day == i && day_cnt != k)
		{
			if(city_heap.find(current_city) == city_heap.end())
			{
				city_heap.insert({current_city, {cnt, 0}});
				hp[cnt++] = {0, current_city};
			}
			int city_from, city_where;

			city_where = city_heap[current_city].first;
			change(city_where, hp[city_where].first + rich_p[current_person].second);
		
			city_from = city_heap[rich_p[current_person].first].first;
			change(city_from, hp[city_from].first - rich_p[current_person].second);
		
			rich_p[current_person].first = current_city;

			day_cnt++;
			if (day_cnt != k)
				read_day();
		}
	}

	map<string, pair<int, int>> sorted_city_heap(city_heap.begin(), city_heap.end());

	for (map<string, pair<int, int>>::iterator it = sorted_city_heap.begin(); it != sorted_city_heap.end(); it++)
	{
		if(it->second.second != 0)
			printf("%s %d\n", it->first.c_str(), it->second.second);
	}

	return 0;
}

void read_day()
{
	current_city = "";
	current_person = "";
	scanf("%d ", &current_day);
	char temp_char;
	scanf("%c", &temp_char);
	while (temp_char != ' ')
	{
		current_person.push_back(temp_char);
		scanf("%c", &temp_char);
	}
	scanf("%c", &temp_char);
	while (temp_char != '\n' && temp_char != -1)
	{
		current_city.push_back(temp_char);
		scanf("%c", &temp_char);
	}
}

void restore(int i)
{
	pair<unsigned long long int, string> temp;
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
		city_heap[hp[i].second].first = i;
		city_heap[hp[largest].second].first = largest;
		restore(largest);
	}
}

void change(int i, unsigned long long x)
{
	pair<unsigned long long int, string> temp;
	if (x > hp[i].first)
	{
		hp[i].first = x;
		while(i > 1 && hp[i/2].first < hp[i].first)
		{
			temp = hp[i];
			hp[i] = hp[i/2];
			hp[i/2] = temp;
			city_heap[hp[i].second].first = i;
			city_heap[hp[i/2].second].first = i/2;
			i/=2;
		}
	}
	else if (x < hp[i].first)
	{
		hp[i].first = x;
		restore(i);
	}
}