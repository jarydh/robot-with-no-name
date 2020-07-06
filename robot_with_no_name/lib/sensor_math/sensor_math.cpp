// Code to do math related to sensors

#include "sensor_math.h"

// From https://www.geeksforgeeks.org/bubble-sort/  
void swap(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}

// Bubble sorts array
void bubbleSort(int arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
  
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
} 

// From https://stackoverflow.com/questions/44511623/how-to-find-the-approximate-median-from-continuous-data
void pushNewData(int data[], int new_data, int data_size) {
    for (int i = data_size - 1; i >= 1; i--)
    {
        data[i] = data[i - 1];
    }
    data[0] = new_data;
}

// Returns the median of an array
int median(int data[], int data_size) {
    int sorted_data[data_size];
    for(int i = 0; i < data_size; i++) {
        sorted_data[i] = data[i];
    }
    bubbleSort(sorted_data, data_size);
    return sorted_data[data_size / 2];
}