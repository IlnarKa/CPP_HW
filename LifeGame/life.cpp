#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>

using namespace std;

const int defSize = 64;

int curRound;
int all = 0;
int cellNumber = 0;
int roundNumber = 0;
bool xSh = false;
bool ySh = false;
int xSize = defSize;
int ySize = defSize;
int born10 = 0;
int died10 = 0;

// to show, when cell live
struct cellLife
{
  bool present = false;
  bool future = false;
};

cellLife ** exist;

void ifYesBuild();

void ifNoBuild(int , int);

void reSize(int , int);

int get(int , int);

void roundGen();

void check();

int cellSum(int , int);

int main(int argc, char const *argv[])
{
  srand(time(0));
  exist = new cellLife *[defSize];
  for (int i = 0; i < defSize; i++)
    exist[i] = new cellLife[defSize];

  int height = 0 , weight = 0;
  cout << "Enter starting position height , weight and amount of rounds" << endl;
  cin >> height >> weight >> roundNumber;

  char ans = 'a';
  cout << "Do you wanna type al cells by yourself ? ( y / n )" << endl;
  while (!((ans == 'y' or ans == 'Y') or (ans == 'n' or ans == 'N')))
  {
    cin >> ans;
  }
  cout << "Enter amount of cells" << endl;
  cin >> cellNumber;

  // to create your own arrangment please yes , else it will create by random
  if (ans == 'y' or ans == 'Y')
  {
    ifYesBuild();
  }
  else
  {
    ifNoBuild(height , weight);
  }

  // to know , how many cells born and to build massive, where they will stay
  for (curRound = 1; curRound <= roundNumber; curRound++)
  {
    roundGen();
    if (curRound % 10 == 0)
    {
      cout << "From " << (curRound / 10 - 1) * 10 << " to " << (curRound / 10) * 10 << " born : " << born10 << endl;
      if (died10 != 0)
        cout << "From " << (curRound / 10 - 1) * 10 << " to " << (curRound / 10) * 10 << " average born/died rating : " << (double) born10 / died10 << endl;
      else
        cout << "From " << (curRound / 10 - 1) * 10 << " to " << (curRound / 10) * 10 << " average born/died rating : nonody died" << endl;
      born10 = 0;
      died10 = 0;
    }
  }
  cout << "In full round cells born: " << all << endl;

  int xCor = 0 , yCor = 0;
  int how = 0;
  cout << "How many points show in one block ? (Enter less than 100)"<<endl;
  cin >> how;

  cout << "Click 'l' (left), 'r' (right), 'd' (down), 'u' (up) to view another place in cells world, or click 'e' to end" << endl;
  while (true)
  {
    cout << "Now your position is: x=" << xCor << " y=" << yCor << endl;

    for (int i = yCor; i < yCor + how; i++)
    {
      for (int j = xCor; j < xCor + how; j++)
        //get 1 if there live cell, and 0 in other way
        cout << get(i, j);
      cout << endl;
    }

    ans = 'a';
    while (!(ans == 'l' or ans == 'r' or ans == 'd' or ans == 'u' or ans == 'L' or ans == 'R' or ans == 'D' or ans == 'U' or ans == 'e' or ans == 'E'))
      cin >> ans;
    switch (ans)
    {
    // to go down
    case 'd':
      yCor += how;
      break;
    case 'D':
      yCor += how;
      break;
    // to go right
    case 'r':
      xCor += how;
      break;
    case 'R':
      xCor += how;
      break;
    //to go left , if playground doesn't end
    case 'l':
      if (xCor >= how)
        xCor -= how;
      else
        cout << "You are now outside of cells world" << endl;
      break;
    case 'L':
      if (xCor >= how)
        xCor -= how;
      else
        cout << "You are now outside of cells world" << endl;
      break;
    //to go up , if playground doesn't end
    case 'u':
      if (yCor >= how)
        yCor -= how;
      else
        cout << "You are now outside of cells world" << endl;
      break;
    case 'U':
      if (yCor >= how)
        yCor -= how;
      else
        cout << "You are now outside of cells world" << endl;
      break;
    // to end game
    case 'e':
      return 0;
    case 'E':
      return 0;
    }
  }

  return 0;
}

void ifYesBuild()
{
  cout << "Type x and y of cell" << endl;
    int x = 0;
    int y = 0;
    for (int i = 0; i < cellNumber; i++)
    {
      cin >> x >> y;
      reSize(y + 1, x + 1);
      exist[y][x].present = true;
    }
}

void ifNoBuild(int height , int weight)
{
  srand(time(0));
  for (int i = 0; i < cellNumber; i++)
  {
    int x = rand() % height + 1;
    int y = rand() % weight + 1;
    reSize(x + 1, y + 1);
    exist[x][y].present = true;
  }
}

void reSize(int x, int y)
{
  if (x > xSize or ySize < y)
  {
    cellLife ** field = new cellLife *[xSize];
    for (int i = 0; i < xSize; i++)
    {
      field[i] = new cellLife[ySize];
      for (int j = 0; j < ySize; j++)
        field[i][j] = exist[i][j];
    }
    delete[] exist;
    int a = xSize;
    int b = ySize;
    while (x >= a)
      a *= 2;
    while (y >= b)
      b *= 2;
    // increase our world
    exist = new cellLife *[a];
    for (int i = 0; i < a; i++)
    {
      exist[i] = new cellLife[b];
      if (i < xSize)
        for (int j = 0; j < b; j++)
          exist[i][j] = field[i][j];
    }
    delete[] field;
    xSize = a;
    ySize = b;
  }
}

int get(int x, int y)
{
  // to get if there anu cell in this point
  if (xSize > x and x > 0)
  {
    if (ySize > y and y > 0)
    {
      return exist[x][y].present;
    }
    else return 0;
  }
  else return 0;
}

void roundGen()
{
  // to generate round
  xSh = 0;
  ySh = 0;
  check();
  for (int i = 0; i < xSize; i++)
    for (int j = 0; j < ySize; j++)
    {
      exist[i + xSh][j + ySh].present = exist[i][j].future;
      exist[i][j].future = false;
    }
}

void check()
{
  int sum = 0;
  for (int x = 0; x < xSize; x++)
    for (int y = 0; y < ySize; y++)
    {
      sum = cellSum(x, y);
      if (exist[x][y].present == true and sum == 3)
      {
        born10++;
        all++;
      }
      if (exist[x][y].present == 1 and (sum > 3 || sum < 2))
        died10++;
      // to know, if will live this cell in future
      if ((sum == 3) or ((sum == 2) and (exist[x][y].present == true)))
      {
        exist[x][y].future = true;
        if(x == 0)
          xSh = true;
        else xSh = false;
        if(y == 0)
          ySh = true;
        else ySh = false;
        int xNew , yNew;
        if(xSize - 1 == x)
          xNew = xSize * 2;
        else xNew = xSize;
        if(xSize - 1 == y)
          yNew = xSize * 2;
        else yNew = xSize;

        if (xNew != xSize or yNew != ySize)
          reSize(xNew, yNew);
      }

    }
}

int cellSum(int x, int y)
{
  //to get sum of cells near this point
  int  sum = get(x + 1, y - 1) + get(x + 1, y) + get(x + 1, y + 1) + get(x, y + 1) +get(x - 1, y - 1) + get(x - 1, y) + get(x - 1, y + 1) + get(x, y - 1);
  return sum;
}
