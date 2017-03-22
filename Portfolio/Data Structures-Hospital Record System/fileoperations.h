/*@Author
*Student Name : Melis Gülenay
*Student ID : 150120304
*Date : 18.10.2016
*/




#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <stdio.h>
#include "record.h"


struct Patient_file{
	FILE *database; //filepointer
	char *filename;
	patient_record k[MAX_KAYIT]; //struct array for holding records
	patient_record k2[MAX_KAYIT];//struct array for writing records to the file without changing order or blanks.
	int patientcounter,patientcounter2; //counters to count k and k2 arrays.
	void create(); //to read the text file at the beginning of the program.
	void close(); //to write the record to the file.
	void print_all();
	void sort_the_array(); //sorts the records into the k array
	int search_by_branch(char branch[]); 
	int search_by_polyclinicnum(int);
	void add_record(patient_record *newrecord);
	int remove_record(int patientnumber);
	void tenpoli(int polino); //creates null elements for the polyclinic numbers
	int isnull(int polino); //checks is there any empty element for the entered polyclinic number
	int ispoly(int poli);//checks if there exists any record with the same polyclinic number.
	int add_branch_to_poly(int polino); 
	int poly2_branch1(char *br); // to check the 2 polyclinic number -> 1 branch
	void addpolynull(int polino);//this function adds empty elements for the records taken from the file.
};

#endif
