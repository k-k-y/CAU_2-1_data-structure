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

void swap(Student *first, Student *second)
{
	Student temp;
	temp = *first;
	*first = *second;
	*second = temp;
}

void adjust(Student *arr, int root, int n, char *check)
{
	int child;
	Student temp, rootkey;
	temp = arr[root];
	rootkey = arr[root];
	child = 2 * root;
	if (strcmp(check, "number") == 0)
	{
		while (child <= n)
		{
			if (child < n && strcmp(arr[child].number, arr[child + 1].number) < 0)
			{
				child++;
			}
			if (strcmp(rootkey.number, arr[child].number) > 0)
				break;
			else
			{
				arr[child / 2] = arr[child];
				child *= 2;
			}
		}
		arr[child / 2] = temp;
	}
	else if (strcmp(check, "name") == 0)
	{
		while (child <= n)
		{
			if (child < n && strcmp(arr[child].name, arr[child + 1].name) < 0)
			{
				child++;
			}
			if (strcmp(rootkey.name, arr[child].name) > 0)
				break;
			else
			{
				arr[child / 2] = arr[child];
				child *= 2;
			}
		}
		arr[child / 2] = temp;
	}
}

void heap_sort(Student *arr, int n, char *check)
{
	for (int i = n / 2; i > 0; i--)
	{
		adjust(arr, i, n, check);
	}
	for (int i = n - 1; i > 0; i--)
	{
		swap(&arr[1], &arr[i + 1]);
		adjust(arr, 1, i, check);
	}
}

int check_sort(Student *arr, int n, char *check)
{
	if (strcmp(check, "number") == 0)
	{
		for (int i = 0; i < n - 1; i++)
		{
			if (strcmp(arr[i].number, arr[i + 1].number) > 0)
				return 1;
		}

		return 0;
	}
	else if (strcmp(check, "name") == 0)
	{
		for (int i = 0; i < n - 1; i++)
		{
			if (strcmp(arr[i].name, arr[i + 1].name) > 0)
				return 1;
		}

		return 0;
	}
	exit(1);
}

int main(void)
{
	FILE *fp;
	fp = fopen("student_information.txt", "r");
	char str[200];
	Student s[21000];
	Student copy_s[21000];
	int index;
	time_t start, end;

	for (int i = 1; i < 20001; i++) // heap_sort's start index is 1
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
	fclose(fp);

	for (int i = 1; i < 20001; i++)
	{
		copy_s[i] = s[i];
	}

	printf("<C, heap sort>\n");
	// sort by number
	start = clock();
	heap_sort(copy_s, 20000, "number"); // sorting by number
	end = clock();
	printf("sort by number : %.3lfsec\n", (double)(end - start) / CLOCKS_PER_SEC);

	// check sort by number
	if (check_sort(copy_s, 20000, "number") == 1)
	{
		printf("ERROR!\n");
	}
	else
	{
		printf("sorting by number is good!\n");
	}

	for (int i = 1; i < 20001; i++)
	{
		copy_s[i] = s[i];
	}

	// sort by name
	start = clock();
	heap_sort(copy_s, 20000, "name"); // sorting by name
	end = clock();
	printf("sort by name : %.3lfsec\n", (double)(end - start) / CLOCKS_PER_SEC);

	// check sort by name
	if (check_sort(copy_s, 20000, "name") == 1)
		printf("ERROR!\n");
	else
		printf("sorting by name is good!\n");

	return 0;
}