/***********************************************
 * АлтГУ, ИМиИТ, Кафедра информатики           *
 * Курс "Основы программирования"              *
 * Файл: zadaniye1.с						   *
 *                                             *
 * Программа для вывода таблицы результатов    *
 *                                кросса       *
 ***********************************************/

/*подключаем библиотеки*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

/*функция ввода данных*/
void inputData(int *age, int *Mstart, int *Sstart, int *Mfin, int *Sfin) 
{ 
	printf("Введите возраст участника \n");
	scanf("%i", &*age);
	

	printf("Введите время старта участника (минуты и секунды через пробел) \n");
	scanf("%i %i", &*Mstart, &*Sstart);

	printf("Введите время финиша участника (минуты и секунды через пробел) \n");
	scanf("%i %i", &*Mfin, &*Sfin);

	if ((*age < 16) || (*age > 120) || (*Sstart > 59) || (*Sfin > 59)) 
	{
		printf("Введите корректный возраст или время!");
		exit(0);
	}
}

/*функция вычисления времени*/
int calculateTime(int Mstart, int Sstart, int Mfin, int Sfin) 
{
	int SecStart, SecFin, delta;

	SecStart = (Mstart * 60) + Sstart;
	SecFin = (Mfin * 60) + Sfin;

	delta = SecFin - SecStart;
	if ((delta < 0) || (delta > 1500)) 
	{
		printf("Неверно введенно время!");
		exit(0);
	}
	return delta;
}

/*функция вычисления возрастного коэффицента*/
double calculateAgeCoeff(int age) 
{
	if (age > 35) 
	{
		return 1.45;
	}
	else if (age > 25) 
	{
		return 1.13;
	}
	else 
	{
		return 1.0;
	}
}

/*функция вычисления баллов*/
int calculateResult(int time, double koef) 
{	
	double Result = koef * (1500 - time);

	Result = round(Result);
	return Result;
}

/*функция вычисления результата команды*/
int calculateTeamResult(int result1, int result2, int result3)
{
	int min, sum;

	min = result1;
	if (min > result2) { min = result2; }
	if (min > result3) { min = result3; }
	
	if (min == result1) { sum = result2 + result3; }
	else if (min == result2) { sum = result1 + result3; }
	else { sum = result1 + result2; }

	return sum;
}

/*функция печати результатов*/
void printTable(int age1, int time1, int result1, int age2, int time2, int result2, int age3, int time3, int result3, int resultTeam) 
{
	printf("%-10s %-15s %-10s %-10s \n", "Участник", "Возраст", "Время", "Результат");
	printf("%-10d %-15d %-10d %-10d\n", 1, age1, time1, result1);
	printf("%-10d %-15d %-10d %-10d\n", 2, age2, time2, result2);
	printf("%-10d %-15d %-10d %-10d\n", 3, age3, time3, result3);
	printf("\nРезультаты команды");
	printf("%-20s %i\n", "", resultTeam);
}

void main() 
{
	setlocale(LC_ALL, "Russian");

	/*вводные переменные*/
	int age, Mstart, Sstart, Mfin, Sfin;

	/*вычисляемые переменные*/
	double koef;
	int time, result, resultTeam;

	/*результаты по участникам*/
	int age1, time1, result1;
	int age2, time2, result2;
	int age3, time3, result3;

	for (int nomer = 1; nomer < 4; nomer++) 
	{
		printf("Участник номер %d \n", nomer); /*заголовок*/

		inputData(&age, &Mstart, &Sstart, &Mfin, &Sfin); /*ввод данных участника nomer*/

		koef = calculateAgeCoeff(age); /*вычисление коэффицента*/

		time = calculateTime(Mstart, Sstart, Mfin, Sfin); /*вычисление времени*/

		result = calculateResult(time, koef); /*вычисление баллов участника*/

		if (nomer == 1) {
			age1 = age;
			time1 = time;
			result1 = result;
		}
		else if (nomer == 2) {
			age2 = age;
			time2 = time;
			result2 = result;
		}
		else {
			age3 = age;
			time3 = time;
			result3 = result;
		}
	}

	resultTeam = calculateTeamResult(result1, result2, result3);

	printTable(age1, time1, result1, age2, time2, result2, age3, time3, result3, resultTeam);
}
