#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void fillArray(int array[]);
void singleThreadedMergeSort(int array[]);
void multiThreadedMergeSort(int array[]);
void mergeSort(int array[], int leftBound, int rightBound);
void customMerge(int array[], int leftBound, int middleBound, int rightBound);

// Size of array
#define N 20000

int main() {
    int array[N];

    // multithreaded
    
    // Shuffle
    fillArray(array);
    // Start timer
    auto multiStartTime = std::chrono::high_resolution_clock::now();
    // Sort
    multiThreadedMergeSort(array);
    // Stop timer
    auto multiStopTime = std::chrono::high_resolution_clock::now();
    // Calculate time
    auto multiSortDuration = std::chrono::duration<double, std::milli>(multiStopTime - multiStartTime);
    // Output
    std::cout << "Sorting "<< N << " integers is done in "<< multiSortDuration.count() <<" msec using threads\n";


    // single threaded

    // Shuffle
    fillArray(array);
    // Start timer
    auto singleStartTime = std::chrono::high_resolution_clock::now();
    // Sort
    singleThreadedMergeSort(array);
    // Stop timer
    auto singleStopTime = std::chrono::high_resolution_clock::now();
    // Calculate time
    auto singleSortDuration = std::chrono::duration<double, std::milli>(singleStopTime - singleStartTime);
    // Output
    std::cout << "Sorting "<< N << " integers is done in "<< singleSortDuration.count() <<" msec without-threads\n";

    return 0;
}

// Fills array with random numbers
void fillArray(int array[]) {
    // Traverse array
    for (int i = 0; i < N; i++) {
        // Fill with random number in range [1, 10000]
        array[i] = (rand() % 10000) + 1;
    }
}

// Does a single threaded merge sort with no cutoff on array
void singleThreadedMergeSort(int array[]) {
    // Find middle of array
    int middleBound = (N - 1) / 2;
    // Merge sort left half
    mergeSort(array, 0, middleBound);
    // Merge sort right half
    mergeSort(array, middleBound + 1, N - 1);
    // Merge both halves
    customMerge(array, 0, middleBound, N - 1);
}

void multiThreadedMergeSort(int array[]) {
    int middleBound = (N - 1) / 2;

    // sorts left half on thread1
    std::thread sortingThread1 (mergeSort, array, 0, middleBound);
    // sorts right half on thread2
    std::thread sortingThread2 (mergeSort, array, middleBound + 1, N - 1);
    sortingThread1.join();
    sortingThread2.join();

    // sorts the two halfs on merging thread
    std::thread mergingThread (customMerge, array, 0, middleBound, N - 1);
    mergingThread.join();
};

// Performs a merge sort on array within bounds [leftBound, rightBound]
void mergeSort(int array[], int leftBound, int rightBound) {
    // If bounds are only one number, then it is already sorted
    if ((rightBound - leftBound) == 0) {
        return;
    }

    // Find middle of left and right bound
    int middleBound = leftBound + (rightBound - leftBound) / 2;
    // Merge sort left half
    mergeSort(array, leftBound, middleBound);
    // Merge sort right half
    mergeSort(array, middleBound + 1, rightBound);
    // Merge both halves
    customMerge(array, leftBound, middleBound, rightBound);
}

// Merges two halves in array.
// Bounds of halves are [leftBound, middleBound] and [middleBound + 1, rightBound]
void customMerge(int array[], int leftBound, int middleBound, int rightBound) {
    // Create temporary array
    int tempArray[rightBound - leftBound + 1];
    // Create pointers
    int tempPointer = 0;
    int leftPointer = leftBound;
    int rightPointer = middleBound + 1;

    // While both halves have numbers in them
    while (leftPointer <= middleBound && rightPointer <= rightBound) {
        // Copy smaller number to next available cell in the temporary array and move pointers by 1
        if (array[leftPointer] <= array[rightPointer]) {
            tempArray[tempPointer++] = array[leftPointer++];
        }
        else {
            tempArray[tempPointer++] = array[rightPointer++];
        }
    }

    // Copy leftover numbers in left half
    while (leftPointer <= middleBound) {
        tempArray[tempPointer++] = array[leftPointer++];
    }

    // Copy leftover numbers in right half
    while (rightPointer <= rightBound) {
        tempArray[tempPointer++] = array[rightPointer++];
    }

    // Copy temporary array over to array
    tempPointer = 0;
    leftPointer = leftBound;
    while (leftPointer <= rightBound) {
        array[leftPointer++] = tempArray[tempPointer++];
    }
}