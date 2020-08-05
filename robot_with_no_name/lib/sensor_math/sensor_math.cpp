// Code to do sensor math

#include "sensor_math.h"

#include <algorithm>

/*
* Takes an unsorted array and returns its median
*/
// From https://stackoverflow.com/questions/44511623/how-to-find-the-approximate-median-from-continuous-data
void pushNewData(int data[], int new_data, int data_size)
{
    for (int i = data_size - 1; i >= 1; i--)
    {
        data[i] = data[i - 1];
    }
    data[0] = new_data;
}

/*
* Adds data to an array in index 0, shifts all other data over by 1
* and discards the oldest data point
*/
// Returns the median of an array
int median(int data[], int data_size)
{
    int sorted_data[data_size];
    for (int i = 0; i < data_size; i++)
    {
        sorted_data[i] = data[i];
    }
    std::sort(sorted_data, sorted_data + data_size);

    return sorted_data[data_size / 2];
}

/*
* Clamps n between upper and lower.
*/
int clamp(int n, int upper, int lower)
{
    if (n < lower)
    {
        return lower;
    }
    else if (n > upper)
    {
        return upper;
    }
    else
    {
        return n;
    }
}
