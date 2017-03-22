/*  @Author

	Name: Melis Gülenay

	StudentID: 150120304

	Date: 30.03.2016

*/

#include "instructor.h"
#include "instructorlist.h"

class AddressBook
{
private:
    InstructorList* instructor_list;

public:
    AddressBook();
    ~AddressBook();

    // User interface functions:
    void printChoices();
    void addNewInstructor();
    void deleteInstructor();
    void listAllInstructors();
    void search(int);
};

AddressBook::AddressBook()
{
    instructor_list = new InstructorList();
}

AddressBook::~AddressBook()
{
    delete instructor_list;
}

//printing the menu
void AddressBook::printChoices()
{
    cout << "1. Add a new instructor\n";
    cout << "2. Delete an instructor\n";
    cout << "3. List all instructors\n";
    cout << "4. Search by Name\n";
    cout << "5. Search by Surname\n";
    cout << "6. Search by Telephone Number\n";
    cout << "7. Search by Room Number\n";
    cout << "8. Exit\n";
}


//adding new intructor
void AddressBook::addNewInstructor()
{
    string title;
    string first_name;
    string last_name;
    string telephone_number;
    string room_number;
    string user_name;
    string email_address;
    string courses[N_COURSES_MAX];

    cout << "Enter the title:\n";
    cin >> title;
    cout << "Enter the First Name:\n";
    cin >> first_name;
    cout << "Enter the Last Name:\n";
    cin >> last_name;
    cout << "Enter the Telephone Number:\n";
    cin >> telephone_number;
    cout << "Enter the Room Number:\n";
    cin >> room_number;
    cout << "Enter the User Name:\n";
    cin >> user_name;
    cout << "Enter the Email Address:\n";
    cin >> email_address;
    cout << "Enter the Courses (type -1 to finalize):\n";
    for(int i = 0; i < N_COURSES_MAX; i++){
        string input;
        cin >> input;
        if(input == "-1")
            break;
        courses[i] = input;
    }

    bool result = instructor_list->addInstructor(title, first_name, last_name, telephone_number, room_number, user_name, email_address, courses);

    if(result)
        cout << "New instructor is added!\n";
    else
        cout << "Instructor list is full; new instructor is not added!\n";
}

//removing instructor

void AddressBook::deleteInstructor()
{
    string first_name;
    string last_name;

    cout << "Enter the first name of the record to be deleted:\n";
    cin >> first_name;
    cout << "Enter the last name of the record to be deleted:\n";
    cin >> last_name;

    bool result = instructor_list->deleteInstructor(first_name, last_name);

    if(result)
        cout << "Record has been deleted!\n";
    else
        cout << "No record was found.\n";
}

//listing all instructors

void AddressBook::listAllInstructors()
{
    cout << "----------List of all Instructors in Computer Engineering of ITU----------" << "\n\n";
    for(int i = 0; i < instructor_list->max_n_instructors; i++)
        instructor_list->print(i);
}


//search according to methods
void AddressBook::search(int method)
{
    string entry;

    switch(method){
    case 0: // Search by name
        cout << "Enter the first name:\n";
        break;
    case 1: // Search by surname
        cout << "Enter the last name:\n";
        break;
    case 2:
        cout << "Enter the telephone number:\n";
        break;
    case 3:
        cout << "Enter the room number:\n";
        break;
    default:
        break;
    }

    cin >> entry;
    instructor_list->search(entry, method);
}

int main()
{
    AddressBook address_book;
	/*InstructorList instr;
	instr.addInstructor("Asst. Prof. Dr.", "Gökhan", "Ýnce", "02122856986",
		"4310", "gokhan.ince", "gokhan.ince@itu.edu.tr", NULL);*/

    while(true){
        int selection;
        bool exit = false;

        address_book.printChoices();
        cout << "Enter the number for operation you want to perform:\n";
        cin >> selection;

        switch(selection){
        case 1:
            address_book.addNewInstructor();
            break;
        case 2:
            address_book.deleteInstructor();
            break;
        case 3:
            address_book.listAllInstructors();
            break;
        case 4:
            address_book.search(0);
            break;
        case 5:
            address_book.search(1);
            break;
        case 6:
            address_book.search(2);
            break;
        case 7:
            address_book.search(3);
            break;
        case 8:
            exit = true;
            break;
        default:
            exit = true;
            break;
        }

        string yes_or_no;
        cout << "Do you want to perform another operation?(Y/N)\n";
        cin >> yes_or_no;
        if(yes_or_no == "N")
            exit = true;

        if(exit)
            break;
    }

    return 1;
}

