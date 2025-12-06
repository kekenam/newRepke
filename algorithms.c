#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TIME_LIMIT 100000000

unsigned long long OperatingCounts = 0;
typedef unsigned long long ull;

// 주요 알고리즘들 모음집

/**
* 불친절한 메뉴를 출력
*/
void printUnkindMenu() {
	printf("테스트 할 알고리즘: \n");
	printf("1) sorts(insertion, quick, randomQuick, merge)\n");
	printf("2) etc D & Q(mergeSort 외의 Devide And Conquer algorithms)\n");
	printf("3) DP\n"); // i hate this....
	printf("your input: ");
}

/**
 * 시간 초과했는가? (OperatingCounts가 10^8(1초)을 초과한 경우 안내까지 출력)
*/
void checkTimeLimitExecced() {
	printf("\nopCnt: %lld", OperatingCounts);
	if (OperatingCounts > TIME_LIMIT) {
		printf(" -> TimeLimitExceed -> FUCKED!!!");
	}
	printf("\n\n");

}

/**
 * 출력할게 많아져서 구분을 위해 있는 메소드
*/
void printLine() {
	for (int i = 0; i < 100; i++)
		printf("-");
	printf("\n\n");
}


/**
* insertionSort 삽입정렬
*
* 원소 하나하나를 체크하면서 밀어넣는 작업
*
* n회 순화하면서 순회를 할 때마다 최대 n번 체크 -> O(n^2) (worst case)
* 평균 n/2 회씩 n번 체크 -> O(n^2) (average case)
*
* n (sigma) i=1 { i (sigma) j=1 O(j) }
*/
void insertionSort(int* array, int n) {
	for (int i = 1; i < n; i++) {
		int j = i - 1;
		int temp = array[i];
		OperatingCounts++;
		while (j >= 0 && temp < array[j]) {
			array[j + 1] = array[j];
			OperatingCounts++;
			j--;
		}
		array[j + 1] = temp;
	}
}

// insertionSort 구간 끝, quicSort 구간 시작

void swapArray(int* array, int a, int b) {
	int temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

int partition(int* quickArray, int start, int end) {
	int pivot = quickArray[start];
	int i = start;

	for (int j = start + 1; j <= end; j++) {
		if (pivot >= quickArray[j]) {
			i++;
			swapArray(quickArray, i, j);
		}
		OperatingCounts++;

	}

	swapArray(quickArray, start, i);

	return i; //index of partition (next pivot)


}



/**
* quickSort 퀵정렬
*
* 파티션을 기준으로 크고 작은 것을 갈라서 파티션에 해당하는 원소 위치를 정상화 시키면서 정렬하는 작엄
*
* 만약 행렬이 정렬 되어있거나 역 정렬 되어있는 경우
* pivot 지정 -> n회 순회를 반복 과정을 하고 q의 움직임이 1로 고정되어 이를 n회 반복 -> O(n^2) (worst case)
*
* 그게 아닌 경우에는 2T(n/2)+cn (cn은 partition 과정, 맨 앞의 2는 subArray의 수, "n/2"의 2는 subArray의 크기
* O(nlgn) (average case)
*
*/
void quickSort(int* quickArray, int start, int end) {
	if (end > start) {
		int q = partition(quickArray, start, end);

		quickSort(quickArray, start, q - 1);
		quickSort(quickArray, q + 1, end);
	}
}

int randPartition(int* randQuickArray, int start, int end) {
	int ran = rand() % (end - start + 1) + start;
	swapArray(randQuickArray, start, ran);
	int pivot = randQuickArray[start];

	int i = start;

	for (int j = start + 1; j <= end; j++) {
		if (pivot >= randQuickArray[j]) {
			i++;
			swapArray(randQuickArray, i, j);
		}
		OperatingCounts++;

	}

	swapArray(randQuickArray, start, i);

	return i;
}

void randQuickSort(int* randQuickArray, int start, int end) {
	if (end > start) {
		int q = randPartition(randQuickArray, start, end);

		randQuickSort(randQuickArray, start, q - 1);
		randQuickSort(randQuickArray, q + 1, end);
	}
}

//quickSort끝, mergeSort 시작

void merge(int* array, int start, int mid, int end, int* temp) {
	int i = start;
	int j = mid + 1;
	int k = start;
	while (i <= mid && j <= end) {
		if (array[i] < array[j]) {
			temp[k] = array[i];
			i++;
			k++;
		}
		else {
			temp[k] = array[j];
			j++;
			k++;
		}
		OperatingCounts++;
	}

	while (i <= mid) {
		temp[k] = array[i];
		i++;
		k++;
		OperatingCounts++;
	}

	while (j <= end) {
		temp[k] = array[j];
		j++;
		k++;
		OperatingCounts++;
	}

	for (int a = start; a <= end; a++) {
		array[a] = temp[a];
		OperatingCounts++;
	}


}

/**
* 합병 정렬 mergeSort
*
* 배열을 항상 반토막 내면서 합병하는 과정을 반복함
* 원소 개수가 1일 때 까지 쪼개다가 1인거 끼리 비교하고 그렇게 완성된 놈들끼리 합병하고 합병하고....
*
* 2T(n/2)+cn (cn은 합병과정에서 n개 원소를 순회, 2 두개는 quickSort의 average case와 동일한 현상이 항상 성립됨 -> O(nlgn) (every case)
*/
void mergeSort(int* array, int start, int end, int* temp) {
	if (end > start) {
		int mid = (end + start) / 2;

		mergeSort(array, start, mid, temp);
		mergeSort(array, mid + 1, end, temp);
		merge(array, start, mid, end, temp);
	}
}
//mergeSort 끝


void printInsertArray(int* insertArray, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", insertArray[i]);
	}
	printf("\n\n");
}

