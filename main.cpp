#include <iostream>
#include <time.h>
#include <algorithm>
#include <math.h>
#include <limits.h>

#include "FileManager.h"

#define MAXN 1000																				
#define MAXK 50	

using namespace std;

void print_books8_5(int s[], int start, int end)
{
	/* counter */
	for (int i = start; i <= end; i++)
		printf(" %d ", s[i]);

	printf("\n");
}

void reconstruct_partition8_5(int s[], int d[MAXN + 1][MAXK + 1], int n, int k)
{
	if (k == 1)
		print_books8_5(s, 1, n);
	else
	{
		reconstruct_partition8_5(s, d, d[n][k], k - 1);
		print_books8_5(s, d[n][k] + 1, n);
	}
}

void partition8_5(int s[], int n, int k)
{
	int m[MAXN + 1][MAXK + 1]; /* DP table for values */
	int d[MAXN + 1][MAXK + 1]; /* DP table for dividers */
	int p[MAXN + 1]; /* prefix sums array */

	int cost; /* test split cost */
	int i, j, x; /* counters */
	p[0] = 0; /* construct prefix sums */

	cout << "p[] = ";
	for (i = 1; i <= n; i++)
	{
		p[i] = p[i - 1] + s[i];
		cout << p[i] << " ";
	}
	cout << endl;

	for (i = 1; i <= n; i++)
		m[i][1] = p[i]; /* initialize boundaries */

	for (j = 1; j <= k; j++)
		m[1][j] = s[1];

	cout << "d[][] = " << endl;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= k; j++)
			cout << d[i][j] << " ";

		cout << endl;
	}
	cout << endl;
	
	for (i = 2; i <= n; i++) /* evaluate main recurrence */
	{
		for (j = 2; j <= k; j++)
		{
			m[i][j] = INT_MAX;

			for (x = 1; x <= (i - 1); x++)
			{
				cost = max(m[x][j - 1], p[i] - p[x]);

				if (m[i][j] > cost)
				{
					m[i][j] = cost;
					d[i][j] = x;

					cout << "d[][], m[][] = " << endl;
					for (int ii = 1; ii <= n; ii++)
					{
						for (int jj = 1; jj <= k; jj++)
							cout << d[ii][jj] << " ";

						cout << "\t\t";

						for (int jj = 1; jj <= k; jj++)
							cout << m[ii][jj] << " ";

						cout << endl;
					}
					cout << endl;
				}
			}
		}
	}

	reconstruct_partition8_5(s, d, n, k); /* print book partition */
}

// Call this in main.
void Example8_5()
{
	cout << "Running Example 8.5:  " << endl << endl;

	int n = 12, k = 4;

	/*cout << "Enter n-value:  ";
	cin >> n;
	while (cin.get() != '\n');

	n = min(n, MAXN);

	cout << "Enter k-value:  ";
	cin >> k;
	while (cin.get() != '\n');

	k = min(k, n);*/

	int valArray[MAXN + 1];

	srand(time(NULL));

	// Initialize the random array... values between 0 and 10000
	cout << "valArray[] = ";
	for (int i = 1; i <= n; i++)
	{
		valArray[i] = rand() % 10001;
		cout << valArray[i] << " ";
	}
	cout << endl;

	partition8_5(valArray, n, k);
}

int main()
{
	int *n, p, *t;
	int** problem;

	FileManager::LoadFile("input.txt", &p, &n, &t, &problem);

	cout << p << endl;

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (j == 0)
				cout << n[i] << " " << t[i] << endl;
			else
			{
				for (int k = 0; k < n[i]; k++)
					cout << problem[i][k] << " ";

				cout << endl;
			}
		}
	}

	std::cout << "\nhello world!\n\n";
	Example8_5();
	std::cout << "\nend program.\n\n";

	cin.get();
}

// End Example 8-5 -----------------------------------------------------------------------------