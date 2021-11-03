#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 112 �������� �����
// ������� ���������� �-�� ��������� ��� � ������
// ���������� 1, ���� ��� � 1-� ����� ������, -1 - ������, 0 - ���������
int bit_compare(const int* k1, const int* k2) {
	unsigned b1, b2;					// ����
	int n1 = 0, n2 = 0;					// ���������� ��. ��� � ������

	for (int i = 31; i >= 0; i--) {
		b1 = (1 << i);
		b1 &= (*k1);
		b1 >>= i;
		b2 = (1 << i);
		b2 &= (*k2);
		b2 >>= i;
		if (b1 == 1) n1++;
		if (b2 == 1) n2++;
	}
	if (n1 < n2) return 1;
	if (n1 > n2) return -1;
	return 0;
}

// 112 �������� �����
// ������� ��������� ������ �� �����������������
// �� ���� �������� ������ � ��� �����
int sort_check(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		if (bit_compare(a + i, a + i + 1) == 1) return 1;
	}
	return 0;
}

// 112 �������� �����
// ������� ������� ����� � �������� �������������
void bit_print(unsigned K) {
	unsigned b;							// ��� �����
	int N = 0;							// ���������� ��������� ���
	printf("%d: ", (int)K);				// �������� ������
	for (int i = 31; i >= 0; i--) {		// �������� ����� ��������
		b = 1 << i;						// ��������� i �� ������� ����
		b &= K;							// ���������� i-�� ��� �����
		b >>= i;						// ��������� ������������ ��� �������
		if (b == 1) N++;				// ������� ���������� ��������� ���
		printf("%u", b);
		if (i % 8 == 0) printf(" ");
	}
	printf("%d\n", N);					// ������� �-�� ��������� ���
}

// 112 �������� �����
// ������� �������� ������ �� ����� � ������ ������
// �� ���� �������� ��� �����, ������ � ��� �����
int read_file(char filename[], int a[], int n) {
	FILE* file;
	if ((file = fopen(filename, "r")) == 0) return 1;
	for (int i = 0; i < n; i++) {
		fscanf(file, "%d", &a[i]);
	}
	fclose(file);
	return 0;
}

// 112 �������� �����
// ������� ���������� ������ �������� �����
// � ������ ��� � ���� filename
// �� ���� �������� ��� ����� � ������
int gener_mas(char filename[], int n) {
	FILE* file;
	if ((file = fopen(filename, "w")) == 0) return 1;
	srand(time(NULL));									//  ������������� ���������� ������� rand
	for (int i = 0; i < n; i++) {
		fprintf(file, "%d ", rand() * rand() * rand());
		if ((i + 1) % 10 == 0) fprintf(file, "%c", '\n');
	}
	fclose(file);
	return 0;
}

// 112 �������� �����
// ������� ������ ������� �������� �������
// �� ���� �������� ��� �����
void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

// 112 �������� �����
// ������� ��������� ����� ������� (������� ����� ����� l � r)
// �� ���� �������� ������, � ��� ������� l � r, ���������� ������ ���������� ��������
int partition(int arr[], int l, int h) {
	int x = arr[h];
	int i = (l - 1);

	for (int j = l; j <= h - 1; j++) {
		if (bit_compare(&arr[j], &x) == -1) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[h]);
	return (i + 1);
}

// 112 �������� �����
// ������� ��������� ����� �������
// �� ���� �������� ������, � ��� �������, �� ������� ����� ��������� ����������
void qsort_no_rec(int arr[], int l, int h) {
	int stack[40];          // ������� ����-����
	int top = -1;           // ������� ����-�����
	stack[++top] = l;       // ������ � ���� ����� �������
	stack[++top] = h;       // ������ � ���� ������ �������

	while (top >= 0) {      // ���������, ���� ���� �� ����
		h = stack[top--];
		l = stack[top--];

		int p = partition(arr, l, h);

		if (p - 1 > l) {
			stack[++top] = l;
			stack[++top] = p - 1;
		}

		if (p + 1 < h) {
			stack[++top] = p + 1;
			stack[++top] = h;
		}
	}
}