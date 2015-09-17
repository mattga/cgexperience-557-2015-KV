#include <iostream> //provides proper definitions, includes "copy & paste" the content of a header file
using namespace std; //using the "std" namespace

//function call must occur after it has been defined

double myFibonacci(int n) //function entrance, defintion of name, datatype, and input parameter (pass arguments to function)
{
	unsigned int i = 0, j = 1, t, k; //'unsigned int' defined variables to be used within the function itself only
	for (k=0; k <= n; ++k) //for loop beginning at 0, while k is less than n, increasing by a value of k incrementally
	{
		t = i + j; //t begins with value of 1 (by i +j), increases by i + j each time
		i = j; //i begins with a value of 1 (by j)
		j = t; //j begins with a value of 1, increases by t (i+j) each time
	}
	return j; //returns a value to the user when the function is called
}

int main(int argc, char *argv[]) // program entry point, required for every program "main"

{
	int p = myFibonacci(10); // variable declaration with "int" defining the datatype as integer set equal to the return of the function "myFunction"
	cout << p << end1; //prints the output of "p", defined by the namespace "std"
}