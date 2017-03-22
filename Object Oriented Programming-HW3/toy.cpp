#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "toy.h"
using namespace std;

Toy::Toy(string label_tobeadd, double weight_toadd, double length_toadd, double width_toadd,bool battery_toadd)
{
	setLabel(label_tobeadd);
	setWeight(weight_toadd);
	setLength(length_toadd);
	setWidth(width_toadd);
	setContainsBattery(battery_toadd);
	setclassName("Toy");
}

Toy::Toy(){
	setLabel("NULL");
	setWeight(0);
	setLength(0);
	setWidth(0);
	setContainsBattery(0);
	setclassName("Toy");
}

void Toy::setLabel(string label_toadd){
	label = label_toadd;
}

void Toy::setWeight(double weight_toadd){
	weight = weight_toadd;
}

void Toy::setLength(double length_toadd){
	length = length_toadd;
}

void Toy::setWidth(double width_toadd){
	width = width_toadd;
}

void Toy::setContainsBattery(bool battery_toadd){
	containsBattery = battery_toadd;
}

void Toy::setclassName(string class_toadd){
	className = class_toadd;
}

string Toy::getLabel(){
	return label;
}

double Toy::getWeight(){
	return weight;
}

double Toy::getLength(){
	return length;
}

double Toy::getWidth(){
	return width;
}

bool Toy::getBattery(){
	return containsBattery;
}

string Toy::getclassName(){
	return className;
}

ostream &operator<<(ostream &out, Toy c){
	out<<"Toy Label: "<<c.getLabel()<<" # "<<c.getLength()<<"x"<<c.getWidth()<<" "<<c.getWeight()<<" kg";
	if(c.getBattery() == false){
		out<<"No Battery"<<endl;
	}
	else{
		out<<"Contains Battery"<<endl;
	}
	return out;
}