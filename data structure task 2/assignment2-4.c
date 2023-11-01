#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAX_SIZE 100
#define True 1
#define False 0

typedef int Bool;
typedef struct
{
  char stackarr[MAX_SIZE];
  int top;
} Stack;

void push(Stack *s, char value);
char pop(Stack *s);
char peek(Stack *s);
Bool isEmpty(Stack *s);
Bool isFull(Stack *s);
Bool isOperator(char c);
int Priority(char c);
void InfixtoPostfix(char *infix, char *postfix);
double Evaluate(char *postfix);
void reverse(char *arr);
void Check_Error(char *infix);

int main(void)
{
  char infix[MAX_SIZE];
  char postfix[MAX_SIZE];

  fgets(infix, MAX_SIZE, stdin);

  Check_Error(infix);

  InfixtoPostfix(infix, postfix);

  double result = Evaluate(postfix);
  printf("= %g\n", result);

  return 0;
}

void push(Stack *s, char value)
{
  if (s->top == MAX_SIZE - 1)
  {
    printf("스택에 자리가 없습니다.\n");
    exit(1);
  }
  s->top++;
  s->stackarr[s->top] = value;
}

char pop(Stack *s)
{
  if (s->top == -1)
  {
    printf("스택에 요소가 없습니다.\n");
    exit(1);
  }
  return (s->stackarr[s->top--]);
}

char peek(Stack *s)
{
  if (s->top == -1)
  {
    printf("스택에 요소가 없습니다.\n");
    exit(1);
  }
  return (s->stackarr[s->top]);
}

Bool isEmpty(Stack *s)
{
  if (s->top == -1)
    return True;
  else
    return False;
}

Bool isFull(Stack *s)
{
  if (s->top == MAX_SIZE - 1)
    return True;
  else
    return False;
}

Bool isOperator(char c)
{
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^')
    return True;
  else
    return False;
}

int Priority(char c)
{
  switch (c)
  {
  case '+':
  case '-':
    return 1;
    break;
  case '*':
  case '/':
    return 2;
    break;
  case '^':
    return 3;
    break;
  default:
    return 0;
    break;
  }
}

void InfixtoPostfix(char *infix, char *postfix)
{
  char temp;
  Stack stack;
  stack.top = -1;
  int len = strlen(infix) - 1;
  int index = 0;
  for (int i = 0; i < len; i++)
  {
    temp = infix[i];
    if (isdigit(temp) || temp == '.')
    {
      while (isdigit(infix[i]) || infix[i] == '.')
      {
        postfix[index++] = infix[i++];
      }
      i--;
      postfix[index++] = ' ';
    }
    else if (isOperator(temp))
    {
      if (temp == '(')
        push(&stack, temp);
      else if (temp == ')')
      {
        while (stack.top != -1 && peek(&stack) != '(')
        {
          postfix[index++] = pop(&stack);
          postfix[index++] = ' ';
        }
        pop(&stack);
      }
      else if (temp == '+' || temp == '-' || temp == '/')
      {
        while (stack.top != -1 && peek(&stack) != '(' && Priority(peek(&stack)) >= Priority(temp))
        {
          postfix[index++] = pop(&stack);
          postfix[index++] = ' ';
        }
        push(&stack, temp);
      }
      else
      {
        if (infix[i + 1] == '*')
        {
          while (stack.top != -1 && Priority(peek(&stack)) > Priority('^'))
          {
            postfix[index++] = pop(&stack);
            postfix[index++] = ' ';
          }
          push(&stack, '^');
          i++;
        }
        else
        {
          while (stack.top != -1 && Priority(peek(&stack)) >= Priority(temp))
          {
            postfix[index++] = pop(&stack);
            postfix[index++] = ' ';
          }
          push(&stack, temp);
        }
      }
    }
  }
  while (isEmpty(&stack) == False)
  {
    postfix[index++] = pop(&stack);
    postfix[index++] = ' ';
  }
  postfix[index] = '\0';
}

