//BLG 335E ANALYSIS OF ALGORITHMS 1 HOMEWORK 2
//Leminur Çelik
//150190085
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include "../include/heap.h"

using namespace std;
long int count_max_heapify = 0;
int count_build_max_heap = 0;
int count_heap_sort = 0;
int count_heap_insert = 0;
int count_heap_increase_key = 0;
int count_mean = 0;
int count_std = 0;
int count_median = 0;
int count_min = 0;
int count_max = 0;
int count_firstq = 0;
int count_thirdq = 0;

//---- HEAP FUNCTIONS ----//
Heap::Heap(){
    size = 0;
}
//Set heap size
void Heap::setSize(){
    size = heap.size();
}
//Return heap size
int Heap::getSize(){
    return size;
};
//To max heapify a subtree rooted with node i
void Heap::max_heapify(int i){
    count_max_heapify++;
    left = 2 * i + 1;//Initialize left child
    right = 2 * i + 2;//Initialize right child
    int largest = i;//Initalize largest as root
    //If left child is larger than root, initialize largest as left
    if(left <= size - 1 && heap[left] > heap[i]){
        largest = left;
    }
    //If right child is larger than largest, initialize largest as right
    if(right <= size - 1 && heap[right] > heap[largest]){
        largest = right;
    }
    //If largest is not root, swap root and largest 
    if(largest != i){
        swap(heap[i], heap[largest]);
        max_heapify(largest);//Recurse by sending largest as input to max_heapify function 
    }
}
//To build max heap
void Heap::build_max_heap(){
    count_build_max_heap++;
    for (int i = (size / 2); i >= 0; i--)
    {
        max_heapify(i);//Call max_heapify function for all interior nodes
    }
}
//Sort the heap into the array
void Heap::heap_sort(){
    count_heap_sort++;
    build_max_heap();//Build a heap
    for (int i = size-1; i > 0; i--)
    {
        swap(heap[0], heap[i]);//Remove the largest element from the heap and move it to the first position in the sorted array 
        size = size - 1;//Decrease size by 1
        max_heapify(0);//To heapify with root
    }
}
//Maintain heap structure bottom up
void Heap::heap_increase_key(int i){
    count_heap_increase_key++;
    parent = (i-1) / 2;//Initialize parent
    if(parent > 0){//If parent value is bigger than 0, check if i value in the heap is bigger than parent
        if(heap[i] > heap[parent]){//If i value is bigger than parent, swap i and parent
            swap(heap[i], heap[parent]);
            heap_increase_key(parent);//Recurse by sending parent as input to heap_increase_key function 
        }
    }
}
//Insert element into a heap
void Heap::heap_insert(double key){
    count_heap_insert++;
    heap.push_back(key);//Push key value into the heap
    size = heap.size();//Assign size to size of heap
    heap_increase_key(size - 1);//Call heap_increase_key function with input of size - 1 
}
//---- END HEAP FUNCTIONS ----//

