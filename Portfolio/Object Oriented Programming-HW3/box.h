#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

//#include "toy.cpp"
using namespace std;

template <class Toy>

class Box
{
public:
	Box(float,float,float,float);
	void setWeight(float);
	void setLength(float);
	void setWidth(float);
	void setmaximumAllowedWeight(float);
	void setIndex(int);
	void setclassName(string);
	void settotalWeight(float);
	float getWeight();
	float getLength();
	float getWidth();
	float getmaximumAllowedWeight();
	int getIndex();
	string getclassName();
	float gettotalWight();
	Toy* list;
	void add(Toy);
	friend ostream &operator<<(ostream &out, Box<Toy> c);
	//Toy& operator[](int);

private:
	float weight;
	float length;
	float width;
	float maximumAllowedWeight;
	int index;
	string className;
	float totalWeight;
};

//Initializer

template <class Toy> Box<Toy>::Box(float weight_toadd, float length_toadd, float width_toadd,float maxAllowed_toadd)
{
		setWeight(weight_toadd);
		setLength(length_toadd);
		setWidth(width_toadd);
		setmaximumAllowedWeight(maxAllowed_toadd);
		setIndex(0);
		settotalWeight(weight_toadd);
		list = NULL;
}

//Setters

template <class Toy> void Box<Toy>::setWeight(float weight_toadd){
	weight = weight_toadd;
}
template <class Toy> void Box<Toy>::setLength(float length_toadd){
	length = length_toadd;
}
template <class Toy> void Box<Toy>::setWidth(float width_toadd){
	width = width_toadd;
}
template <class Toy> void Box<Toy>::setmaximumAllowedWeight(float maxAllowed_toadd){
	maximumAllowedWeight = maxAllowed_toadd;
}
template <class Toy> void Box<Toy>::setIndex(int newIndex){
	index = newIndex;
}
template <class Toy> void Box<Toy>::setclassName(string className){
	className = "Box<" + className + ">" ;
}
template <class Toy> void Box<Toy>::settotalWeight(float weight_toadd){
	totalWeight = weight_toadd;
}

//Getters

template <class Toy> float Box<Toy>::getWeight(){
	return weight;
}
template <class Toy> float Box<Toy>::getLength(){
	return length;
}
template <class Toy> float Box<Toy>::getWidth(){
	return width;
}
template <class Toy> float Box<Toy>::getmaximumAllowedWeight(){
	return maximumAllowedWeight;
}
template <class Toy> int Box<Toy>::getIndex(){
	return index;
}
template <class Toy> string Box<Toy>::getclassName(){
	return className;
}
template <class Toy> float Box<Toy>::gettotalWight(){
	return totalWeight;
}

//Add func.

template <class Toy> void Box<Toy>::add(Toy tobeadded){
	if(tobeadded.getLength() > getLength() || tobeadded.getLength() > getWidth() || tobeadded.getWidth() > getWidth() || tobeadded.getLength() > getLength())
	{
		throw "The dimensions of the contained object should be equal or smaller than those of the box!";
	}

	if(tobeadded.getWeight() + gettotalWight() > getmaximumAllowedWeight())
	{
		throw "The total weight of the contained objects including the box may not exceed the maximum allowed weight for the box!";
	}
	else{
		Toy* list_new;
		setIndex(getIndex()+1);
		list_new = new Toy[getIndex()];

		for (int i=0; i <getIndex()-2; i++){
			list_new[i] = list[i];
		}

		list_new[getIndex()-1] = tobeadded;
		list = list_new;

		settotalWeight(gettotalWight()+tobeadded.getWeight());
	}
}

template <class Toy> ostream &operator<<(ostream &out, Box<Toy> c){
	out<<"**** "<< c.getclassName()<<" ****"<<endl;
	out<<"Box item count:"<<c.getIndex()<<endl;
	out<<"Size: "<<c.getLength()<<"x"<<c.getWidth()<<"Weight:"<<c.getWeigth()<<" Total/Maximum Allowed Weight:"<<c.gettotalWeight()<<"/"<<c.getmaximumAllowedWeight()<<endl;
	out<<"Items:"<<endl;
	for( int i= 0;i< c.getIndex();i++){
		out<<c.list[i]<<endl;
	}
	out<<"********************";
	return out;
}

//template <class Toy> Toy &operator[](int i){
//		return list[i];
//};