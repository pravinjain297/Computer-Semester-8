/*
Title:-Write a program to implement Parallel Bubble Sort and Merge sort using OpenMP. Use existing algorithms and measure the performance of sequential and parallel algorithms
Name:-Pravin Jain
Roll NO:-72
Subject:-LP-V
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

using namespace std;

// Parallel bubble sort algorithm using OpenMP
void parallelBubbleSort(std::vector<int>& arr) {
    // Bubble sort implementation
    int n = arr.size();
    #pragma omp parallel
    {
        for (int i = 0; i < n - 1; ++i) {
            #pragma omp for
            for (int j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
}

// Merge function for merge sort
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; ++i)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            ++i;
        } else {
            arr[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }
}


// Parallel merge sort algorithm using OpenMP
void parallelMergeSort(std::vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            parallelMergeSort(arr, left, mid);
        }

        #pragma omp section
        {
            parallelMergeSort(arr, mid + 1, right);
        }
    }

    merge(arr, left, mid, right);
}

int main() {
    // Get the size of the array from the user
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    // Create a vector to store the elements entered by the user
    std::vector<int> arr(size);

    // Ask the user to enter the elements
    cout << "Enter the elements of the array:\n";
    for (int i = 0; i < size; ++i) {
        cout << "Element " << i + 1 << ": ";
        cin >> arr[i];
    }

    // Sort the array using parallel bubble sort
    vector<int> parallelArr = arr;
    parallelBubbleSort(parallelArr);


    // Sort the array using parallel merge sort
    vector<int> mergeParallelArr = arr;
    parallelMergeSort(mergeParallelArr, 0, size - 1);

 

    cout << "Parallel Bubble Sort Result:\n";
    for (int i = 0; i < size; ++i) {
        cout << parallelArr[i] << " ";
    }
    cout << endl;

  

    std::cout << "Parallel Merge Sort Result:\n";
    for (int i = 0; i < size; ++i) {
        cout << mergeParallelArr[i] << " ";
    }
    cout << endl;

    return 0;
}
