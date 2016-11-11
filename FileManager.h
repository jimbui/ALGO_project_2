#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <string>
#include <fstream>
// #include "Dynamic2DArray.h"

using namespace std;

static class FileManager
{
private:
public:
	/*static void SaveFile(string FileName, Dynamic2DArray<double> AIData)
	{
		ofstream saveFile(FileName);

		for (int i = 0; i < AIData.Length(0); i++)
		{
			for (int j = 0; j < AIData.Length(1); j++)
			{
				if (j < AIData.Length(1) - 1)
					saveFile << AIData.GetValue(j, i) << " ";
				else
					saveFile << AIData.GetValue(j, i);
			}

			saveFile << "\n";
		}

		saveFile.close();
	}*/

	// n and t are 1D arrays representing problem number; problems is 2D array representing each problem; i.e. problems[0][...] is some number to the first problem.
	static void LoadFile(string FileName, int* p, int** n, int** t, int*** problems)
	{
		ifstream loadFile(FileName);

		// int** problems;

		if (loadFile.is_open())
		{
			// Dynamic2DArray<double>* fData = new Dynamic2DArray<double>(-1, false, 1, 1);
			int input;

			int xPos = 0;
			int yPos = 0;

			int problemNum = 0;

			while (loadFile >> input)
			{
				// fData->ModifyOrInsertAt(xPos, yPos, input);

				char duh = loadFile.get();

				if (xPos == 0 && yPos == 0)		// p value
				{
					*problems = new int*[input];
					*p = input;
					*n = new int[input];
					*t = new int[input];
				}
				else if (yPos % 2 == 1)			// n and t values
				{
					if (xPos == 0)
					{
						(*n)[problemNum] = input;
						(*problems)[problemNum] = new int[input];
					}
					else
						(*t)[problemNum] = input;
				}
				else
					(*problems)[problemNum][xPos] = input;	// data values

				xPos++;

				if (duh == '\n')
				{
					xPos = 0;

					if (yPos % 2 == 0 && yPos != 0)
						problemNum++;

					yPos++;
				}
			}

			loadFile.close();
			// return problems;
		}
		else
		{
			cout << "We are unable to read the file." << endl;
			// return NULL;
		}
	}
};

#endif