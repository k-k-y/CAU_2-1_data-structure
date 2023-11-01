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

int partition(Student *arr, int left, int right, char *check)
{
	Student pivot;
	int low, high;

	low = left;
	high = right + 1;
	pivot = arr[left];

	if (strcmp(check, "number") == 0)
	{
		do
		{
			do
			{
				low++;
			} while (low <= right && strcmp(arr[low].number, pivot.number) < 0);
			do
			{
				high--;
			} while (high >= left && strcmp(arr[high].number, pivot.number) > 0);
			if (low < high)
				swap(&arr[low], &arr[high]);
		} while (low < high);

		swap(&arr[left], &arr[high]);
		return high;
	}
	else if (strcmp(check, "name") == 0)
	{
		do
		{
			do
			{
				low++;
			} while (low <= right && strcmp(arr[low].name, pivot.name) < 0);
			do
			{
				high--;
			} while (high >= left && strcmp(arr[high].name, pivot.name) > 0);
			if (low < high)
				swap(&arr[low], &arr[high]);
		} while (low < high);

		swap(&arr[left], &arr[high]);
		return high;
	}
	exit(1);
}

void quick_sort(Student *arr, int left, int right, char *check)
{
	if (left < right)
	{
		int q = partition(arr, left, right, check);
		quick_sort(arr, left, q - 1, check);
		quick_sort(arr, q + 1, right, check);
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
	fclose(fp);

	// for unchanging original array
	for (int i = 0; i < 20000; i++)
	{
		copy_s[i] = s[i];
	}

	printf("<C, quick sort>\n");
	// sort by number
	start = clock();
	quick_sort(copy_s, 0, 19999, "number");
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

	for (int i = 0; i < 20000; i++)
	{
		copy_s[i] = s[i];
	}

	// sort by name
	start = clock();
	quick_sort(copy_s, 0, 19999, "name"); // sorting by name
	end = clock();
	printf("sort by name : %.3lfsec\n", (double)(end - start) / CLOCKS_PER_SEC);

	// check sort by name
	if (check_sort(copy_s, 20000, "name") == 1)
		printf("ERROR!\n");
	else
		printf("sorting by name is good!\n");

	return 0;
}