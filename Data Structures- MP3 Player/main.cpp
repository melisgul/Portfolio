/* @Author
* Student Name: Melis Gülenay
* Student ID : 150120304
* Date: 23.11.2016 */


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>
#include <iomanip>
#include "list.h"

using namespace std;

typedef list Datastructure;
Datastructure box;


void printMenu();
bool performOperation(char);
void play();
void createList();
void addSong();
void removeSong();
void deleteList();
void printList();
void writeToFile();
void exit();

int main(int argc, const char * argv[]){
    bool end = false;
    char choice;
    
    box.createDefaultLists();

    while (!end){
        printMenu();
        cin >> choice;
        end = performOperation(choice);
    }
    
    exit();
    
    return 0;
    
}

void printMenu(){
    cout << endl;
    cout << "SONG BOX APPLICATION (USING DOUBLY, CIRCULAR MULTI LINKED LIST)" << endl;
    cout << "Choose an operation" << endl;
    cout << "P: Play" << endl;
    cout << "L: Show all playlists" << endl;
    cout << "A: Add songs to a playlist" << endl;
    cout << "R: Remove songs from a playlist" << endl;
    cout << "C: Create a new playlist" << endl;
    cout << "D: Delete a playlist" << endl;
    cout << "W: Write to file (SAVE)" << endl;
    cout << "E: Exit" << endl;
    cout << endl;
    cout << "Enter a choice (P,L,A,R,C,D,W,E):";
}



bool performOperation(char choice){
    bool terminate = false;
    
    switch (choice)
    {
        case 'p':case 'P':
            play();
            break;
        case 'l':case 'L':
            printList();
            break;
        case 'a':case 'A':
            addSong();
            break;
        case 'r':case 'R':
            removeSong();
            break;
        case 'c':case 'C':
            createList();
            break;
        case 'd':case 'D':
            deleteList();
            break;
        case 'w':case 'W':
            writeToFile();
            break;
        case 'e':case 'E':
            cout << "Are you sure you want to exit from the program? (Y/N):";
            cin >> choice;
            if (choice == 'Y' || choice == 'y'){
                return terminate = true;
                break;
            }
            else{
                break;
            }
        default:
            cout << "You were entere an invalid choice, please enter again " << endl;
            cout << "Enter a choice (P,L,A,R,C,D,W,E):";
            cin >> choice;
            terminate = performOperation(choice);
            break;
    }
    return terminate;
}

void createList(){
    int listOption;
    char* style;
    char* singer;
    string input;
    
    cout<<"1: songs of a specific STYLE"<<endl;
    cout<<"2: songs of a specific SINGER"<<endl;
    cout<<"3: a combination of existing playlists"<<endl;
    cout<<"4: a combination of existing songs"<<endl;
    cout<<"Choose an option: ";
    cin>>listOption;
    switch (listOption) {
        case 1:
        {
            cin.ignore();
            cout<<"Enter the STYLE: ";
            getline(cin, input);
            style = new char[input.length()]();
            input.copy(style, input.length());
            box.createListWithStyleOrSinger(style , listOption);
            delete [] style;
            break;
        }
        case 2:
        {
            cin.ignore();
            cout<<"Enter the SINGER: ";
            getline(cin, input);
            singer = new char[input.length()]();
            input.copy(singer, input.length());
            box.createListWithStyleOrSinger(singer, listOption);
            delete [] singer;
            break;
        }
        case 3:
        {
            int choice3 = 0;
            bool condition3 = true;
            playlist *newPlaylist;
            char* concName = new char[50];
            cout<<"Enter Comcatenate list name: ";
            cin>>concName;
            newPlaylist = box.createPlaylist(concName);
            while (condition3) {
                cout<<"0. For Exit the Concatenate Operation"<<endl;
                box.writePlayListNames();
                cout<<"Choose a playlist to add new list: ";
                cin>>choice3;
                if (choice3 == 0) {
                    condition3 = false;
                }
                else{
                    box.addToConcatenateList(newPlaylist, choice3);
                    //box.writeToFile(newPlaylist);
                }
            }
            delete [] concName;
            break;
        }
        case 4:
        {
            int choice4 = 0;
            bool condition4 = true;
            playlist *newPlaylist2;
            char* combName = new char[50];
            cout<<"Enter Combination list name: ";
            cin>>combName;
            newPlaylist2 = box.createPlaylist(combName);
            cout<<"0. For Exit the Combination Operation"<<endl;
            box.printPlaylist(box.sorted);
            while (condition4) {
                cout<<"Choose a SONG to add new list: ";
                cin>>choice4;
                if (choice4 == 0) {
                    condition4 = false;
                }
                else{
                    box.addToCombinationList(newPlaylist2, choice4);
                    cout<<"0. For Exit the Combination Operation"<<endl;
                }
            }
            //box.writeToFile(newPlaylist2);
            delete [] combName;
            break;
        }
        default:
            cout<<"ERROR: Wrong Choice!"<<endl;
            break;
    }
}

