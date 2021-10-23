/*
This program finds the standard deviation of a given file of data.
*/

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


//Function 1: Calls for the input file and places the data into the array.
int getInput(double *array)
{
	int count = 0;
	double x;
	int i = 0;
	ifstream inFile;
	inFile.open("project8.dat");
	while(inFile >> x)
{
	array[i]=x;
	i++;
        count++;
}
	inFile.close();
        return count;
}//End of function 1, returns amount of spots being used in the array.

//Function 2: Takes the data in the array and calculates the mean.
double getMean(double *array, int size)
{

	double sum = 0;
	for(int i = 0; i< size; i++) {
	sum = sum + *(array+i);

}
	double mean = sum / size;
	return mean;
}//End of function 2, returns the mean of all numbers in the array.

//Function 3: Takes all info gathered so far and finds the standard deviation.
double getDev(double *array, int size){
	double sumsq, stdev;
	double mean = getMean(array, size);
	sumsq = 0;
	for(int i = 0; i<size; i++){
	sumsq += pow(*(array+i)- mean, 2);
}
	stdev = sqrt((double) sumsq / size);

	return stdev;
}//End of function 3, returns the standard deviation of the data in the array.

//Main
int main()
{
double *arrayPtr = NULL;
arrayPtr = new double[50];
int size = getInput(arrayPtr);

cout << "The standard deviation is: " << getDev(arrayPtr, size) << endl;

return 0;
}
