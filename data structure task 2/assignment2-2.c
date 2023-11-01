#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

typedef struct polynomial Poly;
struct polynomial
{
	int coef;
	int degree;
};

int count1;
int count2;
void add(Poly *p1, Poly *p2, Poly *p3);
void mul(Poly *p1, Poly *p2, Poly *p4);

int main(void)
{
	char *tok;
	char str[100];
	int temp[15];
	int count;
	int count3 = 0;
	int count4 = 0;
	Poly *p1;
	Poly *p2;
	Poly *p3;
	Poly *p4;

	printf("수식 1을 입력하세요 : "); // 수식 1 입력받기
	count = 0;
	fgets(str, 100, stdin);
	str[strlen(str) - 1] = '\0';
	tok = strtok(str, " ");
	while (tok != NULL)

	{
		if (strcmp(tok, "0") == 0 && count % 2 == 0)

		{
			tok = strtok(NULL, " "); // coef가 0이면 계수 그냥 넘겨버리기
		}
		else if (count % 2 == 0) // coef가 입력

		{
			temp[count] = atoi(tok);
			count++;
		}
		else // degree가 입력

		{
			temp[count] = atoi(tok);
			count++;
		}
		tok = strtok(NULL, " ");
	}
	count1 = count / 2;
	p1 = malloc(sizeof(Poly) * count1);
	for (int i = 0; i < count; i += 2)

	{
		p1[i / 2].coef = temp[i];
		p1[i / 2].degree = temp[i + 1];
	}

	printf("수식 2을 입력하세요 : "); // 수식 2 입력받기
	count = 0;
	fgets(str, 100, stdin);
	str[strlen(str) - 1] = '\0';
	tok = strtok(str, " ");
	count = 0;
	while (tok != NULL)

	{
		if (strcmp(tok, "0") == 0 && count % 2 == 0)

		{
			tok = strtok(NULL, " "); // coef가 0이면 계수 그냥 넘겨버리기
		}
		else if (count % 2 == 0) // coef가 입력

		{
			temp[count] = atoi(tok);
			count++;
		}
		else // degree가 입력

		{
			temp[count] = atoi(tok);
			count++;
		}
		tok = strtok(NULL, " ");
	}
	count2 = count / 2;
	p2 = malloc(sizeof(Poly) * count2);
	for (int i = 0; i < count; i += 2)

	{
		p2[i / 2].coef = temp[i];
		p2[i / 2].degree = temp[i + 1];
	}

	int check_degree[11] = {
		0,
	}; // 수식 1과 2에 어떤 degree 종류가 있는지 세고, p3 동적할당.
	for (int i = 0; i < count1; i++)
		check_degree[p1[i].degree]++;
	for (int i = 0; i < count2; i++)
		check_degree[p2[i].degree]++;
	for (int i = 0; i < 6; i++)
		if (check_degree[i] != 0)
			count3++;
	for (int i = 0; i < 6; i++)
		check_degree[i] = 0; // check_degree 배열 요소 0으로 초기화
	p3 = malloc(sizeof(Poly) * count3);

	add(p1, p2, p3); // p3에 1 + 2 값 넣기

	printf("수식 3 : "); // p3 출력
	for (int i = 0; i < count3; i++)
		printf("%d %d ", p3[i].coef, p3[i].degree);
	printf("\n");

	for (int i = 0; i < count1; i++) // 수식 1 * 2에 어떤 degree 종류가 있는지 세고, p4 동적할당

	{
		for (int j = 0; j < count2; j++)
			check_degree[p1[i].degree + p2[j].degree]++;
	}
	for (int i = 0; i < 11; i++)
		if (check_degree[i] != 0)
			count4++;
	p4 = malloc(sizeof(Poly) * count4);

	mul(p1, p2, p4); // p4에 1 * 2 값 넣기

	printf("수식 4 : ");
	for (int i = 0; i < count4; i++)
		printf("%d %d ", p4[i].coef, p4[i].degree);
	printf("\n");

	int a, b;
	int result;
	while (1 > 0)
	{
		result = 0;
		printf("수식에 값을 넣으세요 : "); // 수식 a에 b를 넣겠다.
		scanf("%d%d", &a, &b);
		if (a == 1) // a와 b에 값에 따라 함숫값 계산
		{
			for (int i = 0; i < count1; i++)
				result += p1[i].coef * pow(b, p1[i].degree);
			printf("결과값은 %d\n", result);
		}
		else if (a == 2)
		{
			for (int i = 0; i < count2; i++)
				result += p2[i].coef * pow(b, p2[i].degree);
			printf("결과값은 %d\n", result);
		}
		else if (a == 3)
		{
			for (int i = 0; i < count3; i++)
				result += p3[i].coef * pow(b, p3[i].degree);
			printf("결과값은 %d\n", result);
		}
		else // a == 4
		{
			for (int i = 0; i < count4; i++)
				result += p4[i].coef * pow(b, p4[i].degree);
			printf("결과값은 %d\n", result);
		}
	}

	free(p1);
	free(p2);
	free(p3);
	free(p4);
}

void add(Poly *p1, Poly *p2, Poly *p3)
{
	int cnt = 0;
	int min = count1;
	if (min > count2)
		min = count2;
	int i = 0, j = 0;
	while (i != min && j != min)

	{
		if (p1[i].degree > p2[j].degree)

		{
			p3[cnt].degree = p1[i].degree;
			p3[cnt].coef = p1[i].coef;
			cnt++;
			i++;
		}
		else if (p1[i].degree == p2[j].degree)
		{
			p3[cnt].degree = p1[i].degree;
			p3[cnt].coef = p1[i].coef + p2[j].coef;
			cnt++;
			i++;
			j++;
		}
		else if (p1[i].degree < p2[j].degree)

		{
			p3[cnt].degree = p2[j].degree;
			p3[cnt].coef = p2[j].coef;
			cnt++;
			j++;
		}
	}

	while (j != min)

	{
		p3[cnt].degree = p2[j].degree;
		p3[cnt].coef = p2[j].coef;
		cnt++;
		j++;
	}
	while (i != min)

	{
		p3[cnt].degree = p1[i].degree;
		p3[cnt].coef = p1[i].coef;
		cnt++;
		i++;
	}
}

void mul(Poly *p1, Poly *p2, Poly *p4)
{
	int i, j;
	int check;
	int cnt = 0;
	for (i = 0; i < count1; i++)

	{
		for (j = 0; j < count2; j++)

		{
			check = 0;
			for (int z = 0; z < cnt; z++)

			{
				if (p4[z].degree == p1[i].degree + p2[j].degree)

				{
					p4[z].coef += p1[i].coef * p2[j].coef;
					check = 1;
				}
			}
			if (check == 0)

			{
				p4[cnt].degree = p1[i].degree + p2[j].degree;
				p4[cnt].coef = p1[i].coef * p2[j].coef;
				cnt++;
			}
		}
	}
}
