#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

// Exhaustively iteratively search for the best partition set
void JohnsAlgorithm(vector<int> problem, vector<int>& partitions, vector<int> prefixSum, int offset, int& k, int n, int t)
{
	int partitionLevel = 1;  // Start at 1st partition and work right if current one is valid.
	// int sumLeftInequalityScores = 0;
	bool incrementFlag = true;
	
	// Memoization
	vector<int> partitionSums = vector<int>(k + 1); // O(k)

	while (incrementFlag)
	{
		if (incrementFlag && partitionLevel >= 1)
		{
			partitionSums[partitionLevel] = (int)pow(t - (prefixSum[partitions[offset + partitionLevel]] - prefixSum[partitions[offset + partitionLevel - 1]]), 2) +
				partitionSums[partitionLevel - 1];
			
			if (partitionLevel == k - 1)
				incrementFlag = false;

			if (incrementFlag)
				partitionLevel++;
		}
		else if (!incrementFlag)
		{
			partitions[partitionLevel]++;
		}

		if (partitionLevel < 1)  // Break if solution needs to be returned.
			break;
	}
}

// Defines leftmost location for all partitions, and returns the partition set
vector<int> RyansAlgorithm(vector<int> problem, vector<int> prefixSum, int& offset, int& k, int n, int t)
{
	vector<int> partitionSet(n + 2);  // Due to +1 offset
	int partEnd = n;
	offset = n;
	partitionSet[offset + 1] = n;  // Get the end of the partition set.

	for (int i = n - 1; i >= 0; i--)  // Iterate backwards through array to determine how many partitions there must be.
	{
		int partitionVal = prefixSum[partEnd] - prefixSum[i];

		if (partitionVal > t)
		{
			k++;
			i++;
			partitionSet[offset--] = i;
			partEnd = i;
		}
	}

	return partitionSet;
}

// O(n); get each prefix sum
vector<int> GetPrefixSums(vector<int> problem, int n)
{
	vector<int> prefixSums = vector<int>(n + 2);
	prefixSums[0] = 0;

	for (int i = 1; i <= n; i++)
		prefixSums[i] = prefixSums[i - 1] + problem[i - 1];  // i - 1 for problem b/c no offset exists.

	return prefixSums;
}

void TryProject2(vector<int> problem, int n, int t)
{
	// cout << "Here is project 2:  " << endl << endl;

	// for (int i = 0; i < 1; i++)
	// {
	/*int* problem = new int[7];

	problem[0] = 5;
	problem[1] = 2;
	problem[2] = 3;
	problem[3] = 4;
	problem[4] = 10;
	problem[5] = 5;
	problem[6] = 3;

	int n = 7;
	int t = 10;*/

	// cout << "Problem (" << i + 1 << ")" << endl;
	vector<int> prefixSums = GetPrefixSums(problem, n);

	// Get and print prefix sums.
	cout << "Prefix sums:  ";
	for (int i = 0; i <= n; i++)
	{
		cout << prefixSums[i] << " ";
	}
	cout << endl;

	// Get basic partitions.
	int k = 1;
	int offset = 0;
	vector<int>partitions = RyansAlgorithm(problem, prefixSums, offset, k, n, t);
	// Print array with basic partitioning.
	
	int curPart = 1;
	for (int i = 1; i <= n; i++)
	{
		cout << problem[i - 1] << " ";
		if (partitions[offset + curPart] == i)
		{
			cout << "|";
			curPart++;
		}
		else
			cout << " ";
		cout << " ";
	}

	cout << endl;

	// Partition array

	JohnsAlgorithm(problem, partitions, prefixSums, offset, k, n, t);
}

int main() 
{
	std::cout << " \n" << "    [+] starting program." << " \n\n" ;

	ifstream input_file("input.txt") ; // open the text file.

	if (input_file.is_open()) {
		std::cout << "    [+] input.txt has been opened." << " \n\n" ;

		int problem_count ; // how many problems there are.
		int data_count ; // how many values are in a set.
		int max_partition_size ; // max size of a set.

		input_file >> problem_count ;

		for (int i = 0 ; i < problem_count ; i++) {
			std::cout << "    [+] problem " << i + 1 << " \n\n" ;
			input_file >> data_count ;
			input_file >> max_partition_size ;
			std::vector<int> values_array(data_count) ; 

			// now we fill the array.

			for (int j = 0 ; j < data_count ; j++) {
				input_file >> values_array[j] ;
			}

			// values_array is now populated.

			// this just prints the array.

			std::cout << "        " ;

			for (int j = 0 ; j < data_count ; j++) {
				std::cout << values_array[j] << " " ;
			}

			cout << endl << endl;

			TryProject2(values_array, data_count, max_partition_size);

			std::cout << " \n\n" ;
		}

		input_file.close() ;
	}

	else std::cout << "    [-] input.txt could not be read." << " \n\n" ;

	std::cout << "    [-] ending program." << " \n\n" ;
	cin.get() ;
}