void printQuickArray(int* quickArray, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", quickArray[i]);
	}
	printf("\n\n");
}

void printRandomQuickArray(int* randQuickArray, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", randQuickArray[i]);
	}
	printf("\n\n");
}

void printMergeArray(int* mergeArray, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", mergeArray[i]);
	}
	printf("\n\n");
}

void printCurrentArrays(int* insertArray, int* quickArray, int* randQuickArray, int* mergeArray, int n) {
	printf("current insertArray: ");
	printInsertArray(insertArray, n);
	printf("current quickArray: ");
	printQuickArray(quickArray, n);
	printf("current randomQuickArray: ");
	printRandomQuickArray(randQuickArray, n);
	printf("current mergeArray: ");
	printMergeArray(mergeArray, n);
}

/**
* 배열 자동 입력기
*
* n: size of arrays
* fixedReversed: if switch on this, arrays will have input values that sorted reverse
*/
void autoInputArray(int* insertArray, int* quickArray, int* randQuickArray, int* mergeArray, int n, int fixedReversed) {
	if (fixedReversed)
		for (int i = 0; i < n; i++) {
			insertArray[i] = n - i;
			quickArray[i] = n - i;
			randQuickArray[i] = n - i;
			mergeArray[i] = n - i;
		}
	else
		for (int i = 0; i < n; i++) {
			int ran = rand() % n + 1;
			insertArray[i] = ran;
			quickArray[i] = ran;
			randQuickArray[i] = ran;
			mergeArray[i] = ran;
		}
}


//sorted는 여기서 끝 그 밑은 분할정복

void autoInputSortedArray(int* array, int n) {
	for (int i = 0; i < n; i++)
		array[i] = i + 1;

}

void printBSArray(int* BSArray, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", BSArray[i]);
	}
	printf("\n\n");
}

/**
* 재귀로 된 이진탐색(분할 정복을 다루는 구간이라 재귀로 구현함)
*/
int binarySearch(int* BSArray, int start, int end, int key) {
	OperatingCounts++;
	if (end < start)
		return -1;
	int mid = (end + start) / 2;
	if (BSArray[mid] == key)
		return mid;
	else if (BSArray[mid] > key)
		return binarySearch(BSArray, start, mid - 1, key);
	else
		return binarySearch(BSArray, mid + 1, end, key);

}

/**
* 선형 시간 a^n -> O(n)
*/
long long linearPow(int a, int n) {

	long long result = 1;
	for (int i = 0; i < n; i++) {
		OperatingCounts++;
		result *= a;
	}
	return result;
}

/**
* 분할 정복 제곱 O(lg n)
* n이 짝수 -> a^(n/2) * a^(n/2)
* 홀수 -> a^((n-1)/2) * a^((n-1)/2)*a
*/
long long dcPow(int a, int n) {
	OperatingCounts++;
	if (n == 0)
		return 1;
	if (n == 1)
		return a;

	long long half = dcPow(a, n / 2);

	if (n % 2 == 0)
		return half * half;
	else
		return half * half * a;
}
/**
* 우리가 흔히 아는 선형시간 피보나치 -> O(n)
*/
ull linearFibonacci(int n) {
	if (n == 0)
		return 0;
	ull f1 = 0;
	ull  f2 = 1;
	ull result = f2 + f1;
	for (int i = 2; i <= n; i++) {
		OperatingCounts++;
		result = f2 + f1;
		f1 = f2;
		f2 = result;
	}

	return result;
}


