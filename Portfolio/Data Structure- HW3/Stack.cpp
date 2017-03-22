/*
* @Gülþen Eryiðit
* Student Name: Melis Gülenay
* Student ID : 150120304
* Date:  25.12.2016
*/
#include <iostream>
#include <string.h>
#include <string>
#include "Stack.h"

using namespace std;

string Stack::pop(){
    string gonder;
    gonder = head->str;
    if (head->next == NULL) {
        delete head;
        head = NULL;
        return gonder;
    }
    sd *temp;
    temp = head;
    head = head->next;
    delete temp;
    return gonder;
};
void Stack::push(string add){
    sd *temp = new sd;
    temp->next = NULL;
    
    temp->str = add;
    
    if (head == NULL) {
        head = temp;
    }
    
    else {
        temp->next = head;
        head = temp;
    }
};
bool Stack::empty(){
    return (head == NULL);
};
void Stack::close(){
    sd *temp;
    while (head) {
        temp = head;
        head = head->next;
        delete temp;
    }
};
