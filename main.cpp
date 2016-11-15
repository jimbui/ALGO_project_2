// brought to you by:  john santoro , ryan arredondo , and jim bui.

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std ;

int inequalityCalc(int *partitionedArray , int threshold , int size)
{
    int score = 0 ;
    for (int l = 0 ; l < size ; l++) if (partitionedArray[l] != 0) score += pow((threshold - partitionedArray[l]) , 2) ;
    return score;
}

void naivePartition(vector<int> array , int threshold , int size)
{
    int partitionedArray[size] ; // sum of the partition.
    int inequalityArray[size] ; // for debugging.
    vector<int> sizeArray(size) ; // holds the count of elements in each partition.
    int i = size - 1; // iterates through partitionedArray which holds the sum; starts at back
    int j = size - 1; // iterates through array which is the initial array; starts at back
    int k = 0; // iterates up through inequalityArray holds the inequality score for all valid cases
    int l = 0; // iterates up through size array which holds the number of elements in each partition in order
    int check = 0 ; // partition check make sure it's below threshold
    int total = 1 ; // number of partitions; currently return value of final case
    int count = 0 ; // counts the elements in each partition of the array
    int stopFlag = 9999 ; // checks the inequality score for the current valid partition
    int minScore = 9999 ; // holds the best inequality score we've gotten so far

    ofstream output_file ;
  	output_file.open("output.txt" , fstream::app) ;

    for (int i = 0 ; i < size ; i++)
    {
        partitionedArray[i] = 0 ;
        inequalityArray[i] = 0 ;
        partitionedArray[0] += array[i] ;
    }
    
    sizeArray[0] = size ;
    // partitionedArray[i] = 0 ;
    while (partitionedArray[0] > threshold) // maximum partition size.
    {
        while (partitionedArray[i] < threshold)
        {
            check = partitionedArray[i] + array[j] ;
            count = sizeArray[i] + 1 ;

            if (check <= threshold)
            {
                partitionedArray[i] = check ;
                partitionedArray[0] -= array[j] ;
                sizeArray[i] = count ;
                sizeArray[0] -= 1 ;
            }

            else break ; // if a single value is greater than threshold.

            j--; // step back.
            
            // checks inequality score and stores it in an array.

            if (partitionedArray[0] <= threshold)
            {
                stopFlag = inequalityCalc(partitionedArray , threshold , size) ;
                if (stopFlag < minScore){
                    inequalityArray[k] = stopFlag;
                    minScore = stopFlag;
                    k++;
                }else{
                    j++;
                    partitionedArray[i] -= array[j];
                    partitionedArray[0] += array[j];
                    sizeArray[i] -= 1;
                    sizeArray[0] += 1;
                    break;
                }
            }
        }
        total++;
        l++;
        i--;
    }
    
    output_file << "Total: " << total;
    for(int i = 0; i < size; i++){
        if(partitionedArray[i] != 0){
                    //Delete after we figure out all the bugs
            // cout << "Partitioned Array: " << partitionedArray[i] << endl;
            // cout << "Inequality Array: " << inequalityArray[i] << endl;
            
            //This is suppose to keep track of all the elements in out most optimal partition
            output_file << " " << sizeArray[i];// << endl;
        }
    }
    cout << endl;

    output_file << "hello world.\n" ;
    output_file.close() ;
}

int main() 
{
	std::cout << " \n" << "    [+] starting program." << " \n\n" ;

	ifstream input_file("input.txt") ; // open the text file.

	remove("output.txt") ; // clears the data file.

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

			/*

			// this just prints the array.

			std::cout << "        " ;

			for (int j = 0 ; j < data_count ; j++) {
				std::cout << values_array[j] << " " ;
			}

			cout << endl << endl;
	
			*/

			naivePartition(values_array , max_partition_size , data_count) ;

			std::cout << " \n\n" ;
		}

		input_file.close() ;
	}

	else std::cout << "    [-] input.txt could not be read." << " \n\n" ;

	std::cout << "    [-] ending program." << " \n\n" ;
	cin.get() ;
}