void matrixMulti(ull fmatrixA[2][2], ull fmatrixB[2][2]) {
	ull result[2][2];
	result[0][0] = fmatrixA[0][0] * fmatrixB[0][0] + fmatrixA[0][1] * fmatrixB[1][0];
	result[0][1] = fmatrixA[0][0] * fmatrixB[0][1] + fmatrixA[0][1] * fmatrixB[1][1];
	result[1][0] = fmatrixA[1][0] * fmatrixB[0][0] + fmatrixA[1][1] * fmatrixB[1][0];
	result[1][1] = fmatrixA[1][0] * fmatrixB[0][1] + fmatrixA[1][1] * fmatrixB[1][1];
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			fmatrixA[i][j] = result[i][j];
		}
	}
	OperatingCounts += 16; //temp 4 + mults 8 + adds 4
}

void matrixPow(ull fmatrix[2][2], ull n, ull resMatrix[2][2]) {

	resMatrix[0][0] = 1;
	resMatrix[0][1] = 0;
	resMatrix[1][0] = 0;
	resMatrix[1][1] = 1;
	while (n) {
		if (n & 1) { // n%2!=0
			matrixMulti(resMatrix, fmatrix); // 20회로 고정 -> O(1), 위에 메소드가 2x2행렬을 반환할 경우 -> resMatirx = matrixMulti(resMatrix, fmatrix) 와 같음
		}
		matrixMulti(fmatrix, fmatrix);
		n >>= 1; // n /= 2
	}
}
/**
* 행렬을 이용하는 피보나치
* O(lg n) 분할 정복 제곱에 의해서 이렇게 나옴
* 정확히는 (10~20)lg n 임
*
* 2x2 행렬
* Fn+1 Fn		[1 1] ^ n
* Fn   Fn-1 ->  [1 0]
* 이라는 공식으로 구함
*/
ull matrixFibonacci(int n) {
	if (n == 0)
		return 0;
	ull fmatrix[2][2] = { {1, 1},{1, 0} }; // f2, f1, f1, f0
	ull result[2][2];
	matrixPow(fmatrix, n - 1, result);

	return result[0][0];
}
//분할 정복 끝 그 아래 줄은 DP


/**
* 무지성 ways 호출하기 -> 3개로 분할되는데 이놈들도 선형시간이 걸림 -> 3^n (거의 못씀)
*/
int ways(int n) {
	OperatingCounts++;
	if (n < 0)
		return 0;
	if (n == 0)
		return 1;
	return ways(n - 1) + ways(n - 2) + ways(n - 3);
}

/**
* 그래서 DP로 이전 결과를 저장함 -> O(n)
*
* dpm[n] != -1 이 이미 계산된 내용인지 확인하는 거고
* dpm[n] = ways... 이 부분이 결과를 저장하는 거임
*/
int waysDp(int n, int* dpm) {
	OperatingCounts++;

	if (dpm[n] != -1)
		return dpm[n];

	else if (n < 0)
		return 0;

	else if (n == 0)
		return 1;

	dpm[n] = waysDp(n - 1, dpm) + waysDp(n - 2, dpm) + waysDp(n - 3, dpm);
	return dpm[n];


}



//보조 메소드들 끝

