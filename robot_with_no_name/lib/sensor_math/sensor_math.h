// Code to do sensor math

#ifndef SENSOR_MATH_H
#define SENSOR_MATH_H

#include <algorithm>

/*
* Takes an unsorted array and returns its median
*/
// From https://stackoverflow.com/questions/44511623/how-to-find-the-approximate-median-from-continuous-data
void pushNewData(int data[], int new_data, int data_size);

/*
* Adds data to an array in index 0, shifts all other data over by 1
* and discards the oldest data point
*/
// Returns the median of an array
int median(int data[], int data_size);

/*
* Clamps n between upper and lower.
*/
int clamp(int n, int upper, int lower);

#endif