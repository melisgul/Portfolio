/* @Author
* Student Name: Melis Gülenay
* Student ID : 150120304
* Date: 23.11.2016 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "list.h"
#include <string.h>
#include <cstdlib>

using namespace std;

void list::createDefaultLists(){
    allSongList = new song*[23];
    for (int i = 0; i < 23; i++) {
        allSongList[i] = new song;
    }
    allSongNumber = 0;
	playlist_count = 0;
	chronological = createPlaylist("chronological");
	sorted = createPlaylist("sorted");
	random = createPlaylist("random");
    
    readFromFile();
    for (int k = 0; k < allSongNumber; k++) {
        createChrono(chronological, allSongList[k]);
        createSorted(sorted, allSongList[k]);
    }
    createRandom();
    

    
};

void list::readFromFile(){
	input.open("songbook.txt");
    
	string line;
	char **words;
    
    while (getline(input, line)){
        if (!line.compare(0,5,"*****")) {
            break;
        }
        words = new char*[4]();
        for (int i = 0; i < 4; i++) {
            words[i] = new char[50];
        }
        splitLinesToWords(line, words);
        addToAllSongList(words);
        
        for (int j = 0; j < 4; j++) {
            delete[] words[j];
        }
        delete[] words;
    }
    
    
}

void list::writeToFile(playlist *list){
    output.open("songbook.txt", ios::app);
    if (list->head == NULL) {
        return;
    }
	output << endl;
    output<<"*****"<<endl;
    output<<list->name<<endl;
    song_node* ptr2 = list->head;
    
    while (ptr2->next != list->head){
        output << ptr2->data->name << "    " << ptr2->data->singer << "      " << ptr2->data->year << "      " << ptr2->data->style << endl;
        ptr2 = ptr2->next;
    }
    output << ptr2->data->name << "    " << ptr2->data->singer << "      " << ptr2->data->year << "      " << ptr2->data->style << endl;
    output.close();
}

void list::addToAllSongList(char *newSongInfo[4]){
    strcpy(allSongList[allSongNumber]->name, newSongInfo[0]);
    strcpy(allSongList[allSongNumber]->singer, newSongInfo[1]);
    int year = atoi(newSongInfo[2]);
    allSongList[allSongNumber]->year = year;
    strcpy(allSongList[allSongNumber]->style, newSongInfo[3]);
    
    //cout << allSongList[allSongNumber]->name << " " << allSongList[allSongNumber]->singer << " " << allSongList[allSongNumber]->year << " " << allSongList[allSongNumber]->style << endl;
    
    allSongNumber++;
};


void list::splitLinesToWords(string &line, char** lineWords){
	int i = 0;

	char del = '\t';
	string word;

	stringstream lineToSplit;
	lineToSplit.str(line);

	while (getline(lineToSplit, word, del)){
		lineWords[i] = new char[word.length()]();
		word.copy(lineWords[i], word.length());
		i++;
	}
}

song_node* list::createSongNode(song *songPtr){
    song_node *newSongNode;
    newSongNode = new song_node;
    newSongNode->parent = NULL;
    newSongNode->next = NULL;
    newSongNode->prev = NULL;
    
    newSongNode->data = songPtr;
    
    return newSongNode;
};


//Creating chronological playlist
void list::createChrono(playlist *chronological, song *nptr){
    song_node *newSongNode;
    newSongNode = createSongNode(nptr);

    if (chronological->head == NULL) {
        chronological->head = newSongNode;
        newSongNode->parent = chronological;
        newSongNode->prev = newSongNode;
        newSongNode->next = newSongNode;
        //cout<<"New song is the first element of the Chronogical list"<<endl;
        //cout<<newSongNode->data->singer<<" "<<newSongNode->data->year<<endl;
    }
    else{
        song_node *temp = chronological->head;
        while (temp->next != chronological->head) {
            if (newSongNode->data->year <= temp->data->year) {
                break;
            }
            temp = temp->next;
        }
        if (newSongNode->data->year >= temp->data->year) {
            temp->next->prev = newSongNode;
            newSongNode->next = temp->next;
            temp->next = newSongNode;
            newSongNode->prev = temp;
        }
        else{
            temp->prev->next = newSongNode;
            newSongNode->prev = temp->prev;
            newSongNode->next = temp;
            temp->prev = newSongNode;
        }
        //cout<<"New song is added to the Chronocigal list"<<endl;
        
        if (temp->parent != NULL && newSongNode->data->year < temp->data->year) {
            newSongNode->parent = temp->parent;
            newSongNode->parent->head = newSongNode;
            temp->parent = NULL;
            //cout<<"New song is added the beginning of the list"<<endl;
        }
    }
    
    chronological->songnumber = chronological->songnumber + 1;
}

//Print A List
void list::printPlaylist(playlist *list){
    song_node* ptr2 = list->head;
    int SongNumberPrinting = 1;
 
    while (ptr2->next != list->head){
        cout <<SongNumberPrinting<<". "<< ptr2->data->name << "    " << ptr2->data->singer << "      " << ptr2->data->year << "      " << ptr2->data->style << endl;
        ptr2 = ptr2->next;
        SongNumberPrinting++;
    }
    cout <<SongNumberPrinting<<". "<< ptr2->data->name << "    " << ptr2->data->singer << "      " << ptr2->data->year << "      " << ptr2->data->style << endl;
    cout <<  endl;
    
}

//Creating sorted playlist
void list::createSorted(playlist *sorted, song *nptr){
    song_node *newSongNode;
    newSongNode = createSongNode(nptr);
    
    if (sorted->head == NULL){
        sorted->head = newSongNode;
        newSongNode->parent = sorted;
        newSongNode->prev = newSongNode;
        newSongNode->next = newSongNode;
        //cout<<"New song is the first element of the Sorted list"<<endl;
        //cout<<newSongNode->data->singer<<" "<<newSongNode->data->year<<endl;
    }
    else {
        song_node *tempnode;
        tempnode = sorted->head;
        
        while (tempnode->next != sorted->head) {
            if (strcmp(tempnode->data->singer, newSongNode->data->singer) >= 0) {
                break;
            }
            tempnode = tempnode->next;
        }
        if (strcmp(tempnode->data->singer, newSongNode->data->singer) > 0){
            tempnode->prev->next = newSongNode;
            newSongNode->prev = tempnode->prev;
            newSongNode->next = tempnode;
            tempnode->prev = newSongNode;
        }
        else if (strcmp(tempnode->data->singer, newSongNode->data->singer) < 0) {
            tempnode->next->prev = newSongNode;
            newSongNode->next = tempnode->next;
            tempnode->next = newSongNode;
            newSongNode->prev = tempnode;
        }
        else{
            while (strcmp(tempnode->data->singer, newSongNode->data->singer) == 0) {
                if (strcmp(tempnode->data->name, newSongNode->data->name) == 0){
                    cout<<"ERROR: This song is already in the sorted list!"<<endl;
                    return;
                }
                if(strcmp(tempnode->data->name, newSongNode->data->name) > 0){
                    break;
                }
                tempnode = tempnode->next;
            }
            
            tempnode->prev->next = newSongNode;
            newSongNode->prev = tempnode->prev;
            newSongNode->next = tempnode;
            tempnode->prev = newSongNode;
        }
        //cout << "New song is added to the Sorted list" << endl;
        
        //If the song is added the beginning of list
        if (tempnode->parent != NULL && strcmp(tempnode->data->singer, newSongNode->data->singer) > 0) {
            newSongNode->parent = tempnode->parent;
            newSongNode->parent->head = newSongNode;
            tempnode->parent = NULL;
            //cout << "New song is added the beginning of the sorted list list" << endl;
        }
    }
    sorted->songnumber = sorted->songnumber + 1;
}

void list::createRandom(){
    int temp;
	
    song_node *newSongNode;
    deletePlaylist(random);
	random = createPlaylist("random");
    int isAdded[allSongNumber];
    for (int i = 0; i < allSongNumber; i++) {
        isAdded[i] = 0;
    }
    
    srand(time(NULL));
    temp = rand() % allSongNumber;
    newSongNode = createSongNode(allSongList[temp]);
    
    random->head = newSongNode;
    newSongNode->parent = random;
    newSongNode->prev = newSongNode;
    newSongNode->next = newSongNode;
    //cout<<"New song is the first element of the Sorted list"<<endl;
    //cout<<newSongNode->data->singer<<" "<<newSongNode->data->year<<endl;
    isAdded[temp] = 1;
    random->songnumber++;
    
    while (random->songnumber < allSongNumber) {
        srand(time(NULL));
        temp = rand() % allSongNumber;
        if (isAdded[temp] == 0) {
            newSongNode = createSongNode(allSongList[temp]);
            random->head->prev->next = newSongNode;
            newSongNode->prev = random->head->prev;
            newSongNode->next = random->head;
            random->head->prev = newSongNode;
            isAdded[temp] = 1;
            random->songnumber++;
        }
    }
};

//Delete Playlist
void list::deletePlaylist(playlist* removedList){
    song_node *traverse = removedList->head;
    int deletedNodes = 0;

    while (deletedNodes < removedList->songnumber) {
        removedList->head = traverse->next;
        delete traverse;
        
        traverse = removedList->head;
        deletedNodes++;
    }
	if (playlist_count == 1){
		delete[] removedList->name;
		delete removedList;
		head = NULL;
		playlist_count--;
	}
	else{
		removedList->prev->next = removedList->next;
		removedList->next->prev = removedList->prev;

		if (head == removedList) {
			head = removedList->prev;
		}
		delete[] removedList->name;
		delete removedList;
		playlist_count--;
	}
};


//Create a list according to its style
void list::createListWithStyleOrSinger(char* newCondition, int type){
    song_node *newSongNode;
    song_node *songTraverse;
    playlist* newPlayList;
    playlist* listTraverse = head;
    
    char* commingCondition = new char[strlen(newCondition)]();
    commingCondition = toUpperString(newCondition);
    char* ourCondition;
    
    while(listTraverse) {
        ourCondition = new char[strlen(listTraverse->name)]();
        ourCondition = toUpperString(listTraverse->name);
        if (strcmp(commingCondition, ourCondition) == 0) {
            cout<<"You cannot create playlist with the same names"<<endl;
            return;
        }
        listTraverse = listTraverse->next;
        delete [] ourCondition;
        
        if (listTraverse == head) {
            break;
        }
    }
    
    newPlayList = createPlaylist(newCondition);
    
    if (type == 1) {
        songTraverse = sorted->head;
        while (songTraverse) {
            ourCondition = new char[strlen(songTraverse->data->style)]();
            ourCondition = toUpperString(songTraverse->data->style);
            if (strcmp(commingCondition, ourCondition) == 0) {
                newSongNode = createSongNode(songTraverse->data);
                if (newPlayList->head == NULL) {
                    newPlayList->head = newSongNode;
                    newSongNode->parent = newPlayList;
                    newSongNode->next = newSongNode;
                    newSongNode->prev = newSongNode;
                }
                newPlayList->head->prev->next = newSongNode;
                newSongNode->prev = newPlayList->head->prev;
                newSongNode->next = newPlayList->head;
                newPlayList->head->prev = newSongNode;
                newPlayList->songnumber++;
            }
        
            songTraverse = songTraverse->next;
            if (songTraverse == sorted->head) {
                delete [] ourCondition;
				break;
            }
            delete [] ourCondition;
        }
        
        if (newPlayList->head == NULL) {
			cout << "ERROR: There is not such a type!" << endl;
            deletePlaylist(newPlayList);
        }
    }
    if (type == 2) {
        songTraverse = sorted->head;
        while (songTraverse) {
            ourCondition = new char[strlen(songTraverse->data->singer)]();
            ourCondition = toUpperString(songTraverse->data->singer);
            if (commingCondition == ourCondition) {
                newSongNode = createSongNode(songTraverse->data);
                if (newPlayList->head == NULL) {
                    newPlayList->head = newSongNode;
                    newSongNode->parent = newPlayList;
                    newSongNode->next = newSongNode;
                    newSongNode->prev = newSongNode;
                }
				newPlayList->head->prev->next = newSongNode;
				newSongNode->prev = newPlayList->head->prev;
				newSongNode->next = newPlayList->head;
				newPlayList->head->prev = newSongNode;
				newPlayList->songnumber++;
            }
            
            songTraverse = songTraverse->next;
            if (songTraverse == sorted->head) {
                delete [] ourCondition;
				break;
            }
            delete [] ourCondition;
        }
		if (newPlayList->head == NULL) {
			cout << "ERROR: There is not such a singer!" << endl;
			deletePlaylist(newPlayList);
		}
    }
    
};

//toupper function
char* list::toUpperString(char* str){
    char* ch = new char[strlen(str)]();
    
    for (int i = 0; i < strlen(str); i++){
		if (str[i] == ' ')
			ch[i] = str[i];
		else
			ch[i] = toupper(str[i]);
    }
    return ch;
};

//Print list names
void list::writePlayListNames(){
    playlist *traverse;
    int count = 1;
    traverse = head->next;
    while (traverse != head) {
        cout<<count<<". "<<traverse->name<<endl;
        count++;
        traverse = traverse->next;
    }
    cout<<count<<". "<<traverse->name<<endl;
}

//Creating a playlist
playlist* list::createPlaylist(char *name){
    playlist* newPlayList;
    newPlayList = new playlist;
	if (head == NULL)
	{
		head = newPlayList;
		newPlayList->next = newPlayList;
		newPlayList->prev = newPlayList;
	}
    
    strcpy(newPlayList->name , name);
    newPlayList->head = NULL;
    newPlayList->songnumber = 0;
    
    newPlayList->next = head->next;
    newPlayList->prev = head;
    head->next->prev = newPlayList;
    head->next = newPlayList;
    head = newPlayList;
	playlist_count++;
    
    return newPlayList;
};

//Adding to concatanate list
void list::addToConcatenateList(playlist* newList, int number){
    int whichNumber = 1;
    playlist *traverse = head->next;
    song_node *newSongNode;
    
    while (traverse != head) {
        if (whichNumber == number) {
            break;
        }
        traverse = traverse->next;
        whichNumber++;
    }
    if (strcmp(newList->name, traverse->name) == 0) {
        cout<<"ERROR: You cannot comcatanate a list with itself"<<endl;
        return;
    }
    song_node *songTraverse = traverse->head;
    while(songTraverse->next != traverse->head){
        newSongNode = createSongNode(songTraverse->data);
        if (newList->head == NULL) {
            newList->head = newSongNode;
            newSongNode->parent = newList;
            newSongNode->prev = newSongNode;
            newSongNode->next = newSongNode;
            //cout<<"New song is the first element of the New list"<<endl;
            //cout<<newSongNode->data->singer<<" "<<newSongNode->data->year<<endl;
            newList->songnumber++;
        }
        else{
            newList->head->prev->next = newSongNode;
            newSongNode->prev = newList->head->prev;
            newSongNode->next = newList->head;
            newList->head->prev = newSongNode;
            newList->songnumber++;
        }
        songTraverse = songTraverse->next;
    }
    newSongNode = createSongNode(songTraverse->data);
    newList->head->prev->next = newSongNode;
    newSongNode->prev = newList->head->prev;
    newSongNode->next = newList->head;
    newList->head->prev = newSongNode;
    newList->songnumber++;
};

//Add a combination list
void list::addToCombinationList(playlist* newList, int number){
    int whichNumber = 1;
    song_node *traverse = sorted->head;
    song_node *newSongNode;
    
    while (traverse) {
        if (whichNumber == number) {
            break;
        }
        traverse = traverse->next;
        whichNumber++;
        if (traverse == sorted->head) {
            cout<<"ERROR: Wrong index number!"<<endl;
            return;
        }
    }
    newSongNode = createSongNode(traverse->data);
    if (newList->head == NULL) {
        newList->head = newSongNode;
        newSongNode->parent = newList;
        newSongNode->prev = newSongNode;
        newSongNode->next = newSongNode;
        //cout<<"New song is the first element of the New list"<<endl;
        //cout<<newSongNode->data->singer<<" "<<newSongNode->data->year<<endl;
        newList->songnumber++;
    }
    else{
        newList->head->prev->next = newSongNode;
        newSongNode->prev = newList->head->prev;
        newSongNode->next = newList->head;
        newList->head->prev = newSongNode;
        newList->songnumber++;
    }
};

//Adding song from sorted list into a user list
void list::addingSongToUserLists(int choice1, int choice2){
    song_node *newSongNode;
    int whichList = 1;
    int whichSong = 1;
    playlist *ListTraverse = head->next;
    song_node *songTraverse = sorted->head;
    
    while (ListTraverse != head) {
        if (whichList == choice2) {
            break;
        }
        ListTraverse = ListTraverse->next;
        whichList++;
    }
    if (ListTraverse == head && whichList != choice2) {
        cout<<"ERROR: There is no such a list!"<<endl;
        return;
    }
    else{
        while (songTraverse) {
            if (whichSong == choice1) {
                break;
            }
            songTraverse = songTraverse->next;
            whichSong++;
            if (songTraverse == sorted->head) {
                cout<<"ERROR: Wrong index number!"<<endl;
                return;
            }
        }
        newSongNode = createSongNode(songTraverse->data);
        ListTraverse->head->prev->next = newSongNode;
        newSongNode->prev = ListTraverse->head->prev;
        newSongNode->next = ListTraverse->head;
        ListTraverse->head->prev = newSongNode;
        ListTraverse->songnumber++;
    }
    //writeToFile(ListTraverse);
};


//Playin from the beginning of a List
void list::startPlayFromBeginList(int number){
   // char choicePlaying;
    //bool condition = true;
    int whichList = 1;
    playlist *ListTraverse = head->next;
    //song_node *songTraverse;
    
    while (ListTraverse != head) {
        if (whichList == number) {
            break;
        }
        ListTraverse = ListTraverse->next;
        whichList++;
    }
    if (ListTraverse == head && whichList != number) {
        cout<<"ERROR: There is no such a list!"<<endl;
        return;
    }
    playing(ListTraverse->head);

};

//Playing start from a specific song
void list::startPlayFromSpecificSong(int number){
    int index;
    int whichList = 1;
    int whichSong = 1;
    
    playlist *ListTraverse = head->next;
    
    while (ListTraverse != head) {
        if (whichList == number) {
            break;
        }
        ListTraverse = ListTraverse->next;
        whichList++;
    }
    if (ListTraverse == head && whichList != number) {
        cout<<"ERROR: There is no such a list!"<<endl;
        return;
    }
    printPlaylist(ListTraverse);
    cout<<"Enter index of a song you want to play: ";
    cin>>index;
    song_node *traverse = ListTraverse->head;
    
    while (traverse) {
        if (whichSong == index) {
            break;
        }
        traverse = traverse->next;
        whichSong++;
        if (traverse == ListTraverse->head) {
            cout<<"ERROR: Wrong index number!"<<endl;
            return;
        }
    }
    playing(traverse);
};

//Playing a list
void list::playing(song_node *songTraverse){
    char choicePlaying;
    bool condition = true;
    cout<<"PLAY >"<<endl;
    while (condition) {
        cout<<"playing. . ."<<endl;
        cout<<songTraverse->data->name<<"-"<<songTraverse->data->singer<<"-"<<songTraverse->data->year<<"-"<<songTraverse->data->style<<endl;
        cout<<"NEXT(N) - PREVIOUS(P) - EXIT(E)"<<endl;
        cin>>choicePlaying;
        switch (choicePlaying) {

            case 'N':case 'n':
                songTraverse = songTraverse->next;
                break;
            case 'P':case 'p':
                songTraverse = songTraverse->prev;
                break;
            case 'E':case 'e':
                condition = false;
                break;
            default:
                cout<<"ERROR: Wrong Choice!"<<endl;
                break;
        }
    }
}

//Play just one Song from sorted list
void list::playJustOneSong(int choiceP){
    int whichNumber = 1;
    song_node *traverse = sorted->head;
    
    while (traverse) {
        if (whichNumber == choiceP) {
            break;
        }
        traverse = traverse->next;
        whichNumber++;
        if (traverse == sorted->head) {
            cout<<"ERROR: Wrong index number!"<<endl;
            return;
        }
    }
    cout<<"playing . . ."<<endl;
    cout<<traverse->data->name<<"-"<<traverse->data->singer<<"-"<<traverse->data->year<<"-"<<traverse->data->style<<endl<<endl;
};

//Remove A song from list
void list::removeSong(int index){
    int index2;
    song_node *newSongNode;
    int whichList = 1;
    playlist *ListTraverse = head->next;
    
    while (ListTraverse != head) {
        if (whichList == index) {
            break;
        }
        ListTraverse = ListTraverse->next;
        whichList++;
    }
    if (ListTraverse == head && whichList != index) {
        cout<<"ERROR: There is no such a list!"<<endl;
        return;
    }
    else{
        cout<<"Choose a song from list: "<<endl;
        printPlaylist(ListTraverse);
        cout<<"Enter a song index: ";
        cin>>index2;
        
        int whichSong = 1;
        song_node *songTraverse = ListTraverse->head;
        
        while (songTraverse) {
            if (whichSong == index2) {
                break;
            }
            songTraverse = songTraverse->next;
            whichSong++;
            if (songTraverse == ListTraverse->head) {
                cout<<"ERROR: Wrong index number!"<<endl;
                return;
            }
        }
        songTraverse->prev->next = songTraverse->next;
        songTraverse->next->prev = songTraverse->prev;
        
        if (songTraverse->parent != NULL) {
            songTraverse->next->parent = ListTraverse;
            ListTraverse->head = songTraverse->next;
        }
        cout<<songTraverse->data->name<<"-"<<songTraverse->data->singer<<"-"<<songTraverse->data->year<<"-"<<songTraverse->data->style<<endl;
        cout<<"song is deleted.."<<endl;
        delete songTraverse;
        
        ListTraverse->songnumber--;
    }
};

//Write to file all playlist
void list::writeAllPlaylistToTheFile(){
    writeToFile(chronological);
    int isWrited = 1;
    
    playlist *ListTraverse = head->next;
    
    while (ListTraverse) {
        if (isWrited > 3) {
            writeToFile(ListTraverse);
        }
        ListTraverse = ListTraverse->next;
        isWrited++;
        if (ListTraverse == head->next) {
            break;
        }
    }
};


//Print all list
void list::printAllList(){
    writePlayListNames();
    int counterPrinted = 1;
    char choice;
    int song;
    
    playlist* thePrintedOne = head->next;
    while(thePrintedOne){
        cout<<endl<<counterPrinted<<". "<<thePrintedOne->name<<endl;
        cout<<"PLAY(S) - DELETE(D) - ADD SONG(A) - REMOVE SONG(R) - NEXT(N) - PREVIOUS(P) - INDEX NUMBER(I) - EXIT(E)"<<endl;
        cin>>choice;
        switch (choice) {
            case 'S':case 's':
            {
                startPlayFromBeginList(counterPrinted);
                break;
            }
            case 'D':case 'd':
            {
                if (counterPrinted < 4) {
                    cout<<"ERROR: You can not DELETE a default playlist!"<<endl;
                    break;
                }
                deletePlaylist(thePrintedOne);
                break;
            }
            case 'A':case 'a':
            {
                if (counterPrinted < 4) {
                    cout<<"ERROR: You can not ADD SONGS to the default playlist!"<<endl;
                    break;
                }
                printPlaylist(sorted);
                cout<<"Choose an index: ";
                cin>>song;
                addingSongToUserLists(song, counterPrinted);
                break;
            }
            case 'R':case 'r':
            {
                if (counterPrinted < 4) {
                    cout<<"ERROR: You can not REMOVE SONGS from the default playlist!"<<endl;
                    break;
                }
                removeSong(counterPrinted);
                break;
            }
            case 'N':case 'n':
            {
                thePrintedOne = thePrintedOne->next;
                counterPrinted++;
				if (counterPrinted > playlist_count)
				{ counterPrinted = 1; };
                break;
            }
            case 'P':case 'p':
            {
                thePrintedOne = thePrintedOne->prev;
                counterPrinted--;
				if (counterPrinted <= 0) 
				{ counterPrinted = playlist_count; };
                break;
            }
            case 'I':case 'i':
            {
                int index;
                cout<<"Enter the index: ";
                cin>>index;
                counterPrinted = 1;
                thePrintedOne = head->next;
                while (thePrintedOne) {
                    if (counterPrinted == index) {
                        break;
                    }
                    thePrintedOne = thePrintedOne->next;
                    counterPrinted++;
                    if (thePrintedOne == head->next) {
                        cout<<"ERROR: Invalid index nummber!"<<endl;
                        cout<<"Enter the index: ";
                        cin>>index;
                        counterPrinted = 1;
                        thePrintedOne = head->next;
                    }
                }
                break;
            }
            case 'E':case 'e':
            {
                return;
            }
            default:
            {
                cout<<"ERROR: Invalid Choice!"<<endl;
                cout<<"PLAY(S) - DELETE(D) - ADD SONG(A) - REMOVE SONG(R) - NEXT(N) - PREVIOUS(P) - INDEX NUMBER(I) - EXIT(E)"<<endl;
                cin>>choice;
                continue;
            }
        }
    }
    
    
};

void list::exitSongBox(){
	playlist *list = head->next;
	while (head){
		writeToFile(list);
		deletePlaylist(list);
		
		list = list->next;
	}

	for (int i = 0; i < 23; i++){
		delete [] allSongList[i]->name;
		delete [] allSongList[i]->singer;
		delete [] allSongList[i]->style;
	}
	delete [] allSongList;
};
