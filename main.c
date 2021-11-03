#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funk.h"

// 112 Кузнецов Назар
// Нужно реализовать программу, сортирующую массив чисел по убыванию
// По количеству единичных бит в двоичном представлении числа
// И сравнить время рукописной и библиотечной быстрых сортировок 
int main(void) {
	FILE* file;
	char generfile[120];		//  Путь к файлу с сгенерированным массивом
	char sortfile[120];			//  Путь к файлу с отсортированным массивом
	int n = 40, i;				//  Количество элементов массива, индекс
	int mas[40];				//  Массив
	clock_t  start, end;		//  К-во тиков с момента запуска программы
	float qtime;				//  Время сортировки qsort
	float myqtime;				//  Время сортировки рукописной qsort

													//  Вводим имя файла, куда сгенерируем массив
	printf("Enter the path to the file to store the generated array:\n");
	scanf("%s", generfile);

	if (gener_mas(generfile, n)) {					//  Генерируем массив в файл
		printf("Error opening file\n");				//  Если не удалось открыть файл выводим оповещение
		return 1;
	}

	if (read_file(generfile, mas, n)) {				//  Копируем сгенерированный массив из файла в массив mas
		printf("Could not open file\n");			//  Если не удалось открыть файл выводим оповещение
		return 1;
	}

	start = clock();								//  В start кладем количество тиков до сортировки
	qsort(mas, n, sizeof(int), (int(*)(const void*, const void*))bit_compare);
	end = clock();									//  В end кладем количество тиков после сортировки
	qtime = (float)(end - start) / CLK_TCK;			//  Запоминаем время сортировки qsort

	if (sort_check(mas, n)) {						//  Проверяем, отсортирован ли массив
		printf("Array was not quick sorted\n");		//  Если нет, выводим уведомление
		return 1;									//  и завершаем работу
	}
	else printf("Array was quick sorted:\n");		//  Если да, продолжаем

	if (read_file(generfile, mas, n)) {				//  Копируем сгенерированный массив из файла в массив mas
		printf("Could not open file\n");			//  Если не удалось открыть файл выводим оповещение
		return 1;
	}

	start = clock();								//  В start кладем количество тиков до сортировки
	qsort_no_rec(mas, 0, n - 1);					//  Запускаем рукописный qsort
	end = clock();									//  В end кладем количество тиков после сортировки
	myqtime = (float)(end - start) / CLK_TCK;		//  Запоминаем время сортировки рукописной qsort
	if (sort_check(mas, n)) {						//  Проверяем, отсортирован ли массив
		printf("Array was not quick sorted\n");		//  Если нет, выводим уведомление
		return 1;									//  и завершаем работу
	}												//  Если да, продолжаем
	else printf("Array was handwritten quick sorted:\n\n");

	for (i = 0; i < n; i++) {						//  Выводим массив
		bit_print(mas[i]);
	}
	printf("\n");

	printf("Q-sort sort time(sec): %.3f\n", qtime);
	printf("Handwritten q-sort sort time(sec): %.3f\n\n", myqtime);

	return 0;
}
