#include "quicksort.hpp"

void qs_swap(int &a, int &b){
    int c = a;
    a = b;
    b = c;
}

int qs_partition(int arr[], int start, int end){
    int pivot = arr[start];
    
    int count = 0;
    for (int i = start + 1; i <= end; i++){
        if(arr[i] <= pivot) count++;
    }
    
    int pivotIndex = start + count;
    qs_swap(arr[pivotIndex], arr[start]);

    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex){
        while (arr[i] <= pivot) i++;
        while (arr[j] > pivot) j--;
        if(i < pivotIndex && j > pivotIndex)
            qs_swap(arr[i++], arr[j--]);
    }
    return pivotIndex;
}

void quickSort(int arr[], int start, int end){
    if(start >= end) return;
    int p = qs_partition(arr, start, end);
    quickSort(arr, start, p - 1);
    quickSort(arr, p + 1, end);
}