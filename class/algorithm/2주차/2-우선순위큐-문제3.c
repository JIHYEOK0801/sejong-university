#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
void sortReverse(int* select, int* insert,int n) {
	int i;
	for (i = 0; i < n; i++) {
		select[i] = insert[n - 1 - i];
	}
	for (i = 0; i < n; i++) {
		insert[i] = select[i];
	}
}
void insertion(int* L, int j, int i) {
	int k;
	int temp = L[i];
	//j ���ķ� i ���� ���Ҹ� �о�� �۾�
	for (k = i; k > j; k--) {
		L[k] = L[k - 1];
	}
	//j�� ����
	L[j] = temp;
}
void swap(int* L, int i, int j) {
	int temp;
	temp = L[i];
	L[i] = L[j];
	L[j] = temp;
}
int main() {
	int n;
	scanf("%d", &n);
	
	/*
	* �迭 �ʱ�ȭ
	*/
	int* insert = (int*)malloc(sizeof(int) * n);
	int* select = (int*)malloc(sizeof(int) * n);

	int i,j;
	srand(time(NULL));
	for (i = 0; i < n; i++) {
		insert[i] = rand() % 100;
		select[i] = insert[i];
	}
	
	/*
	* A�� -- slect, insert�迭�� ������ ���� ����
	*/

	/*
	* A - �������� ����
	*/
	printf("A��\n");
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);

	int index = 0;
	int temp;
	for (i = n - 1; i >= 0; i--) {
		for (j = 0; j <= i; j++) {
			if (select[j] > select[index]) {
				index = j;
			}
		}
		swap(select, index, i);
		index = 0;
	}
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf(" selectionSort: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	/*
	* A - �������� ����
	*/
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	for (i = 1; i < n; i++) {
		for (j = 0; j < i; j++) {
			if (insert[i] < insert[j]) {
				insertion(insert, j, i);
				break;
			}
		}
	}	
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf(" insertionSort: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	/*
	* B�� -- ���ĵ� select, insert �迭�� �ٽ��ѹ� ������ ���� ����
	*/
	printf("\nB��\n");
	/*
	* B�� - ��������
	*/
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	index = 0;
	temp;
	for (i = n - 1; i >= 0; i--) {
		for (j = 0; j <= i; j++) {
			if (select[j] > select[index]) {
				index = j;
			}
		}
		swap(select, index, i);
		index = 0;
	}
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf(" selectionSort: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	/*
	* B�� - ��������
	*/
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	for (i = 1; i < n; i++) {
		for (j = 0; j < i; j++) {
			if (insert[i] < insert[j]) {
				insertion(insert, j, i);
				break;
			}
		}
	}
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf(" insertionSort: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	
	/*
	* C�� -- �̹� ���ĵ� select, insert�迭�� ���� ���� ��, ������ ���� ����
	*/
	printf("\nC��\n");
	//��������
	sortReverse(select, insert, n);

	/*
	* C�� - ��������
	*/
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	index = 0;
	temp;
	for (i = n - 1; i >= 0; i--) {
		for (j = 0; j <= i; j++) {
			if (select[j] > select[index]) {
				index = j;
			}
		}
		swap(select, index, i);
		index = 0;
	}
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf(" selectionSort: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
	/*
	* C�� - ��������
	*/

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	for (i = 1; i < n; i++) {
		for (j = 0; j < i; j++) {
			if (insert[i] < insert[j]) {
				insertion(insert, j, i);
				break;
			}
		}
	}
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf(" insertionSort: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
	return 0;
}