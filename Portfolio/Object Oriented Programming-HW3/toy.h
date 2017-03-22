#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

class Toy
{
public:
	Toy(string,double,double,double,bool);
	Toy();
	void setLabel(string);
	void setWeight(double);
	void setLength(double);
	void setWidth(double);
	void setContainsBattery(bool);
	void setclassName(string);
	string getLabel();
	double getWeight();
	double getLength();
	double getWidth();
	bool getBattery();
	string getclassName();
	friend ostream &operator<<(ostream &out, Toy c);
	
private:
	string label;
	string className;
	double weight;
	double length;
	double width;
	bool containsBattery;
};