/**
* 정렬 수행
*/
void sorts() {
	printLine();
	printf("\ninput: (size of Array) (printArray: if this value is zero, result of sorting won't be printed) (inputReversedSortedArray: if this value isn't zero, arrays will be filled with reversed sorted values):\n");
	int n = 0;
	int printArray = 0; // 입력 결과와 출력 결과를 출력할 것인가?
	int fixedReversed = 0; // 입력을 역정렬 상태로 할 것인가?
	scanf("%d %d %d", &n, &printArray, &fixedReversed);

	int* insertArray = (int*)malloc((n + 1) * sizeof(int));
	int* quickArray = (int*)malloc((n + 1) * sizeof(int));
	int* randQuickArray = (int*)malloc((n + 1) * sizeof(int));
	int* mergeArray = (int*)malloc((n + 1) * sizeof(int));
	int* tempArray = (int*)malloc((n + 1) * sizeof(int));
	if (!insertArray || !mergeArray || !quickArray || !randQuickArray || !tempArray) {
		if (insertArray)
			free(insertArray);
		if (mergeArray)
			free(mergeArray);
		if (quickArray)
			free(quickArray);
		if (randQuickArray)
			free(randQuickArray);
		if (tempArray)
			free(tempArray);
		exit(1);
	}

	
	autoInputArray(insertArray, quickArray, randQuickArray, mergeArray, n, fixedReversed);

	if (printArray) {
		printLine();
		printCurrentArrays(insertArray, quickArray, randQuickArray, mergeArray, n);

	}
	printLine();

	printf("result of insertionSort: ");
	insertionSort(insertArray, n); // second param: size


	if (printArray)
		printInsertArray(insertArray, n);
	checkTimeLimitExecced();
	printLine();

	OperatingCounts = 0;
	printf("result of quickSort: ");

	quickSort(quickArray, 0, n - 1); //second param: start index, third param: end index

	if (printArray)
		printQuickArray(quickArray, n);
	checkTimeLimitExecced();
	printLine();


	OperatingCounts = 0;
	printf("result of randomQuickSort: ");

	randQuickSort(randQuickArray, 0, n - 1); //second param: start index, third param: end index

	if (printArray)
		printRandomQuickArray(randQuickArray, n);
	checkTimeLimitExecced();
	printLine();

	OperatingCounts = 0;
	printf("result of mergeSort: ");

	mergeSort(mergeArray, 0, n - 1, tempArray); //second param: start index, third param: end index


	if (printArray)
		printMergeArray(mergeArray, n);
	checkTimeLimitExecced();
	printLine();


	free(insertArray);
	free(quickArray);
	free(randQuickArray);
	free(mergeArray);
	free(tempArray);
	OperatingCounts = 0;
}




/**
* 분할 정복
*/
void devideAndConquer() {
	printLine();
	printf("input:\n(a: a of pow(a, n)) (n: size of binary search array, n of pow(a, n)) (f: f of 'f'-th fibonacci) (printArray: if this value is zero, array won't be printed)\n");
	int a = 0, n = 0, f = 0, printArray = 0;
	scanf("%d %d %d %d", &a, &n, &f, &printArray);
	int* BSArray = (int*)malloc((n + 1) * sizeof(int));
	if (!BSArray) {
		exit(1);
	}

	autoInputSortedArray(BSArray, n);
	
	int ran = rand() % (2 * n) + 1;
	printf("random key value: %d\n", ran);
	if (printArray) {
		printf("current binary search array: ");
		printBSArray(BSArray, n);
	}
	printf("result of binary Search: index of %d is %d\n", ran, binarySearch(BSArray, 0, n - 1, ran)); //second param: start index, third param: end index
	checkTimeLimitExecced();
	printLine();
	OperatingCounts = 0;


	printf("result of linear pow(%d, %d): %lld\n", a, n, linearPow(a, n));
	checkTimeLimitExecced();
	OperatingCounts = 0;
	printf("result of dcpow(%d, %d): %lld\n", a, n, dcPow(a, n));
	checkTimeLimitExecced();
	OperatingCounts = 0;
	printLine();


	printf("result of linearFibonacci: %llu", linearFibonacci(f));
	checkTimeLimitExecced();
	OperatingCounts = 0;
	printf("result of matrixFibonacci: %llu", matrixFibonacci(f));
	checkTimeLimitExecced();
	OperatingCounts = 0;


	free(BSArray);
	printLine();
}
/**
* 무지성 호출과 dp를 비교
*/
void dynamicProgramming() {
	printLine();
	printf("input: (n: n of ways(n)): ");
	int input = 0;
	scanf("%d", &input);

	printf("result of ways(%d): %d\n", input, ways(input));
	checkTimeLimitExecced();
	OperatingCounts = 0;

	int* dpm = (int*)malloc((input + 1) * sizeof(int));
	if (!dpm)
		exit(1);

	for (int i = 0; i <= input; i++)
		dpm[i] = -1; // input+1 크기의 배열을 하나 생성하고 모두 계산되지 않은 상태(-1)로 초기화함
	//input이 양수라는 가정하에 -1이라고 둠(음수면 0으로 끝남)

	printf("result of waysDp(%d): %d\n", input, waysDp(input, dpm));
	checkTimeLimitExecced();
	OperatingCounts = 0;
	free(dpm);
	printLine();
}

int main(void) {
	srand(time(NULL));
	int input = 0;
	do {
		printUnkindMenu();
		scanf("%d", &input);

		switch (input) {
		case 0:
			printf("GOOD BYE");
			return 0;
		case 1:
			sorts();
			break;
		case 2:
			devideAndConquer();
			break;
		case 3:
			dynamicProgramming();
			break;
		default:
			printf("WOW!!! INVALID INPUT!!!\n");
		}
	} while (input);

	return 0;
}