double Evaluate(char *postfix)
{
  Stack stack;
  stack.top = -1;
  double operand1, operand2;
  double answer;
  for (int i = 0; postfix[i] != '\0'; i++)
  {
    if (isdigit(postfix[i]) || postfix[i] == '.')
    {
      while (isdigit(postfix[i]) || postfix[i] == '.')
      {
        push(&stack, postfix[i]);
        i++;
      }
      push(&stack, ' ');
    }
    else if (isOperator(postfix[i]))
    {
      char temp_f[20];
      char temp;
      int count = 0;

      pop(&stack);
      temp = pop(&stack);
      while (temp != ' ')
      {
        temp_f[count++] = temp;
        temp = pop(&stack);
      }
      temp_f[count] = '\0';
      reverse(temp_f);
      operand1 = atof(temp_f);

      count = 0;
      temp = pop(&stack);
      while (stack.top != -1 && temp != ' ')
      {
        temp_f[count++] = temp;
        temp = pop(&stack);
      }
      if (isEmpty(&stack))
        temp_f[count++] = temp;
      temp_f[count] = '\0';

      reverse(temp_f);
      operand2 = atof(temp_f);

      switch (postfix[i])
      {
      case '+':
        answer = operand2 + operand1;
        break;
      case '-':
        answer = operand2 - operand1;
        break;
      case '*':
        answer = operand2 * operand1;
        break;
      case '/':
        answer = operand2 / operand1;
        break;
      case '^':
        if (postfix[i + 2] == '^')
        {
          double operand3;
          count = 0;
          temp = pop(&stack);
          while (stack.top != -1 && temp != ' ')
          {
            temp_f[count++] = temp;
            temp = pop(&stack);
          }
          if (isEmpty(&stack))
            temp_f[count++] = temp;
          temp_f[count] = '\0';

          reverse(temp_f);
          operand3 = atof(temp_f);
          answer = pow(operand2, operand1);
          answer = pow(operand3, answer);
          i += 2;
        }
        else
        {
          answer = pow(operand2, operand1);
          break;
        }
      }
      char answer_char[20];
      sprintf(answer_char, "%lf", answer);

      push(&stack, ' ');
      for (int j = 0; answer_char[j] != '\0'; j++)
      {
        push(&stack, answer_char[j]);
      }
      push(&stack, ' ');
    }
  }

  int count = 0;
  char result[20];
  if (peek(&stack) == ' ')
    pop(&stack);
  char temp = pop(&stack);
  while (stack.top != -1)
  {
    result[count++] = temp;
    temp = pop(&stack);
  }
  result[count++] = temp;
  result[count] = '\0';
  reverse(result);
  return (atof(result));
}

void reverse(char *arr)
{
  char temp;
  int len = strlen(arr);
  for (int i = 0; i < len / 2; i++)
  {
    temp = arr[i];
    arr[i] = arr[len - i - 1];
    arr[len - i - 1] = temp;
  }
}

void Check_Error(char *infix)
{
  int num_bracket = 0;
  int errorplace;
  for (int i = 0; infix[i] != '\0'; i++)
  {
    if (infix[i] == '(')
      num_bracket++;
    else if (infix[i] == ')')
      num_bracket--;
    if (num_bracket < 0)
    {
      for (int j = 0; j < i; j++)
        printf(" ");
      printf("^ 이 자리에 오류가 있습니다.\n");
      exit(1);
    }
  }

  if (num_bracket != 0)
  {
    errorplace = strlen(infix) - num_bracket;
    for (int i = 0; i < errorplace; i++)
      printf(" ");
    printf("^ 이 자리에 오류가 있습니다.\n");
    exit(1);
  }

  errorplace = 0;
  int check_oper = 0;
  int check_mul = 0;
  int check_bracket = 0;
  for (int i = 0; infix[i] != '\0'; i++)
  {

    if (isOperator(infix[i]) && infix[i] != '(')
    {
      if (check_oper == 1)
      {
        if (check_mul == 1 && infix[i] == '*')
          continue;
        else if (check_bracket == 1)
          continue;
        else
        {
          errorplace = i;
          break;
        }
      }
    }

    if (infix[i] == ')')
      check_bracket = 1;
    else if (isOperator(infix[i]) && infix[i] != ')')
      check_bracket = 0;
    if (infix[i] == '*')
      check_mul = 1;
    else if (isOperator(infix[i]) && infix[i] != '*')
      check_mul = 0;
    if (isdigit(infix[i]) || infix[i] == ')')
      check_oper = 0;
    else if (isOperator(infix[i]))
      check_oper = 1;
  }

  if (errorplace != 0)
  {
    for (int i = 0; i < errorplace; i++)
      printf(" ");
    printf("^ 이 자리에 오류가 있습니다.\n");
    exit(1);
  }

  errorplace = 0;
  int check_digit = 0;
  for (int i = 0; infix[i] != '\0'; i++)
  {
    if (isdigit(infix[i]) && i != 0)
    {
      if (infix[i - 1] == ' ' && check_digit == 1)
      {
        errorplace = i;
        break;
      }
    }
    if (!isdigit(infix[i]) && infix[i] != ' ')
      check_digit = 0;
    if (isdigit(infix[i]))
      check_digit = 1;
  }
  if (errorplace != 0)
  {
    for (int i = 0; i < errorplace - 1; i++)
      printf(" ");
    printf("^ 이 자리에 오류가 있습니다.\n");
    exit(1);
  }

  errorplace = 0;
  check_mul = 0;
  for (int i = 0; infix[i] != '\0'; i++)
  {
    if (infix[i] == '*' && check_mul == 1 && infix[i - 1] != '*')
    {
      errorplace = i;
      break;
    }
    if (isdigit(infix[i]))
      check_mul = 0;
    if (infix[i] == '*')
      check_mul = 1;
  }
  if (errorplace != 0)
  {
    for (int i = 0; i < errorplace - 1; i++)
      printf(" ");
    printf("^ 이 자리에 오류가 있습니다.\n");
    exit(1);
  }
}