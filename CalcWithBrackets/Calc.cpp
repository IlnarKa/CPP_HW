#include <iostream>
#include <string>
#include <stack>

using namespace std;

int order (char);

int end();

void negative(stack <long long> &num);


void calculation (stack <long long> &numbers , stack <char> &signs);


int main()
{   string MathExpr;
    getline(cin , MathExpr);
    stack <long long> numbers;
    stack <char> signs;
    long long temp = 0;

    for (int index = 0; index < MathExpr.length(); index++)
    {
        char a = MathExpr[index];
        if (a == ' ') continue;
        else
          if (order(a) != 10)
          {
            switch (a)
            {
                case ')':
                    while (signs.top() != '(')   // Calculating, while don't see opening bracket
                        calculation(numbers, signs);
                    signs.pop();
                    break;
                case '(':
                    signs.push(a);
                    break;

                default:
                    while (!signs.empty() && order(signs.top()) >= order(a))
                        calculation(numbers, signs);
//Calculating,while we have any math signs and the previous sign has a more priority than new
                    signs.push(a);
              }
          }
        else
          if (!isdigit(a))
            end();
        else
          {
            temp = temp * 10 + a - '0';
//getting numbers from string
            if (MathExpr.length() == index + 1 || !isdigit(MathExpr[index + 1]))
              {
                numbers.push(temp);
                temp = 0;
              }
          }
    }
    while (!signs.empty())
      calculation(numbers, signs);

    if (numbers.size())
//we need to have one element,if it's correct,than we get true answer
        cout << numbers.top() << endl;
    else
        end();
    return 0;
}


int order (char Symbol)
{
// we get priority of each signs , if we get some extra mark , function return 10 and we get error
//i use this values (300 , 200 , 100 , 10) for a fun , there may be another numbers
    if (Symbol == '*' || Symbol == '/' || Symbol == '%') return 300;
    if (Symbol == '+' || Symbol == '-') return 200;
    if (Symbol == '(' || Symbol == ')') return 100;
    return 10;
}

int end()
{
// We output "Error" and end programm
  cout<<"Error"<<endl;
  exit(0);
}

void calculation (stack <long long> &numbers , stack <char> &signs)
{
  // if we have less than 2 elements or less than one sign we end programm
  if(numbers.size() < 2 || signs.size() < 1)
      end();

  char sign = signs.top();
  long long b = numbers.top();
    numbers.pop();
  long long a = numbers.top();
    numbers.pop();
  signs.pop();
//what operation need to do each sign
    switch (sign) {
        case '/':
            if (b == 0) end();
            numbers.push(a / b);
            break;
        case '%':
            if (b == 0) end();
            numbers.push(a % b);
            break;
        case '*':
            numbers.push(b * a);
            break;
        case '-':
            numbers.push(a - b);
            break;
        case '+':
            numbers.push(a + b);
            break;
        default:
            end();
    }
}
