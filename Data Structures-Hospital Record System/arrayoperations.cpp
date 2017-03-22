/*@Author
*Student Name : Melis Gülenay
*Student ID : 150120304
*Date : 18.10.2016
*/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iomanip>
#include "fileoperations.h"
#include<string.h>
#include <ctype.h>
#include <fstream>
using namespace std;

ifstream input;

void Patient_file::create(){
	patientcounter = 0;
	input.open("database.txt"); //database text file is opened to read.
	char *ptr;
	int i = 0;
	string line;
	char *line2;

	//untill the end of file
	while (getline(input, line)){
		line2 = &line[0];  //this loop reads line by line from the file. Then separates line into struct element by strtok function.
		ptr = strtok(line2, "\t");
		strcpy((k + i)->name, ptr);

		ptr = strtok(NULL, "\t");
		strcpy((k + i)->doctorName, ptr);

		ptr = strtok(NULL, "\t");
		strcpy((k + i)->diagnosis, ptr);

		ptr = strtok(NULL, "\t");
		(k + i)->patientNumber = atoi(ptr);

		ptr = strtok(NULL, "\t");
		(k + i)->polyclinicNumber = atoi(ptr);

		ptr = strtok(NULL, "\t");
		strcpy((k + i)->branchName, ptr);

		ptr = strtok(NULL, "\t");
		i++;
		patientcounter++;
	}
	patient_record *ptr1 = k, *ptr2 = k2;
	for (int i = 0; i < patientcounter; i++){ //this loop copies data from the k array to the k2 array.
		strcpy(ptr2->name, ptr1->name);
		strcpy(ptr2->doctorName, ptr1->doctorName);
		strcpy(ptr2->diagnosis, ptr1->diagnosis);
		ptr2->polyclinicNumber = ptr1->polyclinicNumber;
		ptr2->patientNumber = ptr1->patientNumber;
		strcpy(ptr2->branchName, ptr1->branchName);
		ptr1++;
		ptr2++;
		patientcounter2++;
	}
	sort_the_array();
	for (int i = 0; i < patientcounter; i++){ //this loop sends the elements of array in order to complete polyclinics to 10 elements.
		addpolynull((k + i)->polyclinicNumber);
	}
	input.close(); //closes the file.
}

void Patient_file::print_all(){ //this function prints all the records in the struct array.
	patient_record *ptr = k; //in order to do pointer arithmetics
	//patient_record *ptr2 = k2; //in order to do pointer arithmetics.


	cout << "Name  " << "  " << "DoctorName  " << "  " << "Diagnosis  " << "  " << "PatientNumber " << "  " << "PolyclinicNumber  " << "  " << "BranchName  " << endl;
	for (int i = 0; i < patientcounter; i++){
		if (strcmp((k + i)->name, "") == 0 && strcmp((k + i)->diagnosis, "") == 0){
			cout << ptr->name << "  " << ptr->doctorName << "  " << ptr->diagnosis << endl;
			ptr++;
		}
		else{
			cout << ptr->name << "  " << ptr->doctorName << "  " << ptr->diagnosis << "  " << ptr->patientNumber << "  " << ptr->polyclinicNumber << "  " << ptr->branchName << endl;
			ptr++;
		}
	}

}

