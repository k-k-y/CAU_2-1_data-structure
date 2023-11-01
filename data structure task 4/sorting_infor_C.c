#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
	char name[11];
	char number[9];
	char address[51];
} Student;

int static compare_number(const void *first, const void *second) // comparing by number
{
	return strcmp(((Student *)first)->number, ((Student *)second)->number);
}

int static compare_name(const void *first, const void *second) // comparing by name
{
	return strcmp(((Student *)first)->name, ((Student *)second)->name);
}

int main(void)
{
	FILE *fp;
	fp = fopen("student_information.txt", "r");
	char str[200];
	Student s[21000];
	int index;

	time_t start, end;

	for (int i = 0; i < 20000; i++)
	{
		fgets(str, 200, fp);
		for (int j = 9, index = 0; j < 17; j++, index++) // store number
		{
			s[i].number[index] = str[j];
		}

		for (int j = 25, index = 0; j < 35; j++, index++) // store name
		{
			s[i].name[index] = str[j];
		}

		for (int j = 46, index = 0; j < 96; j++, index++) // store address
		{
			s[i].address[index] = str[j];
		}
	}

	start = clock();
	qsort(s, 20000, sizeof(Student), compare_number); // sorting by number
	end = clock();
	printf("sort by number : %.3lfsec\n", (double)(end - start) / CLOCKS_PER_SEC);
	/*for (int i = 0; i < 20000; i++)
	{
		printf("%s %s %s\n", s[i].number, s[i].name, s[i].address);
	}*/

	start = clock();
	qsort(s, 20000, sizeof(Student), compare_name); // sorting by name
	end = clock();
	printf("sort by name : %.3lfsec\n", (double)(end - start) / CLOCKS_PER_SEC);

	/*for (int i = 0; i < 20000; i++)
	{
		printf("%s %s %s\n", s[i].number, s[i].name, s[i].address);
	}*/

	return 0;
}