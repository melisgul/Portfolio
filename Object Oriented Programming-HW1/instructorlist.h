/*  @Author

	Name: Melis Gülenay

	StudentID: 150120304

	Date: 30.03.2016

*/

#ifndef INSTRUCTORLIST_H
#define INSTRUCTORLIST_H

#define DEFAULT_SIZE 100

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>
#include <istream>
#include <iomanip>

#include "instructor.h"

using namespace std;

class InstructorList
{
private:
    Instructor* instructors; //the instructors array

public:
    InstructorList(); //deafult constructor
    InstructorList(int); //constructor
    ~InstructorList(); //destructor

    int n_instructors;
    int max_n_instructors;

    bool addInstructor(string, string, string, string, string, string, string, string[]);
    bool deleteInstructor(string, string);
    void print(int);
    void search(string, int);
};

InstructorList::InstructorList()
{
    instructors = new Instructor[DEFAULT_SIZE];
    n_instructors = 0;
    max_n_instructors = DEFAULT_SIZE;
}

InstructorList::InstructorList(int size)
{
    instructors = new Instructor[size];
    n_instructors = 0;
    max_n_instructors = size;
}

InstructorList::~InstructorList() //for memory allocation
{
    delete[] instructors;
}


//adding a new instructor if array is empty
bool InstructorList::addInstructor(string title, string first_name, string last_name, string telephone_number,
                                   string room_number, string user_name, string email_address, string courses[])
{
    int first_available_index = -1;

    for(int i = 0; i < max_n_instructors; i++){
        if(instructors[i].is_empty){
            first_available_index = i;
            break;
        }
    }

    if(first_available_index != -1){
        instructors[first_available_index].is_empty = false;
        instructors[first_available_index].setTitle(title);
        instructors[first_available_index].setFirstName(first_name);
        instructors[first_available_index].setLastName(last_name);
        instructors[first_available_index].setTelephoneNumber(telephone_number);
        instructors[first_available_index].setRoomNumber(room_number);
        instructors[first_available_index].setUserName(user_name);
        instructors[first_available_index].setEmailAddress(email_address);
        instructors[first_available_index].setCourses(courses);
        n_instructors++;
        return true;
    }
    return false;
}

//remove instructor by putting blanks for values

bool InstructorList::deleteInstructor(string first_name, string last_name)
{
    for(int i = 0; i < max_n_instructors; i++){
        if(instructors[i].getFirstName() == first_name && instructors[i].getLastName() == last_name){
            instructors[i].is_empty = true;
            instructors[i].setTitle("");
            instructors[i].setFirstName("");
            instructors[i].setLastName("");
            instructors[i].setTelephoneNumber("");
            instructors[i].setRoomNumber("");
            instructors[i].setUserName("");
            instructors[i].setEmailAddress("");

            string courses[N_COURSES_MAX];
            instructors[i].setCourses(courses);

            return true;
        }
    }
    return false;
}

//print the information of instructor
void InstructorList::print(int index)
{
    if(!instructors[index].is_empty){
        cout << "Title: " << instructors[index].getTitle() << '\n';
        cout << "First Name: " << instructors[index].getFirstName() << '\n';
        cout << "Surname: " << instructors[index].getLastName() << '\n';
        cout << "Telephone Number: " << instructors[index].getTelephoneNumber() << '\n';
        cout << "Room Number: " << instructors[index].getRoomNumber() << '\n';
        cout << "User Name: " << instructors[index].getUserName() << '\n';
        cout << "Email: " << instructors[index].getEmailAddress() << '\n';

        cout << "Courses: [";
        string *courses = instructors[index].getCourses();
        for(int i = 0; i < N_COURSES_MAX; i++){
            if(courses[i].empty())
                break;
            if(i > 0)
                cout << ", ";
            cout << courses[i];
        }
        cout << "]" << "\n";
        cout << "--------------------------------------" << "\n";
    }
}

//search instructor by receiving a method (first name, last name....)

void InstructorList::search(string entry, int method)
{
    int matched_index = -1;

    for(int i = 0; i < max_n_instructors; i++){
        if(instructors[i].is_empty == false){
            switch(method){ //choosing the method and make operation search for this method
            case 0:
            {
                if(instructors[i].getFirstName() == entry)
                    matched_index = i;
                break;
            }
            case 1:
            {
                if(instructors[i].getLastName() == entry)
                    matched_index = i;
                break;
            }
            case 2:
            {
                if(instructors[i].getTelephoneNumber() == entry)
                    matched_index = i;
                break;
            }
            case 3:
            {
                if(instructors[i].getRoomNumber() == entry)
                    matched_index = i;
                break;
            }
            default:
                break;
            }
        }
        if(matched_index != -1)
            break;
    }

    if(matched_index == -1)
        cout << "No results were found.\n";
    else
        this->print(matched_index);
}

#endif // INSTRUCTORLIST_H
