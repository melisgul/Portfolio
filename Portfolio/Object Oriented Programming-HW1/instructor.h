/*  @Author

	Name: Melis Gülenay

	StudentID: 150120304

	Date: 30.03.2016

*/



#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

// Maximum allowed number of courses: 10
#define N_COURSES_MAX 10

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>
#include <istream>
#include <iomanip>

using namespace std;

class Instructor
{
private:
    string title;
    string first_name;
    string last_name;
    string telephone_number;
    string room_number;
    string user_name;
    string email_address;
    string courses[N_COURSES_MAX];

public:
    Instructor();
    ~Instructor();

    bool is_empty = true;
    
    //get the values of Instructor class

    string getTitle();
    string getFirstName();
    string getLastName();
    string getTelephoneNumber();
    string getRoomNumber();
    string getUserName();
    string getEmailAddress();
    string* getCourses();

//set the values of Instructor class

    void setTitle(string);
    void setFirstName(string);
    void setLastName(string);
    void setTelephoneNumber(string);
    void setRoomNumber(string);
    void setUserName(string);
    void setEmailAddress(string);
    void setCourses(string courses[]);
};

Instructor::Instructor() //constructor
{

}

Instructor::~Instructor() //destructor
{

}

// Getter functions:

string Instructor::getTitle()
{
    return title;
}

string Instructor::getFirstName()
{
    return first_name;
}

string Instructor::getLastName()
{
    return last_name;
}

string Instructor::getTelephoneNumber()
{
    return telephone_number;
}

string Instructor::getRoomNumber()
{
    return room_number;
}

string Instructor::getUserName()
{
    return user_name;
}

string Instructor::getEmailAddress()
{
    return email_address;
}

string* Instructor::getCourses()
{
    return courses;
}

// Setter functions:

void Instructor::setTitle(string title)
{
    this->title = title;
}

void Instructor::setFirstName(string first_name)
{
    this->first_name = first_name;
}

void Instructor::setLastName(string last_name)
{
    this->last_name = last_name;
}

void Instructor::setTelephoneNumber(string telephone_number)
{
    this->telephone_number = telephone_number;
}

void Instructor::setRoomNumber(string room_number)
{
    this->room_number = room_number;
}

void Instructor::setUserName(string user_name)
{
    this->user_name = user_name;
}

void Instructor::setEmailAddress(string email_address)
{
    this->email_address = email_address;
}

void Instructor::setCourses(string courses[])
{
    for(int i = 0; i < N_COURSES_MAX; i++){
        if(courses[i].empty())
            break;
        this->courses[i] = courses[i];
    }
}

#endif // INSTRUCTOR_H