//---- STATISTICS FUNCTIONS ----//
//Calculate mean
double Heap::calculate_mean(){
    count_mean++;
    double total = 0; //Initialize addition of the numbers in the heap to 0
    double mean; //Initialize mean variable
    for (int i = 0; i < size; i++)
    {
        total += heap[i];//Add the values in the heap
    }
    mean = total / size;//Divide the total value by the size of the heap
    return mean;//Return mean value
}
//Calculate standard deviation
double Heap::calculate_std(){
    count_std++;
    double mean = calculate_mean();//Call the mean function 
    double total = 0;//Initialize addition of the numbers in the heap to 0
    for (int i = 0; i < size; i++)
    {
        total += pow(heap[i] - mean, 2);//Square the values in the heap after subtracting it from the mean
    }
    return sqrt(total / (size - 1));//Return the square root of the total value divided by one less than the size
}
//Find the minimum value
double Heap::minimum(){
    count_min++;
    return heap[0];//Return the first element of heap after sorting the heap
}
//Calculate first quantile
double Heap::calculate_firstq(){
    count_firstq++;
    double quartile = double((0.25) * (size - 1));//The position of the value in the distribution
    double difference = heap[ceil(quartile)] - heap[floor(quartile)];//Difference between two values less than and bigger than quartile value
    double result = ((quartile - floor(quartile)) * difference) + heap[floor(quartile)];//Get the decimal part of quartile and multiply with difference and add less than quartile value
    return result;//Return result value
}
//Calculate median
double Heap::calculate_median(){
    count_median++;
    if(size %2 == 0){//If size is a factor of two, return the sum of the middle two values divided by two
        return (heap[size / 2] + heap[size / 2 - 1]) / 2;
    }
    else{//If the number is odd, return the middle value of the heap 
        return heap[((size + 1) / 2) - 1];
    }
}
//Calculate third quantile
double Heap::calculate_thirdq(){
    count_thirdq++;
    double quartile = double((0.75) * (size - 1));//The position of the value in the distribution
    double difference = heap[ceil(quartile)] - heap[floor(quartile)];//Difference between two values less than and bigger than quartile value
    double result = ((quartile - floor(quartile)) * difference) + heap[floor(quartile)];//Get the decimal part of quartile and multiply with difference and add less than quartile value
    return result;//Return result value
}
//Find the maximum value
double Heap::maximum(){
    count_max++;
    return heap[size-1];//Return the last element of heap after sorting the heap
}
//---- END STATISTICS FUNCTIONS ----//

