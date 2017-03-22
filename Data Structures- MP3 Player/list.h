/* @Author
* Student Name: Melis Gülenay
* Student ID : 150120304
* Date: 23.11.2016 */


#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <fstream>
#include "song.h"


struct list {
    std::ifstream input;
    std::ofstream output;
	int playlist_count;
	playlist* head;
    int songcounter;
    song** allSongList;
    int allSongNumber=0;
    playlist *chronological;
    playlist *sorted;
    playlist *random;
	
	FILE *songbook;
	char *filename;
    
    void readFromFile();//++
    void writeToFile(playlist* );
	
    void createDefaultLists();//++
	void splitLinesToWords(std::string &line, char** words);
	void createChrono(playlist *, song*);//++
	void createSorted(playlist *, song*);//++
    void createRandom();//++
    void addToAllSongList(char*[4]);//++
    
    
    void deletePlaylist(playlist* );//++
    void writePlayListNames();//
    
    song_node* createSongNode(song *songPtr);//++
    void printPlaylist(playlist *ptr2);//++
    song* createNewSong(song newsong);//++
    
    
    void createListWithStyleOrSinger(char* newCondition, int type);//+
    
	void exitSongBox();
    void addToConcatenateList(playlist* newList, int number);//++
    void addToCombinationList(playlist* newPlaylist, int number);//++
    void addingSongToUserLists(int choice1, int choice2);//++
    
    playlist* createPlaylist(char* name);//++
    void startPlayFromBeginList(int number);//++
    void startPlayFromSpecificSong(int number);//++
    void playing(song_node *songTraverse);//++
    void playJustOneSong(int choiceP);//++
    
    void removeSong(int index);//++
    void writeAllPlaylistToTheFile();//
    
    void printAllList();//
    
    
    char* toUpperString(char* str);//++
	

};


#endif
