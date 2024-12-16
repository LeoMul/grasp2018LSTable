#include "sort.h"
#include <iostream>
#include <vector>

//borrowed from https://www.geeksforgeeks.org/cpp-program-for-quicksort/

void quickSort(vector<int> &vec, int low, int high) {

    // Base case: This part will be executed till the starting
    // index low is lesser than the ending index high
    if (low < high) {

        // pi is Partitioning Index, arr[p] is now at
        // right place
        int pi = partition(vec, low, high);

        // Separately sort elements before and after the
        // Partition Index pi
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

int partition(vector<int> &vec, int low, int high) {

    // Selecting last element as the pivot
    int pivot = vec[high];

    // Index of elemment just before the last element
    // It is used for swapping
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {

        // If current element is smaller than or
        // equal to pivot
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    // Put pivot to its position
    swap(vec[i + 1], vec[high]);

    // Return the point of partition
    return (i + 1);
}

//https://stackoverflow.com/questions/55976487/get-the-sorted-indices-of-an-array-using-quicksort
void argQuickSort(double A[], size_t I[], size_t lo, size_t hi)
{
    if (lo < hi)
    {
        double pivot = A[I[lo + (hi - lo) / 2]];
        size_t t;
        size_t i = lo - 1;
        size_t j = hi + 1;
        while (1)
        {
            while (A[I[++i]] < pivot);
            while (A[I[--j]] > pivot);
            if (i >= j)
                break;
            t = I[i];
            I[i] = I[j];
            I[j] = t;
        }
        argQuickSort(A, I, lo, j);
        argQuickSort(A, I, j + 1, hi);
    }
}