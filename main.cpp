
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

#if !defined(Disks) && !defined(Start) && !defined(Finish) //���� ��������: ���������� ������, ����� ���������� � ����� ��������� �������

	cout << "������� ���������� ������" << endl;
	cin >> AllDisksAmount;

	cout << "������� ����� ���������� �������" << endl;
	cin >> StartPosition;

	cout << "������� ����� ��������� �������" << endl;
	cin >> FinishPosition;

#else	//������������� ������������� ��������

	AllDisksAmount = Disks;
	StartPosition = Start;
	FinishPosition = Finish;

#endif

	unsigned long long IterationsAmount = pow(2, AllDisksAmount) - 1;	//���������� ���������� �������������� 2^x - 1

	cout << "���������� ������: " << AllDisksAmount << endl;
	cout << "����� ���������� �������: " << StartPosition << endl;
	cout << "����� ��������� �������: " << FinishPosition << endl;
	cout << "���������� �����: " << IterationsAmount << endl;

	auto start = chrono::high_resolution_clock::now();	// ������ ���������� ������� ��� �������

	unsigned short CurrentDiskNumber = 0;	//���������� ��� ������ ������ ������������� ������ �����
	unsigned short FromPositionNumber = 0;	//���������� ��� ������ ������ ������� � �������� ������ ���������� ����
	unsigned short ToPositionNumber = 0;	//���������� ��� ������ ������ ������� �� ������� ������ ���������� ����
	unsigned long long IterationNumber = 1;	//���������� �������� �������� ������ ��������������

	unsigned short FirstNumber;
	unsigned short SecondNumber;


	if (AllDisksAmount % 2 != 0) //�������� ��� 1
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
		cout << IterationNumber << ": ����������� ���� " << CurrentDiskNumber << " � " << FromPositionNumber << " �� " << ToPositionNumber << " ��������" << endl;
	#elif OUTPUT_MODE == 'M'
		cout << IterationNumber << ": " << CurrentDiskNumber << " � " << FromPositionNumber << " �� " << ToPositionNumber << endl;
	#elif OUTPUT_MODE == 'S'
		cout << IterationNumber << ": " << CurrentDiskNumber << FromPositionNumber << ToPositionNumber << endl;
	#elif OUTPUT_MODE == 'N'
		cout << CurrentDiskNumber << FromPositionNumber << ToPositionNumber << endl;
	#elif OUTPUT_MODE == 'C'

	#endif 



	for (IterationNumber = 2; IterationNumber <= IterationsAmount; IterationNumber++)
	{
		//-------------------------
		if (log2(IterationNumber) == floor(log2(IterationNumber)))	//���� ����� �������������� �������� 2^x �� ����� ����� ����� x + 1
		{
			CurrentDiskNumber = log2(IterationNumber) + 1;
		}
		else	//��������� ����� �������� � �������� ���� �� ������ ������ �������� (��� ������ ����� ��� ������ �������� �����)
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


		if (IterationNumber % 3 != 0) // ��������� �������� � 
		{
			if (IterationNumber % 3 == 1)	// � �� ��������
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
			else	// � ��������
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
		else // ����� �� ������ ���������
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
				cout << IterationNumber << ": ����������� ���� " << CurrentDiskNumber << " � " << FromPositionNumber << " �� " << ToPositionNumber << " ��������" << endl;
		#elif OUTPUT_MODE == 'M'
				cout << IterationNumber << ": " << CurrentDiskNumber << " � " << FromPositionNumber << " �� " << ToPositionNumber << endl;
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

	auto end = chrono::high_resolution_clock::now();	//����� ���������� ������� ��� �������
	chrono::duration<double> elapsed = end - start;  // ������� �� �������


	#if OUTPUT_MODE != 'C'

		SetConsoleTextAttribute(console, 7);
		cout << endl;
		cout << "���������� ������: " << AllDisksAmount << endl;
		cout << "����� ���������� �������: " << StartPosition << endl;
		cout << "����� ��������� �������: " << FinishPosition << endl;
		cout << "���������� �����: " << IterationsAmount << endl;

	#endif

	cout << endl << "����� ���������� ���������: " << elapsed.count() << endl;

	return 0;
}