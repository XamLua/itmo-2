#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <math.h>
#include <float.h>

using namespace std;

int res_1, n, start_dot = 1, end_dot, res_n;

int quadrants[4];

int dots[30000];

int xs[30000], ys[30000];

double angle(int x, int y);

int cmp_angle(const int &a, const int &b);

void find_path();

int main() 
{

	scanf("%d", &n);

 	dots[0] = 0;

	scanf("%d %d", &xs[0], &ys[0]);

	for (int i = 1; i < n; i++)
	{
		dots[i] = i;

		scanf("%d %d", &xs[i], &ys[i]);

		if (xs[dots[i]] >= xs[res_1] && ys[dots[i]] > ys[res_1])
			quadrants[0]++;
		else if (xs[dots[i]] > xs[res_1] && ys[dots[i]] <= ys[res_1])
			quadrants[1]++;
		else if (xs[dots[i]] <= xs[res_1] && ys[dots[i]] < ys[res_1])
			quadrants[2]++;
		else if (xs[dots[i]] < xs[res_1] && ys[dots[i]] >= ys[res_1])
			quadrants[3]++;
	}

	end_dot = n - 1;

	find_path();

	printf("%d\n", n);

	printf("%d\n", dots[0] + 1);

	if (end_dot >= start_dot)
	{
		for (int i = start_dot; i <= end_dot; i++)
		{
			printf("%d\n", dots[i] + 1);
		}
	}
	else
	{
		for (int i = start_dot; i < n; i++)
		{
			printf("%d\n", dots[i] + 1);
		}		
		for (int i = 1; i <= end_dot; i++)
		{
			printf("%d\n", dots[i] + 1);
		}

	}

	return 0;
}

double angle(int x, int y){
	if ((x - xs[res_1]) == 0)
	{
		return DBL_MAX;
	}
	return (double) (y-ys[res_1])/(double) (x-xs[res_1]);
}

int cmp_angle(const int &a, const int &b){

	double angle_a;
	double angle_b;

	if (((xs[a] >= xs[res_1] && xs[b] >= xs[res_1]) &&
		!((xs[a] == xs[res_1] && ys[a] < ys[res_1]) ||
		   xs[b] == xs[res_1] && ys[b] < ys[res_1])) ||
	    ((xs[a] <= xs[res_1] && xs[b] <= xs[res_1]) &&
			!((xs[a] == xs[res_1] && ys[a] > ys[res_1]) ||
			   xs[b] == xs[res_1] && ys[b] > ys[res_1])))
	{
		angle_a = angle(xs[a], ys[a]);
		angle_b = angle(xs[b], ys[b]);

		if (angle_a == angle_b)
			return (abs(ys[a]-ys[res_1]) + abs(xs[a]-xs[res_1])) < 
					abs(ys[b]-ys[res_1]) + abs(xs[b]-xs[res_1]);

		return angle_a > angle_b;
	}

	return xs[a] > xs[b];
}

void find_path()
{

	res_1 = dots[0];

	int temp = 0;

	sort(dots+1, dots+n, cmp_angle);

	int empty = 0;

	for (int i = 0; i < 4; ++i)
	{
		if (quadrants[i] == 0)
			empty++;
	}

	if (empty == 1)
	{
		if (quadrants[1] == 0)
		{
			start_dot = quadrants[0] + 1;
			end_dot = quadrants[0];
		}
		else if (quadrants[2] == 0)
		{
			start_dot = quadrants[0] + quadrants[1] + 1;
			end_dot = quadrants[0] + quadrants[1];
		}

		return;
	}


	if (empty == 2){

		int q_1, q_2;

		for (int i = 0; i < 4; i++)
		{
			if (quadrants[i] != 0){
				q_2 = i;
			}
		}
		for (int i = 3; i >= 0; i--)
		{
			if (quadrants[i] != 0)
				q_1 = i;
		}

		if ((q_2 - q_1) == 1 || (q_2 - q_1) == 3)
		{
			if ((q_2 - q_1) == 3)
			{
				start_dot = quadrants[0] + 1;
				end_dot = quadrants[0];
			}
			return;
		}

		double start_angle_1, start_angle_2, end_angle_1, end_angle_2;

		temp = 1;
		start_angle_1 = abs(angle(xs[dots[temp]], ys[dots[temp]]));
		temp = quadrants[q_1];
		end_angle_1 = (angle(xs[dots[temp]], ys[dots[temp]]));
		temp++;
		start_angle_2 = (angle(xs[dots[temp]], ys[dots[temp]]));
		temp += quadrants[q_2] - 1;
		end_angle_2 = abs(angle(xs[dots[temp]], ys[dots[temp]]));

		if ((double) end_angle_1 >= (double) start_angle_2)
		{
			start_dot = quadrants[q_1] + 1;
			end_dot = quadrants[q_1];

		}
	}

	return;
}