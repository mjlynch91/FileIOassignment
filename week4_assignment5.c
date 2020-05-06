/*
This is a program to read an input text file whose first element consists of the number of elements to be stored in an array. 
The rest of the elements are populated into an array and their max and average are computed and stored into an output file along with the initial input elements. 
If the inputfile looks like this:
3 45 91 5
then the program creates an array with 3 elements and those elements are 45, 91, and 5.
All elements of the inputfile must be separated by a space. 
Note that this program won't run in Visual Studio because it gives an error about the number of elements in an array cannot be a variable. 
However the program runs fine when complied with GCC.
The purpose of the program is to give an example of file I/O.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define SIZE 5

void print_file(FILE *fptr) //this function prints all characters in a file
{
	int c;
	rewind(fptr);
	while((c = getc(fptr)) != EOF)
		putc(c,stdout);
}

double average(int data[], int size) //this function finds the average of an array
{
	int i;
	int sum;
	for(i=0;i<size;i++)
		sum+=data[i];
	double average = sum/size;
	return average;
}

int max(int data[],int size) //this function finds the maxiumum of an array
{
	int i;
	int max=0;
	for(i=0;i<size;i++)
	{
		if(data[i]>max)
			max = data[i];
	}
	return max;
}

int read_first_element(FILE *fptr) //this function will read and return the first integer of the inputfile
{
	int a;
	fscanf(fptr,"%d",&a);
	return a;
}

int* read_other_elements(FILE *fptr, int* dptr, int size) //this function will read all the elements in the rest of the inputfile and store them in an array
{
	int i=0;
	for(i=0; i < size ; i++)
	{
		fscanf(fptr,"%d",dptr+i);
	}
	return dptr;
}




int main(int argc, char* argv[]) //start of out program
{
	FILE *ifp, *ofp; //input and output file pointers
	if(argc != 3) //if the user didn't input 3 arguments send an error
	{
		printf("Need executable inputfile outputfile");
		exit(1);
	}
	
	ifp = fopen(argv[1],"r+"); //open the input file for reading
	ofp = fopen(argv[2],"w+");	//open the output file for writing
	
	int size = read_first_element(ifp); //file pointer should be pointing at the second element after this line is run
	int data[size]; 
	int* dptr=data;
	read_other_elements(ifp,dptr, size); //after this line is run the array data contains all the elements that were present after the first element in the inputfile
	
	
	int data_max = max(data,size); //find max of input data
	double data_average = average(data,size); //find average of input data
	int i;
	fprintf(ofp,"The elements of your input file are:\n"); //this line and the rest of the for loop populate the outputfile
	for(i=0;i<size+2;i++)
	{
		if(i<size)
			fprintf(ofp,"%d, ",data[i]);
		else if(i==size)
			fprintf(ofp, "\nThe maximum of the elements is: %d", data_max);
		else if(i==size+1)
			fprintf(ofp, "\nThe average of the elements is: %f", data_average);
	}
		
	print_file(ofp);	//prints what the output file will say	
	fclose(ifp); //good hygiene
	fclose(ofp); //good hygiene
	
	return 0;
}