//Adding a song from sorted List to a specific list
void addSong(){
    int choice1;
    int choice2;
    bool condition = true;
    cout<<"0. For Exit the Adding Operation"<<endl;
    box.printPlaylist(box.sorted);
    while (condition) {
        cout<<"Choose a SONG to add the list: ";
        cin>>choice1;
        if (choice1 == 0) {
            condition = false;
        }
        else{
            cout<<"0. For Exit the Adding Operation"<<endl;
            box.writePlayListNames();
            cout<<"Choose a playlist to add chosen song: ";
            cin>>choice2;
            if (choice2 == 0) {
                condition = false;
            }
            else if (choice2 < 4){
                cout<<"ERROR: You cannot change the default playlist!"<<endl;
                condition = false;
            }
            else{
                box.addingSongToUserLists(choice1, choice2);
            }
        }
    }
}

//Play a song from a list
void play(){
    char playOption;
    cout<<"Choose an option:"<<endl;
    cout<<"L: Playing a playlist"<<endl;
    cout<<"S: Playing a playlist starting from a specific song."<<endl;
    cout<<"P: Playing a single song."<<endl;
    cout<<"E: Exit"<<endl<<endl;
    cout<<"Enter a choice(L, S, P, E): ";
    
    cin>>playOption;
    switch (playOption) {
        case 'L':case 'l':
        {
            int choiceL;
            cout<<"Choose a playlist:"<<endl;
            box.writePlayListNames();
            cout<<endl<<"Enter an index: ";
            cin>>choiceL;
            box.startPlayFromBeginList(choiceL);
            break;
        }
        case 'S':case 's':
        {
            int choiceS;
            cout<<"Choose a playlist:"<<endl;
            box.writePlayListNames();
            cout<<endl<<"Enter an index: ";
            cin>>choiceS;
            box.startPlayFromSpecificSong(choiceS);
            break;
        }
        case 'P':case 'p':
        {
            int choiceP;
            cout<<"Choose a song: "<<endl;
            box.printPlaylist(box.sorted);
            cout<<endl<<"Enter an index: ";
            cin>>choiceP;
            box.playJustOneSong(choiceP);
            break;
        }
        case 'E':case 'e':
            break;
        default:
            cout<<"ERROR: Wrong choice!"<<endl;
            break;
    }
}

//Delete a list
void deleteList(){
    int whichNumber = 1;
    playlist *traverse = box.head->next;
    
    int choiceDelete;
    cout<<"Choose a playlist you want to delete:"<<endl;
    box.writePlayListNames();
    cout<<endl<<"Enter an index(You can not delete default Lists): ";
    cin>>choiceDelete;
    if (choiceDelete < 4) {
        cout<<"ERROR: You can not delete default Lists!"<<endl;
        return;
    }
    else{
        while (traverse) {
            if (whichNumber == choiceDelete) {
                break;
            }
            traverse = traverse->next;
            whichNumber++;
            if (traverse == box.head->next) {
                cout<<"ERROR: There is no such a list!"<<endl;
                return;
            }
        }
        box.deletePlaylist(traverse);
    }
};

//Removing a song
void removeSong(){
    int choiceDelete;
    cout<<"Choose a playlist:"<<endl;
    box.writePlayListNames();
    cout<<endl<<"Enter an index(You can not delete default Lists): ";
    cin>>choiceDelete;
    if (choiceDelete < 4) {
        cout<<"ERROR: You can not delete from default Lists!"<<endl;
        return;
    }
    box.removeSong(choiceDelete);
    
};

//Write to file function
void writeToFile(){
    box.writeAllPlaylistToTheFile();
};

void printList(){
    box.printAllList();
}

void exit(){
	box.exitSongBox();
};