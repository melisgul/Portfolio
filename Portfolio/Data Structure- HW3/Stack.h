/*
* @Gülþen Eryiðit
* Student Name: Melis Gülenay
* Student ID : 150120304
* Date:  25.12.2016
*/

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

struct sd {
    std::string str;
    sd *next;
};

struct Stack {
    void create();
    sd *head;
    std::string pop();
    void push(std::string);
    bool empty();
    void close();
};
#endif
