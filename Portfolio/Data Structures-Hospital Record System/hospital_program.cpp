/*@Author
*Student Name : Melis Gülenay
*Student ID : 150120304
*Date : 18.10.2016
*/



#include "fileoperations.h"
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctype.h>
 
using namespace std;

typedef Patient_file Datastructure;
Datastructure book;

void print_menu();
bool perform_operations(char);
void branch_search();
void polyclinic_search();
void insert_record();
void delete_recod();

int main(){
	book.create();
	bool end = false; //controls the whether user want to make operation.
	char choice;
	while (!end){//controls the whether user want to make operation.
		print_menu();//prints menu
		cin >> choice;
		end = perform_operations(choice);
	}

	book.close();
	return 0;
}


void print_menu(){  //prints all the operations 
	cout << endl << endl;
	cout << "Hospital Record Application" << endl;
	cout << "Please select the operation to perform and enter the operation code" << endl;
	cout << "(P) Print all of the patient records," << endl;
	cout << "(B) Search the data by the branch name," << endl;
	cout << "(C) Search the data by the polyclinic number," << endl;
	cout << "(I) Insert a new patient record" << endl;
	cout << "(R) Remove the patient record," << endl;
	cout << "(E) Exit the program." << endl;
	cout << endl;
	cout << "Please enter the operation you want to choose {P,B,C,R,I,E}" << endl;
	cout << "Your selection is:";
}


bool perform_operations(char choice){
	bool terminate = false;
	switch (choice)
	{
	case 'p':case 'P':
		book.print_all(); //prints all the records
		break;
	case 'b':case 'B':
		branch_search(); //searches patients by branch. Then, print them.
		break;
	case 'c':case 'C':
		polyclinic_search();//searches patients by polyclinic number. Then, print them.
		break;
	case 'r':case 'R':
		delete_recod(); //removes the record specified by user.
		break;
	case 'i':case 'I':
		insert_record(); //inserts the record entered by user.
		break;
	case 'e':case 'E':
		cout << "Are you sure that you want to exit from the program? (Y/N):"; //check whether user wants to exit or does not.
		cin >> choice;
		if (choice == 'Y' || choice == 'y'){
			terminate = true;
			return terminate;
		}
		break;

	default:
		cout << " You have entered an invalid choice. Please enter again {P,B,C,R,I,E}:"; //for the wrong enters.
		cin >> choice;
		perform_operations(choice);
		break;
	}

	return terminate;

}


void insert_record(){ // adds record.
	patient_record nrecord;
	int flag=0,flag2=0;
	cout << "-Insert operation-"<< endl;//the inputs are taken from the user.
	cout << "Patient Name: ";
	cin.ignore(1000, '\n');
	cin.getline(nrecord.name,50);

	cout <<  "Doctor's Name: ";
	cin.getline(nrecord.doctorName, 50);

	cout <<"Diagnosis: ";
	cin.getline(nrecord.diagnosis, 50);

	cout << "Patient Number: ";
	cin >> nrecord.patientNumber;
	while (nrecord.patientNumber < 1000 || nrecord.patientNumber > 9999){ //the patient number must be 4 digits.
		cout << "Patient number must be 4 digits. Please enter again." << endl;
		cin >> nrecord.patientNumber;
	}

	cout <<  "Polyclinic Number: ";
	cin >> setw(10) >> nrecord.polyclinicNumber;

	
	flag = book.isnull(nrecord.polyclinicNumber); // is there any empty element for the entered polyclinic number.
	while (flag==10) { //full element.
		cout << "The polyclinic is full. Please enter different polyclinic number:";
		cin >> nrecord.polyclinicNumber;
		flag = book.isnull(nrecord.polyclinicNumber);
	}
	flag2 = book.ispoly(nrecord.polyclinicNumber); //if there exists any record with the same polyclinic number. the record must take the branch with others. 1 polyclinic -> 1 branch
	if (flag2 == 0){ 

		cout << "Branch Name: ";
		cin.ignore(1000, '\n');
		cin.getline(nrecord.branchName, 50);
		for (int m = 0; m < 50; m++){ //toupper for the equality between the records.
			nrecord.branchName[m] = toupper(nrecord.branchName[m]);
		}
		int br_flag = 0;
		br_flag = book.poly2_branch1(nrecord.branchName); //if the entered branch has already 2 polyclinic number?

		while (br_flag != 0){
			cout << "Each branch must have at most 2 polyclinic number. The branch you entered has already belong to 2 polyclinic.Please enter again:" << endl;
			cin.getline(nrecord.branchName, 50);
			for (int m = 0; m < 50; m++){
				nrecord.branchName[m] = toupper(nrecord.branchName[m]);
			}
			br_flag = book.poly2_branch1(nrecord.branchName);

		}

	}
	else
	{
		cout << "The polyclinic number is already assigned to branch. There is no need to assign it." << endl;
	}
    

	book.add_record(&nrecord); //adds the record
	if (flag==0) book.tenpoli(nrecord.polyclinicNumber); //creates a null elements for the new entered polyclinic number that never exist before.(10 element 1 polyclinic).
	book.sort_the_array(); //sorts after add operation.
	
}

void branch_search(){ //searches by branch
	char desired[50];
	int found = 0;
	cout << " Please enter the branch of the record you want to search:";
	cin.ignore(1000, '\n');
	cin.getline(desired, 50);
	for (int m = 0; m < 50; m++){   //the branch must be upperletter in case of equality of branches.
		desired[m]=toupper(desired[m]);

	}
		
	found = book.search_by_branch(desired);

	if (found == 0){
		cout << "Record could not be found" << endl;	
	}
	else {
		cout << "Record has been found" << endl;
	}
}

void polyclinic_search(){ //searches by polyclinic number.
	int poli;
	int found = 0;
	cout << " Please enter the polyclinic number of the record you want to search:";
	cin.ignore(1000, '\n');
	cin >> setw(10) >> poli;
	found = book.search_by_polyclinicnum(poli);

	if (found == 0){
		cout << "Record could not be found" << endl;
	}
	else {
		cout << "Record has been found" << endl;
	}
}

void delete_recod(){ //deletes the record according to patient number.
	int patient;
	int found = 0;
	cout << "Please enter the patient number of the person you want to remove. Press '-1' to see full list: ";
	cin.ignore(1000, '\n');
	cin >> setw(10) >> patient;
	while (patient == -1){
		book.print_all();
		cout << "Please enter the patient number of the person you want to remove.Press '-1' to see full list: ";
		cin >> setw(10) >> patient;
	}
	found = book.remove_record(patient);

	if (found == 0){
		cout << "Record could not be found" << endl;
	}
	else {
		cout << "Record has been found and deleted" << endl;

	}


}