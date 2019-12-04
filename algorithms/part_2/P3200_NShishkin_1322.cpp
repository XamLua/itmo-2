#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;

char str[100001];
int s_less[123];
int s_equal[100001];
int s_freq[123];

int cnt = 0;

string answer = "";

int n;

void decode();

int main() {

	scanf("%d\n", &n);

	n--;

	scanf("%c", &str[cnt]);
	while (str[cnt] != '\n' && str[cnt] != -1)
	{
		s_equal[cnt] = c[str[cnt]]++;
		scanf("%c", &str[++cnt]);
	}

	for (int i = 65; i < 123; i++)
		s_less[i] = s_less[i-1] + s_freq[i-1];

	decode();

	return 0;
}

void decode(){

	for (int i = 0; i < cnt; i++)
	{
		answer.push_back(str[n]);
		n = s_less[str[n]] + s_equal[n];
	}
	reverse(answer.begin(), answer.end());

	printf("%s\n", answer.c_str());

}