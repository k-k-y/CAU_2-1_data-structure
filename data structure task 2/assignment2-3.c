
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int **Matrix;

Matrix createMatrix(int row, int column);
void randMatrix(Matrix *matrix, int start, int end);
Matrix createMatrixfromArray(int *arr, int row, int column);
Matrix resizeMatrix(Matrix *matrix, int row, int column);
Matrix addMatrix(Matrix x, Matrix y);
Matrix multiplyMatrix(Matrix x, Matrix y);
Matrix transposeMatrix(Matrix *matrix);
void printMatrix(Matrix matrix);

int main(void)
{
  Matrix a, b, e, f;
  int c[] = {1, 2, 3, 4, 5, 6, 7, 8};

  a = createMatrix(3, 3);
  randMatrix(&a, 1, 10);
  b = createMatrixfromArray(c, 2, 4);

  printf("a 행렬\n");
  printMatrix(a);

  printf("b 행렬\n");
  printMatrix(b);

  printf("b 행렬 전치\n");
  b = transposeMatrix(&b);
  printMatrix(b);

  b = resizeMatrix(&b, 3, 3);
  e = addMatrix(a, b);
  f = multiplyMatrix(a, b);

  printf("resize b 행렬\n");
  printMatrix(b);

  printf("e 행렬(a + b)\n");
  printMatrix(e);

  printf("f 행렬(a * b)\n");
  printMatrix(f);

  printf("e 행렬 전치\n");
  e = transposeMatrix(&e);
  printMatrix(e);

  free(a);
  free(b);
  free(e);
  free(f);

  return 0;
}

Matrix createMatrix(int row, int column)
{
  Matrix temp;
  temp = malloc(sizeof(int *) * (row + 1));
  for (int i = 0; i < row; i++)
    temp[i] = malloc(sizeof(int) * (column + 1));

  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
      temp[i][j] = 0;
    temp[i][column] = 'x';
  }
  temp[row] = NULL;

  return temp;
}

void randMatrix(Matrix *matrix, int start, int end)
{
  int row = 0;
  int column = 0;
  while ((*matrix)[row] != NULL)
  {
    while ((*matrix)[row][column] != 'x')
      column++;
    row++;
  }
  srand(time(NULL));
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
      (*matrix)[i][j] = (rand() % (end - start + 1)) + start;
    }
  }
}

Matrix createMatrixfromArray(int *arr, int row, int column)
{
  Matrix temp;
  temp = malloc(sizeof(int *) * (row + 1));
  for (int i = 0; i < row; i++)
    temp[i] = malloc(sizeof(int) * (column + 1));

  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
      temp[i][j] = arr[i * column + j];
    temp[i][column] = 'x';
  }
  temp[row] = NULL;

  return temp;
}

Matrix resizeMatrix(Matrix *matrix, int row, int column) M
{
  int col_m = 0;
  int row_m = 0;

  while ((*matrix)[row_m] != NULL)
  {
    while ((*matrix)[row_m][col_m] != 'x')
      col_m++;
    row_m++;
  }

  int *arr = malloc(sizeof(int) * (col_m * row_m + 1));
  for (int i = 0; i < row_m; i++)
    for (int j = 0; j < col_m; j++)
    {
      arr[i * col_m + j] = (*matrix)[i][j];
    }
  arr[col_m * row_m] = '\0';

  Matrix temp;
  temp = malloc(sizeof(int *) * (row + 1));
  for (int i = 0; i < row; i++)
    temp[i] = malloc(sizeof(int) * (column + 1));

  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
      temp[i][j] = 0;
    temp[i][column] = 'x';
  }
  temp[row] = NULL;
  int count = 0;
  for (int i = 0; i < row && arr[count] != '\0'; i++)
  {
    for (int j = 0; j < column && arr[count] != '\0'; j++)
    {
      temp[i][j] = arr[count++];
    }
  }

  free(*matrix);

  return temp;
}

Matrix addMatrix(Matrix a, Matrix b)
{
  int row_a = 0;
  int col_a = 0;
  int row_b = 0;
  int col_b = 0;
  while (a[row_a] != NULL) // 행렬 a와 b의 행과 열 값 세주기
  {
    while (a[row_a][col_a] != 'x')
      col_a++;
    row_a++;
  }
  while (b[row_b] != NULL)
  {
    while (b[row_b][col_b] != 'x')
      col_b++;
    row_b++;
  }

  if (row_a != row_b || col_a != col_b)
    return NULL; // a와 b가 same size가 아닐 경우, NULL return

  int row = row_a;
  int column = col_a;
  Matrix temp;
  temp = malloc(sizeof(int *) * (row + 1));
  for (int i = 0; i < row; i++)
    temp[i] = malloc(sizeof(int) * (column + 1));

  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
      temp[i][j] = a[i][j] + b[i][j]; // 덧셈 수행
    temp[i][column] = 'x';
  }
  temp[row] = NULL;

  return temp;
}

Matrix multiplyMatrix(Matrix a, Matrix b)
{
  int row_a = 0;
  int col_a = 0;
  int row_b = 0;
  int col_b = 0;
  while (a[row_a] != NULL) // 행렬 a와 b의 행과 열 값 세주기
  {
    while (a[row_a][col_a] != 'x')
      col_a++;
    row_a++;
  }
  while (b[row_b] != NULL)
  {
    while (b[row_b][col_b] != 'x')
      col_b++;
    row_b++;
  }

  if (col_a != row_b)
    return NULL; // a의 열값과 b의 행값이 다른 경우 NULL return

  Matrix temp;

  temp = malloc(sizeof(int *) * (row_a + 1));
  for (int i = 0; i < row_a; i++)
    temp[i] = malloc(sizeof(int) * (col_b + 1));

  for (int i = 0; i < row_a; i++)
    for (int j = 0; j < col_b; j++)
    {
      temp[i][j] = 0;
      temp[i][col_b] = 'x';
      for (int k = 0; k < row_b; k++)
        temp[i][j] += a[i][k] * b[k][j];
    }
  temp[row_a] = NULL;

  return temp;
}

Matrix transposeMatrix(Matrix *matrix)
{
  int row = 0;
  int column = 0;
  while ((*matrix)[row] != NULL)
  {
    while ((*matrix)[row][column] != 'x')
      column++;
    row++;
  }

  Matrix matrix_t;
  matrix_t = malloc(sizeof(int *) * (column + 1));
  for (int i = 0; i < column; i++)
    matrix_t[i] = malloc(sizeof(int) * (row + 1));

  for (int i = 0; i < column; i++)
  {
    for (int j = 0; j < row; j++)
      matrix_t[i][j] = (*matrix)[j][i];
    matrix_t[i][row] = 'x';
  }
  matrix_t[column] = NULL;

  free(*matrix);

  return matrix_t;
}

void printMatrix(Matrix matrix)
{
  int row = 0;
  int column = 0;
  if (matrix == NULL)
    printf("입력값이 잘못되었습니다~!~!~!~!\n");
  while (matrix[row] != NULL)
  {
    while (matrix[row][column] != 'x')
      column++;
    row++;
  }

  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
      printf("%d ", matrix[i][j]);
    printf("\n");
  }
  printf("\n");
}