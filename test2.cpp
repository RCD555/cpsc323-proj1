#include <iostream>

using namespace std;

void putNChars(int n, char charOut);

int main()
{
	int num = 5;

	char ch = 'C';

	putNChars(num, ch);

	int argc = 5;
	cout << "You have entered " << argc << " arguments:" << "\n";

}

void putNChars(int n, char charOut)
{
	while (n--)
	{
		cout << charOut;
	}    // example line found in the test.cpp file
}