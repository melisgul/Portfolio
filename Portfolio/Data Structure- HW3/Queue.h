/*
* @G�l�en Eryi�it
* Student Name: Melis G�lenay
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
