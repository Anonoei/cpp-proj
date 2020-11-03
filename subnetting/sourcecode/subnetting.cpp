#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

// Variables for user input
vector<int> inputBytes;

int intCIDR = 0;

// Variables for functions
int index = 0;
string sIPv4 = "";
string HostBits;


// variables for displaying / calculating
int bitClass = 0;
int intOctet = 0;
int bitValue = 0;
vector<int> NetworkBytes;
int intNetwork = 0;
int intFirst = 0;
int intLast = 0;
int intBroadcast = 0;
int intNext = 0;
long intHostNum = 0;
int intNetNum = 0;
int intSMaskNum = 0;



int inputValidation(void);
void calcLogic(void);
void calcClass(void);
void calcBitValue(void);
void calcNetwork(void);
void calcFirst(void);
void calcLast(void);
void calcBroadcast(void);
void calcNext(void);
void calcHostNum(void);
void calcNetNum(void);
void calcSMask(void);

void printValue(int);

int main()
{
	int usrInput = 0;

	while (1)
	{
		while (index <= 5)
		{
			
			cout << "\t============================================================" << endl;
			cout << "\t=    S U B N E T T I N G / I P V 4 / C A L C U L A T O R   =" << endl;
			cout << "\t============================================================" << endl;
			cout << "\tEnter your IPv4 Address: (192 - 168 - 0 - 1 / 24)" << endl;
			cout << "Current Address:\t" << sIPv4 << "\n" << endl;
			

			if (index == 0)
			{
				cout << "First Byte: (192): ";
				inputBytes.push_back(inputValidation());
			}
			else if (index == 1)
			{
				cout << "Second Byte: (168): ";
				inputBytes.push_back(inputValidation());
			}
			else if (index == 2)
			{
				cout << "Third Byte: (0): ";
				inputBytes.push_back(inputValidation());
			}
			else if (index == 3)
			{
				cout << "Fourth Byte: (1): ";
				inputBytes.push_back(inputValidation());
			}
			else if (index == 4)
			{
				cout << "CIDR value: (/24) ";
				intCIDR = inputValidation();
			}
			else if (index == 5)
			{
				calcLogic();
				system("pause");
				index = 0;
			}
			else
			{
				cerr << "Something went horribly wrong!" << endl;
				return 1;
			}

			system("cls");
		}	//	END NESTED WHILE LOOP

		
	}

	return 0;
}	// END MAIN


int inputValidation(void)
{
	index++;
	int choice;
	cin >> setw(1) >> choice;


	while (!cin.good())	// error check
	{
		std::cout << "Invalid Input! Try again." << endl;

		//	clear stream
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		std::cout << "Enter your byte again." << endl;
		cin >> setw(1) >> choice;

	}
	//clear stream
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	if (index == 1)
	{
		sIPv4 = std::to_string(choice);
	}
	else if (index == 5)
	{
		sIPv4 = sIPv4 + "/" + std::to_string(choice);
	}
	else
	{
		sIPv4 = sIPv4 + "." + std::to_string(choice);
	}

	return choice;

}	// end of getUsrChoice


void calcLogic(void)
{
	calcClass();
	calcBitValue();
	calcNetwork();
	calcFirst();
	calcLast();
	calcBroadcast();
	calcNext();
	calcHostNum();
	calcNetNum();
	calcSMask();

}	//	END CALC LOGIC


void printValue(int j)
{
	

	for (unsigned int i = 0; i < NetworkBytes.size(); i++)
	{
		if (i == (NetworkBytes.size()) - 1)
		{
			cout << NetworkBytes.at(i);
		}
		else
		{
			cout << NetworkBytes.at(i) << ".";
		}
	}

	if (j > 0)
	{
		NetworkBytes.pop_back();
		j--;
	}
	NetworkBytes.pop_back();

	return;
}


void calcClass(void)
{
	int byteOne = inputBytes.at(0);
	if (byteOne >= 0 && byteOne <= 127)	//	if class is A
	{
		bitClass = 8;
	}
	else if (byteOne >= 128 && byteOne <= 191)	// if class is B
	{
		bitClass = 16;
	}
	else if (byteOne >= 192 && byteOne <= 223)	// if class is C
	{
		bitClass = 24;
	}
	else if (byteOne >= 224 && byteOne <= 239)	// if class is D
	{
		bitClass = 4;
	}
	else if (byteOne >= 240 && byteOne <= 255)	//	if class is E
	{
		bitClass = 2;
	}
	else
	{
		cerr << "Invalid First Octet \"" << byteOne << "\"" << endl;
	}
	return;

}	//	END CALC CLASS