void Patient_file::add_record(patient_record *nptr){ //this function adds a new record to the both k and k2 arrays.
	int flag = 0;
	int choosen1 = 0, choosen2 = 0;
	for (int j = 0; j < patientcounter; j++){  //this loop controls that the polyclinic number was used before in order to check it is belong any branch.
		if ((k + j)->polyclinicNumber == nptr->polyclinicNumber){
			choosen1 = j; //the record number has the same polyclinic number.
			break;
		}
	}
	for (int m = 0; m < patientcounter; m++){ //if there exists any null element for the entered polyclinic number?
		if (((k + m)->polyclinicNumber == nptr->polyclinicNumber) && (strcmp((k + m)->name, "") == 0)){
			choosen2 = m; //The null record with entered polyclinic number.
			flag = 1; //this flag means there is a null element with the same entered polyclinic number.
			break;
		}
	}
	if (flag == 1){ //null record changes with the entered record.
		strcpy((k + choosen2)->name, nptr->name);
		strcpy((k + choosen2)->doctorName, nptr->doctorName);
		strcpy((k + choosen2)->diagnosis, nptr->diagnosis);
		(k + choosen2)->patientNumber = nptr->patientNumber;
		(k + choosen2)->polyclinicNumber = nptr->polyclinicNumber;
		strcpy((k + choosen2)->branchName, (k + choosen1)->branchName);

		strcpy((k2 + patientcounter2)->name, nptr->name);//also the new record is added to the k2 array
		strcpy((k2 + patientcounter2)->doctorName, nptr->doctorName);
		strcpy((k2 + patientcounter2)->diagnosis, nptr->diagnosis);
		(k2 + patientcounter2)->patientNumber = nptr->patientNumber;
		(k2 + patientcounter2)->polyclinicNumber = nptr->polyclinicNumber;
		strcpy((k2 + patientcounter2)->branchName, (k + choosen1)->branchName);
		patientcounter2++;
	}
	else{
		strcpy((k + patientcounter)->name, nptr->name);  //if there isnt any a null element with the same entered polyclinic number.
		strcpy((k + patientcounter)->doctorName, nptr->doctorName); //new record created.
		strcpy((k + patientcounter)->diagnosis, nptr->diagnosis);
		(k + patientcounter)->patientNumber = nptr->patientNumber;
		(k + patientcounter)->polyclinicNumber = nptr->polyclinicNumber;
		strcpy((k + patientcounter)->branchName, nptr->branchName);

		strcpy((k2 + patientcounter2)->name, nptr->name); //new record created in k2.
		strcpy((k2 + patientcounter2)->doctorName, nptr->doctorName);
		strcpy((k2 + patientcounter2)->diagnosis, nptr->diagnosis);
		(k2 + patientcounter2)->patientNumber = nptr->patientNumber;
		(k2 + patientcounter2)->polyclinicNumber = nptr->polyclinicNumber;
		strcpy((k2 + patientcounter2)->branchName, nptr->branchName);
		patientcounter++;
		patientcounter2++;
	}

	cout << " Record has been added." << endl << endl;
	sort_the_array(); //records in the k array is sorted.
}
void Patient_file::sort_the_array(){ //sorts the array k
	patient_record *ptr1, *ptr2, temp;
	ptr1 = &k[1];
	ptr2 = k;
	for (int i = 0; i < patientcounter; i++){
		ptr1 = &k[1];
		ptr2 = k;
		for (int j = 0; j<patientcounter - 1; j++){
			if (strcmp(ptr2->branchName, ptr1->branchName) > 0){
				temp = *ptr2;
				*ptr2 = *ptr1;
				*ptr1 = temp;

			}
			if (strcmp(ptr2->branchName, ptr1->branchName) == 0){
				if (ptr2->polyclinicNumber > ptr1->polyclinicNumber){
					temp = *ptr2;
					*ptr2 = *ptr1;
					*ptr1 = temp;
				}
			}
			ptr1++;
			ptr2++;
		}

	}
}


int Patient_file::search_by_branch(char branch[]){ //searches by branch
	int flag = 0;
	patient_record *ptr;
	ptr = k;
	for (int i = 0; i < patientcounter; i++) {
		if (strcmp(ptr->branchName, branch) == 0){  //matchinng record
			cout << i + 1 << "  " << ptr->name << "  " << ptr->doctorName << "  " << ptr->diagnosis << "  " << ptr->patientNumber << "  " << ptr->polyclinicNumber << "  " << ptr->branchName << endl;
			flag++; //record was found.

		}
		ptr++;
	}
	return flag;
}

int Patient_file::search_by_polyclinicnum(int poly){//searches by polyclinic number
	int flag = 0;
	patient_record *ptr;
	ptr = k;
	for (int i = 0; i < patientcounter; i++) {

		if (ptr->polyclinicNumber == poly)//matchinng record
		{
			cout << i + 1 << "  " << ptr->name << "  " << ptr->doctorName << "  " << ptr->diagnosis << "  " << ptr->patientNumber << "  " << ptr->polyclinicNumber << "  " << ptr->branchName << endl;
			flag++;//record was found.

		}
		ptr++;
	}



	return flag;
}


int Patient_file::remove_record(int pat){ //removes te record.
	int flag = 0;
	int counter = 0;
	patient_record *ptr, *ptr1;
	ptr = k;
	ptr1 = k;

	for (int i = 0; i < patientcounter; i++) {
		if (ptr->patientNumber == pat) //search for the desired record
		{
			flag++; // desired record was found.
			cout << i + 1 << "  " << ptr->name << "  " << ptr->doctorName << "  " << ptr->diagnosis << "  " << ptr->patientNumber << "  " << ptr->polyclinicNumber << "  " << ptr->branchName << endl; //print the desired record.
			for (int m = 0; m < patientcounter; m++){
				if ((ptr->polyclinicNumber == ptr1->polyclinicNumber) && (strcmp(ptr1->name, "") == 0)) counter++; //if there exists a null record with polyclinic number same as the record will remove.
				ptr1++;
			}
			if (counter == 9){ //if the number of null record that counts by 'counter' is equal to 9. That means there wont be any record with the same polyclinic number.
				for (int m = 0; m < 10; m++){ //so all the null record are deleted.
					for (int s = i; s < patientcounter; s++){
						strcpy((k + s)->name, (k + s + 1)->name);
						strcpy((k + s)->doctorName, (k + s + 1)->doctorName);
						strcpy((k + s)->diagnosis, (k + s + 1)->diagnosis);
						(k + s)->patientNumber = (k + s + 1)->patientNumber;
						(k + s)->polyclinicNumber = (k + s + 1)->polyclinicNumber;
						strcpy((k + s)->branchName, (k + s + 1)->branchName);


					}
					patientcounter--;
				}
			}
			else //if the number of null record that counts by 'counter' is not equal to 9.That means there will be records with the same polyclinic number after remove operation.
			{
				strcpy(ptr->name, "");
				strcpy(ptr->doctorName, "");
				strcpy(ptr->diagnosis, "");
				ptr->patientNumber = 0;
			}

		}
		ptr++;
	}

	ptr = k2;
	for (int i = 0; i < patientcounter2; i++){ //the k2 array is uptaded for remove operation.
		if (ptr->patientNumber == pat){
			for (int s = i; s < patientcounter2; s++){
				strcpy((k2 + s)->name, (k2 + s + 1)->name);
				strcpy((k2 + s)->doctorName, (k2 + s + 1)->doctorName);
				strcpy((k2 + s)->diagnosis, (k2 + s + 1)->diagnosis);
				(k2 + s)->patientNumber = (k2 + s + 1)->patientNumber;
				(k2 + s)->polyclinicNumber = (k2 + s + 1)->polyclinicNumber;
				strcpy((k2 + s)->branchName, (k2 + s + 1)->branchName);
			}
			patientcounter2--;
		}
		ptr++;
	}

	return flag;
}

