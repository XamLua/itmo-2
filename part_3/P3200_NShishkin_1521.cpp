#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <list>

using namespace std;

int n, k;

const int T = 100000;

int r[4*T+1];

vector<int> T;
vector<int> a;

void teach();

void build(int v, int tl, int tr);

int count_pref(int v, int tl, int tr, int val);

void build_f(int v, int tl, int tr);

int count_pref_f(int v, int tl, int tr, int val);

int main() {

	memset(r, 0, (sizeof r[0]) * (4*T+1));

	scanf("%d %d", &n, &k);

	teach();

	//check_naive();

	return 0;
}

void teach(){

/*	build(1, 0, n-1);
	int temp = 1, temp1 = 1;
	int i = n;

	do
	{
		temp1 = ((temp1 + k) % i == 0)? i : (temp1 + k) % i;
		temp = count_pref(1, 0, n-1, temp1--);

		if (temp == 0)
			printf("%d ", n);
		else
			printf("%d ", temp);
	}while(--i > 0);*/
	for (int i = 1; i <= n; ++i)
	{
		a.push_back(i);
	}
	init(a);
	int temp = 1, temp1 = 1;
	int i = n;

	do
	{
		temp1 = ((temp1 + k) % i == 0)? i : (temp1 + k) % i;
		temp = count_f(temp1--);

		if (temp == 0)
			printf("%d ", n);
		else
			printf("%d ", temp);
	}while(--i > 0);

}

void build(int v, int tl, int tr){

	if (tl == tr)
		r[v] = 1;
	else
	{
		int tm = (tl + tr) >> 1;
		build(v<<1, tl, tm);
		build((v<<1)+1, tm+1, tr);
		r[v] = r[v<<1] + r[(v<<1)+1];
	}

}

int count_pref(int v, int tl, int tr, int val){

	if (tl == tr)
	{
		r[v]--;
		return tl;
	}

	int tm = (tl + tr) >> 1;

	r[v]--;
	if (r[v<<1] >= val)
		return count_pref (v<<1, tl, tm, val);
	else
		return count_pref ((v<<1)+1, tm+1, tr, val - r[v<<1]);

}

void init(int nn)
{
	n = nn;
	t.assign(n, 0);
}

int sum(int r)
{
	int result = 0;
	for (; r >= 0; r = (r & (r+1)) - 1)
		result += t[r];
	return result;
}

void inc(int i, int delta)
{
	for (; i < n; i = (i | (i+1)))
		t[i] += delta;
}

int sum(int l, int r)
{
	return sum(r) - sum(l-1);
}

int count_f(int val)
{
	return `;
}

void init()
{
	init ((int) t.size());
	for (unsigned i = 0; i < t.size(); i++)
		inc (i, t[i]);
}