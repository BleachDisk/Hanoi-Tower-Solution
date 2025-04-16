
#include <iostream>
#include <cmath>
#include <chrono>
#include<Windows.h>


using namespace std;

#define Disks 10;
#define Start 1;
#define Finish 2;
#define OUTPUT_MODE 'M'    // L-large, M-medium, S-small, N-numbers only, C-clear no output

int main()
{
	setlocale(LC_ALL, "Russian");
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	unsigned int AllDisksAmount;
	unsigned short StartPosition;
	unsigned short FinishPosition;

#if !defined(Disks) && !defined(Start) && !defined(Finish) //Enter values: number of disks, number of starting and number of ending rods

	cout << "Enter the number of disks" << endl;
	cin >> AllDisksAmount;

	cout << "Enter the starting rod number" << endl;
	cin >> StartPosition;

	cout << "Enter the end rod number" << endl;
	cin >> FinishPosition;

#else	//Using prepared values

	AllDisksAmount = Disks;
	StartPosition = Start;
	FinishPosition = Finish;

#endif

	unsigned long long IterationsAmount = pow(2, AllDisksAmount) - 1;	//Least number of shifts 2^x - 1

	cout << "Number of disks: " << AllDisksAmount << endl;
	cout << "Starting rod number: " << StartPosition << endl;
	cout << "End rod number: " << FinishPosition << endl;
	cout << "Number of moves: " << IterationsAmount << endl;

	auto start = chrono::high_resolution_clock::now();	// Starting the timer for measurements

	unsigned short CurrentDiskNumber = 0;	//Variable for recording the number of the disk currently being moved
	unsigned short FromPositionNumber = 0;	//Variable for recording the number of the rod FROM WHICH we are currently moving the disk
	unsigned short ToPositionNumber = 0;	//Variable for recording the number of the rod TO WHICH we are currently moving the disk
	unsigned long long IterationNumber = 1;	//Variable storing the value of the shift number

	unsigned short FirstNumber;
	unsigned short SecondNumber;


	if (AllDisksAmount % 2 != 0) //Values ​​for 1
	{
		CurrentDiskNumber = 1;
		FromPositionNumber = StartPosition;
		ToPositionNumber = FinishPosition;
		FirstNumber = FinishPosition;

		if (StartPosition == 1)
		{
			if (FinishPosition == 3)
			{
				SecondNumber = 2;
			}
			else if (FinishPosition == 2)
			{
				SecondNumber = 3;
			}
		}
		else if (FromPositionNumber == 2)
		{
			if (FinishPosition == 1)
			{
				SecondNumber = 3;
			}
			else if (FinishPosition == 3)
			{
				SecondNumber = 1;
			}
		}
		else if (FromPositionNumber == 3)
		{
			if (FinishPosition == 1)
			{
				SecondNumber = 2;
			}
			else if (FinishPosition == 2)
			{
				SecondNumber = 1;
			}
		}

	}
	else
	{
		CurrentDiskNumber = 1;
		FromPositionNumber = StartPosition;
		SecondNumber = FinishPosition;

		if (StartPosition == 1)
		{
			if (FinishPosition == 3)
			{
				ToPositionNumber = 2;
				FirstNumber = 2;
			}
			else if (FinishPosition == 2)
			{
				FirstNumber = 3;
				ToPositionNumber = 3;
			}
		}
		else if (FromPositionNumber == 2)
		{
			if (FinishPosition == 1)
			{
				FirstNumber = 3;
				ToPositionNumber = 3;
			}
			else if (FinishPosition == 3)
			{
				FirstNumber = 1;
				ToPositionNumber = 1;
			}
		}
		else if (FromPositionNumber == 3)
		{
			if (FinishPosition == 1)
			{
				FirstNumber = 2;
				ToPositionNumber = 2;
			}
			else if (FinishPosition == 2)
			{
				FirstNumber = 1;
				ToPositionNumber = 1;
			}
		}
	}

	#if OUTPUT_MODE != 'C'
		SetConsoleTextAttribute(console, 6);
		cout << endl;
	#endif

	#if OUTPUT_MODE == 'L'
		cout << IterationNumber << ": move disk " << CurrentDiskNumber << " from " << FromPositionNumber << " to " << ToPositionNumber << " rod" << endl;
	#elif OUTPUT_MODE == 'M'
		cout << IterationNumber << ": " << CurrentDiskNumber << " from " << FromPositionNumber << " to " << ToPositionNumber << endl;
	#elif OUTPUT_MODE == 'S'
		cout << IterationNumber << ": " << CurrentDiskNumber << FromPositionNumber << ToPositionNumber << endl;
	#elif OUTPUT_MODE == 'N'
		cout << CurrentDiskNumber << FromPositionNumber << ToPositionNumber << endl;
	#elif OUTPUT_MODE == 'C'

	#endif 



	for (IterationNumber = 2; IterationNumber <= IterationsAmount; IterationNumber++)
	{
		//-------------------------
		if (log2(IterationNumber) == floor(log2(IterationNumber)))	//If the number of the move is 2^x then the disk number is x + 1
		{
			CurrentDiskNumber = log2(IterationNumber) + 1;
		}
		else	//We check the number by dividing with remainder until we find the desired value (the larger the number, the more iterations are needed)
		{
			bool NoExit = true;
			int n = 1;
			do
			{
				if (IterationNumber % unsigned long long(pow(2, n)) == unsigned long long(pow(2, n - 1)))
				{
					CurrentDiskNumber = n;
					NoExit = false;
				}
				n++;

			} while (NoExit);
		}
		//-------------------------


		if (IterationNumber % 3 != 0) // starting rod and 
		{
			if (IterationNumber % 3 == 1)	// and not final
			{
				//NEW PART!!!!
				if ((IterationNumber % 2 == 1) || (static_cast<int>(round(sqrt(IterationNumber))) * static_cast<int>(round(sqrt(IterationNumber))) == IterationNumber))
				{
					FromPositionNumber = StartPosition;
					ToPositionNumber = FirstNumber;
				}
				else 
				{
					unsigned long long IterationNumberForCalculations = IterationNumber;
					bool Cycle = true;
					bool GoodNumber = false;
					do
					{
						if (IterationNumberForCalculations % 4 == 0)
						{
							IterationNumberForCalculations /= 4;
						}
						else
						{
							if (IterationNumberForCalculations % 2 == 0)
							{
								Cycle = false;
							}
							else
							{
								GoodNumber = true;
								Cycle = false;
							}
						}
					} while (Cycle);

					if (GoodNumber)
					{
						FromPositionNumber = StartPosition;
						ToPositionNumber = FirstNumber;
					}
					else
					{
						FromPositionNumber = FirstNumber;
						ToPositionNumber = StartPosition;
					}
				}
			}
			else	// and final
			{
				if (IterationNumber % 2 != 0)
				{
					FromPositionNumber = SecondNumber;
					ToPositionNumber = StartPosition;
				}
				else
				{
					unsigned long long IterationNumberForCalculations = IterationNumber;
					bool Cycle = true;
					bool GoodNumber = false;
					do
					{
						if (IterationNumberForCalculations % 4 == 0)
						{
							IterationNumberForCalculations /= 4;
						}
						else
						{
							if (IterationNumberForCalculations % 2 == 0)
							{
								Cycle = false;
							}
							else
							{
								GoodNumber = true;
								Cycle = false;
							}
						}
					} while (Cycle);

					if (GoodNumber)
					{
						FromPositionNumber = SecondNumber;
						ToPositionNumber = StartPosition;
					}
					else
					{
						FromPositionNumber = StartPosition;
						ToPositionNumber = SecondNumber;
					}
				}
			}
		}
		else //otherwise the starting one is not included
		{
			if ((IterationNumber % 2 == 1))
			{
				FromPositionNumber = FirstNumber;
				ToPositionNumber = SecondNumber;
			}
			else
			{
				unsigned long long IterationNumberForCalculations = IterationNumber;
				bool Cycle = true;
				bool GoodNumber = false;
				do
				{
					if (IterationNumberForCalculations % 4 == 0)
					{
						IterationNumberForCalculations /= 4;
					}
					else
					{
						if (IterationNumberForCalculations % 2 == 1)
						{
							Cycle = false;
						}
						else
						{
							GoodNumber = true;
							Cycle = false;
						}
					}
				} while (Cycle);

				if (GoodNumber)
				{
					FromPositionNumber = SecondNumber;
					ToPositionNumber = FirstNumber;

				}
				else
				{
					FromPositionNumber = FirstNumber;
					ToPositionNumber = SecondNumber;

				}
			}
		}

		#if OUTPUT_MODE != 'C'

			if (IterationNumber % 2 == 0)
			{
				SetConsoleTextAttribute(console, 5);
			}
			else
			{
				SetConsoleTextAttribute(console, 6);
			}

		#endif

		#if OUTPUT_MODE == 'L'
				cout << IterationNumber << ": move disk " << CurrentDiskNumber << " from " << FromPositionNumber << " to " << ToPositionNumber << " rodь" << endl;
		#elif OUTPUT_MODE == 'M'
				cout << IterationNumber << ": " << CurrentDiskNumber << " from " << FromPositionNumber << " to " << ToPositionNumber << endl;
		#elif OUTPUT_MODE == 'S'
				cout << IterationNumber << ": " << CurrentDiskNumber << FromPositionNumber << ToPositionNumber << endl;
		#elif OUTPUT_MODE == 'N'
				cout << CurrentDiskNumber << FromPositionNumber << ToPositionNumber << endl;
		#elif OUTPUT_MODE == 'C'

		#endif 


		#if OUTPUT_MODE != 'C'

			if (IterationNumber % 2 == 0)
			{
				cout << endl;
			}

		#endif
	}

	auto end = chrono::high_resolution_clock::now();	//End of execution of the timer for measurements
	chrono::duration<double> elapsed = end - start;  // Time difference


	#if OUTPUT_MODE != 'C'

		SetConsoleTextAttribute(console, 7);
		cout << endl;
		cout << "Number of disks: " << AllDisksAmount << endl;
		cout << "Starting rod number: " << StartPosition << endl;
		cout << "End rod number: " << FinishPosition << endl;
		cout << "Number of moves: " << IterationsAmount << endl;

	#endif

	cout << endl << "Program execution time: " << elapsed.count() << endl;

	return 0;
}