int main(int argc, char **argv){
    string input = argv[1];//Get the input file from the command line
    auto t1 = clock();//Time starts
    int count;//Initialize how many properties will be in the input file
    string a_line, a_word;
    fstream file (input, ios::in);//Define the input file as file
    ofstream output("output.txt", ios::out);//Define the output file as output
    if(output.is_open()){//If the output is opened, write 
        if(file.is_open()){
            file >> count;//Read how many properties from file
            string array[count];//Create a string array with the size of count
            for (int i = 0; i < count; i++)
            {
                file >> array[i];//Put each property into the array
            }
            string line;//Initialize the line to read from the file
            file >> line;//Read the line from the file 
            //Read line by line from input file
            vector<string> v;
            stringstream ss(line);
            while(ss.good()){
                string substr;
                getline(ss, substr, ',');
                v.push_back(substr);
            } 
            Heap newHeap;//Create a newHeap from Heap class
            string feature = v[1];//Assign vector's first value to a feature
            vector<string> date_value;//Create a string vector to store date
            vector<string> time_value;//Create a string vector to store time
            while(!file.eof()){//Until it is reached the end of the file 
                string word;//Initialize the word to be given as add or print
                file >> word;//Read word from the file
                bool isSorted = false;
                if(word == "add"){//If the word is add, add the values of the desired property to the heap
                    //Read line by line from input file
                    vector<string> vec;
                    file >> a_line;
                    stringstream ss(a_line);
                    while(ss.good()){
                        string sub;
                        getline(ss, sub, ',');
                        vec.push_back(sub);
                    }
                    string date = vec[0];//The first value in the row is the date
                    string time = vec[1];//The second value in the row is the time
                    date_value.push_back(date);//Push dates to vector
                    time_value.push_back(time);//Push times to vector
                    //Send the values to heap according to the desired feature
                    if(feature == "gap"){
                        newHeap.heap_insert(stod(vec[2]));
                    } 
                    else if(feature == "grp"){
                        newHeap.heap_insert(stod(vec[3]));
                    }
                    else if(feature == "v"){
                        newHeap.heap_insert(stod(vec[4]));
                    }
                    else{
                        newHeap.heap_insert(stod(vec[5]));
                    }
                }
                else if(word == "print"){//If the word is print, print in the output file after finding the values in the desired property
                    string starting_date = date_value[0];//Assign the zeroth element of the date value vector to the starting date
                    string starting_time = time_value[0];//Assign the zeroth element of the time vector vector to the starting date
                    string latest_retrieved_date = date_value[newHeap.getSize() - 1];//Assign the last element of the date value vector to the latest retrieved date
                    string latest_retrieved_time = time_value[newHeap.getSize() - 1];//Assign the last element of the time value vector to the latest retrieved time
                    //Print the starting date, starting time, latest retrieved date and latest retrieved time into the output file
                    output << starting_date << "," << starting_time << "," << latest_retrieved_date << "," << latest_retrieved_time << ",";
                    for (int i = 0; i < count; i++){
                        if(array[i] == "mean"){//Call the calculate_mean function when it is wanted the mean to be calculated
                            double mean = newHeap.calculate_mean();
                            output << mean;
                            if((i+1) != count){
                                output << ",";
                            }
                        }
                        else if(array[i] == "std"){//Call the calculate_std function when it is wanted the standard deviation to be calculated
                            double std = newHeap.calculate_std();
                            output << std;
                            if((i+1) != count){
                                output << ",";
                            }
                        }
                        else if(array[i] == "min"){//Call the minimum function when it is wanted the minimum to be found
                           if(isSorted == false){
                                newHeap.heap_sort();//Sort the heap
                                newHeap.setSize();
                                isSorted = true;
                            }
                            double min = newHeap.minimum();
                            output << min;
                            if((i+1) != count){
                                output << ",";
                            }
                        }
                        else if(array[i] == "firstq"){//Call the calculate_firstq function when it is wanted the first quantile to be calculated
                            if(isSorted == false){
                                newHeap.heap_sort();//Sort the heap
                                newHeap.setSize();
                                isSorted = true;
                            }
                            double firstq = newHeap.calculate_firstq();
                            output << firstq;
                            if((i+1) != count){
                                output << ",";
                            }
                        }
                        else if(array[i] == "median"){//Call the calculate_median function when it is wanted the median to be calculated
                            if(isSorted == false){
                                newHeap.heap_sort();//Sort the heap
                                newHeap.setSize();
                                isSorted = true;
                            }
                            double median = newHeap.calculate_median();
                            output << median;
                            if((i+1) != count){
                                output << ",";
                            }
                        }
                        else if(array[i] == "thirdq"){//Call the calculate_thirdq function when it is wanted the third quantile to be calculated
                            if(isSorted == false){
                                newHeap.heap_sort();//Sort the heap
                                newHeap.setSize();
                                isSorted = true;
                            }
                            double thirdq = newHeap.calculate_thirdq();
                            output << thirdq;
                            if((i+1) != count){
                                output << ",";
                            }
                        }
                        else if(array[i] == "max"){//Call the maximum function when it is wanted the maximum to be found
                            if(isSorted == false){
                                newHeap.heap_sort();//Sort the heap
                                newHeap.setSize();
                                isSorted = true;
                            }
                            double max = newHeap.maximum();
                            output << max;
                            if((i+1) != count){
                                output << ",";
                            }
                        }
                    }
                    output << endl;
                }
            }
        }
        output.close();//Close the output file
    }
    else{
        cout << "Could not open the file" << endl; // If the file couldn't be opened, print the error message
    }
    cout << "Count max heapify:" << count_max_heapify << endl;
    cout << "Count build max heap:" << count_build_max_heap << endl;
    cout << "Count heap sort:" << count_heap_sort << endl;
    cout << "Count heap increase key:" << count_heap_increase_key << endl;
    cout << "Count heap insert:" << count_heap_insert << endl;
    cout << "Count mean:" << count_mean << endl;
    cout << "Count standard deviation:" << count_std << endl;
    cout << "Count median:" << count_median << endl;
    cout << "Count minimum:" << count_min << endl;
    cout << "Count maximum:" << count_max << endl;
    cout << "Count first quantile:" << count_firstq << endl;
    cout << "Count third quantile:" << count_thirdq << endl;

    auto t2 = clock();//Time stops
    cout << "Time: " << (double)(t2-t1)/CLOCKS_PER_SEC << endl;
}