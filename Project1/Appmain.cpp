#include <iostream>
#include "LargeNumber.h"
#include "time.h"
#define MYSTYLE 0
using namespace std;



int main(){
#if MYSTYLE
	int i=1,j;
	LargeNumber LagNumber[10];
	cout << "0:exit" << endl
		<< "1:Input data by person " << endl
		<< "2:Create data in random" << endl;
	cin >> i;
	cout << endl;
	while (i)
	{
		LagNumber[1].CreateLargeNumber(i);
		//LagNumber[1].ShowLargeNumber();
		LagNumber[2].CreateLargeNumber(i);
		//LagNumber[2].ShowLargeNumber();
		cout << endl;
		cout << "1:Addition,2:Substract,3:Multiply,4:Division,5:Input other LargeNumber,0:exit" << endl;
		cin >> j;
		if (j == 0)
		{
			return 0;
		}
		while (j&&j!=5)
		{
			double dur;
			clock_t start, end;
			switch (j)
			{
			case 1:
			{
					  start = clock();
					  LagNumber[3] = LagNumber[1] + LagNumber[2];
					  end = clock();
					  dur = (double)(end - start);
					  if (i == 1)
					  {
						  cout << '(';
						  LagNumber[1].ShowLargeNumber();
						  cout << ')';
						  cout << '+';
						  cout << '(';
						  LagNumber[2].ShowLargeNumber();
						  cout << ')';
						  cout << '=';
						  LagNumber[3].ShowLargeNumber();
						  cout << endl;
						  LagNumber[3].Destroy();
					  }
					  break;
			}
			case 2:
			{
					  start = clock();
					  LagNumber[4] = LagNumber[1] - LagNumber[2];
					  end = clock();
					  dur = (double)(end - start);
					  if (i == 1)
					  {
						  //cout << "substract result:" << endl;
						  cout << '(';
						  LagNumber[1].ShowLargeNumber();
						  cout << ')';
						  cout << '-';
						  cout << '(';
						  LagNumber[2].ShowLargeNumber();
						  cout << ')';
						  cout << '=';
						  LagNumber[4].ShowLargeNumber();
						  cout << endl;
						  LagNumber[4].Destroy();
					  }

					  break;
			}
			case 3:
			{
					  start = clock();
					  LagNumber[5] = LagNumber[1] * LagNumber[2];
					  end = clock();
					  dur = (double)(end - start);
					  //cout << "product result:" << endl;
					  if (i == 1)
					  {
						  cout << '(';
						  LagNumber[1].ShowLargeNumber();
						  cout << ')';
						  cout << 'x';
						  cout << '(';
						  LagNumber[2].ShowLargeNumber();
						  cout << ')';
						  cout << '=';
						  LagNumber[5].ShowLargeNumber();
						  cout << endl;
						  LagNumber[5].Destroy();
					  }					
					  break;
			}
			default:
			{
					   start = clock();
					   LagNumber[6] = LagNumber[1] / LagNumber[2];
					   end = clock();
					   dur = (double)(end - start);
					   if (i == 1)
					   {
						   dur = (double)(end - start);
						   //cout << "quotient result:" << endl;
						   cout << '(';
						   LagNumber[1].ShowLargeNumber();
						   cout << ')';
						   cout << '/';
						   cout << '(';
						   LagNumber[2].ShowLargeNumber();
						   cout << ')';
						   cout << '=';
						   LagNumber[6].ShowLargeNumber();
						   cout << endl;
						   LagNumber[6].Destroy();
					   }
					   break;
			}

			}
			cout << "Spend time:" << endl
				<< (dur / CLOCKS_PER_SEC)<<'s' << endl;
			cout << "1:Addition,2:Substract,3:Multiply,4:Division,5:Input other LargeNumber,0:exit" << endl;
			cin >> j;
			if (j == 0)
			{
				return 0;
			}
		}
		cout << endl;
		cout << "0:exit" << endl
			<< "1:Input data by person " << endl
			<< "2:Create data in random" << endl;
		cin >> i;
		cout << endl;
	}
#else
	char c;
	LargeNumber LagNumber[10];
	double dur;
	clock_t start, end;
	cout << "Input +,-,*,/" << endl;
	cin >> c;
	LagNumber[1].CreateLargeNumber(1);
	LagNumber[2].CreateLargeNumber(1);
	start = clock();
	if (c == '+')
	{
		LagNumber[3] = LagNumber[1] + LagNumber[2];
		cout << "addition result:" << endl;
		LagNumber[3].ShowLargeNumber();
		LagNumber[3].Destroy();
	}
	else if (c == '-')
	{
		LagNumber[4] = LagNumber[1] - LagNumber[2];	
		cout << "substract result:" << endl;
		LagNumber[4].ShowLargeNumber();
		LagNumber[4].Destroy();
	}
	else if (c == '*')
	{
		LagNumber[5] = LagNumber[1] * LagNumber[2];
		cout << "product result:" << endl;
		LagNumber[5].ShowLargeNumber();
		LagNumber[5].Destroy();
	}
	else
	{
		LagNumber[6] = LagNumber[1] / LagNumber[2];

		//LagNumber[6].ShowLargeNumber();
		LagNumber[6].Destroy();
	}
	end = clock();
	dur = (double)(end - start);
	//cout << endl<< "Spend time:" << endl
	//	<< (dur / CLOCKS_PER_SEC) << 's' << endl;
#endif

	system("pause");
	return 0;
}