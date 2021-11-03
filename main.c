#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funk.h"
#define LEN 80000

// 112 �������� �����
// ����� ����������� ���������, ����������� ������ ����� �� ��������
// �� ���������� ��������� ��� � �������� ������������� �����
// � �������� ����� ���������� � ������������ ������� ���������� 
int main(void) {
	FILE* file;
	char generfile[120];		//  ���� � ����� � ��������������� ��������
	char sortfile[120];			//  ���� � ����� � ��������������� ��������
	int n = 40, i;				//  ���������� ��������� �������, ������
	int mas[40];				//  ������
	clock_t  start, end;		//  �-�� ����� � ������� ������� ���������
	float qtime;				//  ����� ���������� qsort
	float myqtime;				//  ����� ���������� ���������� qsort

													//  ������ ��� �����, ���� ����������� ������
	printf("Enter the path to the file to store the generated array:\n");
	scanf("%s", generfile);

	if (gener_mas(generfile, n)) {					//  ���������� ������ � ����
		printf("Error opening file\n");				//  ���� �� ������� ������� ���� ������� ����������
		return 1;
	}

	if (read_file(generfile, mas, n)) {				//  �������� ��������������� ������ �� ����� � ������ mas
		printf("Could not open file\n");			//  ���� �� ������� ������� ���� ������� ����������
		return 1;
	}

	start = clock();								//  � start ������ ���������� ����� �� ����������
	qsort(mas, n, sizeof(int), (int(*)(const void*, const void*))bit_compare);
	end = clock();									//  � end ������ ���������� ����� ����� ����������
	qtime = (float)(end - start) / CLK_TCK;			//  ���������� ����� ���������� qsort

	if (sort_check(mas, n)) {						//  ���������, ������������ �� ������
		printf("Array was not quick sorted\n");		//  ���� ���, ������� �����������
		return 1;									//  � ��������� ������
	}
	else printf("Array was quick sorted:\n");		//  ���� ��, ����������

	if (read_file(generfile, mas, n)) {				//  �������� ��������������� ������ �� ����� � ������ mas
		printf("Could not open file\n");			//  ���� �� ������� ������� ���� ������� ����������
		return 1;
	}

	start = clock();								//  � start ������ ���������� ����� �� ����������
	qsort_no_rec(mas, 0, n - 1);					//  ��������� ���������� qsort
	end = clock();									//  � end ������ ���������� ����� ����� ����������
	myqtime = (float)(end - start) / CLK_TCK;		//  ���������� ����� ���������� ���������� qsort
	if (sort_check(mas, n)) {						//  ���������, ������������ �� ������
		printf("Array was not quick sorted\n");		//  ���� ���, ������� �����������
		return 1;									//  � ��������� ������
	}												//  ���� ��, ����������
	else printf("Array was handwritten quick sorted:\n\n");

	for (i = 0; i < n; i++) {						//  ������� ������
		bit_print(mas[i]);
	}
	printf("\n");

	printf("Q-sort sort time(sec): %.3f\n", qtime);
	printf("Handwritten q-sort sort time(sec): %.3f\n\n", myqtime);

	return 0;
}