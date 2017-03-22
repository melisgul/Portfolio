/*
* @Gülþen Eryiðit
* Student Name: Melis Gülenay
* Student ID : 150120304
* Date:  25.12.2016
*/


#include "Queue.h"

using namespace std;

string Queue::pop(){
        qd *temp;
        string popped;
        temp = front;
        front = front->next;
        popped = temp->str;
        delete temp;
        
        return popped;
};
void Queue::push(string add){
    qd *temp = new qd;
    temp->next = NULL;
    
    temp->str = add;
    
    if (front == NULL) {
        front = temp;
        back = temp;
    }
    
    else {
        back->next = temp;
        back = temp;
    }
};
bool Queue::empty(){
    return (front == NULL);
};
void Queue::close(){
    qd *temp;
    while (front) {
        temp = front;
        front = front->next;
        delete temp;
    }
};
