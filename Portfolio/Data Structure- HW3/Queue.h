/*
* @Gülþen Eryiðit
* Student Name: Melis Gülenay
* Student ID : 150120304
* Date:  25.12.2016
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string.h>
#include <string>
using namespace std;

struct qd {
    string str;
    qd *next;
};

struct Queue {
    void create();
    qd *front = NULL;
    qd *back = NULL;
    string pop();
    void push(string);
    bool empty();
    void close();
};
#endif
