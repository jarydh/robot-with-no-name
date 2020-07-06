// Code to do sensor math

#ifndef SENSOR_MATH_H
#define SENSOR_MATH_H

/*
* Takes an unsorted array and returns its median
*/
int median(int data[], int data_size);

/*
* Adds data to an array in index 0, shifts all other data over by 1
* and discards the oldest data point
*/
void pushNewData(int data[], int new_data, int data_size);



#endif