void calcBitValue(void)
{
	if (intCIDR == 1 || intCIDR == 9 || intCIDR == 17 || intCIDR == 25)
	{
		bitValue = 128;
	}
	else if (intCIDR == 2 || intCIDR == 10 || intCIDR == 18 || intCIDR == 26)
	{
		bitValue = 64;
	}
	else if (intCIDR == 3 || intCIDR == 11 || intCIDR == 19 || intCIDR == 27)
	{
		bitValue = 32;
	}
	else if (intCIDR == 4 || intCIDR == 12 || intCIDR == 20 || intCIDR == 28)
	{
		bitValue = 16;
	}
	else if (intCIDR == 5 || intCIDR == 13 || intCIDR == 21 || intCIDR == 29)
	{
		bitValue = 8;
	}
	else if (intCIDR == 6 || intCIDR == 14 || intCIDR == 22 || intCIDR == 30)
	{
		bitValue = 4;
	}
	else if (intCIDR == 7 || intCIDR == 15 || intCIDR == 23 || intCIDR == 31)
	{
		bitValue = 2;
	}
	else if (intCIDR == 8 || intCIDR == 16 || intCIDR == 24 || intCIDR == 32)
	{
		bitValue = 1;
	}
	else
	{
		cerr << "Invalid CIDR value \"" << intCIDR << "\"" << endl;
	}


	if (intCIDR >= 1)
	{
		NetworkBytes.push_back(inputBytes.at(0));
		intOctet = 0;
	}
	if (intCIDR >= 9)
	{
		NetworkBytes.push_back(inputBytes.at(1));
		intOctet = 1;
	}
	if (intCIDR >= 17)
	{
		NetworkBytes.push_back(inputBytes.at(2));
		intOctet = 2;
	}
	if (intCIDR >= 25)
	{
		NetworkBytes.push_back(inputBytes.at(3));
		intOctet = 3;
	}

	return;


}	//	END CALC Bit Value

void calcNetwork(void)
{

	


	int i = 0;
	unsigned int j = 0;
	//	Networks increment by the bit value
	if (bitValue >= inputBytes.at(intOctet))
	{
		intNetwork = 0;
	}
	else
	{
		for (i = 1; bitValue * i <= inputBytes.at(intOctet); i++)
		{
			intNetwork = bitValue * (i);
		}
	}

	NetworkBytes.pop_back();
	
	NetworkBytes.push_back(intNetwork);

	for (j = 0; NetworkBytes.size() < 4; j++)
	{
		NetworkBytes.push_back(0);
	}
	
	cout << "N value of:\t.\tN. ";

	printValue(j);

	cout << "/" << intCIDR << endl;

	NetworkBytes.pop_back();

	return;

}

void calcFirst(void)
{
	intFirst = intNetwork + 1;
	unsigned int j;

	
	if (NetworkBytes.size() < 3)
	{
		NetworkBytes.push_back(intNetwork);

		for (j = 0; NetworkBytes.size() < 4; j++)
		{
			if (NetworkBytes.size() == 3)
			{
				NetworkBytes.push_back(1);
			}
			else
			{
				NetworkBytes.push_back(0);
			}
		}

	}
	else
	{
		NetworkBytes.push_back(intFirst);
	}

	cout << "F value of:\t.\tF. ";

	printValue(j);

	cout << endl;

	NetworkBytes.pop_back();

	return;
}

void calcLast(void)
{
	intLast = (intNetwork + bitValue) - 2;
	unsigned int j = 0;

	if (NetworkBytes.size() < 3)
	{
		NetworkBytes.push_back((intNetwork + bitValue) - 1);

		for (j = 0; NetworkBytes.size() < 4; j++)
		{
			if (NetworkBytes.size() == 3)
			{
				NetworkBytes.push_back(255 - 1);
			}
			else
			{
				NetworkBytes.push_back(255);
			}
		}

	}
	else
	{ 
		NetworkBytes.push_back(intLast);
	}

	cout << "L value of:\t.\tL. ";

	printValue(j);

	cout << endl;

	NetworkBytes.pop_back();

	return;
}

void calcBroadcast(void)
{
	intBroadcast = (intNetwork + bitValue) - 1;
	unsigned int j = 0;

	if (NetworkBytes.size() < 3)
	{
		NetworkBytes.push_back(intBroadcast);

		for (j = 0; NetworkBytes.size() < 4; j++)
		{
			NetworkBytes.push_back(255);
		}

	}
	else
	{
		NetworkBytes.push_back(intBroadcast);
	}

	cout << "B value of:\t.\tB. ";

	printValue(j);

	cout << endl;

	NetworkBytes.pop_back();

	return;
}

void calcNext(void)
{
	unsigned int j = 0;

	intNext = (intNetwork + bitValue);

	if (NetworkBytes.size() < 3)
	{
		NetworkBytes.push_back(intNext);

		for (j = 0; NetworkBytes.size() < 4; j++)
		{
				NetworkBytes.push_back(0);
		}
	}
	else
	{
		NetworkBytes.push_back(intNext);
	}

	cout << "X value of:\t.\tX. ";

	printValue(j);

	cout << endl;

	NetworkBytes.pop_back();

	return;
}

void calcHostNum(void)
{
	intHostNum = 32 - intCIDR;
	cout << "Host value of:\t.\t. " << (pow(2, intHostNum)) - 2 << endl;
	return;
}

void calcNetNum(void)
{
	intNetNum = intCIDR - bitClass;
	cout << "Network value of:\t. " << pow(2, intNetNum) << endl;
	return;
}

void calcSMask(void)
{
	int i = 0;
	unsigned int j = 0;
	while(!NetworkBytes.empty())
	{
		NetworkBytes.pop_back();
		i++;
	}

	while (bitClass > 8)
	{
		NetworkBytes.push_back(255);
		bitClass = bitClass / 8;
	}
	intSMaskNum = 256 - bitValue;

	NetworkBytes.push_back(intSMaskNum);

	for (j = 0; NetworkBytes.size() < 4; j++)
	{
		NetworkBytes.push_back(0);
	}

	cout << "S/M value of:\t.\t. ";

	printValue(j);

	cout << endl;

	return;
}