void Patient_file::addpolynull(int polino){ //this function adds empty elements for the records taken from the file.
	int counter = 0;
	int branchno = 0;
	for (int i = 0; i < patientcounter; i++){
		if ((k + i)->polyclinicNumber == polino){
			counter++;
		}
	}
	if ((10 - counter) != 0){
		for (int j = 0; j < (10 - counter); j++){
			strcpy((k + patientcounter)->name, "");
			strcpy((k + patientcounter)->doctorName, "");
			strcpy((k + patientcounter)->diagnosis, "");
			(k + patientcounter)->patientNumber = 0;
			(k + patientcounter)->polyclinicNumber = polino;
			branchno = add_branch_to_poly(polino);
			strcpy((k + patientcounter)->branchName, (k + branchno)->branchName);
			patientcounter++;

		}
	}
	sort_the_array();
}

void Patient_file::tenpoli(int polino){//creates a null elements for the new entered polyclinic number that never exist before.(10 element 1 polyclinic).
	int branchno = 0;
	for (int i = 0; i < 9; i++){
		strcpy((k + patientcounter)->name, "");
		strcpy((k + patientcounter)->doctorName, "");
		strcpy((k + patientcounter)->diagnosis, "");
		(k + patientcounter)->patientNumber = 0;
		(k + patientcounter)->polyclinicNumber = polino;
		branchno = add_branch_to_poly(polino); //
		strcpy((k + patientcounter)->branchName, (k + branchno)->branchName);
		patientcounter++;
	}

}



int Patient_file::isnull(int polino){//checks is there any empty element for the entered polyclinic number
	int counter = 0;
	for (int i = 0; i < patientcounter; i++){
		if (((k + i)->polyclinicNumber == polino) && (strcmp((k + i)->name, "") != 0)){
			counter++; // counts the number of used element with the entered polyclinic number
		}
	}
	return counter;
}

int Patient_file::ispoly(int polino){//checks if there exists any record with the same polyclinic number. the record must take the branch with others. 1 polyclinic -> 1 branch
	int flag = 0;
	for (int i = 0; i < patientcounter; i++){
		if ((k + i)->polyclinicNumber == polino){
			return flag = 1; //the polyclinic number was used and already belongs to a branch.
		}
	}
	return flag;
}


int Patient_file::add_branch_to_poly(int polino){
	for (int i = 0; i < patientcounter; i++){
		if ((k + i)->polyclinicNumber == polino) return i;
	}
	return -1;
}

int Patient_file::poly2_branch1(char *br){  //this function checks the 2polclinic number -> 1 branch rule.
	int p1 = 0;
	int counter = 0;

	for (int i = 0; i < patientcounter2; i++){
		if (strcmp((k2 + i)->branchName, br) == 0){
			p1 = (k2 + i)->polyclinicNumber; //if there exists,the first polyclinic number with desired branch.
			break;
		}
	}

	for (int j = 0; j < patientcounter2; j++){
		if (strcmp((k2 + j)->branchName, br) == 0 && (k2 + j)->polyclinicNumber != p1){ //if there exists, the seconds polyclinic number with desired branch.
			counter++;
		}
	}
	return counter;
}

void Patient_file::close(){ //this function writes the records in the k2 array into the file without blanks and order operation.Then closes the file.

	database = fopen("database.txt", "w+");
	for (int i = 0; i < patientcounter2; i++){
		fprintf(database, "%s\t%s\t%s\t%d\t%d\t%s\n", (k2 + i)->name, (k2 + i)->doctorName, (k2 + i)->diagnosis, (k2 + i)->patientNumber, (k2 + i)->polyclinicNumber, (k2 + i)->branchName);

	}
	fclose(database);

}