#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
typedef unsigned long long ull;
#define TIME_LIMIT 100000000
ull opCnt = 0;

void checkTimeAndLimitExceed() {
	printf("opCnt: %llu", opCnt);
	if (opCnt > TIME_LIMIT)
		printf(" -> TimeLimitExceed -> FUCKED!!!");
	printf("\n");
	opCnt = 0;
}

#define CAP 100
ull* dp;
char* x;
char* y;
int** c;
char* result;
int sizeX;
int sizeY;
int n;

ull waysTD(int n) {
	if (n == 0)
		return 1;
	else if (n < 0)
		return 0;
	if (dp[n] != -1)
		return dp[n];

	dp[n] = waysTD(n - 1) + waysTD(n - 2) + waysTD(n - 3);
	return dp[n];
}

ull waysBU(int n) {
	if (n == 0)
		return 1;
	else if (n < 0)
		return 0;

	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		dp[i] += dp[i - 1];
		if (i - 2 >= 0)
			dp[i] += dp[i - 2];
		if (i - 3 >= 0)
			dp[i] += dp[i - 3];
	}
	return dp[n];
}

ull waysUpgradedBU(int n) {
	if (n == 0)
		return 1;
	else if (n < 0)
		return 0;

	ull prev1=1, prev2= 0, prev3=0;
	ull current = 0;

	for (int i = 1; i <= n; i++) {
		current = prev1 + prev2 + prev3;
		prev3 = prev2;
		prev2 = prev1;
		prev1 = current;

	}
	return current;
}

int fuckedLcs(char* x, char* y, int i, int j) {
	opCnt++;
	if (i == 0 || j == 0)
		return 0;
	if (x[i] == y[j])
		return fuckedLcs(x, y, i - 1, j - 1) + 1;
	else
		return max(fuckedLcs(x, y, i, j - 1), fuckedLcs(x, y, i - 1, j));
}

int lcsTD(char* x, char* y, int i, int j) {
	if (i == 0 || j == 0)
		return 0;
	if (c[i][j] != -1)
		return c[i][j];
	if (x[i] == y[j])
		c[i][j] = lcsTD(x, y, i - 1, j - 1) + 1;
	else
		c[i][j] = max(fuckedLcs(x, y, i, j - 1), fuckedLcs(x, y, i - 1, j));

	return c[i][j];

}


void allocateDP() {
	dp = (ull*)calloc(n + 1, sizeof(ull));	
	if (!dp)
		exit(1);
	x = (char*)malloc((sizeX + 1) * sizeof(char));
	if (!x) {
		free(dp);
		exit(1);
	}
	y = (char*)malloc((sizeY + 1) * sizeof(char));
	if (!y) {
		free(x);
		free(dp);
		exit(1);
	}

	for (int i = 0; i <= n; i++) {
		dp[i] = -1;
	}

	result = (char*)malloc(min(sizeX, sizeY) * (sizeof(char)));
	if (!result) {
		deAllocteDP();
		exit(1);
	}
	
	c = (int**)calloc((sizeX + 1), sizeof(int*));
	if (!c)
		exit(1);

	for (int i = 0; i <= sizeX; i++) {
		c[i] = (int*)calloc((sizeY + 1), sizeof(int));
		if (!c[i]) {
			for (int j = i - 1; j >= 0; j--) {
				free(c[i]);
			}
			free(c);
			deAllocteDP();
		}
	}
	for (int i = 1; i <= sizeX; i++) {
		for (int j = 1; j <= sizeY; j++) {
			c[i][j] = -1;
		}
	}

}

void deAllocteDP() {
	if(y)
		free(y);
	if(x)
		free(x);
	if(dp)
		free(dp);
	if (c) {
		for (int i = 0; i <= sizeX; i++) {
			if(c[i])
				free(c[i]);
		}
		free(c);

	}
	if (result)
		free(result);
}

int main(void) {
	printf("n of ways(n): ");
	scanf("%d", &n);
	allocateDP();
	printf("result of TD BU 3 Variables BU\n%llu %llu %llu\n", waysTD(n), waysBU(n), waysUpgradedBU(n));
	
	printf("length of str x, y (sizeX sizeY): ");
	scanf("%d %d", &sizeX, &sizeY);
	printf("str x y (x y): ");
	scanf("%s %s", x, y);
	fuckedLcs(x, y, sizeX, sizeY);
	lcsTD(x, y, sizeX, sizeY);
	
	deAllocteDP();
	return 0;
}

