#include <iostream>
#include <fstream>
#include <vector>

using namespace std ;

int main() {
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

			std::cout << " \n\n" ;
		}

		input_file.close() ;
	}

	else std::cout << "    [-] input.txt could not be read." << " \n\n" ;

	std::cout << "    [-] ending program." << " \n\n" ;
	cin.get() ;
}