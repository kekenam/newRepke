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
	printf("\n\n");
	opCnt = 0;
}

#define CAP 100
ull* dp;
char* x;
char* y;
int** c;
int** v;
int* values;
int* weights;
int sizeX;
int sizeY;
int sizeV;
int sizeW;
int n;


ull fuckedWays(int n) {
	opCnt++;
	if (n == 0)
		return 1;
	else if (n < 0)
		return 0;
	else
		return fuckedWays(n - 1) + fuckedWays(n - 2) + fuckedWays(n - 3);
}

ull waysTD(int n) {
	opCnt++;
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
	opCnt++;
	if (n == 0)
		return 1;
	else if (n < 0)
		return 0;

	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		opCnt++;
		dp[i] += dp[i - 1];
		if (i - 2 >= 0)
			dp[i] += dp[i - 2];
		if (i - 3 >= 0)
			dp[i] += dp[i - 3];
	}
	return dp[n];
}

ull waysUpgradedBU(int n) {
	opCnt++;
	if (n == 0)
		return 1;
	else if (n < 0)
		return 0;

	ull prev1 = 1, prev2 = 0, prev3 = 0;
	ull current = 0;

	for (int i = 1; i <= n; i++) {
		opCnt++;
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
	if (x[i - 1] == y[j - 1])
		return fuckedLcs(x, y, i - 1, j - 1) + 1;
	else
		return fmax(fuckedLcs(x, y, i, j - 1), fuckedLcs(x, y, i - 1, j));
}

int lcsTD(char* x, char* y, int i, int j) {
	opCnt++;
	if (i == 0 || j == 0)
		return 0;
	if (c[i][j] == -1) {
		if (x[i - 1] == y[j - 1])
			c[i][j] = lcsTD(x, y, i - 1, j - 1) + 1;
		else
			c[i][j] = fmax(lcsTD(x, y, i, j - 1), lcsTD(x, y, i - 1, j));
	}
	return c[i][j];

}

int lcsBU(char* x, char* y, int n, int m) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (x[i - 1] == y[j - 1]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				opCnt++;
			}
			else {
				c[i][j] = fmax(c[i][j - 1], c[i - 1][j]);
				opCnt += 2;
			}
		}
	}
	return c[n][m];
}

int lcsUpgradedBU(char* x, char* y, int n, int m) {
	int* strMatrix[2];
	strMatrix[0] = c[0];
	strMatrix[1] = c[1];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (x[i - 1] == y[j - 1]) {
				strMatrix[i % 2][j] = strMatrix[!(i % 2)][j - 1] + 1;
				opCnt++;
			}
			else {
				strMatrix[i % 2][j] = fmax(strMatrix[i % 2][j - 1], strMatrix[!(i % 2)][j]);
				opCnt += 2;
			}
		}
	}
	return strMatrix[n % 2][m];
}

int knapsackBU(int** v, int* values, int* weights, int n, int w) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= w; j++) {
			if (j >= weights[i]) {
				v[i][j] = fmax(v[i - 1][j], values[i] + v[i - 1][j - weights[i]]);
				opCnt += 2;
			}
			else {
				v[i][j] = v[i - 1][j];
				opCnt++;
			}
		}
	}

	return v[n][w];
}

void initDP(int a) {
	for (int i = 0; i <= n; i++) {
		dp[i] = a;
	}
}

void initMatrixDP(int a) {
	for (int i = 1; i <= sizeX; i++) {
		for (int j = 1; j <= sizeY; j++) {
			c[i][j] = a;
		}
	}

	for (int i = 1; i <= sizeV; i++) {
		for (int j = 1; j <= sizeW; j++) {
			v[i][j] = a;
		}
	}
}

void deAllocateDP() {
	if (y)
		free(y);
	if (x)
		free(x);
	if (dp)
		free(dp);
	if (values)
		free(values);
	if (weights)
		free(weights);
	if (c) {
		for (int i = 0; i <= sizeX; i++) {
			if (c[i])
				free(c[i]);
		}
		free(c);

	}
	if (v) {
		for (int i = 0; i <= sizeV; i++) {
			if (v[i])
				free(v[i]);
		}
		free(v);
	}
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

	values = (int*)calloc((sizeV + 1), sizeof(int));
	if (!values) {
		free(dp);
		free(x);
		free(y);
		exit(1);
	}

	weights = (int*)calloc((sizeV + 1), sizeof(int));
	if (!weights) {
		free(dp);
		free(x);
		free(y);
		free(values);
		exit(1);
	}



	c = (int**)calloc((sizeX + 1), sizeof(int*));
	v = (int**)calloc((sizeV + 1), sizeof(int*));
	if (!c || !v) {
		deAllocateDP();
		exit(1);
	}
	for (int i = 0; i <= sizeX; i++) {
		c[i] = (int*)calloc((sizeY + 1), sizeof(int));
		if (!c[i]) {
			for (int j = i - 1; j >= 0; j--) {
				free(c[i]);
			}
			free(c);
			deAllocateDP();
		}
	}
	for (int i = 0; i <= sizeV; i++) {
		v[i] = (int*)calloc((sizeW + 1), sizeof(int));
		if (!v[i]) {
			for (int j = i - 1; j >= 0; j--) {
				free(v[i]);
			}
			free(v);
			deAllocateDP();
		}
	}


}


int main(void) {
	printf("n of ways(n): ");
	scanf("%d", &n);
	printf("length of str x, y (sizeX sizeY): ");
	scanf("%d %d", &sizeX, &sizeY);

	printf("n w of knapsack(n, w): ");
	scanf("%d %d", &sizeV, &sizeW);

	allocateDP();

	printf("str x y (x y): ");
	scanf("%s %s", x, y);


	printf("v values, w values\n v1 w1\nv2 w2\n...:\n");
	for (int i = 1; i <= sizeV; i++) {
		int inputV, inputW;
		scanf("%d %d", &inputV, &inputW);
		values[i] = inputV;
		weights[i] = inputW;
	}

	printf("result of TD BU 3 Variables BU\n");
	printf("Brute Force: %llu\n", fuckedWays(n));
	checkTimeAndLimitExceed();
	initDP(-1);
	printf("Top-Down: %llu\n", waysTD(n));
	checkTimeAndLimitExceed();
	initDP(0);
	printf("Bottom-Up: %llu\n", waysBU(n));
	checkTimeAndLimitExceed();
	printf("3 varitables Bottom-Up: %llu\n", waysUpgradedBU(n));
	checkTimeAndLimitExceed();


	printf("result of LCS\n");
	printf("Brute Force: %d\n", fuckedLcs(x, y, sizeX, sizeY));
	checkTimeAndLimitExceed();
	initMatrixDP(-1);
	printf("Top-Down: %d\n", lcsTD(x, y, sizeX, sizeY));
	checkTimeAndLimitExceed();
	initMatrixDP(-1);
	printf("Bottom-Up: %d\n", lcsBU(x, y, sizeX, sizeY));
	checkTimeAndLimitExceed();
	initMatrixDP(-1);
	printf("2-line-Bottom-Up: %d\n", lcsUpgradedBU(x, y, sizeX, sizeY));
	checkTimeAndLimitExceed();

	printf("knapsack: %d\n", knapsackBU(v, values, weights, sizeV, sizeW));
	checkTimeAndLimitExceed();

	deAllocateDP();
	return 0;
}
