//BLG 335E ANALYSIS OF ALGORITHMS 1 HOMEWORK 1
//Leminur Çelik
//150190085
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
 
using namespace std;
int iterations = 0; // Create the global value iterations to calculate the number of partitionings
int swap_number = 0; // Create the global value swap_number to calculate the number of swaps

int partition(double array[], int low, int high){
    double pivot = array[high]; // Pivot is selected as the last element
    int i = low; // i is initialized as low value
    int j = low; // j is initialized as low value
    while(j >= i){ // j moves first
        if(array[i] <= pivot && array[j] <= pivot){ // Increment i and j if the ith and jth value of the array is less than pivot
            i++;
            j++;
        }
        if(array[j] > pivot){ // Increment j and swap ith and jth value of array if jth value of array is bigger than pivot
            j++;
            if(j == high){ // If j is equal to high value, swap ith and high value of the array and break while loop
                swap(array[i], array[high]);
                swap_number++;
                break;
            }
            swap(array[i], array[j]); 
            swap_number++;
            if(array[i] <= pivot){ // If ith value of the array is less and equalt to pivot, increment i
                i++;
            }
        }
        if(j == high){ // If j is equal to high value, swap ith and high value of the array and break while loop
            swap(array[i], array[high]);
            swap_number;
            break;
        }
    }
    return i; // Return i value
}
int partition_vector(vector<vector<string>> &books, int low, int high){
    double pivot = stod(books[high][3]); // Pivot is selected as the forth element of the books
    int i = low; // i is initialized as low value
    int j = low; // j is initialized as low value
    while(j >= i){ // j moves first
        if(stod(books[i][3]) <= pivot && stod(books[j][3]) <= pivot){ // Increment i and j if the ith and jth value of the vector's average rating values is less than pivot
            i++;
            j++;
        }
        if(stod(books[j][3]) > pivot){ // Increment j and swap ith and jth value of vector if jth value of vector's average rating values is bigger than pivot
            j++;
            if(j == high){ // If j is equal to high value, swap ith and high value of the vector and break while loop
                swap(books[i], books[high]);
                break;
            }
            swap(books[i], books[j]); 
            if(stod(books[i][3]) <= pivot){ // If ith value of the vector is less and equalt to pivot, increment i
                i++;
            }
        }
        if(j == high){ // If j is equal to high value, swap ith and high value of the vector and break while loop
            swap(books[i], books[high]);
            break;
        }
    }
    return i; // Return i value
}
void quick_sort(double array[], int low, int high){
    if(low < high){
        int pivot = partition(array, low, high); // Determine the pivot using the partition function
        iterations++; // Increment iterations
        quick_sort(array, low, pivot - 1); // Recurrence operation of sub-arrays
        quick_sort(array, pivot + 1, high); // Recurrence operation of sub-arrays
    }
}
void quick_sort_vector(vector<vector<string>> &books, int low, int high){
    if(low < high){
        int pivot = partition_vector(books, low, high); // Determine the pivot using the partition function
        quick_sort_vector(books, low, pivot - 1); // Recurrence operation of sub-arrays
        quick_sort_vector(books, pivot + 1, high); // Recurrence operation of sub-arrays
    }
}
void print_array(double array[], int size){ // Print the array 
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}
void print_vector(vector<vector<string>> &books, int size){ // Print the vector
    for(int i = 0; i < size; i++){
            for(int j = 0; j < books[i].size(); j++){
                cout << books[i][j] << " ";
            }
            cout << endl;
    }
}
int main()
{
    string fname;
    cout<<"Enter the file name: "; // File name is taken as input
    cin>>fname;
    
    vector<vector<string>> content; // Create a vector containing string storing rows and columns
    vector<string> row; // Crate a vector containing string storing rows 
    string line, word; 
    
    fstream file (fname, ios::in);
    if(file.is_open()){
        while(getline(file, line)) // Pull lines from file
        {
            row.clear(); // Clear row every time
            stringstream str(line); // Parse lines
            while(getline(str, word, ',')) // Take the words in the line as word
            row.push_back(word); // Push words to the vector row
            content.push_back(row); // Push rows to the vector content
        }
    }
    else{
        cout << "Could not open the file" << endl; // If the file couldn't be opened, print the error message
    }
    
    double array[content.size() - 1]; // Array is initialized 
    int size = content.size() - 1; // Size is initialized using the given file 
    for (int i = 1; i < content.size(); i++)
    {
        array[i-1] = stod(content[i][3]); // Initialize the fourth element of the file, the average rating property, to the array by converting it from string to double
    } 
    cout << "Before sorting" << endl;
    print_array(array, size); // Print the array before sorting
  
    quick_sort(array, 0, size - 1); // Quicksort algorithm for average rating values that takes an array as input

    cout << "After sorting" << endl;
    print_array(array, size); // Print the array after sorting
    //print_vector(content, size); // Print the vector before sorting
    quick_sort_vector(content, 1, size - 1); // Quicksort algorithm for books that takes a vector as input
    //print_vector(content, size); // Print the vector after sorting

    for (int i = 1; i < content.size(); i++)
    {
        to_string(array[i-1]) = (content[i][3]); // Initialize the fourth element of the file, the average rating property, to the array by converting it from string to double
    } 

    ofstream newfile;
    newfile.open ("new_books.txt"); // Create a text file named new_books
    if( !newfile ) { // If the file couldn't be opened, print the error message
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    for(int i = 0; i < content.size(); i++)
        {
        for(int j = 0; j < content[i].size(); j++)
        {
            newfile << content[i][j]<<" "; // Write the books into the text file
        }
        newfile << endl;
    }
    newfile.close(); // Close the file

    ofstream myfile;
    myfile.open ("sorted_books.txt"); // Create a text file named sorted_books
    if( !myfile ) { // If the file couldn't be opened, print the error message
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    for (int i = 0; i < size; i++)
    {
        myfile << array[i] << endl; // Write the array elements into text file
    }
    myfile.close(); // Close the file
    cout << "Number of partitionings: " << iterations << endl;
    cout << "Number of swaps: " << swap_number << endl;
    return 0;
}
 