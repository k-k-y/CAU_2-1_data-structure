#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

void reverse(int *arr, int len);
void add(int *p1, int *p2, int *p3);
void mul(int *p1, int *p2, int *p3);
int eval(int *arr, int len, int num);

int main(void)
{
	char str1[100];
	char str2[100];
	int i;
	int count;
	char str1_i[100];
	int p1[6];
	int p2[6];
	int p3[6]; // 1 + 2 다항식
	int p4[11] = {
		0,
	}; // 1 * 2 다항식
	char temp;
	int index;

	printf("수식 1을 입력하세요 : "); // 수식 1 입력받기
	fgets(str1, 100, stdin);
	str1[strlen(str1) - 1] = '\0';
	count = 0;
	for (i = 0; str1[i] != '\0'; i++)
	{
		if (str1[i] != ' ')
		{
			index = 0;
			while (str1[i] != ' ' && str1[i] != '\0')
			{
				str1_i[index] = str1[i];
				index++;
				i++;
			}
			str1_i[index] = '\0';
			p1[count] = atoi(str1_i);
			count++;
		}
	}
	reverse(p1, count);
	for (i = count; i < 6; i++)
		p1[i] = 0;

	count = 0;
	printf("수식 2을 입력하세요 : "); // 수식 2 입력받기
	fgets(str2, 100, stdin);
	str2[strlen(str2) - 1] = '\0';
	for (i = 0; str2[i] != '\0'; i++)
	{
		if (str2[i] != ' ')
		{
			index = 0;
			while (str2[i] != ' ' && str2[i] != '\0')
			{
				str1_i[index] = str2[i];
				index++;
				i++;
			}
			str1_i[index] = '\0';
			p2[count] = atoi(str1_i);
			count++;
		}
	}

	reverse(p2, count);
	for (i = count; i < 6; i++)
		p2[i] = 0;

	add(p1, p2, p3); // p3에 더해서 저장
	mul(p1, p2, p4); // p4에 더해서 저장

	printf("수식 1 + 2 : "); // p3 출력하기
	for (i = 0; i < 6; i++)
	{
		if (p3[5 - i] != 0)
		{
			printf("%d ", p3[5 - i]);
		}
	}
	printf("\n");

	printf("수식 1 * 2 : "); // p4 출력하기
	for (i = 0; i < 11; i++)
	{
		if (p4[10 - i] != 0)
		{
			printf("%d ", p4[10 - i]);
		}
	}
	printf("\n");

	int a, b;
	while (1 > 0)
	{
		printf("수식에 값을 넣으세요 : ");
		scanf("%d%d", &a, &b);
		if (a == 1)
			printf("결과값은 : %d\n", eval(p1, 6, b));
		else if (a == 2)
			printf("결과값은 : %d\n", eval(p2, 6, b));
		else if (a == 3)
			printf("결과값은 : %d\n", eval(p3, 6, b));
		else
			printf("결과값은 : %d\n", eval(p4, 11, b));
	}

	return 0;
}

void reverse(int *arr, int len)
{
	int temp;
	for (int i = 0; i < len / 2; i++)
	{
		temp = arr[i];
		arr[i] = arr[len - i - 1];
		arr[len - i - 1] = temp;
	}
}

void add(int *p1, int *p2, int *p3)
{
	for (int i = 0; i < 6; i++)
		p3[i] = p1[i] + p2[i];
}

void mul(int *p1, int *p2, int *p4)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
			p4[i + j] += p1[i] * p2[j];
	}
}

int eval(int *arr, int len, int num)
{
	int result = 0;
	for (int i = 0; i < len; i++)
		result += arr[i] * pow(num, i);

	return result;
}
