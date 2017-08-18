#include <sstream>
#include <iostream>
#include <string>
#include <vector>

void clearInput(std::istringstream &is)
{
	is.clear();
	is.ignore(INT_MAX, '\n');
}

void parseString(std::string &inputString, std::vector<int> &iVector, std::vector<double> &dVector) 
{
	
}

void test1()
{
	std::string sa[] = { "14","+","2","*","33" };
	std::string s1 = "14+2*33";
	std::string s2 = "(add(14,mul(2,33)))";

	std::string si = "(20.3+4.6*-16.32)";

	double d[] = { 20.3,4.6,-16.32 };
	int i[] = { -10,0,-1,1,-3,2,-11 };
}

void checkForLegalSymbol(std::istringstream &is, std::vector<double> &d1)
{
	is.clear();
	std::string legalChars = " +-*/";
	char c;
	is >> c;
	for (int i = 1; i < legalChars.length(); i++)
	{
		if (c == legalChars[i])
		{
			std::cout << c << '\n';
			d1.push_back(-i);
			return;
		}
	}
	std::cout << "FAIL!!!\n";
	clearInput(is);
}

void test2()
{
	std::vector<double> v1;
	std::string s1;
	std::getline(std::cin, s1);
	std::istringstream is(s1);
	std::string s2;
	double d1;
	//is.
	while (is.rdbuf()->in_avail() > 0)
	{
		is >> d1;
		if (is.fail())
		{
			checkForLegalSymbol(is,v1);
		}
		else
		{
			v1.push_back(d1);
		}
		//std::cout << "Here: " << d1 << '\n';
	}
	for (int i = 0; i < v1.size(); i++)
	{
		std::cout << i << ": " << v1[i] << '\n';
	}
}

int main()
{
	test2();

	system("PAUSE");
	return 0;
}