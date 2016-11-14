//
//  main.cpp
//  Array Partition
//
//  Created by Ryan Arredondo on 11/12/16.
//  Copyright © 2016 AppCoda. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

//Didn't feel like look up squareing function
int inequalityCalc(int *partitionedArray,int threshold, int size){
    int score = 0;
    for(int l = 0; l < size; l++){
        if(partitionedArray[l] != 0){
            score += (threshold - partitionedArray[l]) * (threshold - partitionedArray[l]);
            
        }
    }
    return score;
}

void naivePartition(int *array, int threshold, int size){
    int partitionedArray[size];
    int inequalityArray[size];
    vector<int> sizeArray (size);
    int sum = 0; // sum of defualt array
    int i = size - 1; //iterates through partitionedArray which holds the sum; starts at back
    int j = size - 1; //iterates through array which is the initial array; starts at back
    int k = 0; // iterates up through inequalityArray holds the inequality score for all valid cases
    int l = 0; //iterates up through size array which holds the number of elements in each partition in order
    int check = 0; //partition check make sure it's below threshold
    int total = 1; // number of partitions; currently return value of final case
    int count = 0; //counts the elements in each partition of the array
    int stopFlag = 9999; //checks the inequality score for the current valid partition
    int minScore = 9999; // holds the best inequality score we've gotten so far
    
    for(int i = 0; i < size; i++){
        partitionedArray[i] = 0;
        inequalityArray[i] = 0;
        sum += array[i];
    }
    
    sizeArray[0] = size;
    partitionedArray[0] = sum;
    partitionedArray[i] = 0;
    while(partitionedArray[0] > threshold){
        while(partitionedArray[i] < threshold){
            check = partitionedArray[i] + array[j];
            count= sizeArray[i] + 1;
            if(check <= threshold){
                partitionedArray[i] = check;
                partitionedArray[0] -= array[j];
                sizeArray[i] = count;
                sizeArray[0] -= 1;
            }else{
                break;
            }
            j--;
            //sizeArray[l] = count;
            //if(l+1 == sizeArray.size()){
             //   sizeArray.resize(sizeArray.size() * 2);
            //}
            
            //Checks Inequality score and stores it in an array
            if(partitionedArray[0] <= threshold){
                stopFlag = inequalityCalc(partitionedArray, threshold, size);
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
    
    cout << "Total: " << total;
    for(int i = 0; i < size; i++){
        if(partitionedArray[i] != 0){
                    //Delete after we figure out all the bugs
            //cout << "Partitioned Array: " << partitionedArray[i] << endl;
            //cout << "Inequality Array: " << inequalityArray[i] << endl;
            
            //This is suppose to keep track of all the elements in out most optimal partition
            cout << " " << sizeArray[i];// << endl;
        }
    }
    cout << endl;
}

int main() {
    // insert code here...
    
    //int n = 7;
    //int t = 10;
    //int arr[7] = {5,2,3,4,10,5,3};
    
    int n = 278;
    int t = 50;
    //int t = 15;
    int arr[278] = {5,6,4,6,6,4,4,8,8,6,3,5,11,2,4,8,10,3,9,4,10,3,4,12,5,4,4,4,8,7,4,3,4,8,3,2,6,6,5,8,8,5,8,3,4,7,3,10,4,3,11,4,5,8,3,4,4,3,2,6,13,3,5,5,3,5,5,3,9,2,8,3,5,7,3,2,6,8,6,4,6,4,5,5,6,6,5,5,7,6,6,3,3,11,8,4,7,5,3,7,3,6,5,3,2,7,7,3,4,4,9,3,3,4,4,11,3,3,4,4,7,3,5,8,4,6,5,7,4,6,4,10,6,5,12,4,4,6,4,5,6,3,4,3,9,4,6,5,7,6,4,5,9,5,3,4,6,4,3,4,6,7,5,5,4,6,3,3,4,3,4,8,8,3,3,10,5,3,4,11,5,6,5,4,7,5,5,5,4,3,6,10,3,3,7,4,3,3,3,5,10,3,4,6,5,10,7,3,3,5,5,6,8,5,3,5,10,9,3,5,6,4,6,5,5,4,5,5,8,3,9,3,5,3,5,7,8,5,6,5,6,4,5,5,3,5,3,5,5,8,6,5,6,5,2,4,6,3,8,3,4,5,11,3,4,8,3,4,8,4,4,8,6,4,7,5,4,7};
    
    //int arr[9] = {4,6,6,4,7,5,4,5,4};
    //int t = 40;
    //int n = 9;
    
    naivePartition(arr, t, n);
    return 0;
}
