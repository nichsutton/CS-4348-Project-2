#include <cstdlib>
#include <iostream>
#include <thread>
using namespace std;

void fillArray(int array[]);
void singleThreadedMergeSort(int array[]);
void multiThreadedMergeSort(int array[]);
void mergeSort(int array[], int leftBound, int rightBound);
void customMerge(int array[], int leftBound, int middleBound, int rightBound);

// For testing purposes only
void printArray(int array[]);
void printArrayIsSorted(int array[]);
bool arrayIsSorted(int array[]);

// Size of array
#define N 10000

int main() {
    int array[N];
    int multithreadedArray[N];

    fillArray(array);
    fillArray(multithreadedArray);

    // Here for testing only
    printArrayIsSorted(array);
    printArrayIsSorted(multithreadedArray);

    cout << "Sorting singlethreaded... \n";
    singleThreadedMergeSort(array);

    cout << "Sorting multithreaded... \n";
    multiThreadedMergeSort(multithreadedArray);
    
    // Here for testing only
    printArrayIsSorted(array);
    printArrayIsSorted(multithreadedArray);

    fillArray(array);

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

// Prints array, for testing purposes only
void printArray(int array[]) {
    for (int i = 0; i < N; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

// Prints if array is sorted, for testing purposes only
void printArrayIsSorted(int array[]) {
    if (arrayIsSorted(array)) {
        cout << "Array is sorted\n";
    }
    else {
        cout << "Array is NOT sorted\n";
    }
}

// Returns true if array is sorted, for testing purposes only
bool arrayIsSorted(int array[]) {
    for (int i = 1; i < N; i++) {
        if (array[i] < array[i-1]) {
            return false;
        }
    }
    return true;
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